// kayit.h
// Bu dosya sadece BILDIRIM (declaration) icin var.
// Ne yapildigini tarif eder, nasil yapildigini gizler.
// Gercek is kayit.cpp'de.

#pragma once
// #pragma once: bu header birden fazla .cpp tarafindan include edilse bile
// derleyici onu sadece BIR KEZ okur. Eski yontem #ifndef guard'dir,
// #pragma once daha kisa ve modern derleyicilerin hepsi destekler.

#include <vector>
#include <string>
// fstream burada gerekmiyor; dosya acma/kapama isleri .cpp'de yapilacak.
// Header'a sadece fonksiyon imzalarinin ihtiyac duydugu tipleri ekle.

class kayit {
// Bu siniftan hic nesne olusturulmayacak.
// Tum metodlar 'static' oldugu icin kayit::gunluk_Kaydet(...) seklinde
// dogrudan cagrilir; kayit k; k.gunluk_Kaydet(...) yazmana gerek yok.
// Dusun: C'deki utility fonksiyon kutuphanesi gibi, sadece C++ sinifinaya sarmalanmis hali.

public:
    // --- KAYDETME ---

    // Gununun tum kayitlarini dosyaya yazar.
    // Her cagrildiginda dosyayi BASTAN yazar (truncate), eklemez.
    // Yani ayni gunun kayitlarini ikinci kez kaydedersen eski silinir, yenisi yazilir.
    static void gunluk_Kaydet(int id, const std::string& isim,
                              const std::vector<float>& gnkKayit);

    // Haftanin kayitlarini dosyaya EKLER (append).
    // Onceki haftalarin uzerine yazmaz, alta ekler.
    // Boylece haftalik dosya tum gecmisi biriktirir.
    static void haftalik_Kaydet(int id, const std::string& isim,
                                const std::vector<float>& hftKayit);

    // --- YUKLEME ---

    // Daha once kaydedilmis gunluk veriyi diskten okuyup vektore atar.
    // Referans (&) ile aldigi icin vektoru dogrudan degistirir, kopya cikmaz.
    // Dosya bulunduysa true, yoksa false doner → cagiran kod buna gore davranir.
    static bool gunluk_Yukle(int id, std::vector<float>& gnkKayit);

    // Ayni mantik, haftalik dosya icin.
    static bool haftalik_Yukle(int id, std::vector<float>& hftKayit);

    // --- SIFIRLAMA ---

    // Gunluk dosyanin icini bosaltir; haftalik dosyaya dokunmaz.
    // Sadece gunluk dosyayi etkiler.
    static void gunluk_Sifirla(int id);

    // --- KONTROL ---

    // Verilen id'ye ait kayit dosyasi var mi diye bakar.
    // Varsa dosyanin icinden kullanici ismini okur ve isimOut'a yazar.
    // Bu sayede program acilisinda "bu id daha once kaydedilmis mi?" sorusunun cevabini verir.
    // isimOut: C'deki "cikis parametresi" mantigi; fonksiyon hem bool doner hem de ismi disari verir.
    static bool kullanici_VarMi(int id, std::string& isimOut);

private:
    // Bu iki yardimci fonksiyon disaridan cagrilmasin diye private'ta.
    // Sadece bu sinifin kendi metodlari kullanir.

    // id'den dosya yolunu uretir: "kayitlar/kullanici_3_gunluk.txt" gibi.
    static std::string gunluk_Yol(int id);
    static std::string haftalik_Yol(int id);

    // "kayitlar/" klasoru yoksa olusturur.
    // Her kaydetme oncesi cagrılır; klasor zaten varsa sessizce geri doner.
    static void klasor_Olustur();
};

// butce.h
// butce sinifinin bildirimi (declaration).
// Kullanicinin butce verilerini tutan ve isleyen sinif.
// Dosya okuma/yazma islerini dogrudan yapmaz; kayit sinifina devreder.

#pragma once
#include <vector>
#include <string>
// kayit.h burada include edilmiyor.
// Neden? Header'lar birbirini include ederse "include zincirleri" siser.
// butce.cpp zaten kayit.h'i include edecek; implementasyon orada oldugu icin yeterli.
// Header'da sadece fonksiyon imzalari var, gercek cagrı .cpp'de.

class butce {
private:
    // private: bu alana sadece sinifin kendi metodlari erisebilir.
    // main.cpp'den dogrudan gnkKayit.push_back(...) yapilamaz; getiri() uzerinden gecmek zorunlu.
    // Bu OOP'nin "encapsulation" prensibi: veriyi sakla, kontrollu erisim sagla.

    std::vector<float> gnkKayit;     // gunun gelir/gider kayitlari; + gelir, - gider
    std::vector<float> haftalik_Kyt; // haftanin birikimi; gunluk aktarim buraya eklenir
    std::string kullanici;           // kullanicinin adi
    int id;                          // benzersiz tanimlayici; dosya adinda kullanilir

public:
    // public: disaridan erisilebilir. main.cpp bu alani kullanir.

    // ── Constructor ──────────────────────────────────────────────────────────
    // C'de init_butce(&nesne, isim, id) seklinde ayri bir fonksiyon yazardik.
    // C++'da constructor otomatik cagirilir; nesne olusturulur olusturulmaz calısır.
    // Iceride dosya_Yukle() cagirarak diske kayitli veriyi otomatik yukler.
    butce(std::string isim, int id);

    // ── Gelir / Gider ────────────────────────────────────────────────────────

    // Pozitif deger alir, gnkKayit'e dogrudan ekler.
    // const float: fonksiyon icinde kar'i degistirmeyecegimizi garanti eder.
    float getiri(const float kar);

    // Pozitif deger alir, eksi yapar ve gnkKayit'e ekler.
    // Kullanici "2000" yazsa bile -2000 olarak saklanir; gider her zaman negatif.
    float goturu(float zarar);

    // ── Goruntulem ───────────────────────────────────────────────────────────

    // Tum kayitlari yazdirir ve net durumu hesaplayip ekrana basar.
    // Donus degeri toplam; ilerleyen gelistirmelerde kullanilabilir.
    float gunluk();

    // Kayitlari tablo seklinde sirali numaralarla gosterir.
    // sil() oncesi hangi siradaki kaydin silineceğini gormek icin kullanilir.
    void yazdir();

    // ── Silme ────────────────────────────────────────────────────────────────

    // silinicek: 1'den baslayan siranin numarasi (kullanicinin gördugu numara).
    // Iceride vektör indeksine (0 bazli) cevirilerek erase() yapilir.
    void sil(int silinicek);

    // ── Dosya Islemleri ──────────────────────────────────────────────────────

    // Suanki gnkKayit vektorunu diske yazar.
    // Menu'den "Verileri Kaydet" secilince cagrilir.
    // Kayit sinifina id, isim ve vektoru iletir; o gerisini halleder.
    void dosya_Kayit();

    // Constructor tarafindan otomatik cagrilir; disaridan da cagrilabilir.
    // id'ye ait gunluk dosya varsa gnkKayit vektorunu diskten doldurur.
    // Dosya yoksa sessizce geri doner; hata vermez.
    void dosya_Yukle();

    // Gunluk kayitlari haftalik dosyaya (append) aktarir.
    // Sonra gnkKayit'i ve gunluk dosyayi sifirlar.
    // Haftalik dosya silinmez, sadece gunluk temizlenir.
    void gunluk_HaftaligaAktar();

    // Haftaliga aktarmadan sadece gunlugu sifirlar.
    // Hem ram'daki vektoru (gnkKayit.clear) hem disk dosyasini sifirlar.
    void gunluk_Sifirla();

    // ── Getter'lar ───────────────────────────────────────────────────────────
    // private alanlar disaridan okunamaz ama bazen okumak gerekir.
    // Getter: sadece okuma saglar, degistirme saglamaz.
    // const: bu fonksiyon sinifin hicbir uye degiskenini degistirmez, sozlesme verir.
    int         getId()   const { return id; }
    std::string getIsim() const { return kullanici; }
    // Header'da { } ile yazilan kisa metodlar "inline" olur; derleyici cagri yapmak yerine
    // kodu dogrudan yerlestirebilir. Cok kisa fonksiyonlar icin tercih edilir.
};

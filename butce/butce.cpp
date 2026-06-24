// butce.cpp
// butce sinifinin implementasyonu.
// Bildirimler (ne yapilir) → butce.h
// Tanimlar   (nasil yapilir) → bu dosya

#include "butce.h"
#include "../kayit/kayit.h" // kayit sinifi burada lazim; .h'da degil .cpp'de include ediyoruz
                             // "../kayit/" : butce/ klasöründen bir üste çıkıp kayit/ klasörüne gir
#include <iostream>
#include <sstream>  // yazdir() icinde float→string donusumu icin stringstream kullanilıyor
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────────────────────────────────────────
butce::butce(string isim, int id) {
    // Kapsam cozumu operatoru (::): "bu fonksiyon butce sinifina ait" demek.
    // C'de struct + ayri fonksiyonlarla yapardik; burada sinifa bagliyoruz.

    kullanici = isim;

    // 'id' hem parametre adi hem de uye degisken adi; ikisi cakisiyor.
    // this->id = sinifin id'si; sag taraftaki id = parametredeki id.
    // this: suanki nesnenin adresini tutan pointer; C'deki struct pointer'i gibi dusun.
    this->id = id;

    dosya_Yukle(); // nesne hazir hale gelir gelmez diskteki veriyi ram'a yukle
}

// ─────────────────────────────────────────────────────────────────────────────
// getiri()
// ─────────────────────────────────────────────────────────────────────────────
float butce::getiri(const float kar) {
    // push_back: vektorun sonuna eleman ekler; dinamik dizi buyur.
    // C'de realloc + elle index takibi yapardik; vector bunu otomasyon ediyor.
    gnkKayit.push_back(kar); // gelir pozitif saklanir
    return kar;              // cagiran kod isterse donusu kullanabilir
}

// ─────────────────────────────────────────────────────────────────────────────
// goturu()
// ─────────────────────────────────────────────────────────────────────────────
float butce::goturu(float zarar) {
    // Kullanicidan pozitif deger bekliyoruz (insan "5000 harcadim" der, "-5000" demez).
    // Ama negatif girilirse tekrar negatif yapmasin diye kontrol ediyoruz.
    if (zarar > 0) {
        zarar = -1 * zarar; // gideri negatif olarak sakla; gidirler hep ekside kalsin
    }
    gnkKayit.push_back(zarar);
    return 0; // hata kodu gibi dusunebilirsin; simdillik kullanilmiyor
}

// ─────────────────────────────────────────────────────────────────────────────
// gunluk()
// ─────────────────────────────────────────────────────────────────────────────
float butce::gunluk() {
    float toplam = 0;
    int boyut = gnkKayit.size(); // size() unsigned dondurur; int'e atiyoruz cunku asagida karsilastirma yapacagiz

    if (boyut == 0) {
        cout << kullanici << " icin henuz kayit girilmemis." << endl;
        return 0;
    }

    cout << kullanici << " gunluk kayitlar: ";

    for (int i = 0; i < boyut; i++) {
        toplam += gnkKayit[i]; // suanki kaydi toplama ekle

        if (i == boyut - 1) {
            // Son eleman: arkasina "||" yok, satir sonu var
            cout << gnkKayit[i] << endl;

            // Net durumu rapor et
            if (toplam > 0) {
                cout << "Tebrikler, bugun kasana: " << toplam << " kadar bakiye girdi" << endl;
            } else if (toplam < 0) {
                cout << "Bugun kasadan: " << -toplam << " kadar zarardasin" << endl;
                // -toplam: toplam negatif oldugu icin eksi ile carparak pozitif gosteriyoruz
            } else {
                cout << "Mukemmel bir denge saglanmis, gelir ve gider esit" << endl;
            }
        } else {
            cout << gnkKayit[i] << " || "; // aradaki elemanlari ayirici ile yaz
        }
    }

    return toplam; // net bakiyeyi dondur; cagiran kod kullanmak isterse var
}

// ─────────────────────────────────────────────────────────────────────────────
// sil()
// ─────────────────────────────────────────────────────────────────────────────
void butce::sil(int secimInt) {
    // Kullanici 1'den baslayan numara girer ama vektör 0'dan baslar.
    // Giren 1 → indeks 0, giren 2 → indeks 1, vs.

    // (int) cast: size() unsigned (size_t) dondurur; signed/unsigned karsilastirma uyarisi onlemek icin cast
    if (secimInt >= 1 && secimInt <= (int)gnkKayit.size()) {
        // erase(iterator): vector'den eleman siler; sonrasini kaydirır.
        // begin() ilk elemanin iterator'i; + (secimInt-1) ile istedigimiz pozisyona gidiyoruz.
        // C'de memmove ile elle kaydirisrdik; vector bunu otomatik yapar.
        gnkKayit.erase(gnkKayit.begin() + (secimInt - 1));
        cout << secimInt << " numarali kayit basariyla silindi." << endl;
    } else {
        cout << "Gecersiz bir sira numarasi girdiniz!" << endl;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// yazdir()
// ─────────────────────────────────────────────────────────────────────────────
void butce::yazdir() {
    if (gnkKayit.empty()) {
        // empty(): size() == 0 ile ayni anlam ama niyeti daha net ifade eder
        cout << kullanici << " icin gosterilecek herhangi bir kayit bulunmamaktadir." << endl;
        return;
    }

    // --- 1. Gecis: Sira numaralari satirini yaz ---
    // Amac: her sira numarasini altindaki degerle hizali gostermek.
    // Orneg: deger "10000", numara "1" → "1" 4 bosluk icinde ortalanir.
    for (int i = 0; i < (int)gnkKayit.size(); i++) {

        stringstream ss;
        ss << gnkKayit[i]; // float'i stringe cevir; to_string yerine stringstream kullandik
        string yazi       = ss.str();           // degerın yazi karsiligi, ornek: "-2000"
        string indeksYazi = to_string(i + 1);   // sira numarasi, ornek: "1"

        // Deger kac karakter uzunsa, numara o kadar boslukla ortalanacak
        int toplamBosluk = (int)yazi.length() - (int)indeksYazi.length();
        if (toplamBosluk < 0) toplamBosluk = 0; // numara degerden uzunsa bosluk gerekmez

        int solBosluk = toplamBosluk / 2;
        int sagBosluk = toplamBosluk - solBosluk; // tam bolunmeyince kalan sag tarafa gider

        cout << " || ";
        for (int j = 0; j < solBosluk; j++) cout << " ";
        cout << (i + 1);
        for (int j = 0; j < sagBosluk; j++) cout << " ";

        if (i == (int)gnkKayit.size() - 1) cout << " ||" << endl; // son sutundan sonra satir bitir
    }

    // --- 2. Gecis: Degerleri yaz ---
    // Numaralar hizali, degerlerin altinda sirayla yazilir.
    for (int i = 0; i < (int)gnkKayit.size(); i++) {
        cout << " || " << gnkKayit[i];
        if (i == (int)gnkKayit.size() - 1) cout << " ||" << endl;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// dosya_Kayit()
// ─────────────────────────────────────────────────────────────────────────────
void butce::dosya_Kayit() {
    // butce sinifi dosya formatini bilmek zorunda degil; sadece "kaydet" der.
    // Gercek yazma islemi kayit sinifindadir. Bu "sorumluluk ayirma" prensibi.
    // Ileride dosya formati degisse (JSON, binary vs.) sadece kayit.cpp degisir,
    // buraya dokunulmaz.
    kayit::gunluk_Kaydet(id, kullanici, gnkKayit);
}

// ─────────────────────────────────────────────────────────────────────────────
// dosya_Yukle()
// ─────────────────────────────────────────────────────────────────────────────
void butce::dosya_Yukle() {
    // Referans ile gonderdigimiz gnkKayit, kayit::gunluk_Yukle icerisinde doldurulur.
    // Fonksiyon true donerse dosya bulundu ve okundu demek; false ise dosya hic yok demek.
    bool bulundu = kayit::gunluk_Yukle(id, gnkKayit);

    if (bulundu && !gnkKayit.empty()) {
        // Kullaniciya kac kayit yuklendigi haber verilir; sessizce doldurmak yerine bunu yapiyoruz.
        cout << "[YUKLE] " << kullanici << " (ID:" << id
             << ") icin " << gnkKayit.size()
             << " gunluk kayit yuklendi." << endl;
    }
    // Dosya yoksa veya dosya bos ise hic ses cikmaz; ilk acilista gereksiz mesaj olmasi istemiyoruz.
}

// ─────────────────────────────────────────────────────────────────────────────
// gunluk_HaftaligaAktar()
// ─────────────────────────────────────────────────────────────────────────────
void butce::gunluk_HaftaligaAktar() {
    if (gnkKayit.empty()) {
        cout << "[BILGI] Aktarilacak gunluk kayit yok." << endl;
        return;
    }

    // Adim 1: gunluk vektoru haftalik dosyaya (append ile) yaz
    kayit::haftalik_Kaydet(id, kullanici, gnkKayit);

    // Adim 2: ram'daki haftalik vektore de ekle
    // (ileride haftalik rapor gosterilmek istenirse bellekte hazir olsun)
    for (float f : gnkKayit) {
        haftalik_Kyt.push_back(f);
    }

    // Adim 3: gunluk vektoru ram'dan temizle
    gnkKayit.clear(); // C'deki memset yerine; vector'un boyutunu sifirlar

    // Adim 4: disk uzerindeki gunluk dosyayi da sifirla
    kayit::gunluk_Sifirla(id);

    cout << "[OK] Gunluk kayitlar haftaliga aktarildi ve gunluk sifirlandi." << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// gunluk_Sifirla()
// ─────────────────────────────────────────────────────────────────────────────
void butce::gunluk_Sifirla() {
    // gunluk_HaftaligaAktar'dan farki: haftalik dosyaya YAZMAZ, sadece gunlugu siler.
    // Kullanici verileri kaybetmeyi kabul etmis demek; direk sifirla.

    gnkKayit.clear();       // ram'daki listeyi bosalt
    kayit::gunluk_Sifirla(id); // diskteki dosyayi bosalt

    cout << "[OK] Gunluk kayitlar sifirlandi (haftaliga aktarilmadi)." << endl;
}

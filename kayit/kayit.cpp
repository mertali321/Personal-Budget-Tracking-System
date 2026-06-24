// kayit.cpp
// kayit.h'da bildirilen fonksiyonlarin gercek implementasyonu burada.
// Bu dosya disari kapatilmis; baska .cpp'ler sadece kayit.h'i include eder,
// bu dosyayi dogrudan gormez. Derleyici hepsini linkleyince birlestir.

#include "kayit.h"
#include <fstream>    // ifstream (okuma), ofstream (yazma)
#include <iostream>   // cerr ile hata mesaji basmak icin
#include <sstream>    // bu dosyada kullanilmiyor ama ileride gerekebilir
#ifdef _WIN32
    #include <direct.h>   // Windows/MinGW: _mkdir() burada
#else
    #include <sys/stat.h> // Linux/macOS: mkdir() burada
#endif

using namespace std;

void kayit::klasor_Olustur() {
    
    #ifdef _WIN32
        _mkdir("kayitlar");       // Windows (MinGW ve MSVC her ikisinde de calisir)
    #else
        mkdir("kayitlar", 0755); 
    #endif
   
}

// ─────────────────────────────────────────────────────────────────────────────
// Yardimci: dosya yolu uret
// ─────────────────────────────────────────────────────────────────────────────
string kayit::gunluk_Yol(int id) {
    // to_string(id) int'i stringe cevirir; C'deki sprintf(buf, "%d", id) karsiligi.
    // String birlestirme '+' operatoru C++'a ozgu, C'de yoktu.
    return "kayitlar/kullanici_" + to_string(id) + "_gunluk.txt";
    // Ornek: id=2 → "kayitlar/kullanici_2_gunluk.txt"
}

string kayit::haftalik_Yol(int id) {
    return "kayitlar/kullanici_" + to_string(id) + "_haftalik.txt";
}


void kayit::gunluk_Kaydet(int id, const string& isim,
                           const vector<float>& gnkKayit) {
    klasor_Olustur(); // yazmayi denemeden once klasorun var oldugunu garantile

    // ofstream: C'deki fopen(yol, "w") karsiligi. Varsayilan mod: basta yazar (truncate).
    // Yani dosya zaten varsa icini siler, yeniden yazar. Gunluk icin bu istedigimiz davranis:
    // ayni gunu iki kez kaydedersen eski veri kaybolmaz, sadece guncellenir.
    ofstream dosya(gunluk_Yol(id));

    if (!dosya.is_open()) {
        // Dosya acilamazsa (izin sorunu, disk dolu vs.) programi cokertmek yerine
        // hata mesaji yazip geri donuyoruz. cerr: hata ciktisi, cout'tan ayri akis.
        cerr << "[HATA] Gunluk dosyasi acilamiyor: " << gunluk_Yol(id) << endl;
        return;
    }

    // << operatoru ile dosyaya yaziyoruz; cout'a yazmaktan farki yok, sadece hedef farklı.
    dosya << "ISIM:" << isim << "\n";
    dosya << "ID:"   << id   << "\n";

    // Range-based for: C++11 ile geldi. C'deki for(i=0; i<n; i++) yerine daha temiz.
    // gnkKayit icindeki her float'i sirayla 'deger' degiskenine atar.
    for (float deger : gnkKayit) {
        dosya << "KAYIT:" << deger << "\n";
    }

    dosya.close(); // C'deki fclose() karsiligi. Destructor da kapatir ama acik birakmak kotu aliskanlik.
    cout << "[OK] Gunluk kayitlar '" << gunluk_Yol(id) << "' dosyasina yazildi." << endl;
}

void kayit::haftalik_Kaydet(int id, const string& isim,
                             const vector<float>& hftKayit) {
    klasor_Olustur();

    // ios::app = append modu. C'deki fopen(yol, "a") karsiligi.
    // Dosyanin sonuna ekler, varolan veriyi silmez.
    // Gunluk farkli: her seferinde ustune yazar.
    // Haftalik farkli: gecmis biriktirilir, silinmez.
    ofstream dosya(haftalik_Yol(id), ios::app);

    if (!dosya.is_open()) {
        cerr << "[HATA] Haftalik dosyasi acilamiyor: " << haftalik_Yol(id) << endl;
        return;
    }

    // Ayni format: her hafta aktariminda ISIM ve ID satirlari tekrar yazilir.
    // Bu sayede dosyada hangi blogun kime ait oldugu her zaman okunabilir.
    dosya << "ISIM:" << isim << "\n";
    dosya << "ID:"   << id   << "\n";
    for (float deger : hftKayit) {
        dosya << "KAYIT:" << deger << "\n";
    }

    dosya.close();
    cout << "[OK] Haftalik kayitlar '" << haftalik_Yol(id) << "' dosyasina eklendi." << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// gunluk_Yukle()
// ─────────────────────────────────────────────────────────────────────────────
bool kayit::gunluk_Yukle(int id, vector<float>& gnkKayit) {
    // ifstream: C'deki fopen(yol, "r") karsiligi, okuma icin acar.
    ifstream dosya(gunluk_Yol(id));

    if (!dosya.is_open()) {
        // Dosya yok demek = kullanici hic kaydetmemis veya ilk calisma.
        // Hata degil; false donuyoruz, cagiran kod buna gore karar verir.
        return false;
    }

    // Yukleme oncesi vektoru temizle.
    // Yoksa eski verinin uzerine yeni veri birikirdi; her yuklemede tekrar okumak istiyoruz.
    gnkKayit.clear();

    string satir;
    // getline: dosyadan satir satir okur. Dosya bittikten sonra false doner, dongu biter.
    // C'deki fgets() karsiligi ama string ile daha rahat.
    while (getline(dosya, satir)) {

        // substr(0, 6): satirin ilk 6 karakterini al ve "KAYIT:" ile karsilastir.
        // "ISIM:" ve "ID:" satirlarini atlamak icin; sadece sayisal degerleri istiyoruz.
        if (satir.substr(0, 6) == "KAYIT:") {

            // substr(6): 6. karakterden sonrasini al, yani sayi kismini.
            // stof: string'i float'a cevirir. C'deki atof() veya sscanf(buf, "%f", &f) karsiligi.
            float deger = stof(satir.substr(6));
            gnkKayit.push_back(deger); // vektorun sonuna ekle
        }
        // "ISIM:" veya "ID:" ile baslayan satirlar atlanir; bize sadece sayilar lazim.
    }

    dosya.close();
    return true; // dosya vardi ve okuduk
}

// ─────────────────────────────────────────────────────────────────────────────
// haftalik_Yukle()
// ─────────────────────────────────────────────────────────────────────────────
bool kayit::haftalik_Yukle(int id, vector<float>& hftKayit) {
    // gunluk_Yukle ile ayni mantik, sadece farkli dosyayi aciyor.
    // Haftalik dosyada birden fazla haftanin blogu olabilir ama hepsi "KAYIT:" ile baslayan satir;
    // hepsini sirayla okuyup vektore atiyoruz.
    ifstream dosya(haftalik_Yol(id));
    if (!dosya.is_open()) {
        return false;
    }

    hftKayit.clear();
    string satir;
    while (getline(dosya, satir)) {
        if (satir.substr(0, 6) == "KAYIT:") {
            float deger = stof(satir.substr(6));
            hftKayit.push_back(deger);
        }
    }

    dosya.close();
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// gunluk_Sifirla()
// ─────────────────────────────────────────────────────────────────────────────
void kayit::gunluk_Sifirla(int id) {
    // ios::trunc: dosyayi acarken icini sifirla (truncate).
    // Dosya zaten ofstream'in varsayilan davranisi truncate'tir ama
    // burada niyetimizi acikca belirtmek icin yaziyoruz.
    // Bos bir ofstream acip hemen kapatmak = dosyayi sifirlamak.
    // Haftalik dosyaya hic dokunmuyoruz; o birikmeye devam eder.
    ofstream dosya(gunluk_Yol(id), ios::trunc);

    if (!dosya.is_open()) {
        cerr << "[HATA] Gunluk dosyasi sifirlanamadi: " << gunluk_Yol(id) << endl;
        return;
    }

    dosya.close(); // icine hicbir sey yazmadan kapatinca dosya bos kalir
    cout << "[OK] Gunluk dosya sifirlandi: " << gunluk_Yol(id) << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// kullanici_VarMi()
// ─────────────────────────────────────────────────────────────────────────────
bool kayit::kullanici_VarMi(int id, string& isimOut) {
    // Gunluk dosyayi okuma modunda acmaya calis.
    // Acilirsa → dosya var → kullanici daha once kaydedilmis.
    // Acilmazsa → dosya yok → kullanici yeni.
    ifstream dosya(gunluk_Yol(id));

    if (!dosya.is_open()) {
        return false; // bu id'ye ait kayit yok
    }

    string satir;
    while (getline(dosya, satir)) {
        if (satir.substr(0, 5) == "ISIM:") {
            // "ISIM:Ahmet" satirindan "Ahmet" kismini kesip cikis parametresine yaz.
            // isimOut referans oldugu icin burada yapilan atama cagiran fonksiyona yansir.
            // C'de bunu pointer ile yapardik: char* isimOut → strcpy(isimOut, ...)
            isimOut = satir.substr(5);
            dosya.close();
            return true; // ismi bulduk, daha fazla okumaya gerek yok
        }
    }

    // Dosya vardi ama ISIM satiri yoktu (bos ya da bozuk dosya).
    // Yine de false donmek daha guvenli.
    dosya.close();
    return false;
}

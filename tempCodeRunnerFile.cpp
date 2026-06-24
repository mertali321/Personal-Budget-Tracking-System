// main.cpp
// Programin giris noktasi ve kullanici arayuzu.
// "Is mantigi" burada yok; butce ve kayit siniflari onu halleder.
// Bu dosya sadece kullanicidan girdi alir, dogru metodlari cagirır.

#include "butce/butce.h"   // butce sinifi
#include "kayit/kayit.h"  // kullanici_VarMi() main'de dogrudan kullanilacak
#include <iostream>
#include <vector>
using namespace std;

// Fonksiyon prototipleri: C'de de ayni sey. Fonksiyon asagida tanimlanacak ama
// birbirini cagirabilmeleri icin derleyiciye onceden bildirilmesi gerekiyor.
void olusturma(string name, vector<butce>& kayitgirdi);
void menuYazdir();
void secimYap(vector<butce>& kullaniciler);

// ─────────────────────────────────────────────────────────────────────────────
// gunlukSifirla()
// Menuden secilince cagrilir. Kullaniciya iki yol sunar:
//   1 → Gunluk veriyi haftaliga tasi, sonra gunlugu temizle
//   2 → Haftaliga tasimadan sadece gunlugu temizle
// ─────────────────────────────────────────────────────────────────────────────
void gunlukSifirla(vector<butce>& kullaniciler) {
    // vector referansi (&): kopya olusturmadan buyuk listeyi fonksiyona verir.
    // C'de dizi pointer'i gecerdik: void gunlukSifirla(butce* arr, int n)
    // C++'da vector& daha guvenli; boyutu ayri tasimak gerekmez.

    if (kullaniciler.empty()) {
        cout << "[BILGI] Hic kullanici yok." << endl;
        return;
    }

    int secim = 0; // hangi kullanicinin gunlugu sifirlanacak

    if (kullaniciler.size() > 1) {
        // Birden fazla kullanici varsa listele ve hangisi icin yapilacagini sor
        cout << "Hangi kullanici icin gunluk sifirlansin?" << endl;
        for (int i = 0; i < (int)kullaniciler.size(); i++) {
            // getIsim() ve getId(): private alanlara getter uzerinden erisim
            cout << "  " << (i + 1) << " - " << kullaniciler[i].getIsim()
                 << " (ID:" << kullaniciler[i].getId() << ")" << endl;
        }
        cout << "Secim: ";
        cin >> secim;

        if (secim < 1 || secim > (int)kullaniciler.size()) {
            cout << "[HATA] Gecersiz secim." << endl;
            return;
        }
        secim -= 1; // kullanici 1-bazli saydi; vector 0-bazli; 1 cikar
    }
    // Tek kullanici varsa secim zaten 0; if bloguna girmeye gerek yok.

    cout << endl;
    cout << "Gunluk sifirlama secenekleri:" << endl;
    cout << "  1 - Gunlugu haftaliga aktar ve sifirla" << endl;
    cout << "  2 - Sadece gunlugu sifirla (haftaliga aktarma)" << endl;
    cout << "Secim: ";
    int islem;
    cin >> islem;

    if (islem == 1) {
        kullaniciler[secim].gunluk_HaftaligaAktar(); // aktar + sifirla
    } else if (islem == 2) {
        kullaniciler[secim].gunluk_Sifirla();        // sadece sifirla
    } else {
        cout << "[HATA] Gecersiz secim, islem iptal edildi." << endl;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// olusturma()
// Vektore yeni butce nesnesi ekler; id olarak listenin o anki boyutunu kullanir.
// ─────────────────────────────────────────────────────────────────────────────
void olusturma(string name, vector<butce>& kayitgirdi) {
    int yeniId = (int)kayitgirdi.size();
    // Listede 0 kullanici varsa yeni id=0, 1 varsa id=1 olur.
    // Silme islemi olmadigi surece id'ler hic cakismaz.

    // emplace_back: push_back'ten farki, nesneyi gecici kopyalamadan
    // dogrudan vektorun icinde insa eder (construct eder).
    // Argümanlar butce sinifinin constructor'ina iletilir: butce(name, yeniId)
    kayitgirdi.emplace_back(name, yeniId);

    cout << "[OK] '" << name << "' (ID:" << yeniId << ") kullanici olusturuldu." << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// main()
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    vector<butce> kullaniciler; // tum kullanicilarin listesi; baslangiçta bos

    // ── Acilis: Kayitli kullanicilari diskten yukle ──────────────────────────
    {
        // Kume parantezi { }: buradaki degiskenlerin omrunu sinirlamak icin.
        // taramaId ve bulunanIsim sadece bu tarama icin lazim; disariya sizdirmiyoruz.
        int taramaId = 0;
        string bulunanIsim;

        // id=0'dan baslayarak sirali ara: 0 varsa 1'e bak, 1 varsa 2'ye bak...
        // kullanici_VarMi false donunce dur; ardisik id'ler oldugu icin bos buldun mu dur.
        while (kayit::kullanici_VarMi(taramaId, bulunanIsim)) {
            cout << "[YUKLE] Kayitli kullanici bulundu: " << bulunanIsim
                 << " (ID:" << taramaId << ")" << endl;

            // emplace_back: constructor'u cagirır → butce(bulunanIsim, taramaId)
            // Constructor icinde dosya_Yukle() otomatik calısır → disk → ram
            kullaniciler.emplace_back(bulunanIsim, taramaId);
            taramaId++;
        }
    } // taramaId ve bulunanIsim burada olur; vector<butce> kullaniciler devam eder

    // ── Hic kayit yoksa ilk kullanicıyı olustur ─────────────────────────────
    if (kullaniciler.empty()) {
        cout << "Hic kayitli kullanici bulunamadi." << endl;
        cout << "Lutfen yeni kullanici ismi giriniz: ";
        string isim;
        cin.ignore(); // cin >> ile getline karismasini onle: tamponu temizle
        // Neden: cin >> bir onceki giristen "\n" birakir, getline onu bos satir olarak okur.
        getline(cin, isim); // bosluklu isim girilmesine izin vermek icin getline
        olusturma(isim, kullaniciler);
    }

    // ── Ana menü dongusu ─────────────────────────────────────────────────────
    secimYap(kullaniciler);

    return 0; // main'den 0 donmek "program basariyla bitti" anlamina gelir (POSIX gelenegı)
}

// ─────────────────────────────────────────────────────────────────────────────
// menuYazdir()
// Sadece ekrana yazar; hicbir degisken tutmaz, hicbir degiskeni degistirmez.
// ─────────────────────────────────────────────────────────────────────────────
void menuYazdir() {
    cout << endl;
    cout << "=============================" << endl;
    cout << " 1 - Gelir / Gider islemleri" << endl;
    cout << " 2 - Mevcut kayitlari goruntule" << endl;
    cout << " 3 - Yeni kullanici olustur" << endl;
    cout << " 4 - Verileri kaydet" << endl;
    cout << " 5 - Gunluk sifirla / Haftaliga aktar" << endl;
    cout << " 6 - Cikis" << endl;
    cout << "=============================" << endl;
    cout << "Secim: ";
}

// ─────────────────────────────────────────────────────────────────────────────
// secimYap()
// Programin ana dongusu. while(true) ile kullanici "Cikis" secene kadar doner.
// ─────────────────────────────────────────────────────────────────────────────
void secimYap(vector<butce>& kullaniciler) {

    // Birden fazla kullanici varsa hangisi uzerinde islem yapilacak?
    int aktifIdx = 0; // varsayilan: ilk kullanici (indeks 0)

    if (kullaniciler.size() > 1) {
        cout << "Hangi kullanici ile devam edilsin?" << endl;
        for (int i = 0; i < (int)kullaniciler.size(); i++) {
            cout << "  " << (i + 1) << " - " << kullaniciler[i].getIsim() << endl;
        }
        cout << "Secim: ";
        cin >> aktifIdx;
        // min/max ile gecersiz deger gelirse en yakin gecerli degere kirilir
        aktifIdx = max(1, min(aktifIdx, (int)kullaniciler.size())) - 1; // 0-bazliya cevir
    }

    int secim = 0;
    while (true) { // kullanici cikis secene kadar don
        menuYazdir();
        cin >> secim;

        switch (secim) {

            // ── 1: Gelir / Gider ──────────────────────────────────────────────
            case 1: {
                // switch icinde yeni degisken tanimlayabilmek icin {} kullaniyoruz.
                // {} olmasa "initialization of 'altSecim' is skipped by 'case'" derleyici hatasi verir.
                cout << "  1 - Gelir ekle" << endl;
                cout << "  2 - Gider ekle" << endl;
                cout << "  3 - Kayit sil" << endl;
                cout << "  Secim: ";
                int altSecim;
                cin >> altSecim;

                if (altSecim == 1) {
                    float tutar;
                    cout << "Gelir tutari: ";
                    cin >> tutar;
                    kullaniciler[aktifIdx].getiri(tutar); // pozitif olarak ekler
                } else if (altSecim == 2) {
                    float tutar;
                    cout << "Gider tutari: ";
                    cin >> tutar;
                    kullaniciler[aktifIdx].goturu(tutar); // eksi yaparak ekler
                } else if (altSecim == 3) {
                    kullaniciler[aktifIdx].yazdir();      // once listele, hangi no silinecek?
                    cout << "Silinecek kayit no: ";
                    int no;
                    cin >> no;
                    kullaniciler[aktifIdx].sil(no);
                } else {
                    cout << "[HATA] Gecersiz secim." << endl;
                }
                break; // switch'ten cik; break olmasa alt case'e duser (fall-through)
            }

            // ── 2: Goruntule ──────────────────────────────────────────────────
            case 2:
                kullaniciler[aktifIdx].yazdir();  // tablo goster
                kullaniciler[aktifIdx].gunluk();  // net bakiye hesapla ve yazdir
                break;

            // ── 3: Yeni Kullanici ─────────────────────────────────────────────
        }
    }

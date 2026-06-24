#include "butce/butce.h"  
#include "kayit/kayit.h"
#include <iostream>
#include <vector>
using namespace std;

void olusturma(string name, vector<butce>& kayitgirdi);
void menuYazdir();
void secimYap(vector<butce>& kullaniciler);

void gunlukSifirla(vector<butce>& kullaniciler) {

    if (kullaniciler.empty()) {
        cout << "[BILGI] Hic kullanici yok." << endl;
        return;
    }

    int secim = 0;

    if (kullaniciler.size() > 1) {
       
        cout << "Hangi kullanici icin gunluk sifirlansin?" << endl;
        for (int i = 0; i < (int)kullaniciler.size(); i++) {
       
            cout << "  " << (i + 1) << " - " << kullaniciler[i].getIsim()
                 << " (ID:" << kullaniciler[i].getId() << ")" << endl;
        }
        cout << "Secim: ";
        cin >> secim;

        if (secim < 1 || secim > (int)kullaniciler.size()) {
            cout << "[HATA] Gecersiz secim." << endl;
            return;
        }
        secim -= 1;
    }
    

    cout << endl;
    cout << "Gunluk sifirlama secenekleri:" << endl;
    cout << "  1 - Gunlugu haftaliga aktar ve sifirla" << endl;
    cout << "  2 - Sadece gunlugu sifirla (haftaliga aktarma)" << endl;
    cout << "Secim: ";
    char islem;
    while (-1)
    {
       cin >> islem;

    if (islem == '1') {
        kullaniciler[secim].gunluk_HaftaligaAktar(); 
        break;
    } else if (islem == '2') {
        kullaniciler[secim].gunluk_Sifirla();   
        break;   
    } 
    else if (islem == 'c' || islem == 'C')
    {
        cout << "Islemden cikiliyor..." << endl;
        break;
    }
    else {
        
          cout << endl;
          cout << "Gunluk sifirlama secenekleri:" << endl;
          cout << "  1 - Gunlugu haftaliga aktar ve sifirla" << endl;
          cout << "  2 - Sadece gunlugu sifirla (haftaliga aktarma)" << endl;
          cout << "[HATA] Gecersiz secim, islem tekrar deneyin/bu islemden cikmak icin ('C/c'): " << endl;
          cout << "Secim: ";
    }
    }
    
    
}


int main() {
    vector<butce> kullaniciler; 

  
    {
       
        int taramaId = 0;
        string bulunanIsim;

  
        while (kayit::kullanici_VarMi(taramaId, bulunanIsim)) {
            cout << "[YUKLE] Kayitli kullanici bulundu: " << bulunanIsim
                 << " (ID:" << taramaId << ")" << endl;

            kullaniciler.emplace_back(bulunanIsim, taramaId);
            taramaId++;
        }
    } 


    if (kullaniciler.empty()) {
        cout << "Hic kayitli kullanici bulunamadi." << endl;
        cout << "Lutfen yeni kullanici ismi giriniz: ";
        string isim;
        cin.ignore(); 
      
        getline(cin, isim); 
        olusturma(isim, kullaniciler);
    }

    // ── Ana menü dongusu ─────────────────────────────────────────────────────
    secimYap(kullaniciler);

    return 0; 
}

void menuYazdir() {
    cout << endl;
    cout << "=============================" << endl;
    cout << " 1 - Gelir / Gider islemleri" << endl;
    cout << " 2 - Mevcut kayitlari goruntule" << endl;
    cout << " 3 - Verileri kaydet" << endl;
    cout << " 4 - Gunluk sifirla / Haftaliga aktar" << endl;
    cout << " 5 - Cikis" << endl;
    cout << "=============================" << endl;
    cout << "Secim: ";
}

void secimYap(vector<butce>& kullaniciler) {

    
    int aktifIdx = 0; 

    if (kullaniciler.size() > 1) {
        int i = 0;
        cout << "Hangi kullanici ile devam edilsin?" << endl;
        for (i; i < (int)kullaniciler.size(); i++) {
            cout << "  " << (i + 1) << " - " << kullaniciler[i].getIsim() << endl;
        }
        cout << "  " << (i + 1) << " - Yeni kullanici olustur " << endl;
        cout << "Secim: ";
        cin >> aktifIdx;
        if (aktifIdx == i+1)
        {
            cout << "Yeni kullanici ismi: ";
                string isim;
                cin.ignore(); 
                getline(cin, isim);
                olusturma(isim, kullaniciler);
                aktifIdx = (int)kullaniciler.size() - 1;
            
        }
        
   
        aktifIdx = max(1, min(aktifIdx, (int)kullaniciler.size())) - 1; 
    }

    int secim = 0;
    while (true) { 
        menuYazdir();
        cin >> secim;

        switch (secim) {

         
            case 1: {
                
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
                    kullaniciler[aktifIdx].getiri(tutar); 
                } else if (altSecim == 2) {
                    float tutar;
                    cout << "Gider tutari: ";
                    cin >> tutar;
                    kullaniciler[aktifIdx].goturu(tutar); 
                } else if (altSecim == 3) {
                    kullaniciler[aktifIdx].yazdir();   
                    cout << "Silinecek kayit no: ";
                    int no;
                    cin >> no;
                    kullaniciler[aktifIdx].sil(no);
                } else {
                    cout << "[HATA] Gecersiz secim." << endl;
                }
                break;
            }

     
            case 2:
                kullaniciler[aktifIdx].yazdir(); 
                kullaniciler[aktifIdx].gunluk(); 
                break;

            case 3:
              
                kullaniciler[aktifIdx].dosya_Kayit();
                break;

            case 4:
                gunlukSifirla(kullaniciler); 
                break;

            case 5:
                cout << "Cikis yapiliyor..." << endl;
                return; 

            default:
               
                cout << "[HATA] Gecersiz deger, yeniden deneyiniz." << endl;
                break;
        }
    }
}

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
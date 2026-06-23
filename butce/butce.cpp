#include "butce.h"
#include <iostream>
#include <sstream>
using namespace std;

butce::butce(string isim) {
    kullanici = isim;
}

// Kar kayıt
float butce::getiri(const float kar) {
    gnkKayit.push_back(kar);
    return kar; 
}

// Götürü kayıt
float butce::goturu(float zarar) {
    if (zarar > 0) {
        zarar = -1 * zarar;
    }
    gnkKayit.push_back(zarar);
    return 0;
}

float butce::gunluk() {
    float toplam = 0;
    int boyut = gnkKayit.size();
    
    if (boyut == 0) {
        cout << kullanici << " icin henüz kayit girilmemis." << endl;
        return 0;
    }
else{

    cout << kullanici << " gunluk kayitlar: ";
    for (int i = 0; i < boyut; i++) {
        toplam += gnkKayit[i];
        
        if (i == boyut - 1) {
            cout << gnkKayit[i] << endl; 
            
            if (toplam > 0) {
                cout << "Tebrikler, bugun kasana: " << toplam << " kadar bakiye girdi" << endl;
            } 
            else if (toplam < 0) {
                // Zararı pozitif gösterip "zarardasın" demek daha mantıklı, eksi ile çarptık
                cout << "Bugun kasadan: " << -toplam << " kadar zarardasin" << endl;
            } 
            else {
                cout << "Mukemmel bir denge saglanmis, gelir ve gider esit" << endl; 
            }
        } 
        else {
            cout << gnkKayit[i] << " || ";
        }
    }
    
  }  
    return 0;
}

void butce::sil(int secimInt) {
    if (secimInt >= 1 && secimInt <= gnkKayit.size()) {
        gnkKayit.erase(gnkKayit.begin() + (secimInt - 1));
        cout << secimInt << " numarali kayit basariyla silindi." << endl;
    } 
    else {
        cout << "Gecersiz bir sira numarasi girdiniz!" << endl;
    }
}

void butce::yazdir() {
    if (gnkKayit.empty()) {
        cout << kullanici << " icin gosterilecek herhangi bir kayit bulunmamamaktadir." << endl;
        return;
    }

    // 1. DÖNGÜ: Elemanları Yazdırma
    for (int i = 0; i < gnkKayit.size(); i++) {
        cout << " || " << gnkKayit[i];
        if (i == gnkKayit.size() - 1) {
            cout << " ||" << endl;
        }
    }
    
    for (int i = 0; i < gnkKayit.size(); i++) {
       
        stringstream ss;
        ss << gnkKayit[i];
        string yazi = ss.str();
        string indeksYazi = to_string(i + 1); 
      
        int toplamBosluk = yazi.length() - indeksYazi.length();
        if (toplamBosluk < 0) toplamBosluk = 0; 
        
        int solBosluk = toplamBosluk / 2;
        int sagBosluk = toplamBosluk - solBosluk;

        cout << " || ";
        for (int j = 0; j < solBosluk; j++) { cout << " "; }
        cout << (i + 1); 
        for (int j = 0; j < sagBosluk; j++) { cout << " "; }

        if (i == gnkKayit.size() - 1) {
            cout << " ||" << endl;
        }
    }
}

/*int main(){

butce ahmet("Ahmet");

ahmet.getiri(50000);
ahmet.goturu(40000);
ahmet.yazdir();


}
*/
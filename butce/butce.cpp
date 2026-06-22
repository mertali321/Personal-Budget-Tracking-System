#include "butce.h"
#include <iostream>

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
    return zarar;
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
    return toplam;
}
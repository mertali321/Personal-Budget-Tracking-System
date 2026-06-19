#pragma once
#include "butce.h"
#include <vector>
#include <iostream>
using namespace std;

class butce
{
private:
      //degerler
     vector<float> gnkKayit,haftalik_Kyt; string kullanici; 
public:
    //kullanici isim parametresi
    butce(string kullanici){
        this->kullanici = kullanici;
    }

  //kar kayit
  float getiri(const float kar){

  gnkKayit.push_back(kar);
    
}

//goturu kayit
float goturu(float zarar){


    if (zarar>0)
    {
        zarar = -1*zarar;
    }
    
  gnkKayit.push_back(zarar);

}
//gunluk gelir gider yazdirma
float gunluk(){
float toplam =0;
int boyut = gnkKayit.size();
  cout << "gunluk kayitlar ";
for (int i = 0; i <boyut; i++)
{
    toplam = gnkKayit[i]+toplam;
    if (i==boyut-1)
    {
        cout << gnkKayit[i]<< endl; 
        
       if (toplam>0)
       {
          cout << "Tebrikler, bu gun kasana: " << toplam << " kadar bakiye girdi" << endl;
       }
       else if (toplam < 0)
       {
          cout << "bu gun kasadan: " << toplam << " kadar zarardasin" << endl;
       }
       else{
               cout << "Mukemmel bir denge sağlamis gelir ve gider esit" << endl; 
       }
    }
    else{
       
     cout << gnkKayit[i] << " || ";
    }
  
}


}


};




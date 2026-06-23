#include "butce/butce.h"
#include <iostream>
#include <vector>
using namespace std;
void olusturma(string name,vector<butce> &kayitgirdi){
 int i=0; 

    
kayitgirdi.emplace_back(name,i);

}

void yazdir();

void secim();
int main(){
    
vector<butce> kullaniciler;





if (kullaniciler.empty())
{
    cout << "Hic kullanici yoktir. --> Lutfen yeni kullanici tanimlayiniz." << endl;
    cout << "kullanicinin ismini/Soyisin giriniz ";
    string isim;
    getline(cin,isim);
    olusturma(isim,kullaniciler);

    
}

secim();





cin.get();
}


void secim(){

    while (true)
{
    yazdir();
    int secim =0;
    cout << "yapmak istediginiz islemi secin: ";
    cin >> secim;
   switch (secim)
   {
   case 1:
  
    break;
   
     case 2:
  
    break;
     case 3:
  
    break;
     case 4:
  
    break;
   default:
      cin >> secim;
       cout << endl << "gecersiz deger yeniden deneyiniz: ";
   }
    
        
    }
}


void yazdir(){

    cout << "1-Gelir Gider islemleri" << endl;
    cout << "2-Mevcut Kayit islemleri" << endl;
    cout << "3-yeni kullanici kayidi" << endl;
    cout << "4-Verileri Kaydetme" << endl;

}
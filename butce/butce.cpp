#pragma
#include <butce.h>
#include <vector>
#include <iostream>
using namespace std;

class butce
{
private:

     vector<float> gnkKayit,haftalik_Kyt; string kullanici; 
public:

    butce(string kullanici){
        this->kullanici = kullanici;
    }


  float getiri(const float kar){

  gnkKayit.push_back(kar);
    
}


float goturu(float zarar){


    if (zarar>0)
    {
        zarar = -1*zarar;
    }
    
  gnkKayit.push_back(zarar);

}

float gunluk(){

int boyut = gnkKayit.size();
  cout << "gunluk kayitlar ";
for (int i = 0; i <boyut; i++)
{
    if (i==boyut-1)
    {
        cout << gnkKayit[i];   
    }
    else{

     cout << gnkKayit[i] << " || ";
    }
  
}


}


};




#pragma
#include <butce.h>
#include <vector>
#include <iostream>
using namespace std;

class butce
{
private:

     vector<float> kayit; string kullanici;
public:

    butce(string kullanici){
        this->kullanici = kullanici;
    }


  float getiri(const float kar){

  kayit.push_back(kar);
    
}


float goturu(float zarar){


    if (zarar>0)
    {
        zarar = -1*zarar;
    }
    
  kayit.push_back(zarar);

}

float gunluk(){

int boyut = kayit.size();
  cout << "gunluk kayitlar ";
for (int i = 0; i <boyut; i++)
{
    if (i==boyut-1)
    {
        cout << kayit[i];   
    }
    else{

     cout << kayit[i] << " || ";
    }
  
}


}


};




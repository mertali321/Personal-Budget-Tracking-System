#include "butce/butce.h"
#include <iostream>
#include <vector>
using namespace std;


int main(){
    
vector<butce> kullaniciler;

kullaniciler.emplace_back("Mert");

kullaniciler.emplace_back("Kerhian");


kullaniciler[0].getiri(5000);
kullaniciler[0].goturu(400);
kullaniciler[0].gunluk();
}
#pragma once
#include <vector>
#include <string>

class butce {
private:
    std::vector<float> gnkKayit;
    std::vector<float> haftalik_Kyt; // .cpp'de kullandığın için buraya ekledik
    std::string kullanici;

public:
    // Constructor (Yapıcı Fonksiyon)
    butce(std::string isim);

    // Geri dönüş tipleri float olduğu için return değerleri ekleyeceğiz
    float getiri(const float kar);
    float goturu(float zarar);
    float gunluk(); 
};
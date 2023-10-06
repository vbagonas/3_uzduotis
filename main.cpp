#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

 struct Studentas {
        string vardas;
        string pavarde;
        vector<int> paz;
        int egzam;
        double vidurkis;
        double vidurkis2;
    };
double Mediana(const vector<int>& pazymiai) {
    vector<int> rus_pazym = pazymiai;
    sort(rus_pazym.begin(), rus_pazym.end());

    size_t size = rus_pazym.size();
    if (size % 2 == 0) {
        return (rus_pazym[size / 2 - 1] + rus_pazym[size / 2]) / 2.0;
    } else {
        return rus_pazym[size / 2];
    };
}
int main() {
    ifstream file("kursiokai2.txt");
    if(!file.is_open()){
        cerr<<"Nepavyko atidaryti failo."<<endl;
        return 1;
    }
    string eile;
    vector<Studentas> studentai;
    bool skaitytind = false;
    int skND = 0;

    if (getline(file, eile)) {
        istringstream titleLine(eile);
        string stulpav;
        while (titleLine >> stulpav) {
            if (stulpav == "Vardas") {
                continue;
            } else if (stulpav == "Pavarde") {
                continue;
            } else if (stulpav == "Egz.") {
                skaitytind = false;
                break;
            } else {
                skaitytind = true;
                skND++;
            }
        }
    } else {
        cerr << "Error: Empty input file." << endl;
        return 1;
    }

    while(getline(file, eile)){
        istringstream iss(eile);
        Studentas studentas;
        iss>>studentas.vardas>>studentas.pavarde;
        int balas;

        for(int i = 0; i<skND; i++) {
            if(iss>>balas) {
                studentas.paz.push_back(balas);
            } else {
                cerr << "Klaida. Nera ND pazymio" << endl;
            }
        }
        if (iss>>studentas.egzam) {
            studentai.push_back(studentas);
        } else {
            cerr << "Klaida. Nera egzamino pazymio" << endl;
        }
    }

    for (Studentas& studentas : studentai) {
        double ndSuma = 0, ndMed = 0;
        for (int balas : studentas.paz) {
            ndSuma += balas;
        }
        double ndVid = ndSuma / skND;
        studentas.vidurkis = 0.4 * ndVid + 0.6 * studentas.egzam;
        ndMed = Mediana(studentas.paz);
        studentas.vidurkis2 = 0.4 * ndMed + 0.6 * studentas.egzam;
    }

    cout<<"Vardas\tPavarde\tVidurkis"<<endl;
    for(const Studentas& studentas : studentai){
        cout<<studentas.vardas<<"\t"<<studentas.pavarde<<"\t"<<studentas.vidurkis<<"\t"<<studentas.vidurkis2<<endl;
    }
    return 0;
}




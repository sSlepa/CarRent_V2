#include <iostream>
#include "../headers/masina.hpp"

Masina::Masina(){

    this->nume = "";
    this->model = "";
    this->an = "";
    this->disponibilitate = "";
    this->pret = "";

}

Masina::Masina(string nume,string model,string an,string disponibilitate,string pret){

    this->nume = nume;
    this->model = model;
    this->an = an;
    this->disponibilitate = disponibilitate;
    this->pret = pret;

}

ostream & operator << (ostream &st, const Masina &x){
    
    st << x.nume << ' ' << x.model << ' ' << x.an << ' ' << x.disponibilitate << ' ' << x.pret;
    return st;
    
}
bool operator ==(const Masina &a,const Masina &b){

    if(a.nume == b.nume && a.model == b.model && a.an == b.an && a.disponibilitate == b.disponibilitate 
    && a.pret == b.pret)
        return 1;
    
    return 0;

}
void change_disp(Masina &x,const char s[]){

    x.disponibilitate = s;
    
}
void change_price(Masina &x,const char s[]){

    x.pret = s;

}
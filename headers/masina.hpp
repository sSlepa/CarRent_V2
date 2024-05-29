#include <string>

using namespace std;

class Masina{

    string nume,model,an,disponibilitate,pret;
    
public:
    
    Masina();
    Masina(string,string,string,string,string);
    friend ostream & operator << (ostream &, const Masina &);
    friend bool operator== (const Masina &, const Masina &);
    string get_dispon(){
        return disponibilitate;
    }
    string get_nume(){
        return nume;
    }
    string get_model(){
        return model;
    }
    string get_an(){
        return an;
    }
    string get_pret(){
        return pret;
    }
    friend void change_disp(Masina &,const char[]);
    friend void change_price(Masina &,const char []);
};
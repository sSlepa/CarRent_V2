#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <windows.h>
#include "../headers/masina.hpp"

using namespace std;

Masina Masini[10005];
int nrMasini;
int nrOameni;

void coloredtext(WORD Culoare,const char* text){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, Culoare);
    
    cout << text;

    SetConsoleTextAttribute(hConsole, saved_attributes);

}

void load_from_file_car_stock(){

    ifstream fp("txt_files/masini.txt");

    if(!fp){
        coloredtext(FOREGROUND_RED,"Fisierul masini.txt nu este creat !");
        Sleep(5000);
        fp.close();
        exit(0);
    }
    else{
        char linie[256];
        char mat[256][256];
        nrMasini = 0;
        while(fp.getline(linie,255)){

            //printf("%s",linie);
            strcpy(mat[++nrMasini],linie);
        
        }
        for(int i = 1 ; i <= nrMasini ; ++i){
            char *p = strtok(mat[i]," ");
            char nume[50],model[50],an[50],dispon[50],pret[50];
            strcpy(nume,p);
            p = strtok(NULL," ");
            strcpy(model,p);
            p = strtok(NULL," ");
            strcpy(an,p);
            p = strtok(NULL," ");
            strcpy(dispon,p);
            p = strtok(NULL," ");
            strcpy(pret,p);

            Masini[i] = Masina(nume,model,an,dispon,pret);

        }
        
        fp.close();
    }
}

void help(){

    system("cls");
    cout << "1. VA - Vizualizare Autoturisme\n";
    cout << "2. RENT [nume] [model] [an] [disponibilitate] [pret]\n";
    cout << "3. UNRENT [nume] [model] [an] [disponibilitate] [pret]\n";
    cout << "4. ADD [nume] [model] [an] [disponibilitate] [pret]\n";
    cout << "5. DELETE [nume] [model] [an] [disponibilitate] [pret]\n";
    cout << "6. UPDATE [nume] [model] [an] [disponibilitate] [pret] [\"Disponibil\"/\"Indisponibil\"/\"Pret\"]\n";
    cout << "7. SEARCH ([nume] / [model] / [an] / [disponibilitate] / [pret]) [text] - Doar 1 optiune \n";

}

void add_veh(int argc,char *argv[]){

    if(argc == 7){

        Masini[++nrMasini] = Masina(argv[2],argv[3],argv[4],argv[5],argv[6]);
    
        ofstream ofs("txt_files/masini.txt", ofstream::out | ofstream::trunc);
        ofs.close();
        ofstream afis("txt_files/masini.txt");
        for(int i = 1 ; i <= nrMasini ; ++i)
            afis << Masini[i] << '\n';

        coloredtext(FOREGROUND_GREEN,"Masina adauga cu succes !");
        Sleep(2500);

        afis.close();
    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }

}
void viz_veh(){

    system("cls");
    for(int i = 1 ; i <= nrMasini ; ++i)
        cout << i << ". " << Masini[i] << '\n';

    cout << '\n';

}

void del_veh(int argc,char *argv[]){

    if(argc == 7){

        int ok = 0;
        for(int i = 1 ; i <= nrMasini ; ++i){
            Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
            if(a == Masini[i]){
                for(int j = i ; j < nrMasini ; ++j)
                    Masini[j] = Masini[j + 1];

                nrMasini--;
                ok = 1;
                ofstream ofs("txt_files/masini.txt", ofstream::out | ofstream::trunc);
                ofs.close();
                ofstream afis("txt_files/masini.txt");
                for(int i = 1 ; i <= nrMasini ; ++i)
                    afis << Masini[i] << '\n';

                coloredtext(FOREGROUND_GREEN,"Masina stearsa cu succes !");
                Sleep(2500);

                afis.close();

                break;
            }
        }
        if(ok == 0){
            coloredtext(FOREGROUND_RED,"Masina nu a fost gasita ! Foloseste comanda VA pentru a vizualiza vehiculele");
        }
    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }

}
void update_veh(int argc,char *argv[]){

    if(argc == 8){
        int ok = 0;
        if(strcmp("Disponibil",argv[7]) == 0){
            for(int i = 1 ; i <= nrMasini ; ++i){
                Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
                if(a == Masini[i]){
                    ok = 1;
                    change_disp(Masini[i],"Disponibil");
                }
            }
            if(ok == 0){
                coloredtext(FOREGROUND_RED,"Masina nu a fost gasita ! Foloseste comanda VA pentru a vizualiza vehiculele");
            }   
        }
        else if(strcmp("Indisponibil",argv[7]) == 0){
            
            for(int i = 1 ; i <= nrMasini ; ++i){
                Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
                if(a == Masini[i]){
                    ok = 1;
                    change_disp(Masini[i],"Indisponibil");
                }
            }
            if(ok == 0){
                coloredtext(FOREGROUND_RED,"Masina nu a fost gasita ! Foloseste comanda VA pentru a vizualiza vehiculele");
            }
        }
        else{
            for(int i = 1 ; i <= nrMasini ; ++i){
                Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
                if(a == Masini[i]){
                    ok = 1;
                    change_price(Masini[i],argv[7]);
                }
            }
            if(ok == 0){
                coloredtext(FOREGROUND_RED,"Masina nu a fost gasita ! Foloseste comanda VA pentru a vizualiza vehiculele");
            }
        }
        if(ok){
            ofstream ofs("txt_files/masini.txt", ofstream::out | ofstream::trunc);
            ofs.close();
            ofstream afis("txt_files/masini.txt");
            for(int i = 1 ; i <= nrMasini ; ++i)
                afis << Masini[i] << '\n';

            coloredtext(FOREGROUND_GREEN,"Masina modificata cu succes !");
            Sleep(2500);

            afis.close();
        }

    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }
}
void rent_veh(int argc,char *argv[]){

    if(argc == 7){
        for(int i = 1 ; i <= nrMasini ; ++i){
            Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
            if(a == Masini[i]){
                if(Masini[i].get_dispon() == "Disponibil"){
                    change_disp(Masini[i],"Indisponibil");

                    ofstream ofs("txt_files/masini.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    ofstream afis("txt_files/masini.txt");
                    for(int i = 1 ; i <= nrMasini ; ++i)
                        afis << Masini[i] << '\n';

                    coloredtext(FOREGROUND_GREEN,"Masina inchiriata cu succes !");
                    Sleep(2500);

                    afis.close();

                }
                else{
                    coloredtext(FOREGROUND_RED,"Masina este indisponibila ! Foloseste comanda VA pentru a vizualiza vehiculele");
                }
            }
        }
    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }

}

void unrent_veh(int argc,char *argv[]){

    if(argc == 7){
        for(int i = 1 ; i <= nrMasini ; ++i){
            Masina a(argv[2],argv[3],argv[4],argv[5],argv[6]);
            if(a == Masini[i]){
                if(Masini[i].get_dispon() == "Indisponibil"){
                    change_disp(Masini[i],"Disponibil");

                    ofstream ofs("txt_files/masini.txt", ofstream::out | ofstream::trunc);
                    ofs.close();
                    ofstream afis("txt_files/masini.txt");
                    for(int i = 1 ; i <= nrMasini ; ++i)
                        afis << Masini[i] << '\n';

                    coloredtext(FOREGROUND_GREEN,"Rezervare anulata cu succes !");
                    Sleep(2500);

                    afis.close();

                }
                else{
                    coloredtext(FOREGROUND_RED,"Masina nu este rezervata ! Foloseste comanda VA pentru a vizualiza vehiculele");
                }
            }
        }
    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }

}

void search_veh(int argc,char *argv[]){

    if(argc == 4){
        string aux = argv[3];
        if(strcmp(argv[2],"nume") == 0){
            int cnt = 1;
            cout << '\n';
            for(int i = 1 ; i <= nrMasini ; ++i){
                if(aux == Masini[i].get_nume()){
                    cout << cnt << ". " << Masini[i] << '\n';
                    cnt++;
                }
            }
        }
        else if(strcmp(argv[2],"model") == 0){
            int cnt = 1;
            cout << '\n';
            for(int i = 1 ; i <= nrMasini ; ++i){
                if(aux == Masini[i].get_model()){
                    cout << cnt << ". " << Masini[i] << '\n';
                    cnt++;
                }
            }
        }
        else if(strcmp(argv[2],"an") == 0){
            int cnt = 1;
            cout << '\n';
            for(int i = 1 ; i <= nrMasini ; ++i){
                if(aux == Masini[i].get_an()){
                    cout << cnt << ". " << Masini[i] << '\n';
                    cnt++;
                }
            }
        }
        else if(strcmp(argv[2],"disponibilitate") == 0){
            int cnt = 1;
            cout << '\n';
            for(int i = 1 ; i <= nrMasini ; ++i){
                if(aux == Masini[i].get_dispon()){
                    cout << cnt << ". " << Masini[i] << '\n';
                    cnt++;
                }
            }
        }
        else if(strcmp(argv[2],"pret") == 0){
            int cnt = 1;
            cout << '\n';
            for(int i = 1 ; i <= nrMasini ; ++i){
                if(aux == Masini[i].get_pret()){
                    cout << cnt << ". " << Masini[i] << '\n';
                    cnt++;
                }
            }
        }
        else{
            coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
        }
    }
    else{
        coloredtext(FOREGROUND_RED,"SINTAXA INVALIDA ! Foloseste comanda Help");
    }

}

int main(int argc,char *argv[]){

    load_from_file_car_stock();

    system("cls");
    coloredtext(FOREGROUND_GREEN,"=== MENIU PRINCIPAL ===\n");
    cout << "1. Vizualizare Autoturisme\n";
    cout << "2. Inchiriere\n";
    cout << "3. Anuleaza inchiriere\n";
    cout << "4. Adaugare Masina\n";
    cout << "5. Stergere Masina\n";
    cout << "6. Actualizare Masina\n";
    cout << "7. Cautare Masina\n";
    cout << "8. Help\n";

    if(strcmp(argv[1],"Help") == 0)
        help();
    else if(strcmp(argv[1],"ADD") == 0)
        add_veh(argc,argv);
    else if(strcmp(argv[1],"VA") == 0)
        viz_veh();
    else if(strcmp(argv[1],"DELETE") == 0)
        del_veh(argc,argv);
    else if(strcmp(argv[1],"UPDATE") == 0)
        update_veh(argc,argv);
    else if(strcmp(argv[1],"RENT") == 0)
        rent_veh(argc,argv);
    else if(strcmp(argv[1],"UNRENT") == 0)
        unrent_veh(argc,argv);
    else if(strcmp(argv[1],"SEARCH") == 0)
        search_veh(argc,argv);
    


    return 0;
}
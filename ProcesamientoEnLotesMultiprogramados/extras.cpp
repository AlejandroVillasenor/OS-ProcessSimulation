#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
int main(){
    char key;
    while(true){
        if(kbhit()){
            key = getch();
            switch(key){
                case 'i':{cout<<"Interrupcion"<<endl;}break;
                case 'e':{cout<<"Error"<<endl;}break;
                case 'p':{
                    cout<<"Pausa"<<endl;
                    while(true){
                        if(kbhit()){
                            key = getch();
                            if(key == 'c'){
                                cout<<"Continuar"<<endl;
                                break;
                            }
                        }
                    }
                }break;
                case 'c':{cout<<"Continuar"<<endl;}break;
                default:{cout<<"Opcion no valida"<<endl;}break;
            }
        }
    }
    return 0;
}
/*
Entregar investigacion, presentacion y el juego de nuestro tema. 
Se quiere adelantar a la segunda semana de octubre 
*/
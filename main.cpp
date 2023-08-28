#include <bits/stdc++.h>
#include "process.hpp"
#include "validacion.hpp"
#include "interface.hpp"
#include <conio.h>
#define errmsg "Error: Dato no valido"
using namespace std;

int main(){
    queue<Process> process; //Cola de procesos
	//Variables registro datos
	int numProcess = 0, proRegistered = 0, timeM = 0;
    string numPro, programer, operation, expresion,operating1, operating2, timeMax, ID; //Datos procesos
	bool numProcessVal, operationVal, timeVal, IDVal, IDRep; //Validaciones
	int loteProcess = 0; //Guarda los procesos de un lote
	float result = 0;//Resultado de operacion
	int lote = 1; //Numero de lote
    //Numero de procesos
    do{
        system("cls");
        cout<<"Numero de procesos a registrar: ";
        getline(cin, numPro);
        numProcessVal = validatePI(&numPro, 2);
        if(numProcessVal){
            numProcess = stoi(numPro);
            (numProcess <= 0 || numProcess >= 30) ? numProcessVal = false : numProcessVal = true ; 
            if(numProcessVal){
                cout<<errmsg;
            }
        }else{
            cout<<errmsg;
			getch();
        }
    }while (numProcessVal == false);

	//Registro de procesos
	while(proRegistered < numProcess){
		system("cls");
		cout<<"- Nombre de Programador: ";
		getline(cin, programer);
		do{
			cout<<"- Operacion a realizar: \n";
			cout<<"  1. Suma (+)\n";
			cout<<"  2. Resta (-)\n";
			cout<<"  3. Multiplicacion (*)\n";
			cout<<"  4. Division (/)\n";
			cout<<"  5. Residuo\n";
			cout<<"  6. Porcentaje (%)\n";
			cout<<" -- Operacion: ";
			getline(cin, operation);
			operationVal = validatePI(&operation, 1);
			if(operationVal == true){
				system("cls");
				switch(stoi(operation)){
					case 1:{//Suma
						cout<<"SUMA"<<endl;
						data1(&operating1, &operating2);
						result = stof(operating1) + stof(operating2);
						expresion = operating1 + " + " + operating2;
					}break;
					case 2:{//Resta
						cout<<"RESTA"<<endl;
						data1(&operating1, &operating2);
						result = stof(operating1) - stof(operating2);
						expresion = operating1 + " - " + operating2;
					}break;
					case 3:{//Multiplicacion
						cout<<"MULTIPLICACION"<<endl;
						data1(&operating1, &operating2);
						result = stof(operating1) * stof(operating2);
						expresion = operating1 + " * " + operating2;
					}break;
					case 4:{//Division
						cout<<"DIVISION"<<endl;
						data1(&operating1, &operating2);
						result = stof(operating1) / stof(operating2);
						expresion = operating1 + " / " + operating2;
					}break;
					case 5:{//Modulo
						cout<<"MODULO"<<endl;
						data2(&operating1, &operating2);
						result = stoi(operating1) % stoi(operating2);
						expresion = operating2 + " % " + operating1;
					}break;
					case 6:{//Porcentaje
						cout<<"PORCENTAJE"<<endl;
						data2(&operating1, &operating2);
						result = (stoi(operating1) * stoi(operating2)) / 100;
						expresion = operating2 + "% de " + operating1; 
					}break;
					default:{//Opcion no valida
						cout << errmsg;
						getch();
						system("cls");
					}break;
				}
			}else{
				cout<<errmsg;
				getch();
				system("cls");
			}
		}while(operationVal == false);
		do{
			cout<<"- Tiempo maximo estimado: ";
			fflush(stdin);
			getline(cin,timeMax);
			timeVal = validatePI(&timeMax, 2);
			if(timeVal){
				timeM = stoi(timeMax);
			}else{
				cout<<errmsg;
				getch();
				timeVal = false;
			}
		}while(!timeVal);
		do{
			cout<<"-  Numero de programa(ID): ";
			getline(cin, ID);
			IDVal = validatePI(&ID, 8);
			if(!IDVal){
				cout<<errormsg;
				getch();
			}else{
				//Validar ID repedito
				queue<Process> processCopy = process; //Cola de procesos auxiliar
				IDRep  = false;
				if(!process.empty()){
					while (!processCopy.empty()){
						if(ID == processCopy.front().getID()){
							IDRep = true;
							//Borrar cola auxiliar
							cout<<"ID repetido!\n";
							while(!processCopy.empty()){
								processCopy.pop();
							}
							getch();
							break;
						}else{
							processCopy.pop();
						}
					}
				}else{
					IDRep = false;
				}
			}
		}while(IDVal == false || IDRep == true);
		//Registro de processo exitoso
		proRegistered+=1;
		loteProcess+=1;
		//Agregar proceso a cola de objetos
		//Validación numero lote
		if(loteProcess == 5){
			loteProcess = 0;
			lote += 1;
		}
		Process job(programer, expresion, result, timeM, ID, lote);
		process.push(job);
	}
	//Mostrar cola de procesos
	system("cls");
	cout<< "Cola de procesos:"<<endl;
	queue<Process> imprimir = process;
	while(!imprimir.empty()){
		cout << "Programador: " << imprimir.front().getName() << endl;
		cout << "Operacion: " << imprimir.front().getOperation() << endl;
		cout << "Resultado: " << imprimir.front().getResult() << endl;
		cout << "Tiempo: " << imprimir.front().getTime() << endl;
		cout << "ID: " << imprimir.front().getID() << endl;
		cout << "Lote: " << imprimir.front().getLote() << endl;
		cout << "--------------------------" << endl;
		imprimir.pop();
	}
	return 0;
}
/*
	Programación de Sistemas - Proyecto 1
	Programa 1 - Procesamiento por lotes
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zúñiga Lozano Racso Siseneg
	06/09/2023
	-- Archivo de cabecera --
*/
#include <bits/stdc++.h>
#include <unistd.h>
#include "process.hpp"
#include "validacion.hpp"
#include "interface.hpp"
#include <conio.h>
#define errmsg "Error: Dato no valido"
using namespace std;

int main(){
	system("title Programa 1 - Procesamiento por lotes");//Configuración consola
    queue<Process> process; //Cola de procesos
	queue<Process> processCopy; //Cola de procesos auxiliar
	vector<Process> processBatch; //Cola de procesos lote Actual
	int numProcess = 0, proRegistered = 0, timeM = 0;//Variables registro datos
    string numPro, programer, operation, expresion,operating1, operating2, timeMax, ID; //Datos procesos
	bool numProcessVal, operationVal, timeVal, IDVal, IDRep; //Validaciones
	int loteProcess = 0; //Guarda los procesos de un lote
	float result;//Resultado de operacion
	int lote = 1, loteAct = 1; //Lote = lotes pendietes, LoteAct = Lote siendo procesado
	int globalCounter = 0, processCounter = 0, maxTime = 0;
	int cordY, yPE; //Coordenadas
    do{
        system("cls");
		cout<<"|| Procesamiento por lotes ||"<<endl;
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
			system("cls");
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
			cout<<"  5. Residuo (mod)\n";
			cout<<"  6. Porcentaje (%)\n\n";
			cout<<"  -- Operacion: ";
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
						data2(&operating1, &operating2);
						result = stof(operating1) / stof(operating2);
						expresion = operating1 + " / " + operating2;
					}break;
					case 5:{//Modulo
						cout<<"RESIDUO"<<endl;
						data2(&operating1, &operating2);
						result = stoi(operating1) % stoi(operating2);
						expresion = operating1 + " mod " + operating2;
					}break;
					case 6:{//Porcentaje
						cout<<"PORCENTAJE"<<endl;
						data3(&operating1, &operating2);
						result = (stof(operating1) * stof(operating2)) / 100;
						expresion = operating2 + "%" + " de " + operating1; 
					}break;
					default:{//Opcion no valida
						cout << errmsg;
						operationVal = false;
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
				//Validacion limites de tiempo
				if (stoi(timeMax)<= 0 || stoi(timeMax)>= 100){
					cout<<errmsg;
					timeVal = false;
					getch();
					system("cls");
				}else{
					timeM = stoi(timeMax);
				}
			}else{
				cout<<errmsg;
				getch();
				system("cls");
			}
		}while(!timeVal);
		do{
			cout<<"-  Numero de programa(ID): ";
			getline(cin, ID);
			IDVal = validatePI(&ID, 8);
			if(!IDVal){
				cout<<errormsg;
				getch();
				system("cls");
			}else{
				//Validar ID repedito
				processCopy = process; //Cola de procesos auxiliar
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
							system("cls");
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
		//Registro de proceso exitoso
		proRegistered+=1;
		loteProcess+=1;
		if(loteProcess > 5){
			loteProcess = 1;
			lote += 1;
		}
		//Agregar proceso a cola de objetos
		Process job(programer, expresion, result, timeM, ID, lote);
		process.push(job);
	}
	//Mostrar cola de procesos
	desactivarMaximizar();
	system("mode con: cols=213 lines=50");//Tamaño de consola en pantalla completa
	system("cls");
	Processinterface();//Pantalla de procesos
	desactiveInput();
	gotoxy(73,44); cout<<"Presione una tecla para comenzar";
	getch();
	gotoxy(73,44); cout<<"                                ";
	processCopy = process;
	cordY = 14; //Para ubicar procesos completados
	gotoxy(200,6); cout<<"0"; //Contador global
	processCounter = 0;
	Process proceso(programer, expresion, result, timeM, ID, lote); //Instancia del proceso
	while(lote > 0){
		lote--; //Se resta el lote actual
		gotoxy(26,6); cout<<string(4,255); //Lotes pendientes
		gotoxy(26,6); cout<<lote;
		cordY+=1;
		gotoxy(140,cordY); cout<<"--------------------------- Lote "<<loteAct<<" ---------------------------";
		//Se obtiene los procesos del lote actual
		while(processCopy.front().getLote() == loteAct){
			//Se extraen los datos
			proceso.setName( processCopy.front().getName());
			proceso.setOp(processCopy.front().getOperation());
			proceso.setResult(processCopy.front().getResult());
			proceso.setTime(processCopy.front().getTime());
			proceso.setID(processCopy.front().getID());
			proceso.setLote(processCopy.front().getLote());
			processBatch.push_back(proceso);
			processCopy.pop();
		}
		while((process.front().getLote() == loteAct)){
			//Proceso en ejecucion
			cleanProcess();
			cleanBatch();
			maxTime = process.front().getTime();
			gotoxy(64,14); cout<<process.front().getName();
			gotoxy(60,16); cout<<process.front().getID();
			gotoxy(67,18); cout<<process.front().getOperation();
			gotoxy(61,20); cout<<process.front().getTime();
			gotoxy(77,22); cout<<"0"; //Tiempo transcurrido
			gotoxy(73,24); cout<<"0"; //Tiempo restante
			//Se imprime Lote Actual
			yPE = 0; //Imprimir procesos de lote actual
			processBatch.erase(processBatch.begin()); //Se elimina el proceso en ejecución
			for(int i = 0; i < processBatch.size(); i++){
				gotoxy(4,17+yPE); cout<<processBatch[i].getID();
				gotoxy(20,17+yPE); cout<<processBatch[i].getTime();
				yPE+=2;
			}
			processCounter = 0;
			//Actualizador de tiempos
			while(processCounter < maxTime){
				cleanTimes();
				sleep(1);
				globalCounter += 1;
				processCounter += 1;
				gotoxy(200,6); cout<<globalCounter;
				gotoxy(77,22); cout<<processCounter;
				gotoxy(73,24); cout<<maxTime - processCounter;
			}
			//Proceso terminado
			gotoxy(140,cordY+1); cout<<process.front().getID();
			gotoxy(164,cordY+1); cout<<process.front().getOperation();
			gotoxy(193,cordY+1); cout<<process.front().getResult();
			process.pop();
			cordY+=1;
		}
		loteAct++;
	}
	gotoxy(26,6); cout<<string(4,255); gotoxy(26,6); cout<<"0"; //Actualiza contador lotes pendites
	cleanAll();
	gotoxy(73,44); cout<<"Fin de procesamiento";
	getch();
	system("cls");
	//Fin del programa
	cout<<"~Gracias por usar el programa\n\n";
	cout<<"Realizado por:\n";
	cout<<"- Villasenor Rivas Alejandro Rodrigo | 218414783"<<endl;
	cout<<"- Zuniga Lozano Racso Siseneg | 221977551"<<endl;
	gotoxy(73,44); cout<<"                                ";
	gotoxy(73,44); cout<<"Presione una tecla para salir";
	getch();
	system("cls");
	return 0;
}
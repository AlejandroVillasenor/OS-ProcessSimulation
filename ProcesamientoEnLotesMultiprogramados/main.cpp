/*
	Programa 2 - Procesamiento por lotes multiprogramados
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zúñiga Lozano Racso Siseneg
	17/09/2023
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
	system("title Programa 2 - Procesamiento por lotes con Multiprogramacion");//Configuración consola
    queue<Process> process; //Cola de procesos
	queue<Process> processCopy; //Cola de procesos auxiliar
	vector<Process> processBatch; //Cola de procesos lote Actual
	int numProcess = 0, proRegistered = 0, timeM = 0, ID = 1, operation, timeMax;//Variables registro datos
    string numPro, operating1, operating2, expresion; //Datos procesos
	bool numProcessVal, intBan = false, errorFlag = false ; //Validacion, Bandera interrupción, Bandera Error en proceso
	int loteProcess = 0; //Guarda los procesos de un lote
	float result;//Resultado de operacion
	int lote = 1, loteAct = 1; //Lote = lotes pendietes, LoteAct = Lote siendo procesado
	int globalCounter = 0, processCounter = 0, maxTime = 0, reTime = 0;
	int cordY, yPE; //Coordenadas
	char tecla; //Almacena tecla presionada durante la ejecución de procesos
	// Crear un generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());
	uniform_int_distribution<int> numOperacion(1, 6); //Random numero operacion
	uniform_int_distribution<int> maximumTime(6, 18);  //Random tiempo maximo
    do{
        system("cls");
		cout<<"|| Procesamiento por lotes multiprogramados ||"<<endl;
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
			/*Opcion de oeracion:
				1. Suma (+)\n";
				2. Resta (-)
				3. Multiplicacion (*)
				4. Division (/)
				5. Residuo  (mod)
				6. Porcentaje (%) */
		operation = numOperacion(generador);
		switch(operation){
			case 1:{//Suma
				data1(&operating1, &operating2);
				result = stof(operating1) + stof(operating2);
				expresion = operating1 + " + " + operating2;
			}break;
			case 2:{//Resta
				data1(&operating1, &operating2);
				result = stof(operating1) - stof(operating2);
				expresion = operating1 + " - " + operating2;
			}break;
			case 3:{//Multiplicacion
				data1(&operating1, &operating2);
				result = stof(operating1) * stof(operating2);
				expresion = operating1 + " * " + operating2;
			}break;
			case 4:{//Division
				data2(&operating1, &operating2);
				result = stof(operating1) / stof(operating2);
				expresion = operating1 + " / " + operating2;
			}break;
			case 5:{//Modulo
				data2(&operating1, &operating2);
				result = stoi(operating1) % stoi(operating2);
				expresion = operating1 + " mod " + operating2;
			}break;
			case 6:{//Porcentaje
				data3(&operating1, &operating2);
				result = (stof(operating1) * stof(operating2)) / 100;
				expresion = operating2 + "%" + " de " + operating1;  
			}break;
		}
		//Tiempo máximo
		timeMax = maximumTime(generador);
		//Registro de proceso exitoso
		proRegistered+=1;
		loteProcess+=1;
		if(loteProcess > 5){
			loteProcess = 1;
			lote += 1;
		}
		//Agregar proceso a cola de objetos
		Process job(expresion, result, timeMax, 0, ID, lote);
		process.push(job);
		ID += 1;//Aumetar ID
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
	Process proceso(expresion, result, timeM, 0, ID, lote); //Instancia del proceso
	while(lote > 0){
		lote--; //Se resta el lote actual
		gotoxy(26,6); cout<<string(4,255); //Lotes pendientes
		gotoxy(26,6); cout<<lote;
		cordY+=1;
		gotoxy(140,cordY); cout<<"--------------------------- Lote "<<loteAct<<" ---------------------------";
		//Se obtiene los procesos del lote actual
		while(processCopy.front().getLote() == loteAct){
			//Se extraen los datos
			proceso.setOp(processCopy.front().getOperation());
			proceso.setResult(processCopy.front().getResult());
			proceso.setTimeMax(processCopy.front().getTimeMax());
			proceso.setTimeTrans(processCopy.front().getTimeTrans());
			proceso.setID(processCopy.front().getID());
			proceso.setLote(processCopy.front().getLote());
			processBatch.push_back(proceso);
			processCopy.pop();
		}
		while(!processBatch.empty()){
			//Proceso en ejecucion
			intBan = false;
			errorFlag = false;
			cleanProcess();
			cleanBatch();
			maxTime = processBatch.front().getTimeMax();
			reTime = (processBatch.front().getTimeMax() - processBatch.front().getTimeTrans()); //Tiempo restante
			gotoxy(60,16); cout<<processBatch.front().getID();
			gotoxy(67,18); cout<<processBatch.front().getOperation();
			gotoxy(61,20); cout<<processBatch.front().getTimeMax();
			gotoxy(77,22); cout<<processBatch.front().getTimeTrans(); //Tiempo transcurrido
			gotoxy(73,24); cout<<reTime; 
			//Se imprime Lote Actual
			yPE = 0; //Imprimir procesos de lote actual
			for(int i = 1; i < processBatch.size(); i++){
				gotoxy(4,16+yPE); cout<<processBatch[i].getID();
				gotoxy(15,16+yPE); cout<<processBatch[i].getTimeMax();
				gotoxy(26,16+yPE); cout<<processBatch[i].getTimeTrans();
				yPE+=2;
			}
			processCounter = processBatch.front().getTimeTrans();
			//Actualizador de tiempos
			while((processCounter < maxTime) && (!intBan)){
				if(kbhit()){ //Se presiona una tecla
					tecla = getch();
					switch (tecla){
						case 'i':{ //Interrupción
							intBan = true;
							proceso =  processBatch[0]; //Se guarda proceso en ejecución
							processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
							processBatch.push_back(proceso); //Se coloca al final de la cola del lote
							break;
						}
						case 'e':{ //Error
							errorFlag = true;
							processCounter = maxTime;
							break;
						}	
						case 'p':{ //Pausa
							while(true){ //Se entra en búcle hasta presionar 'c'
								if(kbhit()){
									tecla = getch();
									if(tecla == 'c'){ //Continuar
										break;
									}
								}else{
									continue;
								}	
							}
							break;
						}
						default:
							continue;
					}
				}else{
					sleep(1);
					globalCounter += 1;
					processCounter += 1;
					processBatch.front().setTimeTrans(processCounter); 
					cleanTimes();
					gotoxy(200,6); cout<<globalCounter;
					gotoxy(77,22); cout<<processCounter;
					gotoxy(73,24); cout<<maxTime - processCounter;
				}
			}
			//Proceso terminado
			if(intBan == false){ //No ocurrio interrupción
				gotoxy(140,cordY+1); cout<<processBatch.front().getID();
				gotoxy(164,cordY+1); cout<<processBatch.front().getOperation();
				gotoxy(193,cordY+1); (errorFlag == false) ? cout<<processBatch.front().getResult() : cout<<"ERROR"; //Comprobación si ocurrio error
				processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
				process.pop();
				cordY+=1;
			}
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
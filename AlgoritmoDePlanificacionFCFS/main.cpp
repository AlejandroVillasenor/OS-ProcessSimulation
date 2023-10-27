/*
	Programa 3 - Algoritmo de planificación de procesos FCFS - Sin thread
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	30/09/2023
	-- Archivo de cabecera --
*/
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <conio.h>
#include "process.hpp"
#include "validacion.hpp"
#include "interface.hpp"
#define errmsg "Error: Dato no valido"
using namespace std;

int main(){
	system("title Programa 3 - Algoritmo de planificacion FCFS"); //Configuración consola
	vector<Process> process; //Cola de procesos
	vector<Process> processBatch; //Cola de procesos en memoria principal
	vector<Process> SecondProcess; //Cola de procesos en memeria secundaria
	int numProcess = 0, proRegistered = 0, timeM = 0, ID = 1, operation, timeMax;//Variables registro datos
    string numPro, operating1, operating2, expresion; //Datos procesos
	bool numProcessVal, intBan = false, errorFlag = false, nullProcess = false;; //Validacion, Bandera interrupción, Bandera Error en proceso, Proceso nulo
	float result;//Resultado de operacion
	int memoryProcess = 1; //Procesos actualmente en memoria
	int indexProcess = 0, finishedProcess = 0, indexExP = 0; //Identifica el proceso a continuación
	int globalCounter = 0, processCounter = 0, maxTime = 0, reTime = 0, timeBlocked = 0;//Contadores de tiempo
	int cordY, coordYB, yPE; //Coordenadas en pantalla
	char tecla; //Almacena tecla presionada durante la ejecución de procesos
	// Crear un generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());
	uniform_int_distribution<int> numOperacion(1, 6); //Random numero operacion
	uniform_int_distribution<int> maximumTime(6, 18);  //Random tiempo maximo
    do{
        system("cls");
		cout<<"|| Algoritmo de planificacion FCFS ||"<<endl;
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
			//Opcion de oeracion: 
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
		//Agregar proceso a cola de objetos
		Process job(expresion, result, timeMax, 0, 0, 0, 0, false, 0, 0, 0, ID, false);
		process.push_back(job);
		ID ++;//Aumetar ID
	}
	//Mostrar cola de procesos
	desactivarMaximizar();
	system("mode con: cols=213 lines=50");//Tamaño de consola en pantal la completa
	system("cls");
	Processinterface();//Pantalla de procesos
	desactiveInput();//Desactivar entrada de datos
	gotoxy(73,44); cout<<"Presione una tecla para comenzar";
	getch();
	gotoxy(73,44); cout<<"                                ";
	cordY = 14; //Para ubicar procesos completados
	gotoxy(200,6); cout<<"0"; //Contador global
	processCounter = 0;
	Process proceso(expresion, result, timeMax, 0, 0, 0, 0, false, 0, 0, 0, ID, false); //Instancia del proceso
	while(finishedProcess < numProcess){
		gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
		gotoxy(26,6); cout<<numProcess-(finishedProcess);
		//Se obtiene los procesos para el espacio en memoria de solo 5 procesos
		indexProcess = finishedProcess;
		while(memoryProcess<=5 && (finishedProcess+memoryProcess <= numProcess)){
			//Se extraen los datos
			proceso.setOp(process[indexProcess].getOperation());
			proceso.setResult(process[indexProcess].getResult());
			proceso.setTimeMax(process[indexProcess].getTimeMax());
			proceso.setTimeTrans(process[indexProcess].getTimeTrans());
			proceso.setTimeLle(process[indexProcess].getTimeLle());
			proceso.setTimeFin(process[indexProcess].getTimeFin());
			proceso.setTimeResp(process[indexProcess].getTimeResp());
			proceso.setBanResp(process[indexProcess].getBanResp());
			proceso.setTimeEsp(process[indexProcess].getTimeEsp());
			proceso.setID(process[indexProcess].getID());
			processBatch.push_back(proceso);
			memoryProcess++;
			indexProcess++;
		}
		memoryProcess--; //Ajuste de recorrimiento
		while(!processBatch.empty() || !SecondProcess.empty()){
			errorFlag = false;
			if(!processBatch.empty()){
				gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
				gotoxy(26,6); cout<<numProcess-(finishedProcess+memoryProcess);
				//Proceso en ejecucion
				intBan = false;
				cleanProcess();
				cleanBatch();
				indexExP = processBatch.front().getID()-1; //Se extrae index del proceso que pasa a ejecución
				maxTime = processBatch.front().getTimeMax();
				reTime = (processBatch.front().getTimeMax() - processBatch.front().getTimeTrans()); //Tiempo restante
				if(processBatch.front().getBanResp() == false){ //Tiempo respuesta
					processBatch.front().setTimeResp(globalCounter-(processBatch.front().getTimeLle()));
					processBatch.front().setBanResp(true);//Bandera de tiempo respuesta
					process[indexExP].setTimeResp(processBatch.front().getTimeResp()); //Se actualizan valores vector principal
				}
				gotoxy(60,14); cout<<processBatch.front().getID();//ID
				gotoxy(67,16); cout<<processBatch.front().getOperation();//Operación
				gotoxy(61,18); cout<<processBatch.front().getTimeMax();//Tiempo máximo
				gotoxy(77,20); cout<<processBatch.front().getTimeTrans(); //Tiempo transcurrido
				gotoxy(73,22); cout<<reTime; //Tiempo restante
				//Se imprime procesos listos
				yPE = 0; //Imprimir procesos Listos
				for(int i = 1; i < processBatch.size(); i++){
					gotoxy(4,16+yPE); cout<<processBatch[i].getID();
					gotoxy(15,16+yPE); cout<<processBatch[i].getTimeMax();
					gotoxy(26,16+yPE); cout<<processBatch[i].getTimeTrans();
					yPE+=2;
				}
				processCounter = processBatch.front().getTimeTrans();
			}
			//Actualizador de tiempos
			while((processCounter < maxTime) && (!intBan)){
				if(kbhit()){ //Se presiona una tecla
					tecla = getch();
					switch (tecla){
						case 'i':{ //Interrupción
							if(processBatch.size()>0){
								intBan = true;
								proceso =  processBatch[0]; //Se guarda proceso en ejecución
								SecondProcess.push_back(proceso); //Se agrega proceso a bloqueados
								processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
							}
							if(processBatch.size() == 0){
									nullProcess = true;//Se activa proceso nulo
									intBan = false;
									processCounter = 0;
									cleanProcess();
							}
							break;
						}
						case 'e':{ //Error
							if(!processBatch.empty()){
								errorFlag = true;
								processCounter = maxTime;
							}
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
					cleanTimes();
					if(nullProcess == true){
						if(!processBatch.empty()){
							nullProcess = false;//Se desactiva proceso nulo
							intBan = true;
							processCounter = maxTime;
						}
					}else{
						processCounter++;
						processBatch.front().setTimeTrans(processCounter);
						process[indexExP].setTimeTrans(processCounter);
						gotoxy(73,22); cout<<maxTime - processCounter;
						gotoxy(77,20); cout<<processCounter;
					}
					for(int i = 0; i<SecondProcess.size(); i++){
						timeBlocked = SecondProcess[i].getTimeBlocked();
						gotoxy(4,coordYB); cout<<SecondProcess[i].getID();
						gotoxy(26,coordYB); cout<<SecondProcess[i].getTimeBlocked();
						if(timeBlocked >= 8){
							cleanBlocked();//Se limpia pantalla de procesos bloqueados
							SecondProcess[i].setTimeBlocked(0); //Se resetea el contador
							proceso =  SecondProcess[i]; //Se guarda proceso en ejecución
							processBatch.push_back(proceso); //Se coloca al final de la cola los procesos listos
							//Imprimir procesos Listos
							gotoxy(4,16+yPE); cout<<SecondProcess[i].getID();
							gotoxy(15,16+yPE); cout<<SecondProcess[i].getTimeMax();
							gotoxy(26,16+yPE); cout<<SecondProcess[i].getTimeTrans();
							yPE+=2;
							SecondProcess.erase(SecondProcess.begin()); //Se elimina el proceso que estaba en bloqueado
							//Se vuelve a imprimir procesos bloqueados
							coordYB = 36;
							for(int i = 0; i<SecondProcess.size(); i++){
								gotoxy(4,coordYB); cout<<SecondProcess[i].getID();
								gotoxy(26,coordYB); cout<<SecondProcess[i].getTimeBlocked();
							}
						}
						timeBlocked += 1;
						SecondProcess[i].setTimeBlocked(timeBlocked);
						coordYB += 2;
					}
					gotoxy(200,6); cout<<globalCounter;
					coordYB = 36; //Para ubicar procesos bloqueados
				}
			}
			//Proceso terminado
			if(intBan == false){ //No ocurrio interrupción
				gotoxy(140,cordY+1); cout<<processBatch.front().getID();
				gotoxy(164,cordY+1); cout<<processBatch.front().getOperation();
				//Comprobación si ocurrio error
				gotoxy(193,cordY+1); (errorFlag == false) ? cout<<processBatch.front().getResult() : cout<<"ERROR"; 
				if(errorFlag == true){
					process[indexExP].setBanerror(true);                 	
				}
				process[indexExP].setTimeFin(globalCounter); //Tiempo finalización
				process[indexExP].setTimeRet(globalCounter-process[indexExP].getTimeLle()); //Tiempo retorno
				process[indexExP].setTimeEsp(process[indexExP].getTimeRet()-process[indexExP].getTimeTrans()); //Tiempo espera
				processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
				finishedProcess++;
				memoryProcess--;
				cordY+=1;
				if(finishedProcess+memoryProcess < numProcess){
					process[indexProcess].setTimeLle(globalCounter); //Se establece tiempo llegada 
					processBatch.push_back(process[indexProcess]);
					indexProcess++;
					memoryProcess++;
				}
				if(processBatch.empty() && !SecondProcess.empty()){ //Se activa proceso nulo
					cleanProcess();
					nullProcess = true;
					intBan = false;
					processCounter = 0;
				}
			}
			
		}
	}
	gotoxy(26,6); cout<<string(4,255); gotoxy(26,6); cout<<"0"; //Actualiza contador lotes pendites
	cleanAll();
	gotoxy(73,44); cout<<"Fin de procesamiento";
	getch();
	system("cls");
	ResultTable();//Tabla de resultados
	int yt = 8;
	for(int i = 0; i < process.size(); i++){
		gotoxy(7,yt); cout<<process[i].getID()<<endl;
		gotoxy(25,yt); cout<<process[i].getOperation()<<endl; 
		gotoxy(46,yt); (!process[i].getBanerror()) ? cout<<process[i].getResult() : cout<<"ERROR";//Comprobación si ocurrio error para imprimir resultado
		gotoxy(67,yt); cout<<process[i].getTimeMax()<<endl;
		gotoxy(88,yt); cout<<process[i].getTimeTrans()<<endl;
		gotoxy(109,yt); cout<<process[i].getTimeLle()<<endl;
		gotoxy(130,yt); cout<<process[i].getTimeFin()<<endl;
		gotoxy(151,yt); cout<<process[i].getTimeResp()<<endl;
		gotoxy(172,yt); cout<<process[i].getTimeEsp()<<endl;
		gotoxy(193,yt); cout<<process[i].getTimeRet()<<endl;
		yt+=2;
	}
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
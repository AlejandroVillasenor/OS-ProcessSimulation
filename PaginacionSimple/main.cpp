/*
	Programa 7.  Paginación Simple 
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	19/10/2023
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

//Variables globales
vector<Process> process; //Cola de procesos
string expresion;
float result;//Resultado de operacion
int numProcess = 0, timeMax;

int addProcess(int ID){
	// Crear un generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());
	uniform_int_distribution<int> numOperacion(1, 6); //Random numero operacion
	uniform_int_distribution<int> maximumTime(6, 18);  //Random tiempo maximo
	uniform_int_distribution<int> tamanioProcess(6,26); //Random tamaño proceso
	string operating1, operating2;
	int sizeProcess = 0;
	int operation, quantum;
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
		//Tamanio proceso
		sizeProcess = tamanioProcess(generador);
		//Agregar proceso a cola de objetos
		Process job(expresion, result, timeMax, 0, 0, 0, 0, false, 0, 0, 0, ID, false, 0, sizeProcess, {0,0,0,0,0,0});
		process.push_back(job);
		numProcess++;
	return ++ID;
}

int main(){
	system("title Programa 7. Paginacion Simple"); //Configuración consola
	vector<Process> processBatch; //Cola de procesos en memoria principal
	vector<Process> SecondProcess; //Cola de procesos en memeria secundaria
	vector<Process> endProcess;//Cola de procesos terminados
	vector<int> memory(45,0);//Memoria principal
	//Asignacion de frames de SO
	memory[41] = 5;
	memory[42] = 5;
	memory[43] = 5;
	memory[44] = 5;
	int  proRegistered = 0, timeM = 0, ID = 1;//Variables registro datos
    string numPro, numQuan; //Datos procesos
	bool numProcessVal, numQuanVal, intBan = false, errorFlag = false, nullProcess = false; //Validacion, Bandera interrupción, Bandera Error en proceso, Proceso nulo
	int memoryProcess = 1; //Procesos actualmente en memoria
	int initialProcess = 0, quantum = 0, indexProcess = 0, finishedProcess = 0, indexExP = 0; //Identifica el proceso a continuación
	int globalCounter = 0, processCounter = 0, maxTime = 0, reTime = 0, timeBlocked = 0, timeQuantum = 0;//Contadores de tiempo
	int cordY, coordYB, yPE; //Coordenadas en pantalla
	char tecla; //Almacena tecla presionada durante la ejecución de procesos
	//Frames libres
	int frameslibres = 40;
	int numFramesProcess = 0;
	int residuoFrames = 0;
	int indexFrame = 0;
	//Frames Procesos
	int tamSiguienteProceso = 0;
	int tamProceso = 0;
	int ultimoIndex = 0;
	int idTablaProceso = 0;
	vector<int> framesProceso;
	//Proceso nuevo 
	bool procesoNuevoFrame = false;
	int numProcesosNuevos = 0;
	int indexProcesoNuevo = 0;
    do{
        system("cls");
		cout<<"|| Programa 7. Paginacion Simple ||"<<endl;
        cout<<"Numero de procesos a registrar: ";
        getline(cin, numPro);
        numProcessVal = validatePI(&numPro, 2);
        if(numProcessVal){
            initialProcess = stoi(numPro);
            (initialProcess <= 0 || initialProcess >= 22) ? numProcessVal = false : numProcessVal = true ; 
            if(!numProcessVal){
                cout<<errmsg;
                getch();
			    system("cls");
            }else{
                do{
                    cout<<"Tamanio del Quamtum: ";
                    getline(cin, numQuan);
                    //Validacion del Quantum
                    numQuanVal = validatePI(&numQuan, 2);
                    if(numQuanVal){
                        quantum = stoi(numQuan);
                        (quantum <= 0 || quantum > 10) ? numQuanVal = false : numQuanVal = true ;
                        if(!numQuanVal){
                            cout<<errmsg;
                            getch();
                        }   
                    }
                    system("cls");
                }while(!numQuanVal);
            }
        }else{
            cout<<errmsg;
			getch();
			system("cls");
        }
    }while (numProcessVal == false);
	//Registro de procesos
	while(proRegistered < initialProcess){
		system("cls");
		//Registro de proceso exitoso
		proRegistered+=1;
		ID = addProcess(ID);
	}
	//Mostrar cola de procesos
	desactivarMaximizar();
	system("mode con: cols=213 lines=60");
	system("cls");
	Processinterface();//Pantalla de procesos
	desactiveInput();//Desactivar entrada de datos
	gotoxy(144,44); cout<<"Presione una tecla para comenzar";
	getch();
	gotoxy(174,6);cout<<quantum; //Quantum
	gotoxy(144,44); cout<<"                                ";
	cordY = 14; //Para ubicar procesos completados
	gotoxy(200,6); cout<<"0"; //Contador global
	processCounter = 0;
	Process proceso(expresion, result, timeMax, 0, 0, 0, 0, false, 0, 0, 0, ID, false, 0, 0, {0,0,0,0,0,0}); //Instancia del proceso
	//Imprimir vector de memoria
	for(int i=1; i<=40; i++){
		gotoxy(69,14+i); cout<<"0/5";
        gotoxy(89,14+i); cout<<"-1";
        gotoxy(110,14+i); cout<<"Libre";
	}
	while(finishedProcess < numProcess){
		gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
		gotoxy(26,6); cout<<numProcess-(finishedProcess);
		//Se obtiene los procesos para el espacio en memoria de solo 40 frames
		tamProceso = process[indexProcess].getSize();
		int espacioFrames = frameslibres * 5;
		while ((espacioFrames >= tamProceso) && (memoryProcess <= numProcess)){
			numFramesProcess = 0;
			residuoFrames = 0;
			framesProceso.clear();
			framesProceso.resize(0);
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
			proceso.setSize(process[indexProcess].getSize());
			
			//Tamanio del vector
			numFramesProcess = (process[indexProcess].getSize())/5;
			residuoFrames = (process[indexProcess].getSize())%5;
			if(residuoFrames != 0) numFramesProcess += 1;
			
			//Impresion en pantalla
			if(frameslibres >= numFramesProcess){
				frameslibres -= numFramesProcess;
				while(numFramesProcess){
					for(int i=1; i<=40; i++){
						if(memory[i] == 0){
							gotoxy(69,14+i); cout<<string(72,255);
							gotoxy(89,14+i); cout<<process[indexProcess].getID();
							gotoxy(110,14+i); cout<<"Listo";
							if(numFramesProcess == 1 && residuoFrames != 0){
								gotoxy(69,14+i); cout<<residuoFrames<<"/5";
								memory[i] = residuoFrames;
							}else{
								gotoxy(69,14+i); cout<<"5/5";
								memory[i] = 5;
							}
							framesProceso.push_back(i);
							break;
						}
						
					}
					numFramesProcess--;
				}		
			}
			process[indexProcess].setMemoryIndex(framesProceso);
			proceso.setMemoryIndex(process[indexProcess].getMemoryIndex());
			processBatch.push_back(proceso);
			memoryProcess++;
			indexProcess++;
			tamProceso = process[indexProcess].getSize();
			espacioFrames = frameslibres * 5;
		}
		memoryProcess--; //Ajuste de recorrimiento
		//Comprobacion procesos que no entraron en memoria
		int aux = 0;
		while(memoryProcess + aux < numProcess){
			numProcesosNuevos += 1;
			gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
			gotoxy(26,6); cout<<numProcesosNuevos;
			if(procesoNuevoFrame == false){
				indexProcesoNuevo = memoryProcess;
				procesoNuevoFrame = true;
				gotoxy(90,6); cout<<"   ";
				gotoxy(105,6); cout<<"   ";
				gotoxy(90,6); cout<<process[indexProcesoNuevo].getID();
				gotoxy(105,6); cout<<process[indexProcesoNuevo].getSize();
			}
			aux++;
		}	
		while(!processBatch.empty() || !SecondProcess.empty()){
			errorFlag = false;
			if(!processBatch.empty()){
				gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
				gotoxy(26,6); cout<<numProcesosNuevos;
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
				gotoxy(148,14); cout<<processBatch.front().getID();//ID
				gotoxy(155,16); cout<<processBatch.front().getOperation();//Operación
				gotoxy(149,18); cout<<processBatch.front().getTimeMax();//Tiempo máximo
				gotoxy(165,20); cout<<processBatch.front().getTimeTrans(); //Tiempo transcurrido
				gotoxy(161,22); cout<<reTime; //Tiempo restante
				gotoxy(177,24); cout<<0;
				gotoxy(153,26); cout<<processBatch.front().getSize(); //Tamanio
				//Se cambia estado del proceso en memoria
				framesProceso = processBatch.front().getMemoryIndex();
				for(auto indexP : framesProceso){
					cleanEstadoMemoria(indexP);
					gotoxy(110,14+indexP); cout<<"Ejecucion"; 
				}
				//Se imprime procesos listos
				yPE = 0; //Imprimir procesos Listos
				for(int i = 1; i < processBatch.size(); i++){
					gotoxy(4,15+yPE); cout<<processBatch[i].getID();
					gotoxy(15,15+yPE); cout<<processBatch[i].getTimeMax();
					gotoxy(26,15+yPE); cout<<processBatch[i].getTimeTrans();
					yPE+=1;
				}
				processCounter = processBatch.front().getTimeTrans();
			}
			//Actualizador de tiempos
			while((processCounter < maxTime) && (!intBan)){
				if(kbhit()){ //Se presiona una tecla
					tecla = getch();
					switch (tecla){
						case 'b':{
							//Se muestra tabla BCP
							system("cls");
							BCPTable();
							//Imprirmir proceso en ejecución y listos
							int yt = 8;
							int tiempoRetornoPar = 0, tiempoEspera = 0;
							for(int i = 0; i < processBatch.size(); i++){
								tiempoRetornoPar = globalCounter - processBatch[i].getTimeLle();
								tiempoEspera = tiempoRetornoPar - processBatch[i].getTimeTrans(); 
								gotoxy(3,yt); cout<<processBatch[i].getID();
								gotoxy(11,yt); cout<<processBatch[i].getOperation(); 
								gotoxy(28,yt); cout<<"N/A";//Resultado
								gotoxy(44,yt); cout<<processBatch[i].getTimeMax();
								gotoxy(56,yt); cout<<processBatch[i].getTimeTrans(); 
								gotoxy(77,yt); cout<<processBatch[i].getTimeLle();
								gotoxy(95,yt); cout<<"N/A";//Tiempo finalizacion
								gotoxy(116,yt); (processBatch[i].getBanResp() == false) ? cout<<"N/A" : cout<<processBatch[i].getTimeResp();//Respuesta
								gotoxy(135,yt); cout<<tiempoEspera; //Tiempo espera
								gotoxy(153,yt); cout<<"N/A";//Tiempo de retorno
								gotoxy(170,yt); cout<<(processBatch[i].getTimeMax() - processBatch[i].getTimeTrans());//Restante
								gotoxy(186,yt); cout<<"N/A";//Bloqueado
								gotoxy(202,yt); (i==0) ? cout<<"Ejecucion" : cout<<"Listo";//Estado
								yt+=2;
							}
							//Imprimir procesos bloqueados 
							for(int i = 0; i < SecondProcess.size(); i++){
								tiempoRetornoPar = globalCounter - SecondProcess[i].getTimeLle();
								tiempoEspera = tiempoRetornoPar - SecondProcess[i].getTimeTrans(); 
								gotoxy(3,yt); cout<<SecondProcess[i].getID(); 
								gotoxy(11,yt); cout<<SecondProcess[i].getOperation(); 
								gotoxy(28,yt); cout<<"N/A";//Resultado   
								gotoxy(44,yt); cout<<SecondProcess[i].getTimeMax();
								gotoxy(56,yt); cout<<SecondProcess[i].getTimeTrans(); 
								gotoxy(77,yt); cout<<SecondProcess[i].getTimeLle(); 
								gotoxy(95,yt); cout<<"N/A";//Tiempo finalizacion  
								gotoxy(116,yt);	cout<<SecondProcess[i].getTimeResp();//Respuesta 
								gotoxy(135,yt); cout<<tiempoEspera; //Tiempo espera 
								gotoxy(153,yt); cout<<"N/A";//Tiempo de retorno  
								gotoxy(170,yt); cout<<(SecondProcess[i].getTimeMax() - SecondProcess[i].getTimeTrans());//Restante
								gotoxy(186,yt); cout<<(8-SecondProcess[i].getTimeBlocked());//Bloqueado 
								gotoxy(202,yt); cout<<"Bloqueado";//Estado 
								yt+=2;
							}
							//Imprimir procesos nuevos
							int indiceNuevos = indexProcess;
							for(int i = indiceNuevos; i < process.size(); i++){
								gotoxy(3,yt); cout<<process[i].getID(); 
								gotoxy(11,yt); cout<<process[i].getOperation(); 
								gotoxy(28,yt); cout<<"N/A";//Resultado   
								gotoxy(44,yt); cout<<process[i].getTimeMax();
								gotoxy(56,yt); cout<<"N/A";//Transcurrido
								gotoxy(77,yt); cout<<"N/A";//Llegada
								gotoxy(95,yt); cout<<"N/A";//Tiempo finalizacion  
								gotoxy(116,yt);	cout<<"N/A";//Respuesta 
								gotoxy(135,yt); cout<<"N/A"; //Tiempo espera 
								gotoxy(153,yt); cout<<"N/A";//Tiempo de retorno  
								gotoxy(170,yt); cout<<"N/A";//Restante
								gotoxy(186,yt); cout<<"N/A";//Bloqueado 
								gotoxy(202,yt); cout<<"Nuevo";//Estado 
								yt+=2;
							}
							//Imprimir procesos finalizados
							for(int i = 0; i < endProcess.size(); i++){
								gotoxy(3,yt); cout<<endProcess[i].getID()<<endl;
								gotoxy(11,yt); cout<<endProcess[i].getOperation()<<endl; 
								gotoxy(28,yt); (!endProcess[i].getBanerror()) ? cout<<endProcess[i].getResult() : cout<<"ERROR";//Comprobación si ocurrio error para imprimir resultado
								gotoxy(44,yt); cout<<endProcess[i].getTimeMax()<<endl;
								gotoxy(56,yt); cout<<endProcess[i].getTimeTrans()<<endl;
								gotoxy(77,yt); cout<<endProcess[i].getTimeLle()<<endl;
								gotoxy(95,yt); cout<<endProcess[i].getTimeFin()<<endl;
								gotoxy(116,yt); cout<<endProcess[i].getTimeResp()<<endl;
								gotoxy(135,yt); cout<<endProcess[i].getTimeEsp()<<endl;
								gotoxy(153,yt); cout<<endProcess[i].getTimeRet()<<endl;
								gotoxy(170,yt); cout<<"N/A";//Restante
								gotoxy(186,yt); cout<<"N/A";//Bloqueado
								gotoxy(202,yt); cout<<"Hecho";//Estado
								yt+=2;
							}
							while(true){ //Se entra en búcle hasta presionar 'c'
								if(kbhit()){
									tecla = getch();
									if(tecla == 'c'){ //Continuar
										system("cls");
										//Se vuelve a imprimir la interfaz
										Processinterface();//Pantalla de procesos
										//Tiempo global
										gotoxy(200,6); cout<<globalCounter;
										//Procesos nuevos
										gotoxy(26,6); cout<<string(4,255); 
										gotoxy(26,6); cout<<numProcess-(finishedProcess+memoryProcess);
										//Proceso en ejecución
										gotoxy(148,14); cout<<processBatch.front().getID();//ID
										gotoxy(155,16); cout<<processBatch.front().getOperation();//Operación
										gotoxy(149,18); cout<<processBatch.front().getTimeMax();//Tiempo máximo
										gotoxy(165,20); cout<<processBatch.front().getTimeTrans(); //Tiempo transcurrido
										gotoxy(161,22); cout<<reTime; //Tiempo restante
										gotoxy(177,24); cout<<timeQuantum;
										gotoxy(153,26); cout<<processBatch.front().getSize(); //Tamanio
										//Procesos en listo
										yPE = 0; //Imprimir procesos Listos
										for(int i = 1; i < processBatch.size(); i++){
											gotoxy(4,15+yPE); cout<<processBatch[i].getID();
											gotoxy(15,15+yPE); cout<<processBatch[i].getTimeMax();
											gotoxy(26,15+yPE); cout<<processBatch[i].getTimeTrans();
											yPE+=1;
										}
										//Procesos en bloqueado
										for(int i = 0; i<SecondProcess.size(); i++){
											gotoxy(126,15+i); cout<<SecondProcess[i].getID();
											gotoxy(133,15+i); cout<<SecondProcess[i].getTimeBlocked();
										}
										//Procesos finalizados
										cordY = 15;
										for(int i = 0; i<endProcess.size(); i++){
											gotoxy(181,cordY); cout<<endProcess[i].getID();
											gotoxy(186,cordY); cout<<endProcess[i].getOperation();
											//Comprobación si ocurrio error
											gotoxy(201,cordY); (endProcess[i].getBanerror() == false) ? cout<<endProcess[i].getResult() : cout<<"ERROR"; 
											cordY+=1;
										}
										//Arreglar valor de Y
										cordY -= 1;
										//Se imprime tabla de paginacion
										//Frames libres
										for(int i=1; i<=40; i++){
											if(memory[i] == 0){
												gotoxy(69,14+i); cout<<"0/5";
												gotoxy(89,14+i); cout<<"-1";
												gotoxy(110,14+i); cout<<"Libre";
											}
										}
										//Frames ocupados
										//Procesos listos y en ejecucion
										for(auto procesoVector : processBatch){
											framesProceso = procesoVector.getMemoryIndex();
											idTablaProceso = procesoVector.getID();
											tamProceso = procesoVector.getSize();
											residuoFrames = tamProceso%5;
											ultimoIndex = framesProceso[framesProceso.back()]; 
											for(auto frame : framesProceso){
												gotoxy(89,14+frame); cout<<idTablaProceso;
												gotoxy(110,14+frame); (idTablaProceso == processBatch.front().getID()) ? cout<<"Ejecucion" : cout<<"Listo";
												gotoxy(69,14+frame);
												(frame != ultimoIndex) ? cout<<"5/5" : cout<<memory[frame]<<"/5"; ; 
											}
										}
										//Procesos bloqueados
										for(auto processVector : SecondProcess){
											framesProceso = processVector.getMemoryIndex();
											idTablaProceso = processVector.getID();
											tamProceso = processVector.getSize();
											residuoFrames = tamProceso%5;
											ultimoIndex = memory[framesProceso.back()];
											for(auto frame : framesProceso){
												gotoxy(89,14+frame); cout<<idTablaProceso;
												gotoxy(110,14+frame); cout<<"Bloqueado";
												gotoxy(69,14+frame); (frame != ultimoIndex) ? cout<<"5/5" : cout<<memory[frame]<<"/5"; ;
											}
										}
										//Impresion de idx y tamanio del siguiente proceso
										if(procesoNuevoFrame == true){
											gotoxy(90,6); cout<<"   ";
											gotoxy(105,6); cout<<"   ";
											gotoxy(90,6); cout<<process[indexProcesoNuevo].getID();
											gotoxy(105,6); cout<<process[indexProcesoNuevo].getSize();
										}	
										break;
									}
								}else{
									continue;
								}	
							}
							break;
						}
						case 'i':{ //Interrupción
							if(processBatch.size()>0){
								intBan = true;
								proceso =  processBatch[0]; //Se guarda proceso en ejecución
								//Se cambia estado en memoria
								framesProceso = processBatch.front().getMemoryIndex();
								for(auto indexP : framesProceso){
									cleanEstadoMemoria(indexP);
									gotoxy(110,14+indexP); cout<<"Bloqueado"; 
								}
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
						case 'n':{
							ID = addProcess(ID);
							numFramesProcess = (process[indexProcess].getSize())/5;
							residuoFrames = (process[indexProcess].getSize())%5;
							if(residuoFrames != 0) numFramesProcess += 1;
							//Cabe en memoria
							if(frameslibres >= numFramesProcess){
								//Tamanio del vector
								framesProceso.clear();
								framesProceso.resize(0);
								//Impresion en pantalla
								frameslibres -= numFramesProcess;
								while(numFramesProcess){
									for(int i=1; i<=40; i++){
										if(memory[i] == 0){
											gotoxy(69,14+i); cout<<string(72,255);
											gotoxy(89,14+i); cout<<process[indexProcess].getID();
											gotoxy(110,14+i); cout<<"Listo";
											if(numFramesProcess == 1 && residuoFrames != 0){
												gotoxy(69,14+i); cout<<residuoFrames<<"/5";
												memory[i] = residuoFrames;
											}else{
												gotoxy(69,14+i); cout<<"5/5";
												memory[i] = 5;
											}
											framesProceso.push_back(i);
											break;
										}
										
									}
									numFramesProcess--;
								}	
								process[indexProcess].setMemoryIndex(framesProceso);
								process[indexProcess].setTimeLle(globalCounter); //Se establece tiempo llegada 
								processBatch.push_back(process[indexProcess]);
								indexProcess++;
								memoryProcess++;
								if(memoryProcess == 1 || (processBatch.size() == 1 &&  !SecondProcess.empty())){
									//Proceso en ejecucion
									intBan = false;
									cleanProcess();
									indexExP = processBatch.front().getID()-1; //Se extrae index del proceso que pasa a ejecución
									maxTime = processBatch.front().getTimeMax();
									reTime = (processBatch.front().getTimeMax() - processBatch.front().getTimeTrans()); //Tiempo restante
									if(processBatch.front().getBanResp() == false){ //Tiempo respuesta
										processBatch.front().setTimeResp(globalCounter-(processBatch.front().getTimeLle()));
										processBatch.front().setBanResp(true);//Bandera de tiempo respuesta
										process[indexExP].setTimeResp(processBatch.front().getTimeResp()); //Se actualizan valores vector principal
									}
									gotoxy(148,14); cout<<processBatch.front().getID();//ID
									gotoxy(155,16); cout<<processBatch.front().getOperation();//Operación
									gotoxy(149,18); cout<<processBatch.front().getTimeMax();//Tiempo máximo
									gotoxy(165,20); cout<<processBatch.front().getTimeTrans(); //Tiempo transcurrido
									gotoxy(161,22); cout<<reTime; //Tiempo restante
									processCounter = processBatch.front().getTimeTrans();
									//Se cambia estado en memoria
									framesProceso = processBatch.front().getMemoryIndex();
									for(auto indexP : framesProceso){
										cleanEstadoMemoria(indexP);
										gotoxy(110,14+indexP); cout<<"Ejecucion"; 
									}
								}
								else{
									cleanBatch();
									yPE = 0; //Imprimir procesos Listos
									for(int i = 1; i < processBatch.size(); i++){
										gotoxy(4,15+yPE); cout<<processBatch[i].getID();
										gotoxy(15,15+yPE); cout<<processBatch[i].getTimeMax();
										gotoxy(26,15+yPE); cout<<processBatch[i].getTimeTrans();
										yPE+=1;
									}
								}
							}else{
								numProcesosNuevos += 1;
								gotoxy(26,6); cout<<string(4,255); //Procesos Nuevos
								gotoxy(26,6); cout<<numProcesosNuevos;
								if(numProcesosNuevos == 1){
									if(indexProcesoNuevo == 0){
										indexProcesoNuevo = process.size()-1;
									}else{
										indexProcesoNuevo += 1;
									} 
								}else{
									if(procesoNuevoFrame == false) indexProcesoNuevo += 1;
								}
								//Se imprimen datos del nuevo proximo
								if(procesoNuevoFrame == false){
									procesoNuevoFrame = true;
									gotoxy(90,6); cout<<"   ";
									gotoxy(105,6); cout<<"   ";
									gotoxy(90,6); cout<<process[indexProcesoNuevo].getID();
									gotoxy(105,6); cout<<process[indexProcesoNuevo].getSize();
								}
								
							}
							break;
						}
						case 't':{ //Tabla de paginas
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
						timeQuantum++;
						processBatch.front().setTimeTrans(processCounter);
						process[indexExP].setTimeTrans(processCounter);
						processBatch.front().setQuantum(processCounter);
						process[indexExP].setQuantum(processCounter);
						gotoxy(165,20); cout<<processCounter;
						gotoxy(161,22); cout<<"    ";
						gotoxy(161,22); cout<<maxTime - processCounter;
						gotoxy(177,24); cout<<timeQuantum;
						gotoxy(153,26); cout<<processBatch.front().getSize(); //Tamanio
					}
					//Procesos bloqueados
					for(int i = 0; i<SecondProcess.size(); i++){
						timeBlocked = SecondProcess[i].getTimeBlocked();
						gotoxy(126,coordYB); cout<<SecondProcess[i].getID();
						gotoxy(133,coordYB); cout<<SecondProcess[i].getTimeBlocked();
						if(timeBlocked >= 8){
							cleanBlocked();//Se limpia pantalla de procesos bloqueados
							SecondProcess[i].setTimeBlocked(0); //Se resetea el contador
							//Se cambia estado en memoria
							framesProceso = SecondProcess[i].getMemoryIndex();
							for(auto indexP : framesProceso){
								cleanEstadoMemoria(indexP);
								gotoxy(110,14+indexP); cout<<"Listo"; 
							}
							proceso =  SecondProcess[i]; //Se guarda proceso en ejecución
							processBatch.push_back(proceso); //Se coloca al final de la cola los procesos listos
							//Imprimir procesos Listos
							gotoxy(4,15+yPE); cout<<SecondProcess[i].getID();
							gotoxy(15,15+yPE); cout<<SecondProcess[i].getTimeMax();
							gotoxy(26,15+yPE); cout<<SecondProcess[i].getTimeTrans();
							yPE+=1;
							SecondProcess.erase(SecondProcess.begin()); //Se elimina el proceso que estaba en bloqueado
							//Se vuelve a imprimir procesos bloqueados
							for(int i = 0; i<SecondProcess.size(); i++){
								gotoxy(126,15+i); cout<<SecondProcess[i].getID();
								gotoxy(133,15+i); cout<<SecondProcess[i].getTimeBlocked();
							}
						}
						timeBlocked += 1;
						SecondProcess[i].setTimeBlocked(timeBlocked);
						coordYB += 1;
					}
					gotoxy(200,6); cout<<globalCounter;
					coordYB = 15; //Para ubicar procesos bloqueados
					//Comprobación valor del quantum
					if(timeQuantum == quantum){
						if(processBatch.size()>0){
								intBan = true;
								timeQuantum = 0;
								processBatch.front().setQuantum(0); //Se retea valor del Quantum en la cola de ejecución
								//Se cambia estado en memoria
								framesProceso = processBatch.front().getMemoryIndex();
								for(auto indexP : framesProceso){
									cleanEstadoMemoria(indexP);
									gotoxy(110,14+indexP); cout<<"Listo"; 
								}
								proceso =  processBatch[0]; //Se guarda proceso en ejecución
								processBatch.push_back(proceso); //Se agrega proceso a la cola 
								processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
						}		processBatch[indexExP].setQuantum(0);//Reseteamos el valor del Quantum en la cola de procesos
					}			
				}
			}
			//Proceso terminado
			if(intBan == false){ //No ocurrio interrupción
				gotoxy(181,cordY+1); cout<<processBatch.front().getID();
				gotoxy(186,cordY+1); cout<<processBatch.front().getOperation();
				//Comprobación si ocurrio error
				gotoxy(201,cordY+1); (errorFlag == false) ? cout<<processBatch.front().getResult() : cout<<"ERROR"; 
				if(errorFlag == true){
					process[indexExP].setBanerror(true);                 	
				}
				process[indexExP].setTimeFin(globalCounter); //Tiempo finalización
				process[indexExP].setTimeRet(globalCounter-process[indexExP].getTimeLle()); //Tiempo retorno
				process[indexExP].setTimeEsp(process[indexExP].getTimeRet()-process[indexExP].getTimeTrans()); //Tiempo espera
				proceso =  process[indexExP]; 
				endProcess.push_back(proceso); //Se agreaga proceso a vector de finalizado
				//Se cambia estado en memoria
				framesProceso = processBatch.front().getMemoryIndex();
				//Se liberan frames que ocupaba el proceso
				for(auto indexP : framesProceso){
					cleanMarcoMemoria(indexP);
					gotoxy(69,14+indexP); cout<<"0/5";
					gotoxy(89,14+indexP); cout<<"-1";
					gotoxy(110,14+indexP); cout<<"Libre";
					memory[indexP] = 0;
				}
				numFramesProcess = (processBatch.front().getSize())/5;
				residuoFrames = (processBatch.front().getSize())%5;
				if(residuoFrames != 0) numFramesProcess += 1;
				frameslibres += numFramesProcess; 
				processBatch.erase(processBatch.begin()); //Se elimina el proceso que estaba ejecución
				finishedProcess++;
				memoryProcess--;
				cordY+=1;
				//Paso de proceso nuevo a listo
				tamProceso = process[indexProcess].getSize();
				int espacioFrames = frameslibres * 5;
				if( (espacioFrames >= tamProceso) && (finishedProcess+memoryProcess < numProcess)){
					process[indexProcess].setTimeLle(globalCounter); //Se establece tiempo llegada 
					//Parte memoria
					//Tamanio del vector
					framesProceso.clear();
					framesProceso.resize(0);
					numFramesProcess = (process[indexProcess].getSize())/5;
					residuoFrames = (process[indexProcess].getSize())%5;
					if(residuoFrames != 0) numFramesProcess += 1;
					//Impresion en pantalla
					if(frameslibres >= numFramesProcess){
						frameslibres -= numFramesProcess;
						while(numFramesProcess){
							for(int i=1; i<=40; i++){
								if(memory[i] == 0){
									gotoxy(69,14+i); cout<<string(72,255);
									gotoxy(89,14+i); cout<<process[indexProcess].getID();
									gotoxy(110,14+i); cout<<"Listo";
									if(numFramesProcess == 1 && residuoFrames != 0){
										gotoxy(69,14+i); cout<<residuoFrames<<"/5";
										memory[i] = residuoFrames;
									}else{
										gotoxy(69,14+i); cout<<"5/5";
										memory[i] = 5;
									}
									framesProceso.push_back(i);
									break;
								}
								
							}
							numFramesProcess--;
						}		
					}
					process[indexProcess].setMemoryIndex(framesProceso);
					processBatch.push_back(process[indexProcess]);
					indexProcess++;
					memoryProcess++;
					//Num Procesos nuevos
					gotoxy(90,6); cout<<"   ";
					gotoxy(105,6); cout<<"   ";
					numProcesosNuevos -= 1;
					procesoNuevoFrame = false;
					if(numProcesosNuevos >= 1){
						procesoNuevoFrame = true;
						indexProcesoNuevo += 1;
						gotoxy(90,6); cout<<process[indexProcesoNuevo].getID();
						gotoxy(105,6); cout<<process[indexProcesoNuevo].getSize();
					}
					if(numProcesosNuevos == 0){
						gotoxy(90,6); cout<<"   ";
						gotoxy(105,6); cout<<"   ";
					}
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
	gotoxy(144,44); cout<<"Fin de procesamiento";
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
	gotoxy(144,44); cout<<"                                ";
	gotoxy(144,44); cout<<"Presione una tecla para salir";
	getch();
	system("cls");
	return 0;
}
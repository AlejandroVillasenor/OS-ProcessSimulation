/*
	Programa 5 - Productor-Consumidor
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	27/10/2023
	-- Archivo de cabecera --
*/
#include <bits/stdc++.h>
#include "interface.hpp"//Interface header
#include <conio.h>
#include <thread>
#include <unistd.h>
using namespace std;

//Global variables
int squaresAvailable = 20;
int indexProducer = 0;
int indexConsumer = 0;
int turn;
bool active = true;
bool sleepConsumer = false, sleepProducer = false;
bool banConsumer = false, banProducer = false;

//Random generators
random_device rd;
mt19937 generador(rd());

//Buffer
vector<int> spaces(20, 0);

//Semaphores
bool producerEntry = false; //Process 0 turn 1
bool consumerEntry = false; //Process 1 turn 0

uniform_int_distribution<int> products(4, 7);
uniform_int_distribution<int> nums(10, 99);
uniform_int_distribution<int> timeSlept(2, 5);

int zeroSerch(){//Function to find the first 0
	int idx = 0;
	for(int i = indexProducer; i < 20; i++){
		if(spaces[i] == 0){
			idx = i;
			indexProducer = idx;
			if (indexProducer == 19) indexProducer = 0;
			break;
		}
	}
	return idx;
}
int firstElement(){//Function to find the first element 
	int idx = 0;
	for(int i = indexConsumer; i < 20; i++){
		if(spaces[i] != 0){
			idx = i;
			break;
		}
	}
	return idx;
}

void Producer(){
	using namespace std::literals::chrono_literals;
	int numProduced = 0;
	int produced = 0, numgen = 0;
	int timeSleep = 0;
	int pos;
	while(active){
		producerEntry = true;
		sleepProducer = false;
        while (consumerEntry && active) {
            if (turn == 1){
                producerEntry = false;
                while(turn == 1 && active){
                    //Wait
                }
                producerEntry = true;
            }
        }
        //Critical Section 4 to 7  
		banProducer = false; //Flag waiting
		gotoxy(28,13); cout<<string(15,255);
		gotoxy(28,13); cout<<" Produciendo";
		numProduced = products(generador);
        while(produced<numProduced && active){
			//State of the other thread
			if(!sleepConsumer & !banConsumer){
				banConsumer = true;
				gotoxy(186,13); cout<<"            ";
				gotoxy(186,13); cout<<" Despierto";
			}
			if(squaresAvailable == 0) break;
			if(indexProducer > 19) indexProducer = 0;
			pos = zeroSerch();
			numgen = nums(generador);
			gotoxy(58+(pos*5),18); cout<<numgen;
			spaces[pos]=numgen;
			indexProducer = pos;
			squaresAvailable -= 1;
			produced++;
			sleep(1);
		}
		indexProducer++;
        // No Critical Section
		sleepProducer =  true;
		gotoxy(28,13); cout<<string(15,255);
		gotoxy(28,13); cout<<" Durmiendo";
        turn = 1;
        producerEntry = false;
		produced = 0;
		timeSleep = timeSlept(generador);
		this_thread::sleep_for(std::chrono::seconds(timeSleep));
	}
}

void Consumer(){
	using namespace std::literals::chrono_literals;
	int numEaten = 0;
	int eat = 0;
	int timeSleep = 0;
	int pos;

	while(active){
		consumerEntry = true;
		sleepConsumer = false;
        while (producerEntry && active) {
            if (turn == 0){
                consumerEntry = false;
                while(turn == 0 && active){
                    //Wait

                }
                consumerEntry = true;
            }
        }
		//Critical Section 4 to 7  
		banConsumer = false; //flag waiting
		numEaten = products(generador);
		gotoxy(186,13); cout<<string(15,255);
		gotoxy(186,13); cout<<" Consumiendo";
        while(eat<numEaten && active){
			//State of the other thread
			if(!sleepProducer & !banProducer){
				banProducer = true;
				gotoxy(28,13); cout<<string(15,255);
				gotoxy(28,13); cout<<" Despierto";
			}
			if(squaresAvailable == 20) break;
			if(indexConsumer > 19) indexConsumer = 0;
			pos = firstElement();
			gotoxy(58+(pos*5),18); cout<<"  ";
			spaces[pos] = 0;
			indexConsumer = pos;
			squaresAvailable += 1;
			eat++;
			sleep(1);
		}
		indexConsumer++;
        // No Critical Section
		sleepConsumer = true;
		gotoxy(186,13); cout<<string(15,255);
		gotoxy(186,13); cout<<" Durmiendo";
        turn = 0;
        consumerEntry = false;
		eat = 0;
		timeSleep = timeSlept(generador);
		this_thread::sleep_for(std::chrono::seconds(timeSleep));
	}
}

int main(){
	char key;
    system("title Programa 5 - Productor-Consumidor");
    desactivarMaximizar();
	system("mode con: cols=213 lines=50");//Console size as fullscreen
	system("cls");
	PCinterface();
    desactiveInput();
	cleansquares();
	gotoxy(91,44); cout<<"Presione una tecla para comenzar";
	getch();
	gotoxy(91,44); cout<<string(35,255);
	gotoxy(91,44); cout<<"Presione ESC para salir";
    
	//Start the threads
	thread prodThread(Producer);
    thread consThread(Consumer);
	turn = 1;
	while(true){
		if(kbhit()){
			key = getch();
			if (key == 27){ // 27 is the ASCII code for key ESC
				active = false;
				break;
			} 
                
		}
	}
	prodThread.join();
	consThread.join();
	//End of the program
    system("cls");
	cout<<"~Gracias por usar el programa\n\n";
	cout<<"Realizado por:\n";
	cout<<"- Villasenor Rivas Alejandro Rodrigo | 218414783"<<endl;
	cout<<"- Zuniga Lozano Racso Siseneg | 221977551"<<endl;
	gotoxy(73,44); cout<<string(35,255);
	gotoxy(73,44); cout<<"Presione una tecla para salir";
	getch();
	system("cls");
	return 0;
}

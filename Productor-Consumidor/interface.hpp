/*
	Programa 5 - Productor-Consumidor
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	27/10/2023
	-- Archivo de cabecera --
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
using namespace std;
#define color SetConsoleTextAttribute //Cambiar color de consola

void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
} 

//Activar y Desactivar entrada
void desactiveInput(){
	// Ocultar cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void activeInput(){
	//Volver a mostrar el cursor
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//Funcion que desactiva las opciones de cambiar aspecto (tamano) de la ventana.
void desactivarMaximizar(){	
	HWND consoleWindow; 
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );
}
//Funcion para dibujar un ascii art para productor
void producer(int x, int y){
    gotoxy(x,y);cout << "   .----------------." << endl;
    gotoxy(x,y+1);cout << "  (c)       -      (c)" << endl;
    gotoxy(x,y+2);cout << "   |               |" << endl;
    gotoxy(x,y+3);cout << "   |               |" << endl;
    gotoxy(x,y+4);cout << "   |===============|" << endl;
    gotoxy(x,y+5);cout << "   _________________" << endl;
    gotoxy(x,y+6);cout << "  / ~~~~~     ~~~~~ \\" << endl;
    gotoxy(x,y+7);cout << " /|     |     |\\" << endl;
    gotoxy(x,y+8);cout << " W   ---  / \\  ---   W" << endl;
    gotoxy(x,y+9);cout << " \\.      |o o|      ./" << endl;
    gotoxy(x,y+10);cout << "  |                 |" << endl;
    gotoxy(x,y+11);cout << "  \\    #########    /" << endl;
    gotoxy(x,y+12);cout << "   \\  ## ----- ##  /" << endl;
    gotoxy(x,y+13);cout << "    \\##         ##/" << endl;
    gotoxy(x,y+14);cout << "     \\_____v_____/" << endl;
}
//Funcion para dibujar un ascii art para consumidor
void consumer(int x, int y){
    gotoxy(x,y);cout << "                             |\\ /| /|_/|" << endl;
    gotoxy(x,y+1);cout << "                          |\\||-|\\||-/|/|" << endl;
    gotoxy(x,y+2);cout << "                           \\\\|\\|//||///" << endl;
    gotoxy(x,y+3);cout << "          _..----.._       |\\/\\||//||||" << endl;
    gotoxy(x,y+4);cout << "        .'     o    '.     |||\\\\|/\\\\ ||" << endl;
    gotoxy(x,y+5);cout << "       /   o       o  \\    | './\\_/.' |" << endl;
    gotoxy(x,y+6);cout << "      |o        o     o|   |          |" << endl;
    gotoxy(x,y+7);cout << "      /'-.._o     __.-'\\   |          |" << endl;
    gotoxy(x,y+8);cout << "      \\      `````     /   |          |" << endl;
    gotoxy(x,y+9);cout << "      |``--........--'`|    '.______.'" << endl;
    gotoxy(x,y+10);cout << "       \\              /" << endl;
    gotoxy(x,y+11);cout << "        `'----------'`" << endl;
}

void PCinterface(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //cols=213 lines=50"
    //Lineas horizontales
    color(hConsole, 4);
    gotoxy(0,0); cout<<string(213,223);
    gotoxy(0,4); cout<<string(213,220);
    //Lineas verticales amarillas
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<" Productor-Consumidor ";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 15);

    //Cuadros
    //Lineas horizontales
    gotoxy(56,16); cout<<string(101,219);
    gotoxy(56,20); cout<<string(101,219);
    //Lineas verticales
    for(int i = 0; i<=20; i++){
       gotoxy(56+(i*5),17); cout<<string(1,219); 
       gotoxy(56+(i*5),18); cout<<string(1,219);  
       gotoxy(56+(i*5),19); cout<<string(1,219);    
    }
    //Enumercion de cuadros
    for(int i = 0; i<20; i++){
        gotoxy(58+(i*5),22);
        (i<9) ? cout<<"0"<<i+1 : cout<<i+1;
    }
    //Titulos
    gotoxy(21,11); cout<<"Productor";
    gotoxy(21,13); cout<<"Estado:";
    gotoxy(179,11); cout<<"Consumidor";
    gotoxy(179,13); cout<<"Estado:";
    //Ascii art
    producer(13,25);
    consumer(151,28);
    
}

void cleansquares(){
    for(int i = 0; i<20; i++){
       gotoxy(57+(i*5),17); cout<<string(4,255); 
       gotoxy(57+(i*5),18); cout<<string(4,255);  
       gotoxy(57+(i*5),19); cout<<string(4,255);
         
    }
}



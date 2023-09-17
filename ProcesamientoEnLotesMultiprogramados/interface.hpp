/*
	Programa 2 - Procesamiento por lotes multiprogramados
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zúñiga Lozano Racso Siseneg
	17/09/2023
    -- Archivo para la interfaz gráfica --
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

void Processinterface(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //cols=213 lines=50"
    //Lineas horizontales
    color(hConsole, 17);
    gotoxy(0,0); cout<<string(213,223);
    gotoxy(0,4); cout<<string(213,220);
    gotoxy(0,8); cout<<string(213,223);
    gotoxy(0,12); cout<<string(213,220);
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<"Procesamiento en lotes";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 192);
    gotoxy(0,5); cout<<string(213,255);
    gotoxy(0,6); cout<<string(213,255);
    gotoxy(4,6); cout<<"No. Lotes pendientes: "; 
    gotoxy(190,6); cout<<"Contador: ";
    gotoxy(0,7); cout<<string(213,255);
    //Subtitulos
    color(hConsole, 208);
    gotoxy(0,9); cout<<string(213,255);
    gotoxy(0,10); cout<<string(213,255);
    gotoxy(0,11); cout<<string(213,255);
    gotoxy(15,10);cout<<"Lote actual";
    gotoxy(74,10); cout<<"Proceso en ejecucion";
    gotoxy(165,10); cout<<"Terminados";
    color(hConsole, 15);
    //Campos
    //1 Batch
    gotoxy(4,14); cout<<"ID"; 
    gotoxy(15,14);cout<<"TME";
    gotoxy(26,14); cout<<"T.TRANS";
    
    //2 Process
    gotoxy(56,14); cout<<"Nombre: ";
    gotoxy(56,16); cout<<"ID: ";
    gotoxy(56,18); cout<<"Operacion: ";
    gotoxy(56,20); cout<<"TME: ";
    gotoxy(56,22); cout<<"Tiempo transcurrido: ";
    gotoxy(56,24); cout<<"Tiempo restante: ";
    //3 Finished
    gotoxy(140,14); cout<<"ID";
    gotoxy(164,14); cout<<"Operacion";
    gotoxy(193,14); cout<<"Resultado";

    color(hConsole, 17);
    //Lineas verticales
    for(int y=8; y<13; y++){
        gotoxy(42,y); cout<<char(219);
        gotoxy(127,y); cout<<char(219);
    }
    color(hConsole, 15);
}
void cleanTimes(){
    gotoxy(200,6); cout<<string(6,255);
    gotoxy(77,22); cout<<string(6,255);
    gotoxy(73,24); cout<<string(6,255);
}

void cleanProcess(){//Limpiar proceso en ejecucion
    gotoxy(64,14); cout<<string(60,255);
    gotoxy(60,16); cout<<string(20,255);
    gotoxy(67,18); cout<<string(20,255);
    gotoxy(61,20); cout<<string(20,255);
    gotoxy(77,22); cout<<string(20,255);
    gotoxy(73,24); cout<<string(20,255);
}
void cleanBatch(){//Limpiar lote actual
    for(int y=16; y<50; y++){
        gotoxy(4,y); cout<<string(20,255);
        gotoxy(20,y); cout<<string(20,255);
    }
}
void cleanAll(){//lIMPIAR TODO
    cleanProcess();
    cleanBatch();
}


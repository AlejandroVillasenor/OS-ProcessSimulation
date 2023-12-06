/*
	Programa 6 - Algoritmo de planificacion Round-Robin
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	15/10/2023
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

void Processinterface(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //cols=213 lines=50"
    //Lineas horizontales
    color(hConsole, 17);
    gotoxy(0,0); cout<<string(213,223);
    gotoxy(0,4); cout<<string(213,220);
    gotoxy(0,8); cout<<string(213,223);
    gotoxy(0,12); cout<<string(213,220);
    gotoxy(0,28); cout<<string(42,220); //aaa
    gotoxy(0,32); cout<<string(42,220); //aaa
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<"      Round Robin      ";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 192);
    gotoxy(0,5); cout<<string(213,255);
    gotoxy(0,6); cout<<string(213,255);
    gotoxy(0,29); cout<<string(42,255); //aa
    gotoxy(0,30); cout<<string(42,255); //aa
    gotoxy(4,6); cout<<"No. Procesos Nuevos: ";
    gotoxy(165,6); cout<<"Quantum: ";
    gotoxy(190,6); cout<<"Contador: ";
    gotoxy(15,30);cout<<"Bloqueados ";
    gotoxy(0,7); cout<<string(213,255);
    gotoxy(0,31); cout<<string(42,255); //aa
    //Subtitulos
    color(hConsole, 208);
    gotoxy(0,9); cout<<string(213,255);
    gotoxy(0,10); cout<<string(213,255);
    gotoxy(0,11); cout<<string(213,255);
    gotoxy(15,10);cout<<"  Listos   ";
    gotoxy(74,10); cout<<"Proceso en ejecucion";
    gotoxy(165,10); cout<<"Terminados";
    color(hConsole, 15);
    //Campos
    //1 Batch
    gotoxy(4,14); cout<<"ID"; 
    gotoxy(15,14);cout<<"TME";
    gotoxy(26,14); cout<<"T.TRANS";
    //Bloqueados
    gotoxy(4,34); cout<<"ID";
    gotoxy(26,34);cout<<"T.T.BLOQ";
    //2 Process
   /*  gotoxy(56,14); cout<<"-- Datos del Proceso --"; */
    gotoxy(56,14); cout<<"ID: ";
    gotoxy(56,16); cout<<"Operacion: ";
    gotoxy(56,18); cout<<"TME: ";
    gotoxy(56,20); cout<<"Tiempo transcurrido: ";
    gotoxy(56,22); cout<<"Tiempo restante: ";
    gotoxy(56,24); cout<<"Tiempo transcurrido del Quantum: ";
    //3 Finished
    gotoxy(140,14); cout<<"ID";
    gotoxy(164,14); cout<<"Operacion";
    gotoxy(193,14); cout<<"Resultado";

    color(hConsole, 17);
    //Lineas verticales
    for(int y=8; y<13; y++){
        gotoxy(42,y); cout<<char(219);
        gotoxy(42,y+20); cout<<char(219); //aa
        gotoxy(127,y); cout<<char(219);
    }
    color(hConsole, 15);
}
void ResultTable(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //cols=213 lines=50"
    //Lineas horizontales
    color(hConsole, 17);
    gotoxy(0,0); cout<<string(213,223);
    gotoxy(0,4); cout<<string(213,220);
    /* gotoxy(0,8); cout<<string(213,223); */
    /* gotoxy(0,12); cout<<string(213,220); */
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<"   Tabla de tiempos   ";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 15);
    //Campos
    gotoxy(7,6); cout<<"ID";
    gotoxy(25,6); cout<<"Operacion"; 
    gotoxy(46,6); cout<<"Resultado";
    gotoxy(67,6); cout<<"T.M.E";
    gotoxy(88,6); cout<<"T. de Servicio";
    gotoxy(109,6); cout<<"T. de Llegada";
    gotoxy(130,6); cout<<"T. de Finalizacion";
    gotoxy(151,6); cout<<"T. de Respuesta";
    gotoxy(172,6); cout<<"T. de Espera";
    gotoxy(193,6); cout<<"T. de Retorno";
}
void BCPTable(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //cols=213 lines=50"
    //Lineas horizontales
    color(hConsole, 17);
    gotoxy(0,0); cout<<string(213,223);
    gotoxy(0,4); cout<<string(213,220);
    /* gotoxy(0,8); cout<<string(213,223); */
    /* gotoxy(0,12); cout<<string(213,220); */
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<"      Tabla BCP       ";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 15);
    //Campos
    gotoxy(3,6); cout<<"ID";
    gotoxy(11,6); cout<<"Operacion"; 
    gotoxy(28,6); cout<<"Resultado";
    gotoxy(44,6); cout<<"T.M.E";
    gotoxy(56,6); cout<<"T. de Servicio";
    gotoxy(77,6); cout<<"T. de Llegada";
    gotoxy(95,6); cout<<"T. de Finalizacion";
    gotoxy(116,6); cout<<"T. de Respuesta";
    gotoxy(135,6); cout<<"T. de Espera";
    gotoxy(153,6); cout<<"T. de Retorno";
    gotoxy(170,6); cout<<"T. Restante";
    gotoxy(186,6); cout<<"T. Bloqueado";
    gotoxy(202,6); cout<<"Estado";
}
void cleanTimes(){
    gotoxy(200,6); cout<<string(6,255);
    gotoxy(77,20); cout<<string(6,255);
    gotoxy(73,22); cout<<string(6,255);
}

void cleanProcess(){//Limpiar proceso en ejecucion
    gotoxy(60,14); cout<<string(20,255);
    gotoxy(67,16); cout<<string(20,255);
    gotoxy(61,18); cout<<string(20,255);
    gotoxy(77,20); cout<<string(20,255);
    gotoxy(73,22); cout<<string(20,255);
    gotoxy(89,24); cout<<string(20,255);
}
void cleanBatch(){//Limpiar lote actual
    for(int y=16; y<28; y++){
        gotoxy(4,y); cout<<string(20,255);
        gotoxy(20,y); cout<<string(20,255);
    }
}
void cleanBlocked(){
    for(int y=35; y<50; y++){
        gotoxy(4,y); cout<<string(20,255);
        gotoxy(20,y); cout<<string(20,255);
    }
}
void cleanAll(){//lIMPIAR TODO
    cleanProcess();
    cleanBatch();
}


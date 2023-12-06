/*
	Programa 7.  Paginación Simple 
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	19/10/2023
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
    color(hConsole, 224);
    gotoxy(0,1); cout<<string(213,255);
    gotoxy(0,2); cout<<string(213,255);
    gotoxy(95,2); cout<<"     Paginacion Simple     ";
    gotoxy(0,3); cout<<string(213,255);
    color(hConsole, 192);
    gotoxy(0,5); cout<<string(213,255);
    gotoxy(0,6); cout<<string(213,255);
    gotoxy(4,6); cout<<"No. Procesos Nuevos: ";
    gotoxy(75,6); cout<<"Siguiente: ID:       Tamanio:      ";
    gotoxy(165,6); cout<<"Quantum: ";
    gotoxy(190,6); cout<<"Contador: ";
    gotoxy(0,7); cout<<string(213,255);
    //Subtitulos
    color(hConsole, 208);
    gotoxy(0,9); cout<<string(213,255);
    gotoxy(0,10); cout<<string(213,255);
    gotoxy(0,11); cout<<string(213,255);
    gotoxy(15,10); cout<<"  Listos   ";
    gotoxy(80,10); cout<<"Memoria";
    gotoxy(129,10); cout<<"Bloqueados";
    gotoxy(151,10); cout<<"Proceso en ejecucion";
    gotoxy(191,10); cout<<"Terminados";
    color(hConsole, 15);
    //Campos
    //1 Batch
    gotoxy(4,14); cout<<"ID"; 
    gotoxy(15,14);cout<<"TME";
    gotoxy(26,14); cout<<"T.TRANS";
    //Memoria empieza en 43
    gotoxy(50,14); cout<<"Marco";
    for(int esp=1; esp<=44;esp++){
        gotoxy(50,14+esp); cout<<esp;
        if (esp>40){
            for(int so=0;so<4;so++){
                gotoxy(69,55+so); cout<<"5/5";
                gotoxy(89,55+so); cout<<"SO";
                gotoxy(110,55+so); cout<<"Reservado";
            }
        }
    }
    gotoxy(69,14); cout<<"Espacio";
    gotoxy(89,14); cout<<"Proceso";
    gotoxy(110,14); cout<<"Estado";
    //Bloqueados
    gotoxy(126,14); cout<<"ID";
    gotoxy(133,14);cout<<"T.T.BLOQ";
    //2 Process
   /*  gotoxy(56,14); cout<<"-- Datos del Proceso --"; 148*/
    gotoxy(144,14); cout<<"ID: ";
    gotoxy(144,16); cout<<"Operacion: ";
    gotoxy(144,18); cout<<"TME: ";
    gotoxy(144,20); cout<<"Tiempo transcurrido: ";
    gotoxy(144,22); cout<<"Tiempo restante: ";
    gotoxy(144,24); cout<<"Tiempo transcurrido del Quantum: ";//56,24
    gotoxy(144,26); cout<<"Tamanio: ";
    //3 Finished
    gotoxy(181,14); cout<<"ID";
    gotoxy(186,14); cout<<"Operacion";
    gotoxy(201,14); cout<<"Resultado";

    color(hConsole, 17);
    //Lineas verticales
    for(int y=8; y<13; y++){
        gotoxy(42,y); cout<<char(219);
        gotoxy(143,y); cout<<char(219); 
        gotoxy(125,y); cout<<char(219); //Vertical Bloqueados
        gotoxy(180,y); cout<<char(219);
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
    gotoxy(148,14); cout<<string(6,255);
    gotoxy(155,16); cout<<string(20,255);
    gotoxy(149,18); cout<<string(10,255);
    gotoxy(165,20); cout<<string(10,255);
    gotoxy(161,22); cout<<string(14,255);
    gotoxy(177,24); cout<<string(2,255);
    gotoxy(153,26); cout<<string(6,255);
}
void cleanBatch(){//Limpiar lote actual
    for(int y=15; y<62; y++){
        gotoxy(4,y); cout<<string(20,255);
        gotoxy(20,y); cout<<string(20,255);
    }
}
void cleanBlocked(){
    for(int y=15; y<62; y++){
        gotoxy(126,y); cout<<string(16,255);

    }
}

void cleanEstadoMemoria(int marco){
    gotoxy(110,14+marco); cout<<string(15,255);
}
void cleanMarcoMemoria(int marco){
    gotoxy(69,14+marco); cout<<string(72,255);
}
void cleanAll(){//lIMPIAR TODO
    cleanProcess();
    cleanBatch();
}


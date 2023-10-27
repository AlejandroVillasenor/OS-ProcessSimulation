/*
	Programa 3 - Algoritmo de planificación de procesos FCFS - Sin thread
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	30/09/2023
	-- Archivo de cabecera --
*/
#include<bits/stdc++.h>
#include<stdlib.h>
#include<string>
#include <conio.h>
using namespace std;
// Crear un generador de números aleatorios
random_device rd;
mt19937 generator(rd());

//Funcion que valida enteros positivos
bool validatePI(string *cadena, int len){  
	bool ban = true;
	if((*cadena) == "" || (*cadena).length() > len){
		ban = false;
	}
	else{
		for(int i=0; i<(*cadena).size(); i++){
			if(int((*cadena)[i])<48 || int((*cadena)[i])>57){
				ban = false;
				break;
			}
		}
	}
	return ban;
}

//Funcion para pedir operandos en sumas, restas, multiplicaciones y divisiones
void data1(string *operando1, string *operando2){
	uniform_int_distribution<int> operating1(-1000, 1000);
	(*operando1) = to_string(operating1(generator));
    (*operando2) = to_string(operating1(generator));
}

//Funcion para pedir operandos en divisiones y modulos
void data2(string *operando1, string *operando2){
	uniform_int_distribution<int> operating2(1, 1000);
	(*operando1) = to_string(operating2(generator));
    (*operando2) = to_string(operating2(generator));
}

//Funcion para pedir operandos en porcentajes
void data3(string *operando1, string *operando2){
	uniform_int_distribution<int> operating3(1, 1000);
	(*operando1) = to_string(operating3(generator));
	uniform_int_distribution<int> operating4(1, 100);
	(*operando2) = to_string(operating4(generator));
}
#include <bits/stdc++.h>
#include<stdlib.h>
#include<string>
#define errormsg "Error: Dato no valido"

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
//Funcion que valida Flotantes Positivos
bool validatePF(string *cadena, int len){ 
	bool ban = true;
	int numPoints = 0;
	int pointIndex = 0;
    if((*cadena) == "" || (*cadena).length() > len){
        ban = false;
    }
    else{
        for(int i=0; i<(*cadena).size(); i++){
            if(int((*cadena)[i])<48 || int((*cadena)[i])>57){ //No es digito en codigo ASCII
                if((*cadena)[i] != '.'){
                    ban = false;
                    break;	
                }
                else{
                    numPoints++;
                    pointIndex = i;
                }
            }
        }
        if(numPoints> 1 || (pointIndex + 1) == (*cadena).length() ){
            ban = false;
        }
        //Corrección para caso especial de un solo caracter como entrada
        if(numPoints == 0 && (*cadena).length() == 1 && isdigit((*cadena)[0])){
            ban = true;
        }
    }
	return ban;
}

//Funcion para pedir operandos en sumas, restas, multiplicaciones y porcentajes
void data1(string *operando1, string *operando2){
	bool ban = false;
	do{
		cout<<"- Operando 1: ";
		getline(cin, (*operando1));
		ban = validatePF(operando1, 5);
		if(!ban){
			cout<<errormsg;
		}
	}while(!ban);
	do{
		cout<<"- Operando 2: ";
		getline(cin, (*operando2));
		ban = validatePF(operando2, 5);
		if(!ban){
			cout<<errormsg;
		}
	}while(!ban);
}

//Funcion para pedir operandos en divisiones y modulos
void data2(string *operando1, string *operando2){
	bool ban = false;
	do{
		cout<<"- Operando 1: ";
		getline(cin, (*operando1));
		ban = validatePF(operando1, 5);
		if(!ban){
			cout<<errormsg;
		}
	}while(!ban);
	do{
		cout<<"- Operando 2: ";
		getline(cin, (*operando2));
		ban = validatePF(operando2, 5);
		if(!ban){
			cout<<errormsg;
		}
		else{
			if(stof((*operando2)) == 0){
				ban = false;
				cout<<"Error: Division entre 0";
			}
		}
	}while(!ban);
}
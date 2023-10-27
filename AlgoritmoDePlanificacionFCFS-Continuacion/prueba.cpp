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
    system("title Prueba");
    desactivarMaximizar();
	system("mode con: cols=213 lines=50");//Tamaño de consola en pantal la completa
    BCPTable();
    return 0;
}
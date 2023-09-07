/*
	Programación de Sistemas - Proyecto 1
	Programa 1 - Procesamiento por lotes
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zúñiga Lozano Racso Siseneg
	06/09/2023
    -- Archivo de la clase Process --
*/
#include <bits/stdc++.h>
using namespace std;
class Process{
    private:
        string name;
        string op;
        float result;
        int time;
        string ID;
        int lote;
    public:
        Process(string name, string op, float result, int time, string ID, int lote){
            this->name = name;
            this->op = op;
            this->result = result;
            this->time = time;
            this->ID = ID;
            this -> lote = lote;
        }
        string getName(){
            return name;
        }
        string getOperation(){
            return op;
        }
        float getResult(){
            return result;
        }
        int getTime(){
            return time;
        }
        string getID(){
            return ID;
        }
        int getLote(){
            return lote;
        }
        void setName(string name){
            this->name = name;
        }
        void setOp(string op){
            this->op = op;
        }
        void setResult(float result){
            this->result = result;
        }
        void setTime(int time){
            this->time = time;
        }
        void setID(string ID){
            this->ID = ID;
        }
        void setLote(int lote){
            this->lote = lote;
        }
};

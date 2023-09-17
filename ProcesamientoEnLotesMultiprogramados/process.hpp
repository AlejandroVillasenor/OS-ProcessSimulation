/*
	Programa 2 - Procesamiento por lotes multiprogramados
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zúñiga Lozano Racso Siseneg
	17/09/2023
    -- Archivo de la clase Process --
*/
#include <bits/stdc++.h>
using namespace std;
class Process{
    private:
        string op;
        float result;
        int timeMax;
        int timeTrans;
        int ID;
        int lote;
    public:
        Process(string op, float result, int timeMax, int timeTrans, int ID, int lote){
            this->op = op;
            this->result = result;
            this->timeMax = timeMax;
            this->timeTrans = timeTrans;
            this->ID = ID;
            this->lote = lote;
        }
        string getOperation(){
            return op;
        }
        float getResult(){
            return result;
        }
        int getTimeMax(){
            return timeMax;
        }
        int getTimeTrans(){
            return timeTrans;
        }
        int getID(){
            return ID;
        }
        int getLote(){
            return lote;
        }
        void setOp(string op){
            this->op = op;
        }
        void setResult(float result){
            this->result = result;
        }
        void setTimeMax(int time){
            this->timeMax = time;
        }
        void setTimeTrans(int time){
            this->timeTrans = time;
        }
        void setID(int ID){
            this->ID = ID;
        }
        void setLote(int lote){
            this->lote = lote;
        }
};

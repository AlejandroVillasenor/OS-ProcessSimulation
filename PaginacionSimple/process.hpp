/*
	Programa 7.  Paginación Simple 
	218414783 - Villaseñor Rivas Alejandro Rodrigo
	221977551 - Zuñiga Lozano Racso Siseneg
	19/10/2023
	-- Archivo de cabecera --
*/
#include <bits/stdc++.h>
using namespace std;
class Process{
    private:
        string op;
        float result;
        int timeMax;
        int timeTrans;
        int timeLle;
        int timeFin;
        int timeResp;
        bool banResp;
        int timeEsp;
        int timeRet;
        int timeBlocked;
        int ID;
        bool banerror;
        int timeTransQuantum;
        int size;
        vector<int> memoryIndex;
    public:
        Process(string op, float result, int timeMax, int timeTrans, int timeLle, int timeFin, int timeResp, bool banResp, int timeEsp, int timeRet, int timeBlocked, int ID, bool banerror, int timeTransQuantum, int size, vector<int> memoryIndex){
            this->op = op;
            this->result = result;
            this->timeMax = timeMax;
            this->timeTrans = timeTrans;
            this->timeLle = timeLle; //
            this->timeFin = timeFin;
            this->timeResp = timeResp;
            this->banResp = banResp;
            this->timeEsp = timeEsp; //
            this->timeRet = timeRet;
            this->timeBlocked = timeBlocked;
            this->ID = ID;
            this->banerror = banerror;
            this->timeTransQuantum = timeTransQuantum;
            this->size = size;
            this->memoryIndex = memoryIndex;
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
        int getTimeLle(){
            return timeLle;
        }
        int getTimeFin(){
            return timeFin;
        }
        int getTimeResp(){
            return timeResp;
        }
        bool getBanResp(){
            return banResp;
        }
        int getTimeEsp(){
            return timeEsp;
        }
        int getTimeRet(){
            return timeRet;
        }
        int getTimeBlocked(){
            return timeBlocked;
        }
        int getID(){
            return ID;
        }
        bool getBanerror(){
            return banerror;
        }
        int getQuantum(){
            return timeTransQuantum;
        }
        int getSize(){
            return size;
        }
        vector<int> getMemoryIndex(){
            return memoryIndex;
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
        void setTimeLle(int time){ 
            this->timeLle= time;
        }
        void setTimeFin(int time){ 
            this->timeFin = time;
        }
        void setTimeResp(int time){ 
            this->timeResp = time;
        }
        void setBanResp(bool ban){
            this->banResp = ban;
        }
        void setTimeEsp(int time){ 
            this->timeEsp = time;
        }
        void setTimeRet(int time){ 
            this->timeRet = time;
        }
        void setTimeBlocked(int time){ 
            this->timeBlocked = time;
        }
        void setID(int ID){
            this->ID = ID;
        }
        void setBanerror(bool ban){
            this->banerror = ban;
        }
        void setQuantum(int QuantumV){
            this->timeTransQuantum = QuantumV;
        }
        void setSize(int size){
            this->size = size;
        }
        void setMemoryIndex(vector<int> memoryIndex){
            this->memoryIndex = memoryIndex;
        }
};

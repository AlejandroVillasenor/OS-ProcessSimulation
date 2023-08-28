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
};

#include "SymbolTable.h"
using namespace std;
void SymbolTable::run(string filename)
{
    ifstream f(filename);
    int cur_level=0;
    while (!f.eof()){
        string ins;
        getline(f, ins);
        if(regex_match(ins,linear)){
            // LINEAR <m> <c1>
            int c1_linear= 1;
            int m_linear= 1;
            this->setAttribute(c1_linear,0,m_linear);
            newHash.hp = linearProbing;
            cout<<"INIT LINEAR"<<endl;
        }
        else if(regex_match(ins,quadratic)){
            // QUADRATIC <m> <c1> <c2>
            int c1_linear= 1;
            int c2_linear= 1;
            int m_linear= 1;
            this->setAttribute(c1_linear,c2_linear,m_linear);
            newHash.hp = quadraticProbing;
            cout<<"INIT QUADRATIC"<<endl;
        }
        else if(regex_match(ins,doublee)){
            //DOUBLE <m> <c1>
            int c1_linear= 1;
            int m_linear= 1;
            this->setAttribute(c1_linear,0,m_linear);
            newHash.hp = doubleHashing;
            cout<<"INIT DOUBLE"<<endl;
        }
        else if(regex_match(ins,ins_vari)) {     ///// HAM INSERT BIEN
           cout<<"INSERT BIEN OK"<<endl;
        }
        else if (regex_match(ins,ins_func)){ ///// HAM INSERT FUNCTION
            cout<<"INSERT FUNC OK"<<endl;
        }
        else if (regex_match(ins, ass_val)){ //// HAM ASSIGN VALUE
            cout<<"ASSIGN VALUE OK"<<endl;
        }
        else if(regex_match(ins, ass_vari)){ //// HAM ASSIGN VARIABLE
            cout<<"ASSIGN VARIABLE OK"<<endl;
        }
        else if(regex_match(ins,ass_func)){ //// HAM ASSIGN HAM
            cout<<"ASSIGN HAM OK"<<endl;
        }
        else if(regex_match(ins,look_up)){
            cout<<"LOOKUP OK"<<endl;
        }
        else if(regex_match(ins,call)){
            cout<<"CALL OK"<<endl;
        }
        else if(ins == "PRINT"){
            cout<<"PRINT OK"<<endl;
        }
        else if(ins == "BEGIN"){
            cout<<"BEGIN OK"<<endl;
            cur_level++;
        }
        else if(ins =="END"){
            if(cur_level == 0){
                throw UnknownBlock();
            }
            cout<<"END OK"<<endl;
            // Doan nay xoa
            cur_level--;
        }
        else throw InvalidInstruction(ins);
    }
    f.close();
}
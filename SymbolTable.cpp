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
            setLinear(ins);
        }
        else if(regex_match(ins,quadratic)){
            setDouble(ins);
        }
        else if(regex_match(ins,doublee)){
            setQuadratic(ins);
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
            string s="";
            print(s);
            if(s.length() ==0 ) {
                return;
            } else {
                s.pop_back();
            }
            cout<<s<<endl;
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
            cur_level--;
        }
        else throw InvalidInstruction(ins);
    }
    f.close();
}
void SymbolTable::setLinear(string ins) {
    int c1_linear= 1;
    int c2_linear= 0;
    int m_linear= 1;
    int index[2]={0,0};
    int j = 0;
    for(int i=0;i<(int)ins.size();++i){
        if(j==2) break;
        if(ins[i]==' '){
            index[j]=i;
            j++;
        }
    }
    m_linear = stoi(ins.substr(index[0]+1,index[1]-index[0]-1));
    c1_linear = stoi(ins.substr(index[1]+1));
    this->setAttribute(c1_linear,c2_linear,m_linear);
    newHash.hp = linearProbing;
}
void SymbolTable::setQuadratic(string ins) {
    int c1_linear= 1;
    int c2_linear= 1;
    int m_linear= 1;
    int index[3]={0,0,0};
    int j = 0;
    for(int i=0;i<(int)ins.size();++i){
        if(j==3) break;
        if(ins[i]==' '){
            index[j]=i;
            j++;
        }
    }
    m_linear = stoi(ins.substr(index[0]+1,index[1]-index[0]-1));
    c1_linear = stoi(ins.substr(index[1]+1,index[2]-index[1]-1));
    c2_linear = stoi(ins.substr(index[2]+1));
    this->setAttribute(c1_linear,c2_linear,m_linear);
    newHash.hp = quadraticProbing;
}
void SymbolTable::setDouble(string ins) {
    int c1_linear= 1;
    int c2_linear= 0;
    int m_linear= 1;
    int count = 0;
    int index[2]={0,0};
    int j = 0;
    for(int i=0;i<(int)ins.size();++i){
        if(j==2) break;
        if(ins[i]==' '){
            index[j]=i;
            j++;
        }
    }
    m_linear = stoi(ins.substr(index[0]+1,index[1]-index[0]-1));
    c1_linear = stoi(ins.substr(index[1]+1));
    this->setAttribute(c1_linear,c2_linear,m_linear);
    newHash.hp = doubleHashing;
}
void SymbolTable::setAttribute(int c1, int c2, int m) {
    this->c1 = c1;
    this->c2 = c2;
    this->m = m;
    newHash.size = m;
    newHash.status = new int[m];
    newHash.arr = new Symbol[m];
    for (int i = 0; i < newHash.size; i++) {
        this->newHash.status[i] = 0; // 0 is null, 1 is has element
    }
}

int SymbolTable::encodeName(string name, int cur_level) {
    string res = to_string(cur_level);
    for(int i = 0 ; i < name.length();++i){
        res+=to_string(name[i]-48);
    }
    return stoi(res);
}
// 0 la null , 1
void SymbolTable::print(string &s) {
    for (int i = 0; i < newHash.size ; i++) {
        if (newHash.status[i] == 1) {
            s += to_string(i) + " " + newHash.arr[i].name + "//" + to_string(newHash.arr[i].scope)+";";
        }
    }
}

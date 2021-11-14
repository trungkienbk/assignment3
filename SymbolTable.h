#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
////////////////////////////////////////////////////////////
static int linearProbing(int key, int i,int c1,int c2,int m) {
    return ((key % m) + c1*i) % m;
}
static int quadraticProbing(int key, int i,int c1,int c2,int m) {
    return ((key % m)  + c1*i + c2*i*i) % m;
}
static int doubleHashing(int key, int i,int c1,int c2,int m) {
    int h1 = key % m;
    int h2 = 1 + (key % (m-2));
    return (h1 + c1*i*h2) % m;
}
////////////////////////////////////////////////////////////
class Symbol{
public:
    string name;
    string type ="";
    int scope;
    string argList =""; // Chua decode
    int encode=-1;
    int index=-1;
public:
    Symbol(){};
    Symbol(const string &name, int scope) : name(name), scope(scope) {};
    ~Symbol() {};
};
class OpenHash{
public:
    int (*hp)(int, int, int, int, int);
    int* status;
    Symbol* arr;
    int size;
public:
  OpenHash() {
      this->hp = nullptr;
      this->size = 0;
      this->arr = nullptr;
      this->status = nullptr;
   }
    ~OpenHash(){
       delete[] arr;
       delete[] status;
    }
};
///////////////////////////////////////////////////////////
class SymbolTable : public OpenHash {
public:
    OpenHash newHash;
    int c1, c2, m;
public:
    SymbolTable(){
        newHash = OpenHash();
    }
    ~SymbolTable(){}
    void run(string filename);
    void setAttribute(int c1_linear, int c2_linear, int m_linear);
    void setLinear(string ins);
    void setQuadratic(string ins);
    void setDouble(string ins);
    int encodeName(string name,int cur_level);
    Symbol isContains(Symbol e,int cur_level);
    void print(string &s);
    void insert_val(string ins,int cur_level);
    void lookup(string ins,int cur_level);
    void remove(int cur_level);

};
regex linear("LINEAR [0-9]+ [0-9]+");
regex quadratic("QUADRATIC [0-9]+ [0-9]+ [0-9]+");
regex doublee("DOUBLE [0-9]+ [0-9]+");
regex ins_vari("INSERT [a-z][a-zA-Z0-9_]*");
regex ins_func("INSERT [a-z][a-zA-Z0-9_]* [0-9]+");
regex ass_val("ASSIGN [a-z][a-zA-Z0-9_]* ([0-9]+|\'[a-zA-Z0-9 ]*\')");
regex ass_vari("ASSIGN [a-z][a-zA-Z0-9_]* [a-z][a-zA-Z0-9_]*");
regex ass_func(R"(ASSIGN [a-z][a-zA-Z0-9_]* [a-z][a-zA-Z0-9_]*\((|(([0-9]+|\'[a-zA-Z0-9 ]*\'|[a-z][a-zA-Z0-9_]*)((,[0-9]+)|(,\'[a-zA-Z0-9 ]*\')|(,[a-z][a-zA-Z0-9_]*))*))\))");
regex look_up("(LOOKUP )([a-z][a-zA-Z0-9_]*)");
regex call(R"(CALL [a-z][a-zA-Z0-9_]*\((|(([0-9]+|'[a-zA-Z0-9 ]*'|[a-z][a-zA-Z0-9_]*)((,[0-9]+)|(,'[a-zA-Z0-9 ]*')|(,[a-z][a-zA-Z0-9_]*))*))\))");
#endif
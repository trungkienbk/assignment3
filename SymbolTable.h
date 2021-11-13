#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
////////////////////////////////////////////////////////////
class OpenHash{
public:
    int (*hp)(int, int, int, int, int);
    int* status;
    int* arr;
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
////////////////////////////////////////////////////////////
class Symbol{
public:
    string name;
    string type;
    int scope;
    string decodes = ""; // Chua decode
    int encode=-1;
    int index=-1;
public:
    Symbol(){};
    Symbol(const string &name, const string &type, int scope) : name(name), type(type), scope(scope) {};
    ~Symbol() {};
};
///////////////////////////////////////////////////////////
class SymbolTable{
public:
    OpenHash newHash;
    int c1, c2, m;
public:
    static int linearProbing(int key, int i,int c1,int c2,int m) {
        return ((key % m) + c1*i) % m;
    }
    static int quadraticProbing(int key, int i,int c1,int c2,int m) {
        return ((key % m) + i + c1* i * c2*i) % m;
    }
    static int doubleHashing(int key, int i,int c1,int c2,int m) {
        int h1 = key % m;
        int h2 = 1 + (key % (m-2));
        return (h1 + c1*i * h2) % m;
    }
    SymbolTable(){
        newHash = OpenHash();
    }
    ~SymbolTable(){}
    void setAttribute(int c1,int c2,int m){
        this->c1 = c1;
        this->c2 = c2;
        this->m = m;
        newHash.size = m;
        newHash.status = new int[m];
        newHash.arr = new int[m];
        for (int i = 0; i < newHash.size; i++) {
            this->newHash.status[i] = 0; // 0 is null, 1 is has element
        }
    }
    void run(string filename);
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
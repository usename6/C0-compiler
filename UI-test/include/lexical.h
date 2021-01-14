#ifndef _LEXICAL_H_
#define _LEXICAL_H_
#include <cstdio>
#include <cstdlib>
#include "lookahead.h"
using namespace std;
struct token                               
{
    string str;                                 
    int id;
    token(){};
    token(string a,int b):str(a),id(b){};
};
extern vector<token> g;
inline void Push(string tp,int id,int &i);
bool check(string str,FILE *f);
#endif 

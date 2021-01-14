#ifndef _ASSEMBLE_H_
#define _ASSEMBLE_H_
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include "midcode.h"
using namespace std;
const int k=4;                      //k个寄存器 （k颜色法分配寄存器）
struct Node                         //定义每个变量节点生命周期
{
    int l,r;
    Node(){};
    Node(int a,int b):l(a),r(b){};
};
struct elem
{
    int id,last;
    elem(){};
    elem(int a,int b):id(a),last(b){};
};
struct Sentence
{
    string op;
    string op_a;
    string op_b;
    string res;
    Sentence(){};
    Sentence(string o,string a,string b,string r):op(o),op_a(a),op_b(b),res(r){};
};
int String_to_Int(string str);
string change_to_char(int tt);
bool isdigit(string tp);
bool cmp(int i,int j);
void set_id(string str,int pos);
int get_id(string str);
void live_init();
inline void check();
inline bool Is_free(int idx,int last);
inline void Update(int idx,int last);
inline int Exist(int idx);
inline void To_Spill(int idx);
inline void pop_out(int idx,int pos);
string get_regname(string str);
void create_sentence(string op,string a,string b,string res);
void create_assemble(int idx);
void allocate(FILE *f);
string get_inv_branch(int op);
bool is_branch(int op);
bool is_switch(int op);
bool is_case(int op);
bool lookahead_if(int id);
bool lookahead_while(int id);
void call_funct(string funct);
void return_funct();
void solve_funct(int &i);
#endif 

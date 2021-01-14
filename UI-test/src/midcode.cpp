#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include "midcode.h"
using namespace std;
FOURVARCODE f[CODE_MAXLEN];
int lab_num;
int code_num;
int var_num;
inline string Int_to_String(int num)
{
   stringstream ss;
   ss<<num;
   string ret=ss.str();
   return ret; 
}
void get_FOURVARCODE(int op,string num_a,string num_b,string res)
{
    code_num++;
    f[code_num]=FOURVARCODE(op,num_a,num_b,res);
}
string get_Lab()
{
    lab_num++;
    string tt=Int_to_String(lab_num);
    string tp="_label_"+tt;
    return tp;
}
string get_MidVar()
{
    var_num++;
    string tt=Int_to_String(var_num);
    string tp="$_"+tt;
    return tp;   
}
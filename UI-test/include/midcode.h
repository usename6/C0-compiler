#ifndef _MIDCODE_H_
#define _MIDCODE_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
using namespace std;
const int CODE_MAXLEN=1e6;
struct FOURVARCODE
{
    string num_b;
    string num_a;
    string res;
    int op;
    FOURVARCODE(){};
    FOURVARCODE(int a,string op1,string op2,string rt)
    {
        op=a;
        num_a=op1;
        num_b=op2;
        res=rt;
    }
};
extern int lab_num;                                                     //label的数量
extern int code_num;                                                    //指令的数量
extern int var_num;                                                     //变量的数量
extern FOURVARCODE f[CODE_MAXLEN];                                             //四元式数组的个数，最多容许1e6条指令
string Int_to_String(int num);                                          //Int 转化为 String
void get_FOURVARCODE(int op,string num_a,string num_b,string res);      //把东西塞到四元式里
string get_Lab();                                                         //生成label
string get_MidVar();                                                      //得到中间变量的名字
#endif 
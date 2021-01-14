#include <cstdio>
#include <string>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <list>
#include <sstream>
#include "lookahead.h"
using namespace std;
bool is_digit(char ch)
{
    if(ch>='0'&&ch<='9')return true;
    return false;
}   
int is_arith_operator(char ch)
{
    if(ch=='+')return Is_add;
    if(ch=='-')return Is_sub;
    if(ch=='*')return Is_mul;
    if(ch=='/')return Is_div;
    return Is_empty;
}   
int is_punctuation(char ch)
{
    if(ch==',')return Is_comma;         //逗号
    if(ch==';')return Is_semi;
    if(ch==':')return Is_colon;
    if(ch=='\"')return Is_dpm;          //双引号
    if(ch=='&')return Is_addr;
    return Is_empty; 
}
bool is_end(char ch)
{
    if(!isalpha(ch))return true;
    return false;
}
bool LH::look_ahead_Int(string str,int pos)
{
    if(str.substr(pos,3)=="int"&&str[pos+3]==' ')return true;
    return false;
}
bool LH::look_ahead_Char(string str,int pos)
{
    if(str.substr(pos,4)=="char"&&str[pos+4]==' ')return true;
    return false;
}
bool LH::look_ahead_Double(string str,int pos)
{
    if(str.substr(pos,6)=="double"&&str[pos+6]==' ')return true;
    return false;
}
bool LH::look_ahead_Long(string str,int pos)
{
    if(str.substr(pos,4)=="long"&&str[pos+4]==' ')return true;
    return false;
}
bool LH::look_ahead_LongLong(string str,int pos)
{
    if(str.substr(pos,9)=="long long"&&str[pos+9]==' ')return true;
    return false;
}
bool LH::look_ahead_Float(string str,int pos)
{
    if(str.substr(pos,5)=="float"&&str[pos+5]==' ')return true;
    return false;
}
bool LH::look_ahead_beq(string str,int pos)
{
    if(str.substr(pos,2)=="==")return true;
    return false;
}
bool LH::look_ahead_assgin(string str,int pos)
{
    if(str.substr(pos,1)=="=")return true;
    return false;
}
bool LH::look_ahead_bne(string str,int pos)
{
        if(str.substr(pos,2)=="!=")return true;
        return false;
}
bool LH::look_ahead_not(string str,int pos)
{
    if(str.substr(pos,1)=="!")return true;
    return false;
}
bool LH::look_ahead_bgt(string str,int pos)
{
    if(str.substr(pos,2)==">=")return true;
    return false;
}
bool LH::look_ahead_srlv(string str,int pos)
{
    if(str.substr(pos,2)==">>")return true;
    return false;
}
bool LH::look_ahead_bg(string str,int pos)
{
    if(str.substr(pos,1)==">")return true;
    return false;
}
bool LH::look_ahead_blt(string str,int pos)
{
    if(str.substr(pos,2)=="<=")return true;
    return false;
}
bool LH::look_ahead_sllv(string str,int pos)
{
    if(str.substr(pos,2)=="<<")return true;
    return false;
}
bool LH::look_ahead_bl(string str,int pos)
{
    if(str.substr(pos,1)=="<")return true;
    return false;
}
int LH::look_ahead_var(string str,int pos)
{
    //printf("this may be var\n");
    int len=str.size(),cnt=1;
    int s=pos;
    pos++;                                      //跳过下划线
    while(pos<len&&str[pos]!=' '&&str[pos]!=';'&&!is_arith_operator(str[pos])&&str[pos]!='='
          &&str[pos]!='!'&&str[pos]!=')'&&str[pos]!='&'&&str[pos]!='%'&&str[pos]!='('&&str[pos]!='{'&&str[pos]!=',')
    {
        //cout<<pos<<" "<<str[pos]<<endl; 
        if(isalpha(str[pos])||is_digit(str[pos])||str[pos]=='_')          
        {
            pos++;
            cnt++;
        }
        else return -1;
    }
    //debug
    //cout<<str.substr(s,cnt)<<endl;
    return cnt;
}
int LH::look_ahead_constant(string str,int pos)
{
    //printf("this it may be constant number\n");
    int len=str.size(),cnt=0;
    int s=pos;
    while(pos<len&&is_digit(str[pos])&&str[pos]!=';'&&str[pos]!=' '&&!is_arith_operator(str[pos]))
    {
        //int ch;
        //scanf("%d",&ch);
        //cout<<pos<<" "<<str[pos]<<endl;
        if(!is_digit(str[pos]))return -1;
        pos++;
        cnt++;
    }
    return cnt;
}
bool LH::look_ahead_If(string str,int pos)
{
    //printf("it may be if statement\n");
    if(str.substr(pos,3)=="if(")return true;
    return false;
}
bool LH::look_ahead_Else(string str,int pos)
{
    if(str.substr(pos,4)=="else"&&((str.size()==pos+4)||(str[pos+4]=='{')))return true;
    return false;
}
bool LH::look_ahead_For(string str,int pos)
{
    if(str.substr(pos,4)=="for(")return true;
    return false;
}
bool LH::look_ahead_While(string str,int pos)
{
    if(str.substr(pos,6)=="while(")return true;
    else return false;
}
bool LH::look_ahead_Main(string str,int pos)
{
    if(str.substr(pos,4)=="main")return true;
    return false;
}
bool LH::look_ahead_Return(string str,int pos)
{
    //printf("this is may be return\n");
    //cout<<str.substr(pos,6)<<endl;
    if(str.substr(pos,6)=="return")return true;
    return false;
}
bool LH::look_ahead_switch(string str,int pos)
{
    if(str.substr(pos,6)=="switch")return true;
    return false;
}
bool LH::look_ahead_case(string str,int pos)
{
    printf("look_ahead_case:%s\n",str.substr(pos,4).c_str());
    if(str.substr(pos,4)=="case")return true;
    return false;
}
bool LH::look_ahead_default(string str,int pos)
{
    if(str.substr(pos,7)=="default")return true;
    return false;
}
bool LH::look_ahead_scanf(string str,int pos)
{
    if(str.substr(pos,5)=="scanf")return true;
    return false;
}
bool LH::look_ahead_printf(string str,int pos)
{
    if(str.substr(pos,6)=="printf")return true;
    return false;
}
bool LH::look_ahead_intprintf(string str,int pos)
{
    if(str.substr(pos,2)=="%d")return true;
    return false;
}
bool LH::look_ahead_void(string str,int pos)
{
    if(str.substr(pos,4)=="void")return true;
    return false;
}

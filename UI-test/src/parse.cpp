#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <cmath>
#include "main.h"
#include "parse.h"
#include "midcode.h"
#include "lexical.h"
using namespace std;
bool work();
int select_program();
int select_complex_sentence();
bool select_var_statement();
bool select_var_definde();
bool select_set_sentence();
int select_single_sentence();
int select_assign_sentence();
int select_condition();
int select_expression();
int select_term();
string ret;                                                 //中间结果的值
int label_cnt,cyc_cnt;
int PAR::match_cnt=0;
int PAR::buffer[1000];
int PAR::buffer_num=0;
int select_program()               //true表示,匹配字符串的前缀含有“int main"的字符串，很有可能是主函数声明
{
    ////cout<<"select program"<<intsy<<" "<<mainsy<<endl;
    if(PAR::buffer[1]==intsy&&PAR::buffer[2]==mainsy)return 1;
    if(PAR::buffer[1]==intsy)return 2;
    if(PAR::buffer[1]==voidsy)return 3;
    return -1;
}
int select_complex_sentence()
{
    if((PAR::buffer[1]==intsy)||(PAR::buffer[1]==charsy))return 1;        //变量声明
    if((PAR::buffer[1]==forsy)||(PAR::buffer[1]==ifsy))return 2;          //语句列 条件语句部分
    if(PAR::buffer[1]=returnsy)return 2;                             //语句列 函数返回值部分
    if(PAR::buffer[1]==identi)return 2;                              //语句列 赋值语句
    if(PAR::buffer[1]==constsy)return 3;                             //常量说明
    if(PAR::buffer[1]==switchsy)return 4;
    if(PAR::buffer[1]==scanfsy)return 5;
    if(PAR::buffer[1]==printfsy)return 6;
    return -1;
}
bool select_var_statement()
{
    if(PAR::buffer[1]==intsy||PAR::buffer[1]==charsy)return true;
    return false;
}
bool select_var_definde()
{
    if(PAR::buffer[1]==intsy||PAR::buffer[1]==charsy)return true;
    return false;
}
bool select_set_sentence()
{
    if(PAR::buffer[1]==lbrace)return true;
    if(PAR::buffer[1]==intsy||PAR::buffer[1]==charsy)return true;
    if(PAR::buffer[1]==ifsy)return true;
    if(PAR::buffer[1]==forsy)return true;
    if(PAR::buffer[1]==returnsy)return true;
    if(PAR::buffer[1]==switchsy)return true;
    if(PAR::buffer[1]==identi)return true;
    if(PAR::buffer[1]==scanfsy)return true;
    if(PAR::buffer[1]==printfsy)return true;
    return false;
}
int select_single_sentence()
{
    if(PAR::buffer[1]==ifsy)return 1;        //条件语句
    if(PAR::buffer[1]==forsy)return 2;       //循环
    if(PAR::buffer[1]==returnsy)return 3;    //返回
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==becomes&&PAR::buffer[3]==identi&&PAR::buffer[4]==lparent)return 11;      //r_funct_call
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==becomes)return 4;        //变量的语句
    if(PAR::buffer[1]==lbrace)return 5;      //左大括号
    if(PAR::buffer[1]==semicolon)return 6;   //空语句
    if(PAR::buffer[1]==switchsy)return 7;   //switch
    if(PAR::buffer[1]==scanfsy)return 8;
    if(PAR::buffer[1]==printfsy)return 9;
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==lparent)return 10;   //
    return -1;
}
int select_assign_sentence()
{
    if(PAR::buffer[1]==identi&&PAR::buffer[1]==lbrack)return 1;          //数组元素赋值的表达式
    if(PAR::buffer[1]==identi)return 2;
    return -1;
}
// eql, neq, gtr, geq, lss, leq, // 12, 13, 14, 15, 16, 17
int select_condition()
{
    //if(PAR::buffer[1]==identi&&PAR::buffer[2]==bitand)return 1;
    //if(PAR::buffer[1]==identi&&PAR::buffer[2]==bitor)return 1;
    //if(PAR::buffer[1]==identi&&PAR::buffer[2]==bitxor)return 1;
    //if(PAR::buffer[1]==identi&&PAR::buffer[2]==and)return 1;
    //if(PAR::buffer[1]==identi&&PAR::buffer[2]==or)return 1;
    //重点实现下面的代码
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==eql)return 1;
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==neq)return 1;
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==gtr)return 1;
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==lss)return 1;
    if(PAR::buffer[1]==identi&&PAR::buffer[2]==leq)return 1;
    //因子*因子
    if(PAR::buffer[1]==identi)return 2;
    return -1;
}
int select_expression()
{
    if(PAR::buffer[1]==iadd)return 1;
    if(PAR::buffer[1]==isub)return 1;
    if(PAR::buffer[1]==identi)return 2;
    if(PAR::buffer[1]==intcon)return 3;         //int常量
    return -1;
}
int select_term()
{
    if(PAR::buffer[1]==identi)return 1;
    if(PAR::buffer[1]==imul||PAR::buffer[1]==idiv)return 2;
    if(PAR::buffer[1]==intcon)return 3;
    return -1;
}
bool select_case_sentence()
{
    if(PAR::buffer[1]==casesy)return true;
    return false;
}
bool select_default_sentence()
{
    if(PAR::buffer[1]==defaultsy)return true;
    return false;
}
bool select_para()
{
    if(PAR::buffer[1]==intsy)return true;
    if(PAR::buffer[1]==identi)return true;
    return false;
}
void PAR::look_ahead(int num)
{
    PAR::buffer_num=num;
    int cnt=0;
    for(int i=PAR::match_cnt;i<=tot_cnt&&i<=PAR::match_cnt+num-1;i++)
        PAR::buffer[++cnt]=ori[i];
    //debug
    //for(int i=1;i<=cnt;i++)//printf("%d\n",PAR::buffer[i]);
}
void PAR::clear_buffer()
{
    PAR::PAR::buffer_num=0;
}
//＜程序＞    ::= ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
bool PAR::program()                      
{
    //递归下降
    //int ch;
    ////cin>>ch;
    PAR::look_ahead(2);
    ////printf("PAR::match_cnt=%d\n",PAR::match_cnt);
    ////cout<<"program part:"<<buffer[1]<<" "<<buffer[2]<<endl;
    int id=select_program();
    if(id==1)
    {
        PAR::clear_buffer();                //先清空缓冲区字符
        PAR::main_statement();
    }
    else
    {
        PAR::clear_buffer();
        if(id==2)
            PAR::ret_function();
        else if(id==3)
            PAR::Non_ret_function();
        else return false;
        PAR::look_ahead(2);
        id=select_program();
        if(id==1)
        {
            PAR::clear_buffer();
            PAR::main_statement();
        }
        else return false;
    }
    if(PAR::match_cnt==tot_cnt)return true;
    return false;
}
//＜主函数＞    ::= int main‘(’‘)’‘{’＜复合语句＞‘}’
void PAR::main_statement()
{
    //int ch;
    ////cin>>ch;
    ////cout<<"main_statement:";
    PAR::match_cnt+=2;                                                               //匹配了int和main的字符串

    if(ori[PAR::match_cnt]==lparent && ori[PAR::match_cnt+1]==rparent)PAR::match_cnt+=2;     //匹配了左边的小括号和右边的小括号
    else return;                                                                //不能匹配返回
    if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;                                    //匹配大括号
    else return;                                                                //不能匹配返回
    ////cout<<"yes"<<endl;
    if(!PAR::complex_sentence())return;                                         //匹配复合语句
    if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
}
//＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
//如果当前匹配的字符串是const -> 常量说明
//如果当前匹配的字符串是类型表示符int char
//如果当前匹配的字符串是if/else or for or 
//如果当前匹配的字符串是标识符
bool PAR::complex_sentence()   //复合语句
{
    PAR::look_ahead(1);
    //int ch;
    ////cin>>ch;
    ////cout<<"complex sentence:"<<buffer[1]<<" ";
    int id=select_complex_sentence();
    if(id==-1)return false;
    ////cout<<id<<endl;
    PAR::clear_buffer();
    if(id==1)          //变量声明  
    {
        if(!var_statement())
            return false;
    }       
    PAR::set_sentence();                    //语句列 
}
//＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
bool PAR::var_statement()                 //变量说明
{
    PAR::look_ahead(1);
    //int ch;
    ////cin>>ch;
    ////cout<<"var_statement:"<<buffer[1]<<" ";
    if(select_var_statement())
    {
        PAR::clear_buffer();
        ////cout<<"first true"<<endl;
        if(!var_define())return false;
    }
    else return false;
    PAR::look_ahead(1);
    bool flag=false;
    while(select_var_statement())
    {
        flag=true;
        ////cout<<"rec select in var_define"<<endl;
        PAR::clear_buffer();
        if(!var_define())return false;          //内部的变量定义如果没完的话肯定错了
        PAR::look_ahead(1);
    }
    PAR::clear_buffer();
    //if(!flag)//cout<<"just once var_define"<<endl;
    return true;
}
bool PAR::var_define()
{
    string res,left,right;
    int op;
    ////cout<<"var_define:";
    if(ori[PAR::match_cnt]==intsy||ori[PAR::match_cnt]==charsy)
    {
        if(ori[PAR::match_cnt]==intsy)op=intsy;
        else if(ori[PAR::match_cnt]==charsy)op=charsy;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==identi)
    {
        res=g[PAR::match_cnt].str;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
    left="NULL";
    right="NULL";
    get_FOURVARCODE(op,left,right,res);                                       //转四元式子
    ////cout<<"true"<<endl;
    ////cout<<"now PAR::match_cnt="<<PAR::match_cnt<<endl;
    return true;
}
//＜语句列＞   ::= ｛＜语句＞｝      {}表示可以重复0到无限次
bool PAR::set_sentence()        //语句列，可以调用多个语句，即single_sentence
{
    PAR::look_ahead(1);
    //cout<<"set_sentence:"<<buffer[1]<<" "<<endl;
    if(select_set_sentence())
    {
        //cout<<"yes"<<endl;
        PAR::clear_buffer();
        if(!single_sentence())return false;
    }
    else return false;
    PAR::look_ahead(1);
    ////cout<<"out first set_sentence:"<<buffer[1]<<" "<<ori[PAR::match_cnt];
    while(select_set_sentence())
    {
        //int ch;
        ////cin>>ch;
        ////cout<<"rec single_sentence"<<endl;
        PAR::clear_buffer();
        if(!single_sentence())return false;
        PAR::look_ahead(1);
    }
    PAR::clear_buffer();
    return true;
}
bool PAR::single_sentence()
{
    PAR::look_ahead(4);
    int id=select_single_sentence();
    //cout<<"single_sentence:"<<buffer[1]<<" "<<id<<endl;
    PAR::clear_buffer();
    if(id==1)
    {
        if(!if_sentence())
            return false;
        ////printf("out if_sentence\n");
        //printf("if_sentence is success!\n");
    }
    else if(id==2)
    {
        if(!PAR::while_sentence())
            return false;
        //printf("while_sentence is success\n");
    }
    else if(id==3)
    {
        if(!PAR::return_sentence())
            return false;
        if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
        else return false;
    }
    else if(id==4)
    {
        if(!assign_sentence())
            return false;
        if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
        else return false;
        ////printf("out assign_sentence\n");
    }
    else if(id==5)
    {
        if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;
        else return false;
        if(set_sentence())return true;
        if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
        else return false;
    }
    else if(id==6)
    {
        if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
        else return false;
    }
    else if(id==7)
    {
        if(PAR::switch_sentence())return true;
        else return false;
    }
    else if(id==8)
    {
        if(PAR::scanf_setence())return true;
        else return false;
    }
    else if(id==9)
    {
        if(PAR::printf_setence())return true;
        else return false;
    }
    else if(id==10)
    {
        if(PAR::nr_call_sentence())return true;
        else return false;
    }
    else if(id==11)
    {
        if(PAR::call_sentence())return true;
        else return false;
    }
    ////printf("ori[%d] = %d\n",PAR::match_cnt,ori[PAR::match_cnt]);
    ////printf("single sentence is true\n");
    return true;
}
//＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞
bool PAR::if_sentence()
{
    string left,right,res;
    int op;

    //int ch;
    //scanf("%d",&ch);
    //cout<<"if_sententence:"<<endl;
    if(ori[PAR::match_cnt]==ifsy)
    {
        op=ifsy;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;
    else return false;
    ////cout<<"yes"<<endl;
    if(!PAR::condition())
        return false;
    left=ret;
    ////cout<<"if_ret="<<ret<<endl;
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;
    else return false;
    right="NULL";

    res="";
    get_FOURVARCODE(op,"!true",right,res);
    int if_id=code_num;
    //printf("out condition\n");
    if(ori[PAR::match_cnt]==lbrace)
        PAR::match_cnt++;
    else return false;

    if(PAR::set_sentence())
    {
        int cur_id=code_num;
        //printf("(%d, %s, %s, %s)\n", f[code_num].op, f[code_num].num_a.c_str(), f[code_num].num_b.c_str(), f[code_num].res.c_str());
        //cout<<"if_cur_id="<<cur_id<<endl;
        label_cnt++;
        string tp=Int_to_String(label_cnt);
        res="LABEL"+tp;
        cout<<res<<endl;
        get_FOURVARCODE(setlab,"NULL","NULL",res);
        f[if_id].res=res;
        if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
        else return false;
        //printf("out if all: ori[%d]=%d\n",PAR::match_cnt,ori[PAR::match_cnt]);
        return true;
    }
    return false;
}
//＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ //表达式为0条件为假，否则为真
//    eql, neq, gtr, geq, lss, leq, // 12, 13, 14, 15, 16, 17
bool PAR::condition()
{
    //int ch;
    ////cin>>ch;
    ////cout<<"condition:"<<" ";
    string left,right,res;
    int op;
    bool flag=false;

    PAR::look_ahead(2);
    int id=select_condition();
    ////cout<<"condition:"<<" "<<buffer[1]<<" "<<buffer[2]<<" "<<id<<endl;
    PAR::clear_buffer();
    if(id==1)           //<表达式＞＜关系运算符＞＜表达式＞
    {
        if(!PAR::expression())return false;
        left=ret;
        if(ori[PAR::match_cnt]==eql||ori[PAR::match_cnt]==neq)
        {
            if(ori[PAR::match_cnt]==eql)
                op=eql;
            else if(ori[PAR::match_cnt]==neq)
                op=neq;
            PAR::match_cnt++;
            ////printf("in eql neq\n");
            if(!PAR::expression())
                return false;
            right=ret;
            res=get_MidVar();
            get_FOURVARCODE(op,left,right,"NULL");
            ret=res;
            ////cout<<"ret="<<ret;
        }
        else if(ori[PAR::match_cnt]==gtr||ori[PAR::match_cnt]==geq)
        {
            if(ori[PAR::match_cnt]==gtr)
                op=gtr;
            else if(ori[PAR::match_cnt]==geq)
                op=geq;
            PAR::match_cnt++;
            ////printf("in gtr geq\n");
            if(!PAR::expression())
                return false;
            right=ret;
            res=get_MidVar();
            get_FOURVARCODE(op,left,right,"NULL");
            ret=res;
        }
        else if(ori[PAR::match_cnt]==lss||ori[PAR::match_cnt]==leq)
        {
            if(ori[PAR::match_cnt]==lss)
                op=lss;
            else if(ori[PAR::match_cnt]==leq)
                op=leq;
            PAR::match_cnt++;
            ////printf("in lss leq\n");
            if(!PAR::expression())
                return false;
            right=ret;
            res=get_MidVar();
            get_FOURVARCODE(op,left,right,"NULL");
            ret=res;
        }
        else return false;
    }
    else if(id==2)          //＜表达式＞
    {
        if(!PAR::expression())
            return false;
        left=ret;
        ret=left;
    }
    return true;
}
//＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
bool PAR::expression()
{
    bool flag=false;                //表示是否存在 a+b+..+d 还是仅仅存在 a
    string left,right,res;
    int op;

    PAR::look_ahead(1);
    int id=select_expression();
    int ch;
    //cin>>ch;
    //cout<<"expression:"<<buffer[1]<<" "<<id<<endl;
    //暴力走一遍第一个项
    if(id==1)                   //+ or -
    {
        PAR::clear_buffer();
        if(ori[PAR::match_cnt]==iadd||ori[PAR::match_cnt]==isub)
            PAR::match_cnt++;
        if(!PAR::term())
            return false;
    }
    else if(id==2)              //变量
    {
        PAR::clear_buffer();
        if(!PAR::term())  
            return false;
        left=ret;
    }
    else if(id==3)              //常量
    {
        PAR::clear_buffer();
        if(!PAR::term())
            return false;
        left=ret;
    }
    //看看有没有第二个项
    while((id=select_expression()!=-1))
    {
        //表示进入有a+b+...+d的形式
        flag=true;
        if(id==1)                           //第一个必须是运算符
        {
            PAR::clear_buffer();
            ////cout<<"rec expression"<<" ";
            if(ori[PAR::match_cnt]==iadd||ori[PAR::match_cnt]==isub)
            {
                if(ori[PAR::match_cnt]==iadd)op=iadd;
                else op=isub;
                PAR::match_cnt++;
            }
            else return false;
            ////cout<<"yes"<<endl;
            if(!PAR::term())
                return false;
            right=ret;
            res=get_MidVar();
            get_FOURVARCODE(op,left,right,res);
            left=res;
        }
        else return false;
        PAR::look_ahead(1);
    }

    if(flag)ret=res;
    else ret=left;
    ////cout<<"out rec expression"<<endl;
    ////printf("ori[%d]=%d\n",PAR::match_cnt,ori[PAR::match_cnt]);
    PAR::clear_buffer();
    return true;
}
bool PAR::term()
{
    string left,right,res;
    int op;
    bool flag=false;

    PAR::look_ahead(1);
    int id=select_term();
    int ch;
    //cin>>ch;
    cout<<"term:"<<buffer[1]<<" "<<id<<endl;
    PAR::clear_buffer();
    if(id==1||id==3)
    {
        if(!PAR::factor())
            return false;
        left=ret;    
    }
    else return false;
    PAR::look_ahead(1);
    while((id=select_term())==2)
    {
        flag=true;
        PAR::clear_buffer();
        if(ori[PAR::match_cnt]==imul)
        {
            op=imul;
            PAR::match_cnt++;
        }
        else if(ori[PAR::match_cnt]==idiv)
        {
            cout<<"idiv"<<endl;
            op=idiv;
            PAR::match_cnt++;
        }
        else return false;
        if(!PAR::factor())
            return false;
        right=ret;
        res=get_MidVar();
        get_FOURVARCODE(op,left,right,res);
        left=res;
        PAR::look_ahead(1);
    }
    PAR::clear_buffer();
    if(flag)ret=res;
    else ret=left;
    return true;
}
bool PAR::factor()
{
    PAR::look_ahead(1);
    int ch;
    //cin>>ch;
    //cout<<"factor:"<<buffer[1]<<" ";
    if(PAR::buffer[1]==identi||PAR::buffer[1]==intcon)
    {
        ret=g[PAR::match_cnt].str;
        PAR::match_cnt++;
        PAR::clear_buffer();
        //cout<<"yes"<<endl;
        //printf("ori[%d]=%d\n",PAR::match_cnt,ori[PAR::match_cnt]);
        return true;
    }
    return false;
}
bool PAR::assign_sentence()
{
    /*赋值的四元式*/
    /* a=b ->  =,b,,a*/
    string left,right;
    int op;
    string res;


    PAR::look_ahead(2);
    int id=select_assign_sentence();
    ////printf("ori[%d]=%d\n",PAR::match_cnt,ori[PAR::match_cnt]);
    int ch;
    //cin>>ch;
    //cout<<"assign_sentence:"<<buffer[1]<<" "<<buffer[2]<<" "<<id<<endl;
    //id==1 是数组形式，暂时不考虑
    if(id==1)
    {
        PAR::clear_buffer();
        res=g[PAR::match_cnt].str;
        PAR::match_cnt+=2;
        if(ori[PAR::match_cnt]==lbrack)
        {
            PAR::match_cnt++;
            if(!PAR::expression())return false;
        }
        else return false;
        if(ori[PAR::match_cnt]==rbrack)
            PAR::match_cnt++;
        else return false;
    }
    //变量形式
    else if(id==2)
    {
        if(ori[PAR::match_cnt]==identi)
        {
            res=g[PAR::match_cnt].str;
            PAR::match_cnt++;
        }
        else return false;
        if(ori[PAR::match_cnt]==becomes)
        {
            op=becomes;
            PAR::match_cnt++;   //代表等于等号时候
        }
        else return false;
        if(!PAR::expression())                      
            return false;
        left=ret;                            //expression的结果的值给res
        //赋值的四元式子
        right="NULL";                       //赋值为空
        get_FOURVARCODE(op,left,right,res);
        //cout<<"assign_sentence_id: "<<code_num<<endl;
        return true;
    }
    else return false;
    return true;
}
bool PAR::while_sentence()
{
    //cout<<"while_sentence:"<<ori[PAR::match_cnt]<<endl;
    string left,right,res;
    int op;
    int while_id;

    /*set label cycle*/
    string tp=Int_to_String(cyc_cnt);
    res="CYCLE"+tp;
    get_FOURVARCODE(setlab,"NULL","NULL",res);

    if(ori[PAR::match_cnt]==forsy)
    {
        op=forsy;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==lparent)
        PAR::match_cnt++;
    else return false;
    ////printf("out forsy\n");
    if(!PAR::condition())
        return false;
    //cout<<"out condition"<<ori[PAR::match_cnt]<<endl;
    if(ori[PAR::match_cnt]==rparent)
        PAR::match_cnt++;
    else return false;
    left=ret;
    right="zero";
    res="";
    get_FOURVARCODE(op,left,right,res);
    while_id=code_num;

    if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;
    else return false;
    if(!PAR::set_sentence())return false;
    if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
    else return false;

    int cur_id=code_num;
    res=Int_to_String(cur_id);

    tp=Int_to_String(label_cnt);
    res="LABEL"+tp;
    f[while_id].res=res;
    get_FOURVARCODE(setlab,"NULL","NULL",res);

    return true;
}
bool PAR::return_sentence()
{
    /*int ch;
    //cin>>ch;
    //cout<<"return_sentence:"<<" ";*/
    int op=returnsy;
    string left,right,res;
    left="NULL";
    right="NULL";
    res="NULL";
    if(ori[PAR::match_cnt]==returnsy)PAR::match_cnt++;
    else return false;
    ////cout<<"yes"<<endl;
    if(PAR::expression())
    {
        res=g[PAR::match_cnt-1].str;
        get_FOURVARCODE(op,left,right,res);
    }
    else return false;
    return true;
}
bool PAR::default_sentence()
{
    int op;
    int default_id;
    string left,right,res;
    op=setlab;
    get_FOURVARCODE(op,"NULL","NULL","DEFAULTIN");
    if(ori[PAR::match_cnt]==defaultsy)
    {
        op=defaultsy;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==colon)
    {
        get_FOURVARCODE(op,"NULL","NULL","NULL");
        default_id=code_num;
        PAR::match_cnt++;
    }
    else return false;
    if(!PAR::single_sentence())return false;
    op=setlab;
    get_FOURVARCODE(op,"NULL","NULL","DEFAULTOUT");
    return true;
}
bool PAR::set_case_sentence(string var)
{
    PAR::look_ahead(1);
    int case_cnt=0;
    while(select_case_sentence())
    {
        case_cnt++;
        PAR::clear_buffer();
        if(!case_sentence(var,case_cnt))return false;
        PAR::look_ahead(1);
    }
    PAR::clear_buffer();
    if(select_default_sentence())
    {
        if(!PAR::default_sentence())
            return false;
    }
    return true;
}
bool PAR::case_sentence(string var,int id)
{
    int op;
    int case_id;
    string left,right,res;
    op=setlab;
    string in_label="CASEIN"+Int_to_String(id);
    get_FOURVARCODE(op,"NULL","NULL",in_label);
    if(ori[PAR::match_cnt]==casesy)
    {
        op=casesy;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==intcon)
    {
        left=var;
        right=g[PAR::match_cnt].str;
        get_FOURVARCODE(op,left,right,res);
        case_id=code_num;
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==colon)PAR::match_cnt++;
    else return false;
    if(!PAR::single_sentence())return false;
    op=setlab;
    string out_label="CASEOUT"+Int_to_String(id);
    get_FOURVARCODE(op,"NULL","NULL",out_label);
    f[case_id].res=out_label;
    return true;
}
bool PAR::switch_sentence()
{
    int op;
    string left,right,res,var;
    op=switchsy;
    get_FOURVARCODE(op,left,"NULL",res);
    int switch_id=code_num;
    if(ori[PAR::match_cnt]==switchsy)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;               //左小括号
    if(PAR::expression())
    {
        var=g[PAR::match_cnt-1].str;
        f[switch_id].num_a=g[PAR::match_cnt-1].str;                   //暂时不支持表达式
    }
    else return false;
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;               //右小括号
    if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;                //左大括号
    if(!PAR::set_case_sentence(var))return false;
    if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;                //右大括号
    f[switch_id].res=Int_to_String(code_num);
    return true;
}
bool PAR::scanf_setence()
{
    //printf("in_scanf\n");
    int op;
    string left,right,res;
    op=scanfsy;
    if(ori[PAR::match_cnt]==scanfsy)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==dpm)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==intprint)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==dpm)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==comma)PAR::match_cnt++;         //逗号 ，
    else return false;
    if(ori[PAR::match_cnt]==gaddr)PAR::match_cnt++;         //取址 &
    else return false;
    printf("expression in\n");
    if(PAR::expression())
    {
        left=g[PAR::match_cnt-1].str;
        right="NULL";
        res="NULL";
        get_FOURVARCODE(op,left,right,res);
    }
    else return false;
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
    else return false;
    return true;
}
bool PAR::printf_setence()
{
    int op;
    string left,right,res;
    op=printfsy;
    if(ori[PAR::match_cnt]==printfsy)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==dpm)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==intprint)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==dpm)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==comma)PAR::match_cnt++;
    else return false;
    if(PAR::expression())
    {
        left=g[PAR::match_cnt-1].str;
        right="NULL";
        res="NULL";
        get_FOURVARCODE(op,left,right,res);
    }
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==semicolon)PAR::match_cnt++;
    else return false;
    return true;
}
bool PAR::parameter(bool tag)
{
    string res;
    if(tag&&ori[PAR::match_cnt]==intsy)PAR::match_cnt++;
    else if(tag)return false;
    if(ori[PAR::match_cnt]==identi)
    {
        if(!tag)printf("%d\n",ori[PAR::match_cnt]);
        res=g[PAR::match_cnt].str;
        PAR::match_cnt++;
    }
    else return false;
    get_FOURVARCODE(intsy,"NULL","NULL",res);               //给形参定义一波
    return true;
}
bool PAR::function_table(bool tag)
{
    PAR::look_ahead(1);
    int op;
    string left,right,res;
    left=right=res="NULL";
    op=lefttab;
    get_FOURVARCODE(op,left,right,res);
    while(select_para())
    {
        PAR::clear_buffer();
        if(!PAR::parameter(tag))
            return false;
        if(ori[PAR::match_cnt]==comma)PAR::match_cnt++;
        else if(ori[PAR::match_cnt]==rparent)break;
        else return false;
        PAR::look_ahead(1);
    }
    PAR::clear_buffer();
    op=righttab;
    get_FOURVARCODE(op,left,right,res);
    return true;
}
bool PAR::ret_function()
{
    int op;
    string left,right,res;
    op=setlab;
    left="NULL";
    right="NULL";
    if(ori[PAR::match_cnt]==intsy)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==identi)
    {
        res="funct"+g[PAR::match_cnt].str;
        get_FOURVARCODE(op,left,right,res);
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;
    else return false;
    if(!PAR::function_table(true))return false;
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;
    else return false;
    PAR::look_ahead(1);
    int id=select_complex_sentence();
    if(id==-1)return false;
    PAR::clear_buffer();
    if(!complex_sentence())
        return false;
    if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
    op=setlab;                                                                      //end of the funct
    left="NULL";
    right="NULL";
    res="exit"+res;
    get_FOURVARCODE(op,left,right,res);
    return true;
}
bool PAR::Non_ret_function()
{
    int op;
    string left,right,res;
    op=setlab;
    left="NULL";
    right="NULL";
    if(ori[PAR::match_cnt]==voidsy)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==identi)
    {
        res="funct"+g[PAR::match_cnt].str;
        get_FOURVARCODE(op,left,right,res);
        PAR::match_cnt++;
    }
    else return false;
    if(ori[PAR::match_cnt]==lparent)PAR::match_cnt++;
    else return false;
    if(!PAR::function_table(true))return false;
    if(ori[PAR::match_cnt]==rparent)PAR::match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lbrace)PAR::match_cnt++;
    else return false;
    PAR::look_ahead(1);
    int id=select_complex_sentence();
    if(id==-1)return false;
    PAR::clear_buffer();
    if(!complex_sentence())
        return false;
    if(ori[PAR::match_cnt]==rbrace)PAR::match_cnt++;
    op=setlab;                                                      //the end of funct
    left="NULL";
    right="NULL";
    res="exit"+res;
    get_FOURVARCODE(op,left,right,res);
    return true;
}
bool PAR::nr_call_sentence()
{
    if(ori[PAR::match_cnt]==identi)match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lparent)match_cnt++;
    else return false;
    if(!function_table(false))return false;
    if(ori[PAR::match_cnt]==rparent)match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==semicolon)match_cnt++;
    else return false;
}
bool PAR::call_sentence()
{
    string left,right,res;
    int op;
    op=callf;
    left=right=res="NULL";
    if(ori[PAR::match_cnt]==identi)
    {
        res=g[PAR::match_cnt].str;
        match_cnt++;
        get_FOURVARCODE(op,left,right,res);
    }
    else return false;
    if(ori[PAR::match_cnt]==becomes)match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==identi)match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==lparent)match_cnt++;
    else return false;
    printf("check in funct tab\n");
    if(!function_table(false))return false;
    printf("funct tab is right\n");
    if(ori[PAR::match_cnt]==rparent)match_cnt++;
    else return false;
    if(ori[PAR::match_cnt]==semicolon)match_cnt++;
    else return false;
    return true;
}
bool work()
{
    if(PAR::program())return true;
    return false;
}

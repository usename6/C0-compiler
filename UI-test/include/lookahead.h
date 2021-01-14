#ifndef _LOOKAHEAD_H_
#define _LOOKAHEAD_H_
#define Is_add 1
#define Is_sub 2
#define Is_mul 4
#define Is_div 8
#define Is_comma 16
#define Is_semi 32
#define Is_colon 64
#define Is_dpm 128
#define Is_addr 256
#define Is_empty 0
using namespace std;
/*
识别符号:
1.数字 0~9
2.运算符 + - * /
3.标点符号 , .
*/
bool is_digit(char ch);
int is_arith_operator(char ch);           //+ - * /
int is_punctuation(char ch);
bool is_end(char ch);
/*
核心算法 look_ahead
1.variable type: "int" "char" "double" "long" "long long" "float"
2.specail operator: "==" and "=" 、 “!=" and "!" 、 ”>" and ">=" and ">>" 、 ”<" and "<=" and "<<"
3.variable or constant value 
4.keyword which include if else for
*/
class LH
{
public:
    //variable type
    static bool look_ahead_Int(string str,int pos);
    static bool look_ahead_Char(string str,int pos);
    static bool look_ahead_Double(string str,int pos);
    static bool look_ahead_Long(string str,int pos);
    static bool look_ahead_LongLong(string str,int pos);
    static bool look_ahead_Float(string str,int pos);
    //special operator
    //1.== and =
    static bool look_ahead_beq(string str,int pos);
    static bool look_ahead_assgin(string str,int pos);
    //2.!= and !
    static bool look_ahead_bne(string str,int pos);
    static bool look_ahead_not(string str,int pos);
    //3.>= and > and >>
    static bool look_ahead_bgt(string str,int pos);
    static bool look_ahead_bg(string str,int pos);
    static bool look_ahead_srlv(string str,int pos);
    //4.<= and < and <<
    static bool look_ahead_blt(string str,int pos);
    static bool look_ahead_bl(string str,int pos);
    static bool look_ahead_sllv(string str,int pos);
    //variable or constant value
    static int look_ahead_var(string str,int pos);
    static int look_ahead_constant(string str,int pos);
    //keyword
    static bool look_ahead_If(string str,int pos);
    static bool look_ahead_Else(string str,int pos);
    static bool look_ahead_For(string str,int pos);
    static bool look_ahead_While(string str,int pos);
    static bool look_ahead_Main(string str,int pos);
    static bool look_ahead_Return(string str,int pos);
    static bool look_ahead_switch(string str,int pos);
    static bool look_ahead_case(string str,int pos);
    static bool look_ahead_default(string str,int pos);
    static bool look_ahead_scanf(string str,int pos);
    static bool look_ahead_printf(string str,int pos);
    static bool look_ahead_intprintf(string str,int pos);
    static bool look_ahead_void(string str,int pos);
};
#endif 

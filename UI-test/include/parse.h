#ifndef _PARSE_H_
#define _PARSE_H_
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
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
bool select_case_sentence();
bool select_default_sentence();
bool select_para();
extern vector<int> AST;
class PAR
{
public:
    static int match_cnt;              //当前匹配数
    static int buffer[1000];        //look_ahead的缓冲区
    static int buffer_num;
    static void init();
    static bool program();
    static void main_statement();
    static bool complex_sentence();    //复合语句
    static bool var_statement();
    static bool var_define();
    static bool set_sentence();        //语句列，可以调用多个语句，即single_sentence
    static bool single_sentence();
    static bool if_sentence();
    static bool condition();
    static bool expression();
    static bool term();
    static bool factor();
    static bool assign_sentence();
    static bool while_sentence();
    static bool return_sentence();
    static bool switch_sentence();
    static bool case_sentence(string var,int case_cnt);
    static bool set_case_sentence(string var);
    static bool default_sentence();
    static bool scanf_setence();
    static bool printf_setence();
    static bool ret_function();
    static bool Non_ret_function();
    static bool parameter(bool tag);
    static bool function_table(bool tag);
    static bool call_sentence();
    static bool nr_call_sentence();
    static void look_ahead(int num);       //多读num个单词,读了几个单词，读了几个单词进缓冲区
    static void clear_buffer();            //清除buffer的单词，具体操作，就是把buffer_num清零 
};
#endif 

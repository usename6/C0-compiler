#ifndef _MAIN_H_
#define _MAIN_H_
#include "parse.h"
#include <QMainWindow>
#include <QApplication>
using namespace std;
typedef enum 
{
    identi, // 0
    constsy, // 1
    intsy, charsy, // 2, 3
    voidsy, // 4
    intcon, charcon, stringcon, // 5, 6, 7
    iadd, isub, imul, idiv, // 8, 9, 10, 11
    eql, neq, gtr, geq, lss, leq, // 12, 13, 14, 15, 16, 17
    becomes, // 18
    lparent, rparent, lbrack, rbrack, lbrace, rbrace, // 19, 20, 21, 22, 23, 24
    comma, semicolon, colon, // 25, 26, 27
    ifsy, elsesy, // 28, 29
    switchsy, casesy, defaultsy, // 30, 31, 32
    forsy, // 33
    scanfsy, printfsy, // 34, 35
    mainsy, // 36
    returnsy, // 37
    orsy,andsy,xorsy,
    setlab,
    dpm,                     //双引号
    gaddr,                   // &
    intprint,                      // %d
    lefttab,righttab,         //函数参数表
    callf
}symbol;
extern int ori[1005];
extern int tot_cnt;
bool isnum(string str);
void init();
bool Lexical(FILE *f);
//bool Lexical();
void check_FOURVARCODE(FILE *ff);
void work_assemble(FILE *f);
bool PARSE_FOURVARCODE();
void parse_init();
void start(string inputfile, string outputfile);
#endif 

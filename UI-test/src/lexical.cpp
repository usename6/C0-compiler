#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <vector>
#include <cstdio>
#include <iostream>
#include "lookahead.h"
#include "main.h"
#include "lexical.h"
using namespace std;
int cnt;
vector<token> g;
inline void Push(string tp,int id,int &i)
{
    g.push_back(token(tp,id));
    i+=tp.size();
}
inline bool solve_var(string str,int &i,FILE *f)
{
    //cout<<"it is a var"<<endl;
    int dd=LH::look_ahead_var(str,i);
    if(dd)
    {
        cout<<str.substr(i,dd)<<endl;
        fprintf(f,"%s %d\n", str.substr(i,dd).c_str(),identi);
        Push(str.substr(i,dd),identi,i);
        return true;
    }
    //printf("error in var name\n");
    return false;
}
bool check(string str,FILE *f)
{
    int len=str.size(),i=0;
    while(i<len)
    {
        /*debug*/
        /*int ch;
        scanf("%d",&ch);
        printf("str[%d] = ",i);
        cout<<str[i]<<endl;*/
        /*debug*/
        //cout<<str[i]<<endl;
        if(str[i]=='\t')
        {
            i++;
            continue;
        }
        if(str[i]==' ')
        {
            i++;
            continue;
        }
        if(str[i]=='i')
        {
            if(LH::look_ahead_Int(str,i))
            {
                fprintf(f,"int %d\n",intsy);
                Push("int",intsy,i);
            }
            else if(LH::look_ahead_If(str,i))
            {
                fprintf(f,"if %d\n",ifsy);
                Push("if",ifsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='l')
        {
            if(LH::look_ahead_Long(str,i))
            {
                fprintf(f,"long 4\n");
                Push("long",1,i);
            }
            else if(LH::look_ahead_LongLong(str,i))
            {
                fprintf(f,"long long 5\n");
                Push("long long",1,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='e')
        {
            if(LH::look_ahead_Else(str,i))
            {
                fprintf(f,"else %d\n",elsesy);
                Push("else",elsesy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='d')
        {
            if(LH::look_ahead_default(str,i))
            {
                fprintf(f,"default %d\n",defaultsy);
                Push("default",defaultsy,i);
            }
            else if(LH::look_ahead_Double(str,i))
            {
                fprintf(f,"double\n");
                Push("double",1,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='c')
        {
            if(LH::look_ahead_case(str,i))
            {
                fprintf(f,"case %d\n",casesy);
                Push("case",casesy,i);
            }
            else if(LH::look_ahead_Char(str,i))
            {
                fprintf(f,"char %d\n",charsy);
                Push("char",charsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='f')
        {
            if(LH::look_ahead_For(str,i))
            {
                fprintf(f,"for %d\n",forsy);
                Push("for",forsy,i);
            }
            else if(LH::look_ahead_Float(str,i))
            {
                fprintf(f,"float\n");
                Push("float",1,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='w')
        {
            if(LH::look_ahead_While(str,i))
            {
                fprintf(f,"while %d\n",forsy);
                Push("while",forsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='m')
        {
            if(LH::look_ahead_Main(str,i))
            {
                fprintf(f, "main %d\n",mainsy);
                Push("main",mainsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='r')
        {
            if(LH::look_ahead_Return(str,i))
            {
                fprintf(f,"return %d\n",returnsy);
                Push("return",returnsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='s')
        {
            if(LH::look_ahead_switch(str,i))
            {
                fprintf(f,"switch %d\n",switchsy);
                Push("switch",switchsy,i);
            }
            else if(LH::look_ahead_scanf(str,i))
            {
                fprintf(f,"scanf %d\n",scanfsy);
                Push("scanf",scanfsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='p')
        {
            if(LH::look_ahead_printf(str,i))
            {
                fprintf(f,"printf %d\n",printfsy);
                Push("printf",printfsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(str[i]=='v')
        {
            if(LH::look_ahead_void(str,i))
            {
                fprintf(f,"void %d\n",voidsy);
                Push("void",voidsy,i);
            }
            else if(!solve_var(str,i,f))return 0;
        }

        else if(isalpha(str[i]))
        {
            int dd=LH::look_ahead_var(str,i);
            if(!solve_var(str,i,f))return 0;
        }

        else if(is_digit(str[i]))
        {
            int dd=LH::look_ahead_constant(str,i);
            if(dd)
            {
                fprintf(f,"%s %d\n", str.substr(i,dd).c_str(),intcon);
                Push(str.substr(i,dd),intcon,i);
            }
            else
            {
                //printf("error in character digit\n");
                return 0;
            }
        }

        else if(str[i]=='>')
        {
            if(LH::look_ahead_bgt(str,i))
            {
                fprintf(f, ">= %d\n",geq);
                Push(">=",geq,i);
            }
            else if(LH::look_ahead_srlv(str,i))
            {
                fprintf(f, ">>\n");
                Push(">>",1,i);
            }
            else if(LH::look_ahead_bg(str,i))
            {
                fprintf(f, "> %d\n",gtr);
                Push(">",gtr,i);
            }
        }

        else if(str[i]=='<')
        {
            if(LH::look_ahead_blt(str,i))
            {
                fprintf(f, "<= %d\n",leq);
                Push("<=",leq,i);
            }
            else if(LH::look_ahead_sllv(str,i))
            {
                fprintf(f, "<<\n");
                Push("<<",1,i);
            }
            else if(LH::look_ahead_bl(str,i))
            {
                fprintf(f, "< %d\n",lss);
                Push("<",lss,i);
            }
        }

        if(is_arith_operator(str[i]))
        {
            fprintf(f, "%s\n",str.substr(i,1).c_str());
            if(str[i]=='+')Push(str.substr(i,1),iadd,i);
            else if(str[i]=='-')Push(str.substr(i,1),isub,i);
            else if(str[i]=='*')Push(str.substr(i,1),imul,i);
            else if(str[i]=='/')Push(str.substr(i,1),idiv,i);
        }

        else if(str[i]=='=')
        {
            if(LH::look_ahead_beq(str,i))
            {
                fprintf(f,"== %d\n",eql);
                Push("==",eql,i);
            }
            else if(LH::look_ahead_assgin(str,i))
            {
                fprintf(f, "= %d\n",becomes);
                Push("=",becomes,i);
            }
        }

        else if(str[i]=='!')
        {
            if(LH::look_ahead_bne(str,i))
            {
                printf("it is neq\n");
                fprintf(f,"!= %d\n",neq);
                Push("!=",neq,i);
            }
        }

        else if(is_punctuation(str[i])==Is_comma)
        {
            fprintf(f, "%s %d\n",str.substr(i,1).c_str(),comma);
            Push(str.substr(i,1),comma,i);
        }

        else if(is_punctuation(str[i])==Is_semi)
        {
            fprintf(f, "%s %d\n",str.substr(i,1).c_str(),semicolon);
            Push(str.substr(i,1),semicolon,i);
        }

        else if(is_punctuation(str[i])==Is_colon)
        {
            fprintf(f,"%s %d\n",str.substr(i,1).c_str(),colon);
            Push(str.substr(i,1),colon,i);
        }

        else if(is_punctuation(str[i])==Is_dpm)
        {
            fprintf(f,"%s %d\n",str.substr(i,1).c_str(),dpm);
            Push(str.substr(i,1),dpm,i);
        }

        else if(is_punctuation(str[i])==Is_addr)
        {
            fprintf(f,"%s %d\n",str.substr(i,1).c_str(),gaddr);
            Push(str.substr(i,1),gaddr,i);
        }

        else if(str[i]=='%')
        {
            if(LH::look_ahead_intprintf(str,i))
            {
                fprintf(f,"%s %d\n",str.substr(i,2).c_str(),intprint);
                Push(str.substr(i,2),intprint,i);
            }
        }
        else if(str[i]=='(')
        {
            fprintf(f, "( %d\n",lparent);
            Push("(",lparent,i);
        }

        else if(str[i]==')')
        {
            fprintf(f, ") %d\n",rparent);
            Push(")",rparent,i);
        }

        else if(str[i]=='{')
        {
            fprintf(f,"{ %d\n",lbrace);
            Push("{",lbrace,i);
        }

        else if(str[i]=='}')
        {
            fprintf(f, "} %d\n",rbrace);
            Push("}",rbrace,i);
        }

    }
    return true;
}

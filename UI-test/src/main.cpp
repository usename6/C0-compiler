#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>
#include "main.h"
#include "lexical.h"
#include "parse.h"
#include "midcode.h"
#include "assemble.h"
#include "work.h"
using namespace std;
fstream inputFile;
bool success;
//char filename[9];
string filename;
string line;
vector<string> gg;                  //存储这个程序每一行的代码
map<string,bool> vis;
int ori[1005];
int tot_cnt;
void init()                                                                                                     //读取文件，一个一个读取放在vector
{
    success=1;
    int cnt=0;
    while(1)
    {
        line="";                                                                    //line赋值成
        if(inputFile.eof())                                                         //读取完成
        {
            cout<<"read finish"<<endl;
            break;
        }
        while (inputFile.peek() != '\n' && inputFile.peek() != EOF) { // 仍需增加一行字符的长度越界判断
            char tempChar;
            tempChar = inputFile.get();
            line += tempChar;
        }
        inputFile.get();
        cnt++;
        //cout<<line<<endl;
        gg.push_back(line);
    }
}

bool Lexical(FILE *f)
{
    printf("in Lexical\n");
    int sz=gg.size();
    for(int i=0;i<sz;i++)
    {
        //printf("debug this is in %dth line\n",i);
        //cout<<gg[i]<<endl;
        if(check(gg[i],f))continue;
        else return false;
    }
    return true;
}

void parse_init()
{
    int sz=g.size();
    //printf("sz=%d\n",sz);
    tot_cnt=sz;
    for(int i=0;i<tot_cnt;i++)
    {
        //printf("%s %d\n",g[i].str.c_str(),g[i].id);
        ori[i]=g[i].id;
    }
}

void check_FOURVARCODE(FILE *ff)
{
    for(int i=1;i<=code_num;i++)
    {
        fprintf(ff,"(%d, %s, %s, %s)\n", f[i].op, f[i].num_a.c_str(), f[i].num_b.c_str(), f[i].res.c_str());
        //printf("(%d, %s, %s, %s)\n", f[i].op, f[i].num_a.c_str(), f[i].num_b.c_str(), f[i].res.c_str());
    }
}

bool isnum(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>='0'&&str[i]<='9')continue;
        return false;
    }
    return true;
}

bool PARSE_FOURVARCODE()
{
    vis.clear();
    string tp;
    for(int i=1;i<=code_num;i++)
    {
        printf("check in code id = %d\n",i);
        printf("%d %s %s %s\n",f[i].op,f[i].num_a.c_str(),f[i].num_b.c_str(),f[i].res.c_str());
        if(f[i].op==intsy)
        {
            if(f[i].res.size())
            {
                tp=f[i].res;
                if(tp[0]!='$')
                    vis[tp]=true;
                //printf("%s is define\n",f[i].res.c_str());
            }
        }
        else if(f[i].op==scanfsy||f[i].op==printfsy)
        {
            tp=f[i].num_a;
            if(!vis[tp])
                return false;
        }
        else if(f[i].op==ifsy)continue;
        else if(f[i].op==eql||f[i].op==gtr||f[i].op==geq||f[i].op==lss||f[i].op==leq||f[i].op==iadd||f[i].op==isub||f[i].op==idiv||f[i].op==imul)
        {
            if(f[i].num_a.size())
            {
                tp=f[i].num_a;
                if(isnum(tp))continue;
                if(tp[0]=='$')
                    continue;
                //printf("check the var name %s\n",f[i].num_a.c_str());
                if(!vis[tp])
                    return false;
            }
            if(f[i].num_b.size())
            {
                tp=f[i].num_b;
                if(isnum(tp))continue;
                if(tp[0]=='$')
                    continue;
                //printf("check the var name %s\n",f[i].num_b.c_str());
                if(!vis[tp])
                    return false;
            }
        }
        else if(f[i].op==becomes)
        {
            if(f[i].res.size())
            {
                tp=f[i].res;
                if(!vis[tp])
                    return false;
            }
        }
    }
    return true;
}
void work_assemble(FILE *f)
{
    live_init();
    allocate(f);
}
void start(string inputfile, string outputfile)
{
    filename="C:/Users/ASUS/Desktop/UI-test/test/"+inputfile;
    printf("%s\n",inputfile.c_str());
    printf("Please input: your filename\n");
    inputFile.open(filename.c_str(), ios::in);
    init();
    int tot=gg.size();
    string out = "C:/Users/ASUS/Desktop/UI-test/out/" + outputfile;
    FILE *f=fopen("C:/Users/ASUS/Desktop/UI-test/out/out.txt","w");
    FILE *ff =fopen(out.c_str(),"w");
    printf("start compile\n");
    Lexical(f);
    printf("compile finsh\n");
    if(success)
    {
        printf("your code doesn't has lexical error\n");
        parse_init();
        printf("yes\n");
        if(work())
        {
            printf("your code doesn't has syntax error\n");
            check_FOURVARCODE(f);
            if(PARSE_FOURVARCODE())
            {
                printf("your code doesn't has level 2 syntax error\n");
                work_assemble(ff);
            }
            else printf("your code has level 2 synyax error\n");
        }
        else printf("your code have some syntax error\n");
    }
    else
    {
        printf("your code have some lexical error\n");
    }
    fclose(f);
    fclose(ff);
}
int main(int argc,char *argv[])
{
    /*UI - test*/
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

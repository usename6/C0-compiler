#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <cctype>
#include <map>
#include <queue>
#include <vector>
#include "assemble.h"
#include "midcode.h"
#include "main.h"
#define error -1
#define unallocate 0
using namespace std;
const int MAXN = 1e6;
map<string,int> id;             //变量名编号，包括中间变量
int r_id;                       //对应变量名的寄存器编号
Node p[MAXN];
int num[MAXN];
int Reg[MAXN];
vector<Sentence> A_S;
int String_to_Int(string str)
{
    stringstream ss;
    ss<<str;
    int res;
    ss>>res;
    return res;
}
string change_to_char(int tt)
{
    char ch=tt+'0';
    string s;
    s+=ch;
    return s;
}
bool isdigit(string tp)
{
    if(tp[0]>='0'&&tp[0]<='9')return true;
    return false;
}
inline void set_id(string str,int pos)          //给对应的变量预分配一个寄存器的名字（假的）
{
    if(get_id(str)==error)return;
    if(get_id(str)==unallocate)         //已经分配过了
    {
        //printf("%s -> %d\n",str.c_str(),r_id+1);
        id[str]=++r_id;
        p[r_id].l=pos;
        p[r_id].r=pos;
        return;
    }
    //printf("pos = %d str=%s\n",pos,str.c_str());
    p[get_id(str)].r=pos;
}
inline int get_id(string str)           //寻找该变量名对应的预分配的名字
{
    if(str=="NULL")return error;           //error
    if(isdigit(str))return error;
    if(str=="!true")return error;
    if(str.find("CASE")!=string::npos)return error;
    if(str.find("DEFAULT")!=string::npos)return error;
    if(id[str]==0)return unallocate;       //unallocate
    return id[str];
}
void live_init()
{
    for(int i=1;i<=code_num;i++)
    {
        if(f[i].op==intsy)continue;
        if(f[i].num_a.size())
            set_id(f[i].num_a,i);
        if(f[i].num_b.size())
            set_id(f[i].num_b,i);
        if(f[i].res.size())
            set_id(f[i].res,i);
    }
    //printf("check live_period\n");
    for(int i=1;i<=r_id;i++)
    {
        p[i].r++;
        printf("%d %d\n",p[i].l,p[i].r);
    }
}
void check_live()
{
    printf("check live period\n");
    for(int i=1;i<=r_id;i++)
        printf("%d:(%d,%d)\n",i,p[i].l,p[i].r);
}
vector<elem> q;                //分配五个寄存器
const int q_num=4;
int Spill;                          //Spill寄存器
inline void check()
{
    printf("check all var status\n");
    for(int i=1;i<=r_id;i++)
        printf("var %d is %d\n",i,Reg[i]);
    for(int i=0;i<(int)q.size();i++)
        printf("Reg %d %d %d\n",i+1,q[i].id,q[i].last);
}
inline bool Is_free(int idx,int last)
{
    //int ch;
    //scanf("%d",&ch);
    //printf("The No.%d var is try to find spare reg to attribute\n",idx);
    if((int)q.size()<q_num)             //如果队列不满
    {
        //printf("Not Full\n");
        //printf("%d %d\n",idx,last);
        q.push_back(elem(idx,last));
        //printf("cur:%d %d %d\n",(int)q.size(),q[(int)q.size()-1].id,q[(int)q.size()-1].last);
        //check();
        Reg[idx]=q.size();
        return true;
    }
    for(int i=0;i<q_num;i++)                //如果队列满了，先寻找有没有被free掉的节点
    {
        if(q[i].id==-1)
        {
            //printf("The %dth is be free\n",i);
            if(Spill==idx)                  //如果该寄存器在Spill
            {
                //Add a Sentence which is to atttribute Spill to cur_Reg
                //printf("In the Spill");
                string tt="$t";
                tt=tt+change_to_char(i+1);
                create_sentence("lw","NULL",tt,"0($s0)");                   //$r0 -> Mem(0)
                //create_sentence("add","$t0","$zero",tt);
            }
            q[i]=elem(idx,last);          //寄存器赋值进去
            Reg[idx]=i+1;
            return true;
        }
    }
    return false;
}
inline void Update(int idx,int last)                //使用LRU算法进行更新分配寄存器
{
    //int ch;
    //scanf("%d",&ch);
    //printf("The No.%d var is Update\n",idx);
    int res_id=-1,mm=10000,mem_id;
    if(Reg[idx]>0)
    {
        q[Reg[idx]-1].last=last;
        //printf("Reg[%d]=%d\n",idx,Reg[idx]);
        int cr_id=Reg[idx]-1;
        //printf("occur %d %d %d\n",Reg[idx],q[cr_id].id,q[cr_id].last);
        return;
    }
    if(!Is_free(idx,last))
    {
        //printf("The NO.%d is fail to find a free reg\n",idx);
        for(int i=0;i<(int)q_num;i++)
        {
            if(mm>q[i].last)
            {
                mm=q[i].last;
                res_id=i;
            }
        }
        if(Spill==idx)                  //如果该寄存器在Spill
        {
            //Add a Sentence which is to atttribute Spill to cur_Reg
            //printf("In the Spill");
            string tt="$t";
            tt=tt+change_to_char(res_id);
            create_sentence("lw","NULL",tt,"0($s0)");
            //create_sentence("add","$t0","$zero",tt);
        }
        //printf("res_id=%d\n",res_id);
        To_Spill(q[res_id].id);                     //将当前的被替换变量的值替换到Spill中
        q[res_id]=elem(idx,last);
        Reg[idx]=res_id+1;
    }
}
inline int Exist(int idx)                   //判断是不是存在
{
    for(int i=0;i<q.size();i++)
    {
        if(q[i].id==-1)continue;            //跳过没有分配的
        if(q[i].id==idx)
            return true;
    }
    return false;
}
inline void To_Spill(int idx)
{
    //int ch;
    //scanf("%d",&ch);
    //printf("The No.%d is To_Spill\n",idx);
    string tt="$t";
    tt=tt+change_to_char(Reg[idx]);
    //create_sentence("add",tt,"$zero","$t0");
    create_sentence("sw","NULL",tt,"0($s0)");         //recover
    Spill=idx;   
    Reg[idx]=0;                             //Spill -> 0
}
inline void pop_out(int pos)                //优化排出生命期结束的变量
{
    //int ch;
    //scanf("%d",&ch);
    //printf("This is pop_out process\n");
    for(int i=0;i<(int)q.size();i++)
    {
        int idx=q[i].id;
        if(p[idx].r==pos)
        {
            printf("The var %dth and the No.%dth Reg is out\n",idx,i);
            q[i].id=-1;
            q[i].last=-1;
        }
    }
}
string get_regname(string str)
{
    int idx=get_id(str);
    string tt="$t";
    tt=tt+change_to_char(Reg[idx]);
    //cout<<"debug:"<<tt<<endl;
    return tt;
}
void create_sentence(string op,string a,string b,string res)
{
    //cout<<op<<" "<<a<<" "<<b<<" "<<res<<endl;
    A_S.push_back(Sentence(op,a,b,res));
    //fprintf(f,"%s %s %s %s\n",op.c_str(), a.c_str(), b.c_str(), res.c_str());
}
void create_assemble(int i)
{
    if(f[i].op==intsy||f[i].op==charsy)return;
    int a,b,res;
    string op_a,op_b;
    if(f[i].op==becomes)                        //赋值
    {
        op_a=f[i].num_a;
        if(isdigit(op_a))
            create_sentence("addi","$zero",op_a,get_regname(f[i].res));
        else
            create_sentence("add",get_regname(op_a),"$zero",get_regname(f[i].res));
    }
    else if(f[i].op==iadd)
    {
        op_a=f[i].num_a;
        op_b=f[i].num_b;
        if(isdigit(op_a)&&isdigit(op_b))
        {
            create_sentence("li","NULL",op_a,"$t0");                            //用t7做add计算
            create_sentence("addi","$t0",op_b,get_regname(f[i].res));
        }
        else if(isdigit(op_a))
            create_sentence("addi",get_regname(op_b),op_a,get_regname(f[i].res));
        else if(isdigit(op_b))
            create_sentence("addi",get_regname(op_a),op_b,get_regname(f[i].res));
        else
            create_sentence("add",get_regname(op_a),get_regname(op_b),get_regname(f[i].res));
    }
    else if(f[i].op==isub)
    {
        op_a=f[i].num_a;
        op_b=f[i].num_b;
        if(isdigit(op_a)&&isdigit(op_b))
        {
            create_sentence("li","NULL",op_a,"$t0");                            //用t7做add计算
            string new_op_b="-"+op_b;
            create_sentence("addi","$t0",new_op_b,get_regname(f[i].res));
        }
        else if(isdigit(op_a))
            create_sentence("subu",op_a,get_regname(op_b),get_regname(f[i].res));
        else if(isdigit(op_b))
        {
            string new_op_b="-"+op_b;
            create_sentence("addi",get_regname(op_a),new_op_b,get_regname(f[i].res));
        }
        else
            create_sentence("sub",get_regname(op_a),get_regname(op_b),get_regname(f[i].res));
    }
    else if(f[i].op==imul)
    {
        op_a=f[i].num_a;
        op_b=f[i].num_b;
        if(isdigit(op_a)&&isdigit(op_b))
        {
            create_sentence("li","NULL",op_a,"$t0");
            create_sentence("li","NULL",op_b,"$s1");
            create_sentence("mult","$t0","$s1","NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
        else if(isdigit(op_a))
        {
            create_sentence("li","NULL",op_a,"$t0");
            create_sentence("mult","$t0",get_regname(op_b),"NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
        else if(isdigit(op_b))
        {
            create_sentence("li","NULL",op_b,"$t0");
            create_sentence("mult",get_regname(op_a),"$t0","NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
        else
        {
            create_sentence("mult",get_regname(op_a),get_regname(op_b),"NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
    }
    else if(f[i].op==idiv)
    {
        op_a=f[i].num_a;
        op_b=f[i].num_b;
        if(isdigit(op_a)&&isdigit(op_b))
        {
            create_sentence("li","NULL",op_a,"$t0");
            create_sentence("li","NULL",op_b,"$s1");
            create_sentence("div","$t0","$s1","NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
        else if(isdigit(op_a))
        {
            create_sentence("li","NULL",op_a,"$t0");
            create_sentence("div","$t0",get_regname(op_b),"NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
         else if(isdigit(op_b))
        {
            create_sentence("li","NULL",op_b,"$t0");
            create_sentence("divu",get_regname(op_a),op_b,get_regname(f[i].res));
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
        else
        {
            create_sentence("div",get_regname(op_a),get_regname(op_b),"NULL");
            create_sentence("mflo","NULL","NULL",get_regname(f[i].res));
        }
    }
}
void set_lab(string lname)
{
    A_S.push_back(Sentence(lname,"NULL","NULL","NULL"));
}
//    eql, neq, gtr, geq, lss, leq, // 12, 13, 14, 15, 16, 17
string get_inv_branch(int op)
{
    if(op==eql)return "bne";
    if(op==neq)return "beq";
    /*if(op==gtr)return "";
    if(op==geq)return lss;
    if(op==lss)return geq;
    if(op==leq)return gtr;*/
}
bool is_branch(int op)
{
    if(op==eql)return true;
    if(op==neq)return true;
    if(op==gtr)return true;
    if(op==geq)return true;
    if(op==lss)return true;
    if(op==leq)return true;
    return false;
}
bool is_case(int op)
{
    if(op==casesy)return true;
    return false;
}
bool is_switch(int op)
{
    if(op==switchsy)return true;
    return false;
}
bool lookahead_if(int id)
{
    if(id>code_num)return false;
    if(f[id].op==ifsy)return true;
    return false;
}
bool lookahead_while(int id)
{
    if(id>code_num)return false;
    if(f[id].op==forsy)return true;
    return false;
}
/********************************* */
/* -----------------------------   */
/* |           $sp              |  */
/* ------------------------------  */
/* |           $ra              |  <- $fp*/
/* ------------------------------  */
/* |           var              |  */
/* ------------------------------  */
/* |                            |  */
/* ------------------------------  */
/********************************* */
void call_funct(string funct)
{
    create_sentence("subu","$sp","4","$sp");                //$sp = $sp - 4
    create_sentence("sw","NULL","$fp","0($sp)");             //Mem($sp) = $fp      上一次的栈顶
    create_sentence("subu","$sp","4","$sp");                //$sp = $sp - 4
    create_sentence("move","NULL","$sp","$fp");              //$fp = $sp
    create_sentence("sw","NULL","$ra","0($sp)");             //Mem(sp) = ra
}
void return_funct()
{
    create_sentence("move","NULL","$fp","$sp");              //$sp = $fp
    create_sentence("lw","NULL","$ra","0($sp)");             //$ra = Mem($sp)
    create_sentence("addi","$sp","4","$sp");               //$sp = $sp + 4     pop
    create_sentence("lw","NULL","$fp","0($sp)");             // $fp = Mem($sp) recover the $fp
    create_sentence("jr","NULL","NULL","$ra");
}
void solve_funct(int &i)
{
    map<string,int> ru;
    int rcnt=1;
    bool rec_tag=false;
    string target;
    bool ttag=false;
    int par_num=0;
    for(;i<=code_num;i++)
    {
        if(f[i].op==lefttab)ttag=true;
        else if(f[i].op==righttab)ttag=false;
        if(f[i].op==setlab)
        {
            if(f[i].res.find("exit")!=string::npos)
                break;
            else if(f[i].res.find("funct")!=string::npos)
            {
                string funct_name;
                funct_name=f[i].res;
                set_lab(funct_name);
                call_funct(funct_name);
            }
            continue;
        }
        if(f[i].op==returnsy)
        {
            if(f[i].res=="NULL")continue;
            string res="$s"+Int_to_String(ru[f[i].res]);
            create_sentence("add","$zero",res,"$v0");
            continue;
        }
        if(f[i].op==intsy)
        {
            if(ttag)
            {
                ru[f[i].res]=par_num+10;
                par_num++;
            }
            create_sentence("subu","$sp","4","$sp");
            continue;
        }
        if(!isdigit(f[i].num_a)&&ru[f[i].num_a]==0)
            ru[f[i].num_a]=++rcnt;
        if(!isdigit(f[i].num_b)&&ru[f[i].num_b]==0)
            ru[f[i].num_b]=++rcnt;
        if(!isdigit(f[i].res)&&ru[f[i].res]==0)
            ru[f[i].res]=++rcnt;
        if(f[i].op==iadd)                                           //目前只实现加法
        {
            if(!isdigit(f[i].num_a)&&!isdigit(f[i].num_b))
            {
                string left,right,res;
                if(ru[f[i].num_a]<10)
                    left="$s"+Int_to_String(ru[f[i].num_a]);
                else
                    left="$a"+Int_to_String(ru[f[i].num_a]-10);
                if(ru[f[i].num_b]<10)
                    right="$s"+Int_to_String(ru[f[i].num_b]);
                else
                    right="$a"+Int_to_String(ru[f[i].num_b]-10);
                res="$s"+Int_to_String(ru[f[i].res]);
                create_sentence("add",left,right,res);
            }
            else if(!isdigit(f[i].num_a))
            {
                string left,right,res;
                if(ru[f[i].num_a]<10)
                    left="$s"+Int_to_String(ru[f[i].num_a]);
                else
                    left="$a"+Int_to_String(ru[f[i].num_a]-10);
                right=f[i].num_b;
                res="$s"+Int_to_String(ru[f[i].res]);
                create_sentence("addi",left,right,res);
            }
            else if(!isdigit(f[i].num_b))
            {
                string left,right,res;
                left=f[i].num_a;
                if(ru[f[i].num_b]<10)
                    right="$s"+Int_to_String(ru[f[i].num_b]);
                else
                    right="$a"+Int_to_String(ru[f[i].num_b]-10);
                res="$s"+Int_to_String(ru[f[i].res]);
                create_sentence("addi",right,left,res);
            }
            continue;
        }
        if(f[i].op==becomes)
        {
            string left,right,res;
            right="$s"+Int_to_String(ru[f[i].num_a]);
            res="$s"+Int_to_String(ru[f[i].res]);
            create_sentence("add","$zero",right,res);
        }
    }
    return_funct();
    return;
}
void allocate(FILE *ff)
{
    bool switch_tag=false;
    int switch_end;
    memset(Reg,-1,sizeof(Reg));
    create_sentence("jal","NULL","NULL","main");             //call 函数
    create_sentence("j","NULL","NULL","maintail");
    bool rec_tag=false;
    string target;
    bool ttag=false;                                        //ttag funct_tab
    int par_num=0;                                             //tcnt
    string funct_name;
    string funct_tar;                                      //funct_tar;
    if(f[1].op!=setlab&&f[1].res.find("funct")==string::npos)
    {
        set_lab("main");
        call_funct("main");
    }
    for(int i=1;i<=code_num;i++)
    {
        if(f[i].op==setlab&&f[i].res.find("funct")!=string::npos)
        {
            funct_name=f[i].res;
            solve_funct(i);
            set_lab("main");
            call_funct("main");
            continue;
        }
        if(f[i].op==callf)
        {
            funct_tar=f[i].res;
            continue;
        }
        if(f[i].op==lefttab)
        {
            ttag=true;
            continue;
        }
        else if(f[i].op==righttab)
        {
            ttag=false;
            create_sentence("jal","NULL","NULL",funct_name);
            if(ori[1]!=voidsy)create_sentence("add","$zero","$v0",get_regname(funct_tar));
            continue;
        }
        if(f[i].op==intsy)
        {
            if(!ttag)create_sentence("subu","$sp","4","$sp");                //压栈
            else
            {
                string tpp;
                tpp="$a"+Int_to_String(par_num);
                create_sentence("add","$zero",get_regname(f[i].res),tpp);           //传递形参
                par_num++;
            }
            continue;
        }
        if(f[i].op==setlab)
        {
            pop_out(i);
            if(rec_tag)
            {
                rec_tag=false;
                create_sentence("j","NULL","NULL",target);
            }
            if(switch_tag)
            {
                if(i==switch_end)
                    switch_tag=false;
            }
            if(f[i].res.find("CASEOUT")!=string::npos)
                create_sentence("j","NULL","NULL","DEFAULTIN");
            set_lab(f[i].res);
            continue;
        }
        pop_out(i);
        int id1=get_id(f[i].num_a);
        if(id1!=error)
            Update(id1,i);
        int id2=get_id(f[i].num_b);
        if(id2!=error)
            Update(id2,i);
        int id3=get_id(f[i].res);
        if(id3!=error&&f[i].op!=casesy)
             Update(id3,i);
        if(id1!=error)cout<<f[i].num_a<<" "<<get_regname(f[i].num_a)<<endl;
        if(id2!=error)cout<<f[i].num_b<<" "<<get_regname(f[i].num_b)<<endl;
        if(f[i].op!=casesy&&id3!=error)cout<<f[i].res<<" "<<get_regname(f[i].res)<<endl;
        if(f[i].op==scanfsy)
        {
            create_sentence("addi","$zero","5","$v0");
            create_sentence("syscall","NULL","NULL","NULL");
            create_sentence("add","$zero","$v0",get_regname(f[i].num_a));
            continue;
        }
        if(f[i].op==printfsy)
        {
            create_sentence("addi","$zero","1","$v0");
            create_sentence("add","$zero",get_regname(f[i].num_a),"$a0");
            create_sentence("syscall","NULL","NULL","NULL");
            continue;
        }
        if(is_branch(f[i].op))
        {
            if(lookahead_if(i+1)||lookahead_while(i+1))
            {
                if(lookahead_while(i+1))
                {
                    target=f[i-1].res;
                    rec_tag=true;
                }
                string res=f[i+1].res;
                string op=get_inv_branch(f[i].op);
                string num_a;
                string num_b;
                if(id1!=error)
                    num_a=get_regname(f[i].num_a);
                else 
                {
                    create_sentence("addi","$zero",f[i].num_a,"$t5");
                    num_a="$t5";
                }
                if(id2!=error)
                    num_b=get_regname(f[i].num_b);
                else 
                {
                    create_sentence("addi","$zero",f[i].num_b,"$t6");
                    num_b="$t6";
                }
                create_sentence(op,num_a,num_b,res);
           }
        }
        else if(is_switch(f[i].op))
        {
            switch_tag=true;
            switch_end=String_to_Int(f[i].res);
        }
        else if(switch_tag)
        {
            if(i==switch_end)switch_tag=false;
            else
            {
                if(is_case(f[i].op))
                {
                    create_sentence("addi","$zero",f[i].num_b,"$t5");
                    create_sentence("bne",get_regname(f[i].num_a),"$t5",f[i].res);
                }
                else create_assemble(i);
            }
        }
        else 
            create_assemble(i);
        if(f[i+1].op==setlab&&f[i].res.find("exit")!=string::npos)
            return_funct();
        //printf("over in the %dth\n",i);
        //check();
    }
    return_funct();
    set_lab("maintail");
    //fprintf(f,"%s %d\n", str.substr(i,dd).c_str(),identi);
    fprintf(ff,".data\n");
    fprintf(ff,".text\n");
    //fprintf(ff,"subu $sp $sp 4");
    //fprintf(ff,"move $sp $ra\n");
    //$fp -> 存的上一个栈的地址
    //$sp -> 存的当前的栈地址
    //$ra -> 当前PC的下一个值
    fprintf(ff,"move $s0 $gp\n");
    for(int i=0;i<(int)A_S.size();i++)
    {
        if(A_S[i].op.find("funct")!=string::npos)
        {
            fprintf(ff,"%s:\n",A_S[i].op.c_str());
            continue;
        }
        if((A_S[i].op.find("LABEL")!=string::npos)||(A_S[i].op.find("CYCLE")!=string::npos))
        {
            //cout<<A_S[i].op<<":"<<endl;
            fprintf(ff,"%s:\n",A_S[i].op.c_str());
            continue;
        }
        if((A_S[i].op.find("CASE")!=string::npos)||(A_S[i].op.find("DEFAULT")!=string::npos))
        {
            fprintf(ff,"%s:\n",A_S[i].op.c_str());
            continue;
        }
        if(A_S[i].op.find("syscall")!=string::npos)
        {
            fprintf(ff,"%s\n",A_S[i].op.c_str());
            continue;
        }
        if(A_S[i].op=="j"||A_S[i].op=="jr")
        {
            fprintf(ff,"%s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str());
            continue;
        }
        if(A_S[i].op=="main"||A_S[i].op=="maintail")
        {
            fprintf(ff,"%s:\n",A_S[i].op.c_str());
            continue;
        }
        if(A_S[i].op=="sw"||A_S[i].op=="lw")
        {
            fprintf(ff,"%s %s %s\n",A_S[i].op.c_str(),A_S[i].op_b.c_str(),A_S[i].res.c_str());
            continue;
        }
        if(A_S[i].op=="move")
        {
            fprintf(ff,"%s %s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str(),A_S[i].op_b.c_str());
            continue;
        }
        if(A_S[i].op=="jal")
        {
            fprintf(ff,"%s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str());
            continue;
        }
        if(A_S[i].op=="beq"||A_S[i].op=="bne")
        {
            //cout<<A_S[i].op<<" "<<A_S[i].op_a<<" "<<A_S[i].op_b<<" "<<A_S[i].res<<endl;
            fprintf(ff,"%s %s %s %s\n",A_S[i].op.c_str(),A_S[i].op_a.c_str(),A_S[i].op_b.c_str(),A_S[i].res.c_str());
            continue;
        }
        if(A_S[i].op=="li")
        {
            fprintf(ff,"%s %s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str(),A_S[i].op_b.c_str());
            continue;
        }
        if(A_S[i].op=="mflo"||A_S[i].op=="mfhi")
        {
            fprintf(ff,"%s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str());
            continue;
        }
        if(A_S[i].op=="mult"||A_S[i].op=="div")
        {
            fprintf(ff,"%s %s %s\n",A_S[i].op.c_str(),A_S[i].op_a.c_str(),A_S[i].op_b.c_str());
            continue;
        }
        //cout<<A_S[i].op<<" "<<A_S[i].res<<" "<<A_S[i].op_a<<" "<<A_S[i].op_b<<endl;
        fprintf(ff,"%s %s %s %s\n",A_S[i].op.c_str(),A_S[i].res.c_str(),A_S[i].op_a.c_str(),A_S[i].op_b.c_str());
    }

    //fprintf(ff,"jal $zero\n");  //return 0
}

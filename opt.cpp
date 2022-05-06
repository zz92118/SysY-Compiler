#include"global.h"
#include<iostream>
using namespace std;



vector <midcode> midcode_vector;

bool isin_basic_block(midcode m)
{
    if(m.op=="jmp" || m.op=="jne" ||m.op=="jeq" || m.op=="L" || m.op=="call" || m.op=="call_return" || m.op=="end_func" || m.op=="para")
    {
        return false;
    }

    return true;
}
void del_common_expression()
{
    int i;//第一个四元式
    int j;//第二个四元式
    int k;//检查中间有没有被修改的四元式
    for(i=0;i<midcode_vector.size();i++)
    {
        // 开始处理基本快
        // 通过func进入一个基本块
        if(midcode_vector[i].op=="+"||midcode_vector[i].op=="="||midcode_vector[i].op=="*"||midcode_vector[i].op=="/")
        {
            // i: (+,a,b,t1)
            // j: (+,a,b,t2)
            // a!=t1 && b!=t1
            if(midcode_vector[i].arg1!=midcode_vector[i].result && midcode_vector[i].arg2!= midcode_vector[i].result)
            {
                // int j;
                j=i+1;//便利到后来的四元式
                for(;j<midcode_vector.size() && isin_basic_block(midcode_vector[j]) ; j++)
                {
                    //找到相同的四元式
                    if( midcode_vector[j].op==midcode_vector[i].op)
                    {
                        // 加法和乘法可以交换 j: (+,a,b,t2)
                        if( (midcode_vector[j].arg1==midcode_vector[i].arg1 && midcode_vector[j].arg2==midcode_vector[i].arg2) || ((midcode_vector[j].op=="+" || midcode_vector[j].op=="*") && midcode_vector[i].arg1==midcode_vector[j].arg2 && midcode_vector[i].arg2==midcode_vector[j].arg1))
                        {
                            k=i+1; //用于寻找中间的四元式有没有被修改的
                            for(;k<j;k++)
                            {
                                // 中间的指令对i的任何一个操作数有修改 则推出K的循环，下面的k==j分支不会被执行到
                                // ！！！！！！！！！数组的处理
                                if( midcode_vector[k].op=="+" || midcode_vector[k].op=="-" || midcode_vector[k].op=="*" || midcode_vector[k].op=="/" || midcode_vector[k].op=="[]=" || midcode_vector[k].op=="=" || midcode_vector[k].op=="=[]")
                                {
                                    if(midcode_vector[k].result==midcode_vector[i].arg1 ||midcode_vector[k].result==midcode_vector[i].arg2 || midcode_vector[k].result==midcode_vector[i].result)
                                    {
                                        break;
                                    }
                                }
                            }

                            if(k==j) //遍历到表达式J
                            {
                                // 删除公共子表达式 存储的变量一样且没有被修改
                                midcode_vector[j].op="=";
                                midcode_vector[j].arg1=midcode_vector[i].result;
                                midcode_vector[j].arg2 = "";

                            }
                        }

                    }

                }
            }
        }
        
    }
}

void algebraic_identity()
{
    int i=0;

    for(i=0;i<midcode_vector.size();i++)
    {
        if(midcode_vector[i].op=="+")
        {
            if(midcode_vector[i].arg1=="0"|| midcode_vector[i].arg2=="0")
            {
                //削弱加法操作，改成赋值
                midcode_vector[i].op="=";
                if(midcode_vector[i].arg2=="0")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg1;
                    midcode_vector[i].arg2="";
                }
                else if(midcode_vector[i].arg1=="0")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg2;
                    midcode_vector[i].arg2="";
                }
            }
        }
// 减法
        else if(midcode_vector[i].op=="-")
        {
            if(midcode_vector[i].arg2=="0")
            {
                //削弱减法操作，改成赋值
                // 
                midcode_vector[i].op="=";
                midcode_vector[i].arg1=midcode_vector[i].arg1;
                midcode_vector[i].arg2="";
            }
        }
         

        else if(midcode_vector[i].op=="*")
        {
            // 0
            if(midcode_vector[i].arg2=="0"|| midcode_vector[i].arg1=="0")
            {
                //削乘法法操作，改成赋值
                // 
                midcode_vector[i].op="=";
                midcode_vector[i].arg1="0";
                midcode_vector[i].arg2="";
            }
            // 1

            else if(midcode_vector[i].arg1=="1"||midcode_vector[i].arg2=="1")
            {
                midcode_vector[i].op="=";
                if(midcode_vector[i].arg2=="1")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg1;
                    midcode_vector[i].arg2="";
                }
                else if(midcode_vector[i].arg1=="1")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg2;
                    midcode_vector[i].arg2="";
                }
            }

            else if(midcode_vector[i].arg1=="2"||midcode_vector[i].arg2=="2")
            {
                midcode_vector[i].op="+";
                if(midcode_vector[i].arg2=="2")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg1;
                    midcode_vector[i].arg2=midcode_vector[i].arg1;
                }
                else if(midcode_vector[i].arg1=="2")
                {
                    midcode_vector[i].arg1=midcode_vector[i].arg2;
                    midcode_vector[i].arg2=midcode_vector[i].arg2;
                }
            }
            // 2

        }           

        else if(midcode_vector[i].op=="/")
        {
            if(midcode_vector[i].arg1=="0")
            {
                midcode_vector[i].op="=";
                midcode_vector[i].arg1="0";
                midcode_vector[i].arg2="";

            }
            else if(midcode_vector[i].arg2=="1")
            {
                midcode_vector[i].op="=";
                midcode_vector[i].arg1=midcode_vector[i].arg1;
                midcode_vector[i].arg2="";
            }
        }
    }

    // 常量合并 constant folding
    for(i=0;i<midcode_vector.size();i++)
    {
        if(midcode_vector[i].op=="+" || midcode_vector[i].op=="-" || midcode_vector[i].op=="*" || midcode_vector[i].op=="/")
        {
            if(isnum(midcode_vector[i].arg1) && isnum(midcode_vector[i].arg2))
            {
                int t1=to_num(midcode_vector[i].arg1);
                int t2=to_num(midcode_vector[i].arg2);
                int temp_result=0;

                if(midcode_vector[i].op=="+")
                {
                    temp_result=t1+t2;
                }
                else if(midcode_vector[i].op=="-")
                {
                    temp_result=t1-t2;
                }
                else if(midcode_vector[i].op=="*")
                {
                    temp_result=t1*t2;
                }
                else if(midcode_vector[i].op=="/")
                {
                    temp_result=t1/t2;
                }
                midcode_vector[i].op="=";
                midcode_vector[i].arg1=to_string(temp_result);
                midcode_vector[i].arg2="";
                midcode_vector[i].result=midcode_vector[i].result;       
            }
        }
    }
}

void del_temp()
{
    int i;
    for(i=0;i<midcode_vector.size();i++)
    {
        if(midcode_vector[i].op=="+" || midcode_vector[i].op=="-" || midcode_vector[i].op=="*" || midcode_vector[i].op=="/" || midcode_vector[i].op=="=")
        {
            // 是临时变量
            if(midcode_vector[i].result[0]=='$')
            {
                if( ((i+1)<midcode_vector.size()) && midcode_vector[i+1].op=="=" && midcode_vector[i].result==midcode_vector[i+1].arg1)
                {
                    midcode_vector[i].result=midcode_vector[i+1].result;
                    midcode_vector.erase(midcode_vector.begin()+i+1);
                }
            }
        }

        else if(midcode_vector[i].op=="=" && midcode_vector[i].result[0]=='$')
        {
            if(((i+1)<midcode_vector.size()) && (midcode_vector[i+1].op=="=") && midcode_vector[i+1].arg1==midcode_vector[i].result)
            {
                midcode_vector[i].result=midcode_vector[i+1].result;
                midcode_vector.erase(midcode_vector.begin()+i+1);
            }
        }
    }
}

void const_propogation()
{
    int i;
    int j;
    int k;
    for(i=0;i<midcode_vector.size();i++)
    {
        // i 赋值语句，且右值是常量
        if(midcode_vector[i].op=="=" && isnum(midcode_vector[i].arg1))
        {
            j=i+1;
            // 找到下一个使用的语句
            for(;j<midcode_vector.size() && isin_basic_block(midcode_vector[j]);j++)
            {
                // j算数运算 对j的运算符进行修改
                // (=,1,,a)
                // (+,a,b,c)-->(+,1,b,c)
                // (+,b,a,c)-->(+,b,1,c)
                if(midcode_vector[j].op=="+" || midcode_vector[j].op=="-" || midcode_vector[j].op=="*" ||midcode_vector[j].op=="/" ||midcode_vector[j].op=="<" ||midcode_vector[j].op==">" || midcode_vector[j].op=="<=" ||midcode_vector[j].op==">=")//!= ==
                {
                    if(midcode_vector[i].result==midcode_vector[j].arg1 || midcode_vector[i].result==midcode_vector[j].arg2)
                    {
                        //找到语句之后查看修改
                        k=i+1;
                        for(;k<j;k++)
                        {
                            // 数组的处理！！！！！！！！
                            if(midcode_vector[k].op=="+"||midcode_vector[k].op=="-"||midcode_vector[k].op=="*"||midcode_vector[k].op=="/"||midcode_vector[k].op=="array"||midcode_vector[k].op=="=")
                            {
                                if(midcode_vector[k].result==midcode_vector[i].result)
                                {
                                    break;
                                }
                            }
                        }
                        // 没有修改过 才能到的k==j的条件
                        if(k==j)
                        {
                            if(midcode_vector[i].result==midcode_vector[j].arg1)
                            {
                                midcode_vector[j].arg1=midcode_vector[i].arg1;
                            }
                            if(midcode_vector[i].result==midcode_vector[j].arg2)
                            {
                                midcode_vector[j].arg2=midcode_vector[i].arg1;
                            }
                        } 
                    }
                }
                // j是赋值语句的情况
                // (=,1,,a)
                // (=,a,,b)-->(=,1,,b)
                // -->()
                else if(midcode_vector[j].op=="=")
                {
                    if(midcode_vector[i].result==midcode_vector[j].arg1)
                    {
                        k=i+1;
                        for(;k<j;k++)
                        {
                            if(midcode_vector[k].op=="+" || midcode_vector[k].op=="-" ||midcode_vector[k].op=="*" ||midcode_vector[k].op=="/" ||midcode_vector[k].op=="=[]" || midcode_vector[k].op=="="||midcode_vector[k].op=="[]=")
                            {
                                if(midcode_vector[k].result==midcode_vector[i].result)
                                {
                                    break;
                                }
                            }
                        }

                        if(k==j)
                        {
                            midcode_vector[j].arg1=midcode_vector[i].arg1;
                        }
                    }
                }
            }
        }
    }
}


void local_opt()
{
    const_propogation();
    del_common_expression();
    del_temp();
    algebraic_identity();
}

void opt_test()
{
    cout << "-------IR optimization-------"<<endl;
    cout <<endl<< "-------before-------" << endl<<endl;
    //gen_test_mide_code();

    for (int i = 0; i < midcode_vector.size(); i++)
    {
        cout << setiosflags(ios::left);

        cout << setw(3) << i + 1 << ": " << setw(15) << midcode_vector[i].op << setw(15) << midcode_vector[i].arg1 << setw(15) << midcode_vector[i].arg2 << setw(15) << midcode_vector[i].result << endl;

    }
    //del_common_expression();
    local_opt();

    cout <<endl<< "-------after-------" << endl<<endl;
    for (int i = 0; i < midcode_vector.size(); i++)
    {
        cout << setiosflags(ios::left);

        cout << setw(3) << i + 1 << ": " << setw(15) << midcode_vector[i].op << setw(15) << midcode_vector[i].arg1 << setw(15) << midcode_vector[i].arg2 << setw(15) << midcode_vector[i].result << endl;

    }
}

void gen_test_mide_code()
{
    midcode m;
    m.op = "*";
    m.arg1 = "$t1";
    m.arg2 = "2";
    m.result = "$t2";
    midcode_vector.push_back(m);

    m.op = "*";
    m.arg1 = "a";
    m.arg2 = "$t2";
    m.result = "$t3";
    midcode_vector.push_back(m);

    m.op = "=";
    m.arg1 = "a";
    m.arg2 = "";
    m.result = "b";
    midcode_vector.push_back(m);


    //m.op = "*";
    //m.arg1 = "b";
    //m.arg2 = "a";
    //m.result = "$t3";
    //midcode_vector.push_back(m);

}

//void gen_test_mide_code()
//{
//    midcode m;
//    m.op = "*";
//    m.arg1 = "a";
//    m.arg2 = "f";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "1";
//    m.arg2 = "2";
//    m.result = "g";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "1";
//    m.arg2 = "3";
//    m.result = "z";
//    midcode_vector.push_back(m);
//
//    m.op = "end_fuc";
//    m.arg1 = "1";
//    m.arg2 = "3";
//    m.result = "z";
//    midcode_vector.push_back(m);
//
//
//    m.op = "*";
//    m.arg1 = "f";
//    m.arg2 = "a";
//    m.result = "$t3";
//    midcode_vector.push_back(m);
//
//}


//void gen_test_mide_code()
//{
// 删除冗余临时变量
//    midcode m;
//    m.op = "=";
//    m.arg1 = "5";
//    m.arg2 = "";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "=";
//    m.arg1 = "$t1";
//    m.arg2 = "";
//    m.result = "b";
//    midcode_vector.push_back(m);
//
//    m.op = "+";
//    m.arg1 = "b";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "=";
//    m.arg1 = "$t1";
//    m.arg2 = "";
//    m.result = "c";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "b";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "=";
//    m.arg1 = "$t1";
//    m.arg2 = "";
//    m.result = "c";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "b";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "-";
//    m.arg1 = "$t1";
//    m.arg2 = "";
//    m.result = "c";
//    midcode_vector.push_back(m);
//
//    m.op = "+";
//    m.arg1 = "b";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "=";
//    m.arg1 = "$t2";
//    m.arg2 = "";
//    m.result = "c";
//    midcode_vector.push_back(m);
//
//}



//void gen_test_mide_code()
//{
//  算术运算
//    midcode m;
//    m.op = "+";
//    m.arg1 = "a";
//    m.arg2 = "0";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "+";
//    m.arg1 = "1";
//    m.arg2 = "2";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "0";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "2";
//    m.arg2 = "10";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "1";
//    m.arg2 = "0";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "a";
//    m.arg2 = "1";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "*";
//    m.arg1 = "a";
//    m.arg2 = "2";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "-";
//    m.arg1 = "a";
//    m.arg2 = "0";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "/";
//    m.arg1 = "0";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "/";
//    m.arg1 = "3";
//    m.arg2 = "3";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "/";
//    m.arg1 = "3";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//    m.op = "-";
//    m.arg1 = "3";
//    m.arg2 = "a";
//    m.result = "$t1";
//    midcode_vector.push_back(m);
//
//}
//

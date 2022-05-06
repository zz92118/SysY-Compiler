#include"global.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int address_pointer=0;
int midcode_index=0;

string outfilename;

string objmips="";
ofstream mipswrite;
int globaladdr=0;
int sp;
string reg[16]; //0-7为t 8-15为s


// string function_name;

//生成mips并且写入txt
void mips_to_text();
void midcode_to_mips();
void lw_mips(string register,string arg1);
void sw_mips(string register,string arg1);
int var_address(string name);
void ret_mips();
void int_call_mips();
void void_call_mips();
void para_mips();
void function_mips();
void main_function_mips();
void algbra_mips();
void logic_mips();
void assign_mips();
void global_mips();
 

// void push_all_global_variable();
// void push_all_global_const();
// void push_all_local_variable();

// void push_global_stack();
// void push_local_stack();
// // size是1 使用的时候不要忘了*4
// void push_global_stack_array(int size);
// void push_local_stack_array(int size);


void insert_address(int index,int size);

void jump_mips(string s);
void genmips(string s);

bool isid(string s);
bool isnum(string s);


int var_addr(string s);

void mips_to_text()
{
   //outfilename;
   mipswrite.open("test.asm");
   //mipswrite << "123";
   mipswrite<<objmips;
}

void midcode_to_mips()
{
// 1.数据段
   genmips(".data");
   // push_all_global_const();
   // global const 在这里？
   // label
   // 函数实现未完成
    global_mips();

// 2.代码段

   genmips("");
   genmips(".text");
   //genmips("ori\t$fp\t$sp\t0");
   //genmips("li\t$t9\t0x7fffeffc"); //global stack bottom
   //genmips("li\t$t8\t0x10010000");//save word

/////////////////
//全局变量和全局常量

// main函数入口 j main
   genmips("j main");
// 函数定义 跳过变量定义


   for(;midcode_index<midcode_vector.size();midcode_index++)
   {

       //函数开始
       if(midcode_vector[midcode_index].op=="func" && midcode_vector[midcode_index].result!="main")
       {
          function_mips();
       }
       // main 开始
       else if(midcode_vector[midcode_index].op=="func" && midcode_vector[midcode_index].result=="main")
       {
           main_function_mips();
       }
       //实参 入栈  
       else if(midcode_vector[midcode_index].op=="para")
       {
           para_mips();
       }

// 没懂
       else if(midcode_vector[midcode_index].op=="void_call")
       {
           void_call_mips();
       }

       else if(midcode_vector[midcode_index].op=="int_call")
       {
           int_call_mips();
       }
// 被调用函数执行ret语句
       else if(midcode_vector[midcode_index].op=="ret")
       {
           ret_mips();
           
       }
       else if(midcode_vector[midcode_index].op=="-" || midcode_vector[midcode_index].op=="+" || midcode_vector[midcode_index].op=="*" ||midcode_vector[midcode_index].op=="/" || midcode_vector[midcode_index].op=="%")
       {
           algbra_mips();
       }

       else if(midcode_vector[midcode_index].op==">" || midcode_vector[midcode_index].op==">=" || midcode_vector[midcode_index].op=="<" ||midcode_vector[midcode_index].op=="<=" || midcode_vector[midcode_index].op=="==" || midcode_vector[midcode_index].op=="!+")
       {
           logic_mips();
       }
       
       else if(midcode_vector[midcode_index].op=="L")
       {
           genmips(midcode_vector[midcode_index].result+":");
       }

       else if(midcode_vector[midcode_index].op=="jmp")
       {
           genmips("\tj\t"+midcode_vector[midcode_index].result);
       }

       else if(midcode_vector[midcode_index].op=="L:")
       {
           genmips(midcode_vector[midcode_index].result+":");
       }

       else if(midcode_vector[midcode_index].op=="=")
       {
           assign_mips();
       }

// 左赋值
       else if(midcode_vector[midcode_index].op=="[]=")
       {
           assign_array();
       }
// 右赋值
       else if(midcode_vector[midcode_index].op=="=[]")
       {
           equal_array();
       }
// 局部变量
       else if(midcode_vector[midcode_index].op=="var")
       {
        //    push_to_stack();
       }

       else if(midcode_vector[midcode_index].op=="const")
       {
           push_to_stack(); //存储常量初值
       }

       else if(midcode_vector[midcode_index].op=="putint")
       {
           if(isnum(midcode_vector[midcode_index].result))
           {
               genmips("\tli\t$a0,"+midcode_vector[midcode_index].result);
           }
           else 
           {
               lw_mips("$a0",midcode_vector[midcode_index].result);
           }

           genmips("\tli\t$v0,1");
           genmips("\tsyscall");
       }




   }
//    mips_to_text();


}






void sort_variables()
{

}




void jump_mips(string s)
{
   genmips("j "+s);
}

void genmips(string s)
{
   objmips+=s;
   objmips += "\n";
}




void void_call_mips()
{
   genmips("\tsubi\t$sp,$sp,4");
   genmips("\tjal\t"+midcode_vector[midcode_index].arg1);
   int temp_n=get_function(midcode_vector[midcode_index].arg1).parameter_num;
   genmips("\taddi\t$sp,$sp,"+to_string(4*temp_n));
}

void int_call_mips()
{
   genmips("\tsubi\t$sp,$sp,4");
   genmips("\tjal\t"+midcode_vector[midcode_index].arg1);
   //跳转执行
   int temp_n=get_function(midcode_vector[midcode_index].arg1).parameter_num;
   genmips("\taddi\t$sp,$sp,"+to_string(4*temp_n));//加回来
   sw_mips("$v1",midcode_vector[midcode_index].result);
   //返回值保存在 v1(调用结束后保存在v1)
}

// 加入寄存器
void para_mips()
{
   if(isnum(midcode_vector[midcode_index].result))
   {
       // 开辟空间 sp-4
       // 
       genmips("\tsubi\t$sp,$sp,4");
       genmips("\tli\t$t1,"+midcode_vector[midcode_index].result);
       genmips("\tsw\t$t1,0($sp)");
   }
   //
   else 
   {
       genmips("\tsubi\t$sp,$sp,4");
       lw_mips("$t1",midcode_vector[midcode_index].result);
       genmips("\tsw\t$t1,0($sp)");
   }
}

// 在被调用的函数
void ret_mips()
{
   if(function_name!="main")
   {
       // void
       if(midcode_vector[midcode_index].result=="")
       {
           // 不对返回值进行处理
       }
       // int 
       else
       {
           if(isnum(midcode_vector[midcode_index].result))
           {
               genmips("\tli\t$v1,"+midcode_vector[midcode_index].result);
           }
           else
           {
               // 写入内存。
               lw_mips("$v1",midcode_vector[midcode_index].result);
           }
       }
       genmips("\t#return");
       genmips("\tadd\t$sp,$fp,$0");//直接让sp=fp吧？
       genmips("\tlw\t$ra,0($sp)");
       genmips("\taddi\t$sp,$sp,4");
       genmips("\tlw\t$fp,-8($sp)");
       genmips("\tjr\t$ra");
   }
   
//返回 最后有个退出
   else if(function_name=="main")
   {
        genmips("\t#return main");
    //    genmips("\tadd\t$sp,$fp,$0");//直接让sp=fp吧？
    //    genmips("\tlw\t$ra,0($sp)");
    //    genmips("\taddi\t$sp,$sp,4");
    //    genmips("\tlw\t$fp,-8($sp)");
    //    genmips("\tjr\t$ra");
   }

}

void algbra_mips()
{
   //arg1 立即数或者变量
   if(isnum(midcode_vector[midcode_index].arg1))
   {
       genmips("\tli\t$t1,"+midcode_vector[midcode_index].arg1);
   }
   else
   {
       lw_mips("$t1",midcode_vector[midcode_index].arg1);
   }
   //arg2 立即数或者变量
   if(isnum(midcode_vector[midcode_index].arg2))
   {
       genmips("\tli\t$t2,"+midcode_vector[midcode_index].arg2);
   }
   else
   {
       lw_mips("$t2",midcode_vector[midcode_index].arg2);
   }

   if(midcode_vector[midcode_index].op=="+")
   {
       genmips("\tadd\t$t3,$t1,$t2");
       sw_mips("$t3",midcode_vector[midcode_index].result);
   }

   else if(midcode_vector[midcode_index].op=="-")
   {
       genmips("\tsub\t$t3,$t1,$t2");
       sw_mips("$t3",midcode_vector[midcode_index].result);      
   }
   
   else if(midcode_vector[midcode_index].op=="*")
   {
       genmips("\tmul\t$t3,$t1,$t2");
       sw_mips("$t3",midcode_vector[midcode_index].result);        
   }
   
   else if(midcode_vector[midcode_index].op=="/")
   {
       genmips("\tdiv\t$t3,$t1,$t2");
       genmips("\tmflo\t$t3");
       sw_mips("$t3",midcode_vector[midcode_index].result);       
   }
   
   else if(midcode_vector[midcode_index].op=="%")
   {
       
   }
}


void logic_mips()
{
   //arg1 立即数或者变量
   if(isnum(midcode_vector[midcode_index].arg1))
   {
       genmips("\tli\t$t1,"+midcode_vector[midcode_index].arg1);
   }
   else
   {
       lw_mips("$t1",midcode_vector[midcode_index].arg1);
   }
   //arg2 立即数或者变量
   if(isnum(midcode_vector[midcode_index].arg2))
   {
       genmips("\tli\t$t2,"+midcode_vector[midcode_index].arg2);
   }
   else
   {
       lw_mips("$t2",midcode_vector[midcode_index].arg2);
   }


   if(midcode_vector[midcode_index].op==">")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tbgt\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tble\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }
   else if(midcode_vector[midcode_index].op=="<")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tblt\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tbge\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }
   else if(midcode_vector[midcode_index].op==">=")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tbge\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tblt\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }
   else if(midcode_vector[midcode_index].op=="<=")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tble\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tbgt\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }
   else if(midcode_vector[midcode_index].op=="==")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tbeq\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tbne\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }
   else if(midcode_vector[midcode_index].op=="!=")
   {
       if(midcode_vector[midcode_index+1].op=="j" || midcode_vector[midcode_index+1].op=="jeq")
       {
           genmips("\tbne\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
       else
       {
           genmips("\tbeq\t$t1,$t2,"+midcode_vector[midcode_index+1].result);
       }
   }

}

void assign_mips()
{
   if(isnum(midcode_vector[midcode_index].arg1))
   {
       genmips("\tli\t$t1,"+midcode_vector[midcode_index].arg1);
   }
   else 
   {
       lw_mips("$t1",midcode_vector[midcode_index].arg1);
   }
   sw_mips("$t1",midcode_vector[midcode_index].result);
}

void assign_array()
{
    //l
    // a[1]=2
    //下标
    if(isnum(midcode_vector[midcode_index].arg2))
    {
        genmips("\tli\t$t1,"+midcode_vector[midcode_index].arg2);
    }
    else
    {
        lw_mips("$t1",midcode_vector[midcode_index].arg2);
    }
    genmips("\tsll\t$t1,$t1,2\n");

    //数组名 首地址
    int offest=var_addr(midcode_vector[midcode_index].result);
    if(offest==-1)
    {
        genmips("\tla\t$t2,"+midcode_vector[midcode_index].result);
        genmips("\tadd\t$t3,$t2,$t1");
    }
    else
    {
        genmips("\tla\t$t2,"+to_string(offest)+"($fp)");
        genmips("\tsub\t$t3,$t2,$t1");
    }

    //相对偏移

    //赋值的临时变量
    if(isnum(midcode_vector[midcode_index].arg1))
    {
        genmips("\tli\t$t2,"+midcode_vector[midcode_index].arg1);
    }
    else 
    {
        lw_mips("$t2",midcode_vector[midcode_index].arg1);
    }
    
    //赋值 存储临时变量
    genmips("\tsw\t$t2,0($t3)");

}
void equal_array()
{
    //r
    // t=a[1]
    //下标
    if(isnum(midcode_vector[midcode_index].arg2))
    {
        genmips("\tli\t$t1,"+midcode_vector[midcode_index].arg2);
    }
    else
    {
        lw_mips("$t1",midcode_vector[midcode_index].arg2);
    }
    genmips("\tsll\t$t1,$t1,2\n");

    //数组名 首地址
    int offest=var_addr(midcode_vector[midcode_index].arg1);
    if(offest==-1)
    {
        genmips("\tla\t$t2,"+midcode_vector[midcode_index].arg1);
        genmips("\tadd\t$t3,$t2,$t1");

    }
    else
    {
        genmips("\tla\t$t2,"+to_string(offest)+"($fp)");
        genmips("\tsub\t$t3,$t2,$t1");

    }

    //t2放地址

    //相对偏移
    //找到a[1]
    genmips("\tlw\t$t2,0($t3)");

    sw_mips("$t2",midcode_vector[midcode_index].result);
}


void lw_mips(string register_name,string name)
{
   int off_address = var_addr(name);
   if(off_address!=-1)
   {
       genmips("\tlw\t"+register_name+","+to_string(off_address)+"($fp)");
   }
   else if(off_address==-1)
   {
       genmips("\tla\t$t1,"+name);
       //la指令被翻译成 lui和ori
       genmips("\tlw\t"+register_name+",0($t1)");        
   }
}

void sw_mips(string register_name,string name)
{
   int off_address = var_addr(name);
   // 运行时站
   if(off_address!=-1)
   {
       genmips("\tsw\t"+register_name+","+to_string(off_address)+"($fp)");
   }
   // 全局符号表
   else if(off_address==-1)
   {
       genmips("\tla\t$t2,"+name);
       //la指令被翻译成 lui和ori
       genmips("\tsw\t"+register_name+",0($t2)");        
   }
}

int var_addr(string name)
{
    if(contain_variable(name))
    {
        variable_symbol s=check_and_get_variable(name);
        if(s.function=="global")
        {
            return -1;
        }

        else
        {
            function_symbol f=get_function(function_name);
            if(s.addr<f.parameter_num)
            {
                return (f.parameter_num-s.addr)*4;
            }
            // 不是参数了
            // 在fp以下？

            // 参数
            // fp-------------
            // 当前函数栈 
            else
            {
                return -((s.addr-f.parameter_num)*4)-8;
            }

        }
    }
//如果是临时变量呢？

    else
    {

    }

}

void push_to_stack()
{

    variable_symbol symbol=check_and_get_variable(midcode_vector[midcode_index].result);
    string kind=symbol.kind;
    int size=symbol.size;
    string name=symbol.name;
    int val=symbol.value;

    if(midcode_vector[midcode_index].op=="var")
    {
        if(size==0)
        {
            genmips("\tsubi\t$sp,$sp,4 #stack for global variable");

        }

        else if(size!=0)
        {
            string tempsize=to_string(4*size);
            genmips("\tsubi\t$sp,$sp," + tempsize + "\t#stack for global variable");
        }
    }
// 要存储初值。
    else if(midcode_vector[midcode_index].op=="const")
    {
        // genmips("\tsubi\t$sp,$sp,4\t#stack for global const");
        genmips("\tli\t$t1,"+to_string(val));
        genmips("\tsw\t$t1,"+to_string(var_addr(name))+"($fp)"+"\t#store const");
    }
}

void global_mips()
{
    int i;
   for(i=0;i<table.All_variable.size();i++)
   {
       variable_symbol s=table.All_variable[i];
       if(s.function=="global")
       {
           //基本类型
           if(s.size==0)
           {
                if(s.kind=="var")
                {
                    genmips(s.name+":\t.word\t"+to_string(s.value));
                }

                else if(s.kind=="const")
                {
                    genmips(s.name+":\t.word\t"+to_string(s.value));
                }
           }
            //数组
           else
           {
               if(s.kind=="var")
               {
                   genmips(s.name+":\t.space\t"+to_string(s.size*4));
               }
           }

       }

   }
}

void function_mips()
{
    init_register();
   function_name=midcode_vector[midcode_index].result;
   genmips(midcode_vector[midcode_index].result+":");//生成一个label？
   // 保存现场
   // save();
   genmips("\tsw\t$ra,0($sp)"); //sw $ra 0($sp) 上一个函数的sp
   genmips("\tsw\t$fp,-4($sp)");// sw $fp,-4($sp) 上一个函数的fp
   genmips("\tadd\t$fp,$sp,$0"); //本函数的fp=sp
   //查符号表
   //参数调用的时候生成对sp操作，sp-4*size;
   int mips_parameter_num=(get_function(function_name).total_offset-get_function(function_name).parameter_num)*4;//这个数字debug一下
   genmips("\tsubi\t$sp,$sp,"+to_string(mips_parameter_num));//开辟栈空间 sp-4*size;
}


void main_function_mips()
{
    init_register();
    function_name = "main";
    genmips(midcode_vector[midcode_index].result+":");
    genmips("\t#main head");
    genmips("\tsw\t$ra,($sp)");//save $ra
    // genmips("\tsw\t$fp,-4($sp)");//sp-4
    genmips("\tadd\t$fp,$sp,$0"); //fp=sp 

    int mips_parameter_num=(get_function(function_name).total_offset-get_function(function_name).parameter_num)*4;//这个数字debug一下
   genmips("\tsubi\t$sp,$sp,"+to_string(mips_parameter_num));//开辟栈空间 sp-4*size;

    //main函数没有参数

    function_symbol f=get_function("main");

    // genmips("")
}

//参数个数+局部变量的存储空间

void save()
{
    int i;
    for(i=0;i<8;i++)
    {
        // genmips("\tsw\t");
    }
}


string allocate_register(string temp)
{
    int i;

    //没有满 就分配一个
    for (i = 0; i < 16; i++)
    {
        //分配
        if (reg[i] == "")
        {
            reg[i] = temp;
            {
                if (i < 8)
                {
                    return ("$t" + to_string(i));
                }

                else
                {
                    return ("$s" + to_string(i - 8));
                }
            }
            break;
        }
    }
    //寄存器满了 就从头开始分配
    // 分配 a1-a3
    return "";
}

void init_register()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        reg[i] = "";
    }
}

//没有找到就返回"" 然后从内存中取， 再给他分配一个寄存器
string find_in_register(string temp)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        if (reg[i] == temp)
        {
            if (i < 8)
            {
                return ("$t" + to_string(i));
            }

            else
            {
                return ("$s" + to_string(i - 8));
            }
        }
    }
    //寄存器中没有
    for (i = 0; i < 16; i++)
    {
        if (reg[i] == "")
        {
            return ""; //寄存器没有 而且没有满
        }

    }
    return "full";
}


// #include"global.h"
// #include<iostream>
// #include<fstream>
// #include<string>
// using namespace std;

// string objmips="";
// ofstream mipswrite;
// int globaladdr=0;
// int midcode_index=0;
// string runtime_function_name;

// //����mips����д��txt
// void mips_to_text();
// void midcode_to_mips();

// void push_all_global_variable();
// void push_all_global_const();
// void push_all_local_variable();

// void push_global_stack();
// void push_local_stack();
// // size��1 ʹ�õ�ʱ��Ҫ����*4
// void push_global_stack_array(int size);
// void push_local_stack_array(int size);

// void jump_mips(string s);
// void genmips(string s);

// void function_mips();
// void main_mips();
// void function_head();
// void function_body();
// void function_tail();
// void main_head();

// void sort_variables();//�Ż�
// void register_allocate(midcode m);
// void store_result(string s1,string s2);

// void allocate_first(string s);
// void allocate_second(string s);
// void allocate_third(string s);
// bool isid(string s);
// bool isnum(string s);




// void midcode_to_mips()
// {
// // 1.���ݶ�
//    genmips(".data");
//    push_all_global_const();
//    // global const �����
//    // label
//    // ����ʵ��δ���

// // 2.�����

//    genmips("");
//    genmips(".text");
// //��������
//    // ����ȫ�ֱ���
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].op=="const";midcode_index++)
//    {
//    }
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].op=="var";midcode_index++)
//    {
//    }

// // 3.����ʱջ
//    // 3.1ȫ��ջ ȫ�ֱ������
//    push_all_global_variable();//����.ȫ�ֱ�������
//    // ��ת��main����
//    jump_mips("main");
//    //3.2func����վ
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].op=="func";midcode_index++)
//    {
//        if(midcode_vector[midcode_index].result!="main")
//        {
//            function_mips();
//        }
//        else if(midcode_vector[midcode_index].result=="main")
//        {
//            break;
//        }
//    }
//    //3.3 main����ջ
//    main_mips();
//    mips_to_text();
   

// }

// void register_allocate(midcode m)
// {
//    allocate_first(m.arg1);
//    allocate_second(m.arg2);
// }

// void allocate_first(string s)
// {
//    //���� ������Ѱַ
//    if(isnum(s))
//    {
//        genmips("li $t1, "+s);
//    }
//    else if(isid(s))
//    {
//        //get current func
//        variable_symbol symbol= check_and_get_variable(s);
//        string key=runtime_function_name+":"+s;
//        int index=
//        if(symbol.kind=="const")
//        {
//            genmips("li $t1, "+symbol.addr)
//        }
//    }
// }

// void allocate_second(string s)
// {

// }



// void function_mips()
// {
//    runtime_function_name=midcode_vector[midcode_index].result;
//    genmips(runtime_function_name+":");
//    midcode_index++;

//    sort_variables();//�Ż�

//    function_head();
//    function_body();
//    genmips(runtime_function_name+"Tail:");
//    function_tail();

// }

// void main_mips()
// {
//    runtime_function_name="main";
//    genmips("main:");
//    midcode_index++;
//    // main_head();
//    sort_variables();
//    genmips("sw $fp, ($sp)");
//    genmips("move $fp, $sp");
//    genmips("sub $sp, $sp, 8");
//    function_body();
//    genmips("main+Tail");
//    //exit;
// }

// void sort_variables()
// {

// }
// void function_head()
// {
//    int paramater_count;
//    int fpoffset;//fp
//    int raoffset;//return address
// }

// void function_body()
// {
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].result=="const";midcode_index++);
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].result=="var";midcode_index++);
//    push_all_local_variable();
//    for(;midcode_index<midcode_vector.size() && midcode_vector[midcode_index].result!="fun";midcode_index++)
//    {
//        midcode m=midcode_vector[midcode_index];

//        if (m.op == "+") 
//        {
//            register_allocate(m);
//            genmips("add $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "-") 
//        {
//            register_allocate(m);
//            genmips("sub $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "*") 
//        {
//            register_allocate(m);
//            genmips("mul $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "/") 
//        {
//            register_allocate(m);
//            genmips("div $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        }
//        else if(m.op=="assign")
//        {

//        }
       
//        else if (m.op == "==")
//        {
//            register_allocate(m);
//            genmips("seq $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "!=") 
//        {
//            register_allocate(m);
//            genmips("sne $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "<") 
//        {
//            register_allocate(m);
//            genmips("slt $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == "<=") 
//        {
//            register_allocate(m);
//            genmips("sle $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == ">=") 
//        {
//            register_allocate(m);
//            genmips("sgt $t0, $t1, $t2");
//            store_result(m.result, "$t0");
//        } 
//        else if (m.op == ">") 
//        {
//            register_allocate(m);
//            genmips("sge $t0, $t1, $t2");
//            store_result(m.result, "$t0");    
//        }
   

// }

// void push_all_local_variable()
// {
//        // string key=runtime_function_name+
//        //�ҵ����ű� func
//        int i;
//        for(i=0;i<table.All_variable.size();i++)
//        {
//            if(table.All_variable[i].function==runtime_function_name)
//            {
//                if(table.All_variable[i].size!=0)
//                {
//                    push_global_stack_array(table.All_variable[i].size);
//                }

//                else
//                {
//                    push_local_stack();
//                }
//            }
//        }
// }

// void jump_mips(string s)
// {
//    genmips("j "+s);
// }

// void genmips(string s)
// {
//    objmips+=s;
// }

// void mips_to_text()
// {
//    mipswrite.open("mipscode.txt");
//    mipswrite<<objmips;

// }

// //pushһ������
// void push_all_global_const()
// {
//    unsigned int i;
//    for(i=0;i<table.All_variable.size();i++)
//    {
//        variable_symbol s;
//        s=table.All_variable[i];
//        if(s.function=="global"&&s.kind=="const")
//        {
//            // 
//            // .data
//        }
//    }
// }
// void push_all_global_variable()
// {
//    unsigned int i;
//    for(i=0;i<table.All_variable.size();i++)
//    {
//        variable_symbol s;
//        s=table.All_variable[i];
//        if(s.function=="global")
//        {
//            //variable 
//            if(s.size==0)
//                {push_global_stack();}
//            //array
//            else
//            {
//                push_global_stack_array(s.size);
//            }

//        }
//    }
// }

// // һ��genһ�����ɴ���
// void push_all_local_varable()
// {
//    unsigned int i;
//    for(i=0;i<table.All_variable.size();i++)
//    {
//        variable_symbol s;
//        s=table.All_variable[i];
//        if(s.function==runtime_function_name)
//        {
//            if(s.size==0)
//            {
//                push_local_stack();
//            }
//            else if(s.size!=0)
//            {
//                push_local_stack_array(s.size);
//            }
//        }

//    }
// }


// void push_global_stack_array(int size)
// {
//    int i;
//    for(i=0;i<size;i++)
//    {
//        globaladdr++;
//    }
// }
// void push_global_stack()
// {
//    globaladdr++;
// }
// void push_local_stack() {
//    genmips("sub $sp, $sp, 4");
// }
// void push_local_stack_array(int count) {
//    // string temps="";
//    // itoa(4*count,temps,10);
//    genmips("sub $sp, $sp, " + to_string(count*4));
// }



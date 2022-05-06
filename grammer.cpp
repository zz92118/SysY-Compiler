#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>
#include<algorithm>
#include<stack>
#include"global.h"
#include"error.h"
using namespace std;

//vector<midcode> midcode_vector;
symbol_table table;

string function_name;
int address_offset=0; //记录一个variable在一个function内部的偏移。
int global_flag;

// result

int label_index = 0;
int temp_index = 0;
string temp;
//table
// symbol_table table;
//token and operater
Token currenttoken;
unsigned int currenttoken_index = 0;
int token_end_flag = 0; // judnge whether the token sequence reach the end

//recursive descent
string exp_value; //并没有涉及到任何计算,只是把两个变量的结果放到了一个新的temp临时变量当中
int function_parameter_num = 0;
int return_flag = 0;

stack<midcode> record;


//table
void init_table()
{
    // table.depth = 0;
}

//variable_symbol check_and_get_variable(string s)
//{
//    string key = function_name + ":" + s;
//    unsigned int i;
//    int 
//}

void check_and_insert_variable(variable_symbol symbol)
{
    static int addr=0;
    string key = function_name + ":" + symbol.name;
    //insert
    unsigned int i;
    int global_function_def = 0;
    for (i = 0; i < table.All_function.size(); i++)
    {
        //rename and is a global variabel
        if ((symbol.name) == table.All_function[i].name && table.index_var.count("global:" + symbol.name) == 1)
        {
            global_function_def = 1;
            break;
        }
    }
    //
    if (table.index_var.count(key) == 0 && global_function_def == 0)
    {
        table.All_variable.push_back(symbol);
        table.num_var = table.All_variable.size();
        //get index
        table.index_var[key] = table.num_var;
    }
    //re declare
    else
    {
        error("rename");
        cout << "variable " << symbol.name << " already declared in this scope"<<endl;
    }
    // global 
}

//no redeclare,golbal variable and function name,
void check_and_insert_function(function_symbol symblo)
{
    //find function 
    //vector<function_symbol>::iterator it = find(table.All_function.begin(), table.All_function.end(), symblo);
    //not in
    //globla:+symblo
    int global_variable_flag = 0;
    int function_in=0;
    unsigned int i;
    for (i = 0; i < table.All_variable.size(); i++)
    {
        //global variable and rename
        if ((symblo.name) == table.All_variable[i].name && table.index_var.count("global:" + symblo.name) == 1)
        {
            global_variable_flag = 1;
            break;
        }
    }
    //not in the table
    for (i = 0; i < table.All_function.size(); i++)
    {
        if (table.All_function[i].name == symblo.name)
        {
            function_in = 1;
            break;
        }
    }

    if ((!function_in) && global_variable_flag == 0)
    {
        table.All_function.push_back(symblo);
    }
    else
    {
        error("rename,cant insert function ");
        cout << "function " << symblo.name << " already declared in this scope" << endl;
    }

}

variable_symbol check_and_get_variable(string name)
{
    string key;
    key = "global:" + name;
    //is global variable
    //higherr priority
    if (table.index_var.count(key) == 1)
    {
        //int index = table.index_var[key];
        //return table.All_variable[index];
        int i;
        for (i = 0; i < table.All_variable.size(); i++)
        {
            if (table.All_variable[i].function == "global" && table.All_variable[i].name == name)
            {
                return table.All_variable[i];
            }
        }
    }

    if (function_name != "global")
    {
        key = function_name + ":" + name;
        if (table.index_var.count(key) == 1)
        {
            int i;
            for (i = 0; i < table.All_variable.size(); i++)
            {
                if (table.All_variable[i].function == function_name && table.All_variable[i].name == name)
                {
                    return table.All_variable[i];
                }
            }
        }
    }
    else
    {
        //error
        cout << name << "identifier not found";
    }
}

bool contain_function(string name)
{
    unsigned int i;
    for (i = 0; i < table.All_function.size(); i++)
    {
        if (table.All_function[i].name == name)
        {
            return true;
        }
    }
    return false;
}

function_symbol get_function(string name)
{
    unsigned int i;
    for (i = 0; i < table.All_function.size(); i++)
    {
        if (name == table.All_function[i].name)
        {
            return table.All_function[i];
        }
    }
}



bool contain_variable(string name)
{
    string key;
    key = "global:" + name;

    if (table.index_var.count(key) == 1)
    {
        return true;
    }

    //在局部函数也没有找到
    else if (function_name != "global")
    {
        key = function_name + ":" + name;
        if (table.index_var.count(key) == 1)
        {
            return true;
        }

        else
        {
            //error("identifier not found");
            return false;
        }
    }

}

// 有且仅有一个mainfunction def
void check_main()
{
    unsigned int i;
    int main_num = 0;
    for (i = 0; i < table.All_function.size(); i++)
    {
        if (table.All_function[i].name == "main")
        {
            main_num += 1;
        }
    }

    if (main_num == 1)
    {
        cout << "main function has declared!";
    }

    else
    {
        error("main function error, you have declare multi main functions or main function missed");
    }
}

//generate midcode
void gen(string op, string arg1, string arg2, string result)
{
    midcode m;
    m.op = op;
    m.arg1 = arg1;
    m.arg2 = arg2;
    m.result = result;

    midcode_vector.push_back(m);
}
//new label
std::string new_label()
{
    label_index += 1;
    return ("L" + to_string(label_index));
}

std::string new_temp()
{
    temp_index += 1;
    temp = "$" + to_string(temp_index);
    return temp;
}




// match and get next token
bool match(string s)
{

    if (currenttoken.word == s && not_the_end())
    {
        //cout << "current token: " << currenttoken.word << " token index: " << currenttoken_index<<endl;
        get_next_token();
        return true;
    }
}

// match and deal with error
bool match_true(string s)
{

    if (currenttoken.word == s && not_the_end())
    {
        //cout << "current token: " << currenttoken.word << " token index: " << currenttoken_index<<endl;
        get_next_token();
        return true;
    }
    else
        error("s");
    return false;
}

bool match_type(TokenType t)
{

    if (currenttoken.type == t && not_the_end())
    {
        //cout << "current token: " << currenttoken.word << " token index: " << currenttoken_index<<endl;
        get_next_token();
        return true;
    }
}

// match and deal with error
bool match_true_type(TokenType t)
{

    if (currenttoken.type == t && not_the_end())
    {
        //cout << "current token: " << currenttoken.word << " token index: "<<currenttoken_index<<endl;
        get_next_token();
        return true;
    }
    else
        error("TD");
    return false;
}





bool not_the_end()
{
    if (currenttoken_index >= token_vector.size())
    {
        return false;
    }
    else return true;
}


void get_next_token()
{
    if (currenttoken_index < token_vector.size())
    {        
        currenttoken_index++;
        if (currenttoken_index < token_vector.size())
        {
            currenttoken = token_vector[currenttoken_index];
        }
        else
        {
            token_end_flag = 1;
            //cout << "That's the end !" << endl;
        }
    }
}

Token no_get_next_token(int i)
{
    if (currenttoken_index + i < token_vector.size())
    {
        return token_vector[currenttoken_index + i];
    }
    else
    {
        token_end_flag = 1;
        //cout << "That's the end !" << endl;
        //debug 返回一个空的
        Token temptoken;
        temptoken.word = "";
        temptoken.type = NONE;
        return temptoken;
    }
}

void assign_statement()
{
    string id_name = currenttoken.word;//数组名 
    match_true_type(ID);

    if (currenttoken.word == "[")
    {
        match("[");
        expression();
        string index = exp_value;
        //语义分析 数组下标
        variable_symbol s = check_and_get_variable(id_name);
        if (index[0] == '-' || (isnum(index) && to_num(index) >= s.size))
        {
            //print(s.name)
            error("index of array out of bounds");
        }
        match_true("]");

        if (currenttoken.word == "=")
        {
            match_true("=");
            expression();
            string value = exp_value;
            gen("[]=", value, index, id_name);
        }

        else
        {
            error("assign statement error");
            exit(0);
        }

    }

    else if (currenttoken.word == "=")
    {
        match("=");
        expression();
        string value = exp_value;
        gen("=", value, "", id_name);
    }

    else
    {
        error("assign statement error");
    }

}

void if_statement()
{
    if (match_true("if"))
    {
        string label1; //if not equal ,the end of if part
        string label2;// the end of else part
        string tempvar;
        label1 = new_label();
        label2 = new_label();
        tempvar = new_temp();
        if (match_true("("))
        {
            condition(tempvar);
            record.pop();
            variable_symbol s;
            s.kind="temp";
            s.name=tempvar;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("jne", tempvar, "", label1); //not equal goto label1
            match_true(")");
            statement();
            gen("jmp", "", "", label2);
            gen("L:", "", "", label1);

            //with else statement
            if (currenttoken.word=="else")
            {
                match("else");
                statement();
            }
            gen("L:", "", "", label2);
        }
    }
}

// how???????????//
void while_statement()
{
    if (match("while"))
    {
        string label1, label2,tempvar;
        label1 = new_label(); 
        label2 = new_label();
        tempvar=new_temp();
        match_true("(");
        condition(tempvar);
        variable_symbol s;
        s.kind="temp";
        s.name=tempvar;
        s.function=function_name;
        s.size=0;
        s.addr=address_offset;
        address_offset+=1;
        check_and_insert_variable(s);       
        match_true(")");
        gen("jne", "", "", label1);
        gen("L:","","",label2);
        statement();
        midcode condition_record;

        condition_record=record.top();
        record.pop();
        gen(condition_record.op,condition_record.arg1,condition_record.arg2,condition_record.result);
        gen("jeq","","",label2);
        gen("L:","","",label1);

        // gen()
    }
}

void return_statement()
{
    string str3;
    if (currenttoken.word=="return")
    {
        match_true("return");
        return_flag = 1;
        //返回值
        expression();
        //match_true(";");
        if (exp_value == "")
        {
            error("return value miss");
        }
        gen("ret", "", "", exp_value);
    }

    //else if (currenttoken.word == ";")
    //{
    //    match_true(";");
    //}
    else
    {
        error("return error");
    }

}

void continue_statement()
{
    if (match("continue"))
    {
        return;
    }
}

void break_statement()
{
    if (match("break"))
    {
        return;
    }
}

void block()
{
    if (match_true("{"))
    {
        //for recursive block
        while (currenttoken.word == ("{"))
        {
            match_true("{");
            blockitem();
            match_true("}");
        }

        blockitem();
        match_true("}");
    }

}

void blockitem()
{
    //decl 
    //用while
    while (currenttoken.word != "}")
    {
        if (currenttoken.word == "int")
        {
            variable_declare();
        }

        else if (currenttoken.word == "const")
        {
            const_declare();
        }

        else
        {
            statement();
        }
    }
    //stmt
}

void statement()
{
    // if no consume a token sequence
    if (currenttoken.word == ("if"))
    {
        if_statement();
    }
    // while
    else if (currenttoken.word == ("while"))
    {
        while_statement();
    }
    // break
    else if (currenttoken.word == ("break"))
    {
        break_statement();
        match_true(";");
    }
    // continue
    else if (currenttoken.word == ("continue"))
    {
        continue_statement();
        match_true(";");
    }
    // return
    else if (currenttoken.word == ("return"))
    {
        return_statement();
        match_true(";");
    }
    //block
    else if (currenttoken.word == ("{"))
    {
        block();
    }

    // /lva=exp 
    // function call
    else if (currenttoken.type == ID)
    {
        //assign statement
        if (contain_variable(currenttoken.word))
        {
            assign_statement();
            match_true(";");
        }
        else if (contain_function(currenttoken.word) || currenttoken.word==function_name)
        {
            if(contain_function(currenttoken.word))
            {
                function_symbol s= get_function(currenttoken.word);
                if (s.is_return == 0)
                {
                    call_function();
                    match_true(";");
                }

                else
                {
                    call_function();
                    gen("int_call", s.name,"","");
                    match_true(";");
                    //error("int function must give a return value");
                }
            }

            else if(currenttoken.word==function_name)
            {
                call_function();
                gen("int_call", currenttoken.word,"","");
                match_true(";");
            }


        }
        else if(currenttoken.word=="putint")
        {
            get_next_token();
            match_true("(");
            expression();
            match_true(")");
            match_true(";");
            gen("putint","","",exp_value);

                        
        }
        else
        {
            error("identifier not found");
            //这里直接退出 处理太过复杂
            exit(0);
        }
    }
    // exp

// exp���Բ�Ҫ??
    else
    {
        expression();
        match_true(";");
    }

}



void compile_unit()
{
    currenttoken = token_vector[0];
    function_name = "global";
    while (!token_end_flag)
    {
        if (currenttoken.word == "const")
        {
            const_declare();
        }
        else if (currenttoken.word == "void")
        {
            void_function_def();
        }

        else if (currenttoken.word == "int")
        {
            if ((no_get_next_token(1).type == ID))
            {
                //可以初始化
                // 考虑情况
                // int x;
                // int x=1;
                //int x[10];
                //int x[10]=5;
                if (no_get_next_token(2).word == "=" || no_get_next_token(2).word == "[" || no_get_next_token(2).word==";")
                {
                    variable_declare();
                }

                else if (no_get_next_token(2).word == "(")
                {
                    int_function_def();
                }

                else
                {
                    error("declare error,a ; is expected");
                    get_next_token();

                }
            }
            // main and only main
            else if (no_get_next_token(1).word == "main")
            {
                //only
                main_func();
            }
            else
            {
                error("conpile unit error");
                get_next_token();

            }
        }
        else
        {
            error("compile unit error");
            get_next_token();
            return;
        }
        // get next token
        //get_next_token();
    }

}


void function_def()
{
    if (currenttoken.word == "void")
    {
        void_function_def();
    }
    else if (currenttoken.word == "int")
    {
        int_function_def();
    }

    else
    {
        error("function type error");
    }
}

// void function_type();
void int_function_def()
{
    if (match("int"))
    {
        function_symbol symbol;
        // match_true_type(ID);
        if (currenttoken.type == ID)
        {
            function_name = currenttoken.word;
            address_offset=0;
            //current function name
            symbol.name = function_name;
            symbol.is_return = true;
            gen("func", "int", "", function_name);
            match_true_type(ID);
            match_true("(");
            function_parameters();
            match_true(")");

            symbol.parameter_num = function_parameter_num;
            // symbol.parameter_size=symbol.parameter_num*4;

            address_offset+=symbol.parameter_num;
            check_and_insert_function(symbol);
            block();
            symbol.total_offset=address_offset+symbol.parameter_num;
            table.All_function.pop_back();
            check_and_insert_function(symbol);
            if (return_flag == 1)
            {
                gen("end_func", "", "", "");
                return_flag = 0;
            }
            else
            {
                error("no return statement");
            }
        }
    }
}
void void_function_def()
{
    if (match("void"))
    {
        if (currenttoken.type == ID)
        {
            function_symbol symbol;
            //current name 
            function_name = currenttoken.word;
            address_offset=0;
            symbol.name = function_name;
            symbol.is_return = false;
            gen("func", "void", "", function_name);
            match_true_type(ID);
            match_true("(");
            function_parameters();
            match_true(")");
            symbol.parameter_num = function_parameter_num;
            // symbol.parameter_size=symbol.parameter_num*4;
            // check_and_insert_function(symbol);
            //append
            address_offset+=symbol.parameter_num;
            block();//function body
            symbol.total_offset=address_offset+symbol.parameter_num;
            check_and_insert_function(symbol);
            if (return_flag == 1)
            {
                return_flag = 0;
                error("void function can not contain return statement");
            }
            gen("ret","","","");
            gen("end_func", "", "", "");
            // return_flag=0;
        }

    }
}

void main_func()
{
    if (match("int"))
    {
        if (match_true("main"))
        {
            match_true("(");
            match_true(")");
            function_name = "main";
            address_offset=0;
            function_symbol symbol;
            symbol.name = "main";
            symbol.is_return = true;
            symbol.parameter_num = 0;
            // symbol.parameter_size=0;
            // check_and_insert_function(symbol);
            gen("func", "int", "", "main");
            address_offset+=0;
            block();
            symbol.total_offset=address_offset+symbol.parameter_num;
            check_and_insert_function(symbol);
            //return_statement();
            if (return_flag == 1)
            {
                gen("end_func", "", "", "");
                return_flag = 0;
            }
            else
            {
                error("no return flag in main");
            }

            // return_flag=0;
            //only main
            //check table
        }
    }
}

void function_parameters()
{
    //�����������
    function_parameter_num = 0;
    if (currenttoken.word == ")")
    {
        //match_true(")");
    }
    else if (currenttoken.word=="int")
    {
        function_parameter();
    }
    while (currenttoken.word == ",")
    {
        match(",");
        function_parameter();
    }
}

// expression as parameters needs to be done
void function_parameter()
{
    //only int type
    int para_index;
    function_parameter_num += 1;
    para_index = function_parameter_num - 1;
    match_true("int");
    // match_true_type(ID);
    variable_symbol s;
    if (currenttoken.type == ID)
    {
        s.name = currenttoken.word;
        s.function = function_name;
        s.addr = para_index;
        s.kind = "para";
        // ����Ҫ��Ҫ��¼һ�²���������Ϊsize��
        // check_and_insert_variable(s);
        match_type(ID);
    }
    //array parameters
    if (currenttoken.word == "[")
    {
        match("[");
        match_true("]");
        // while(currenttoken.word=="[")
        // {
        //     match_true("[");
        //     expression();
        //     match_true("]");
        // }
    }
    check_and_insert_variable(s);

    //[] alternative;
}

void function_real_parameters()
{
    expression();
    while (currenttoken.word == ",")
    {
        match(",");
        expression();
    }
}

void call_function()
{
    if (currenttoken.type == ID && contain_function(currenttoken.word))
    {
        string name = currenttoken.word;
        function_symbol s = get_function(name);
        // call_int();
        match_type(ID);
        match_true("(");
        vector<string> parameter_vector;
        while (currenttoken.word != ")")
        {
            expression();
            parameter_vector.push_back(exp_value);
            if (currenttoken.word == ",")
            {
                match_true(",");
            }

        }
        match_true(")");
        int i;
        //��ջ˳��
        if (parameter_vector.size() != s.parameter_num)
        {
            error("real parameter nums do not match function defination!");
        }
        for (i = 0; i <parameter_vector.size(); i++)
        {
            gen("para", "", "", parameter_vector[i]);
        }

        //return function �� void function 
        if (s.is_return)
        {
            //在表达式expression计算
            //gen("int_call", name, "", exp_value);
        }
        else if (!s.is_return)
        {
            gen("void_call", name, "", "");
        }
    }
}


// void main_func();
void declare()
{
    if (currenttoken.word == "const")
    {
        const_declare();
    }

    else if (currenttoken.word == "int")
    {
        variable_declare();
    }

    else
    {
        error("error declare");
    }
}

void const_declare()
{
    if (match_true("const"))
    {
        if (match_true("int"))
        {
            const_def();
            while (currenttoken.word == ",")
            {
                match(",");
                const_def();
            }
            match_true(";");
        }
    }
}

void variable_declare()
{
    if (match_true("int"))
    {
        varaible_def();
        while (currenttoken.word == ",")
        {
            match(",");
            varaible_def();
        }
        match_true(";");
    }
}

//must declare and initialize
void const_def()
{
    if (currenttoken.type == ID)
    {
        variable_symbol s;
        s.name = currenttoken.word;
        s.kind = "const";
        s.function=function_name;
        s.addr = address_offset;
        match_true_type(ID);

        if (currenttoken.word == "[")
        {
            int size = 0;
            match("[");
            if (currenttoken.type == NUM)
            {
                size = to_num(currenttoken.word);
                if (size <= 0)
                {
                    error("array size must be a positive number");
                }
                match_type(NUM);
                match_true("]");
                s.size = size;
                address_offset += size;
                check_and_insert_variable(s);
                gen("const","int_array" , to_string(size), s.name);
            }
            else
            {
                error("array size must be a positive number");
            }


        }
        //not array
        else
        {
            //initialize
            if (currenttoken.word == "=")
            {
                address_offset += 1;

                if (match_true("="))
                {
                    if (currenttoken.word == "+" || currenttoken.word == "-")
                    {
                        if (currenttoken.word == "+")
                        {
                            match("+");
                            if (currenttoken.type == NUM)
                            {
                                s.value = to_num(currenttoken.word);
                                match_type(NUM);

                                gen("const", "int", to_string(s.value), s.name);
                                check_and_insert_variable(s);
                                // ������ֵ�洢�ڷ��ű�
                            }
                            else
                            {
                                error("must be init with a const expression");
                            }
                        }
                        if (currenttoken.word == "-")
                        {
                            match("-");
                            if (currenttoken.type == NUM)
                            {
                                s.value = -to_num(currenttoken.word);
                                match_type(NUM);

                                gen("const", "int", to_string(s.value), s.name);
                                check_and_insert_variable(s);
                                // ������ֵ�洢�ڷ��ű�
                            }
                            else
                            {
                                error("must be init with a const expression");
                            }
                        }
                        
                    }
                    else if (currenttoken.type == NUM)
                    {
                        s.value = to_num(currenttoken.word);
                        match_type(NUM);

                        gen("const", "int", to_string(s.value), s.name);
                        check_and_insert_variable(s);
                        // ������ֵ�洢�ڷ��ű�
                    }
                    else
                    {
                        error("initialize error");
                    }

                }
            }
            

            else
            {
                error("a const must be initialize");
            }
        }
    }
}

void varaible_def()
{
    if (currenttoken.type == ID)
    {
        variable_symbol s;
        s.name = currenttoken.word;
        s.kind = "var";//kind
        s.function=function_name;
        s.addr=address_offset;
        match_true_type(ID);

        //array
        if (currenttoken.word == "[")
        {
            int size=0;
            match("[");
            if (currenttoken.type == NUM)
            {
                size = to_num(currenttoken.word);
                if (size <= 0)
                {
                    error("array size must be a positive number");
                }
                match_type(NUM);
                match_true("]");
                if(currenttoken.word=="[")
                {
                    match("[");
                    if(currenttoken.type==NUM)
                    {
                        int size2;
                        size2=to_num(currenttoken.word);
                        
                        if(size2<=0)
                        {
                            error("array size must be a positive number");
                        }
                        match_type(NUM);
                        match_true("]");
                        variable_symbol s2;
                        s2.name=s.name+"_";
                        
                        s2.size=size2;
                        address_offset+=size2*size;
                        check_and_insert_variable(s2);
                        gen("var", "int_array", to_string(size2), s2.name);
                    }
                }
                s.size = size;
                address_offset += size;
                check_and_insert_variable(s);
                gen("var", "int_array", to_string(size), s.name);
                

            }
            else
            {
                error("array size must be a positive number");
            }

            
        }
        //not array
        //1.int x;
        //2.int x=1;
        else
        {
            int x = 0;
            if (currenttoken.word == "=")
            {
                if (match_true("="))
                {
                    if (currenttoken.word == "+" || currenttoken.word == "-")
                    {
                        if (currenttoken.word == "+")
                        {
                            match("+");
                            if (currenttoken.type == NUM)
                            {
                                s.size = 0;
                                address_offset += 1;
                                x = to_num(currenttoken.word);
                                match_type(NUM);
                                gen("var", "int", "", s.name);
                                s.value = x;
                                check_and_insert_variable(s);
                                gen("=", to_string(x), "", s.name);
                            }
                            else
                            {
                                error("must be init with a const expression");
                            }
                        }
                        if (currenttoken.word == "-")
                        {
                            match("-");
                            if (currenttoken.type == NUM)
                            {
                                s.size = 0;
                                address_offset += 1;
                                x = -to_num(currenttoken.word);
                                match_type(NUM);
                                gen("var", "int", "", s.name);
                                s.value = x;
                                check_and_insert_variable(s);
                                gen("=", to_string(x), "", s.name);
                            }
                            else
                            {
                                error("must be init with a const expression");
                            }
                        }

                    }
                    else if (currenttoken.type == NUM)
                    {
                        s.size = 0;
                        address_offset += 1;
                        x = to_num(currenttoken.word);
                        match_type(NUM);
                        gen("var", "int", "", s.name);
                        s.value = x;
                        check_and_insert_variable(s);
                        gen("=", to_string(x), "", s.name);
                    }

                    else
                    {
                        error("expected a right value");
                    }

                }
            }

            //variable can not be initiliaze.
            else if(currenttoken.word==";")
            {
                s.size = 0;
                address_offset += 1;
                check_and_insert_variable(s);
                gen("var", "int", "", s.name);
            }

            else
            {
                error("declare error");
            }
        }
    }
}

// void const_init()
// {
//     //array
//     if(currenttoken.word=="{")
//     {
//         match("{");
//         match_true("}");

//     }

//     else
//     {
//         const_expression();
//     }
// }

// void variable_init()
// {
//     //array
//     if(currenttoken.word=="{")
//     {
//         match("{");

//         match_true("}");
//     }

//     else 
//     {
//         expression();
//     }
// }

void expression()
{
    string str1, str2, str3;
    term();
    str3 = exp_value;

    //single op + or - or !
    //if (currenttoken.word == "+" || currenttoken.word == "-" || currenttoken.word == "!")
    //{
    //    if (match("+"))
    //    {
    //        term();
    //        str3 = exp_value;
    //        //dont gen
    //    }
    //    else if (match("-"))
    //    {
    //        term();
    //        str1 = exp_value;
    //        str3 = new_temp();
    //        gen("-", "0", str1, str3);
    //    }
    //    else if (match("!"))
    //    {
    //        term();
    //        str3 = exp_value;
    //        // first expression
    //    }

    //    else
    //    {
    //        term();
    //        str3 = exp_value;
    //    }

        // op node + or -
        while (currenttoken.word == "+" || currenttoken.word == "-")
        {
            str1 = str3;
            if (currenttoken.word == "+")
            {
                match("+");
                term();
                str2 = exp_value;
                // second expression
                str3 = new_temp();//result
                variable_symbol s;
                s.kind="temp";
                s.name=str3;
                s.function=function_name;
                s.size=0;
                s.addr=address_offset;
                address_offset+=1;
                check_and_insert_variable(s);
                gen("+", str1, str2, str3);
            }
            if (currenttoken.word == "-")
            {
                match("-");
                term();
                str2 = exp_value;
                // second expression
                str3 = new_temp();//result

                variable_symbol s;
                s.kind="temp";
                s.name=str3;
                s.function=function_name;
                s.size=0;
                s.addr=address_offset;
                address_offset+=1;
                check_and_insert_variable(s);
                gen("-", str1, str2, str3);
            }
        }
    
    exp_value = str3;
    //save the result to expvalue
}

//must satisfy:
//1.const
//2. already in symtable
void const_expression()
{

}

void term()//mul
{
    string str1, str2, str3;
    factor();
     str3=exp_value;//obtain first value
    if (currenttoken.word == "*" || currenttoken.word == "/" || currenttoken.word == "%")
    {
        str1 = exp_value;//first
        if (match("*"))
        {
            factor();
            str2 = exp_value;//second
            str3 = new_temp();//temp
            variable_symbol s;
            s.kind="temp";
            s.name=str3;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("*", str1, str2, str3);
        }
        else if (match("/"))
        {
            factor();
            str2 = exp_value;//second
            str3 = new_temp();//temp
            variable_symbol s;
            s.kind="temp";
            s.name=str3;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("/", str1, str2, str3);
        }
        else if (match("%"))
        {
            factor();
            str2 = exp_value;//second
            str3 = new_temp();//temp
            variable_symbol s;
            s.kind="temp";
            s.name=str3;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("%", str1, str2, str3);
        }
    }
    exp_value = str3;
    // 每个term的值保存在exp_value里面

}

//deal with expression ID ID[array] function call

void factor() //unaryexp
{
    string str3;
    //负数在得到计算结果之后取负
    //1.pramaryexp function call : (exp) || lval || num || function
    if (currenttoken.word=="(")
    {
        expression();
        match_true(")");
    }

    else if (currenttoken.type == NUM)
    {
        exp_value = currenttoken.word;
        match_type(NUM);
    }

    else if (currenttoken.word=="+" || currenttoken.word=="-")
    {
        if (currenttoken.word == "+")
        {
            match("+");
            factor();
        }

        if (currenttoken.word == "-")
        {
            match("-");
            factor();
            string t = new_temp();
            variable_symbol s;
            s.kind="temp";
            s.name=t;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("-", "0", exp_value, t);
            exp_value = t;
        }
        //save expvalue
    }

    else if (currenttoken.type == ID)
    {
        //function call
        string fname = currenttoken.word;
        if (no_get_next_token(1).word == "(")
        {
            if (contain_function(currenttoken.word))
            {
                function_symbol s = get_function(currenttoken.word);
                if (s.is_return)
                {
                    call_function();
                }
                else
                {
                    call_function();
                    error("can not call a void function here");
                }
            }
            str3 = new_temp();
            variable_symbol s;
            s.kind="temp";
            s.name=str3;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            gen("int_call", fname, "", str3);
            //�����ý���ķ���ֵ���������
            exp_value = str3;// return value

        }
        //array
        else if (no_get_next_token(1).word == "[")
        {
            variable_symbol symbol;
            symbol = check_and_get_variable(currenttoken.word);
            string aname = currenttoken.word;
            match_type(ID);
            match_true("[");
            expression();
            match_true("]");
            string index = exp_value;
            //����Խ����
            if ((index[0] == '-' || (isnum(index) && to_num(index) >= symbol.size)))
            {
                error("index of array out of bounds");
            }
            str3 = new_temp();
            variable_symbol s;
            s.kind="temp";
            s.name=str3;
            s.function=function_name;
            s.size=0;
            s.addr=address_offset;
            address_offset+=1;
            check_and_insert_variable(s);
            exp_value = str3;//store exp_value
            gen("=[]", aname, index, str3);
        }
        //id
        else {
            if (contain_variable(currenttoken.word))
            {
                variable_symbol symbol;
                symbol = check_and_get_variable(currenttoken.word);
                //if(contain_variable)
                exp_value = currenttoken.word;
                match_type(ID);
            }

        }
    }
    //unaryop
    // in expression
    // else if(currenttoken.word=="+" || currenttoken.word=="-" ||currenttoken.word=="!")
    // {
    //     if(currenttoken.word=="+")
    //     {
    //         match("+");
    //         factor();
    //     }
    //     else if(currenttoken.word=="-")
    //     {
    //         match("-");
    //         factor();
    //     }
    //     else if(currenttoken.word=="!")
    //     {
    //         match("!");
    //         factor();
    //     }

    //     factor();
    // }

}

void condition(string tempvar)
{
    //single op !
    if (currenttoken.word == "!")
    {
        string str1, str2;
        expression();
        str1 = exp_value; //the first value 
        gen("==", str1, "0", tempvar);
        midcode condition_record;
        condition_record.op="==";
        condition_record.arg1=str1;
        condition_record.arg2="0";
        condition_record.result=tempvar;
        record.push(condition_record);

    }
    //double op
    //and single + or -
    else
    {
        string str1, str2;
        expression();
        str1 = exp_value; //the first value 
 //perhapas the next value
        if (currenttoken.word == "<" || currenttoken.word == ">" || currenttoken.word == ">=" || currenttoken.word == "<=" || currenttoken.word == "==" || currenttoken.word == "!=")
        {
            if (currenttoken.word == "<")
            {
                match("<");
                expression();
                str2 = exp_value;
                gen("<", str1, str2, tempvar);
                midcode condition_record;  
                condition_record.op="<";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);
            }
            else if (currenttoken.word == ">")
            {
                match(">");
                expression();
                str2 = exp_value;
                gen(">", str1, str2, tempvar);
                midcode condition_record;  

                condition_record.op=">";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);

            }
            else if (currenttoken.word == "<=")
            {
                match("<=");
                expression();
                str2 = exp_value;
                gen("<=", str1, str2, "");
                midcode condition_record;  

                condition_record.op="<=";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);

            }
            else if (currenttoken.word == tempvar)
            {
                match(">=");
                expression();
                str2 = exp_value;
                gen(">=", str1, str2, tempvar);
                midcode condition_record;  

                condition_record.op=">=";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);

            }
            else if (currenttoken.word == "==")
            {
                match("==");
                expression();
                str2 = exp_value;
                gen("==", str1, str2, tempvar);
                midcode condition_record;  

                condition_record.op="==";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);

            }
            else if (currenttoken.word == "!=")
            {
                match("!=");
                expression();
                str2 = exp_value;
                gen("!=", str1, str2, tempvar);
                midcode condition_record;  

                condition_record.op="!=";
                condition_record.arg1=str1;
                condition_record.arg2=str2;
                condition_record.result=tempvar;
                record.push(condition_record);

            }
        }
    }

}



void grammer_test()
{
    int main_flag=0;
    unsigned int i;
    for(i=0;i<table.All_function.size();i++)
    {
        //global variable and rename
        if(("main")==table.All_function[i].name )
        {
            main_flag=1;
            break;
        }
    }
    if(main_flag!=1)
    {
        error("main function miss");
        cout<<"can't find a main function"<<endl;
    }


    cout <<endl<< "---------print midcode---------" << endl;
    cout << endl;
    cout << setiosflags(ios::left);
    cout << setw(4) << "n" << setw(15) << "op" << setw(15) << "arg1" << setw(15) << "arg2" << setw(15) << "result" << endl<<endl;
    for (i = 0; i < midcode_vector.size(); i++)
    {
        cout << setiosflags(ios::left);
        cout << setw(3)<<i + 1 << ": " <<setw(15) << midcode_vector[i].op << setw(15) << midcode_vector[i].arg1 << setw(15) << midcode_vector[i].arg2 << setw(15) << midcode_vector[i].result << endl;
    }
}

void symbol_table_test()
{
    int i;
    cout << endl << "---------function Symbol table---------" << endl;
    cout << setiosflags(ios::left);
    cout << setw(20)<<"function name:"<<setw(20) << "return type"<< setw(20) << "parameter number" <<setw(20) << "total offset "<<endl << endl;
    for (i = 0; i < table.All_function.size(); i++)
    {

        cout << setw(20) << table.All_function[i].name << setw(20) << table.All_function[i].is_return << setw(20) << table.All_function[i].parameter_num <<  setw(20) << table.All_function[i].total_offset<<endl;
        cout << endl;
    }

    cout << endl<<"---------variable Symbol table---------" << endl;

    cout << setiosflags(ios::left);
    cout << setw(20) << "variable name:" << setw(20) << "field" << setw(20) << "address offest" <<setw(20) << "size" << setw(20) << "value" << setw(20) << "kind" <<endl << endl;
    for (i = 0; i < table.All_variable.size(); i++)
    {
        cout << setw(20)<<table.All_variable[i].name << setw(20) << table.All_variable[i].function << setw(20) << table.All_variable[i].addr << setw(20) << table.All_variable[i].size << setw(20) << table.All_variable[i].value<< setw(20) << table.All_variable[i].kind<<endl;
    }
    cout << endl;

}
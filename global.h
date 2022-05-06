// #ifndef起到的效果是防止一个源文件多次包含同一个头文件。 multi define 

#ifndef GLOBAL
#include<string>
#include<map>
#include<vector>
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
#define False 0
#define True 1
using namespace std;

// only int type
typedef enum
{
    CONST, INT, KWCHAR, VOID, MAIN, KWSTRING,
    WHILE, IF, ELSE, BREAK, CONTINUE, RETURN,
    SCANF, PRINTF,
    ID, NUM, 
    CHAR, STRING,
    ARTHMATIC,
    ASSIGN,
    NONE,//用于no_get_next
}TokenType;

//arthimatic symbol : a single word
struct Token
{
    TokenType type;
    int row;
    std::string word;
};

extern int error_num;
extern std::string filename;//declare 
extern string outfilename;//declare 
extern ifstream inFile; //if stream object
extern vector<Token> token_vector;//all token
extern ofstream mipswrite;
extern Token currenttoken;
extern string function_name;

// symblo
struct variable_symbol
{
    std::string function;
    std::string name;
    // std::string type; // variable function
    std::string kind;//kind of symbol const var para temp
    int value;//const value
    int addr;
    int size = 0;//parameters for function;number of array
    // int bytes=4;//int only
    // int offset_address;
};
struct function_symbol
{
    int depth;
    std::string name;
    // std::string type;// variable function
    bool is_return;//int or void
    int parameter_num;
    int total_offset = 0;
    // int parameter_size;
};
struct symbol_table {
    //function 
    //variable belongs to which function
    //global variable
    int num_var;
    // std::map<std::string, function_symbol> map_func;
    std::map<std::string, int> index_var;
    // "function name" + ":" + var_name


    //all map represent a useable variable
    //global variable has the higher priority
    // global:a(function name global)(global represent a function name)
    // max:a (function name)

    std::vector<function_symbol> All_function;
    std::vector<variable_symbol> All_variable;
};
extern symbol_table table;

struct midcode
{
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

extern vector<midcode> midcode_vector;
//table
extern symbol_table table;



char get_next_char();
char no_get_next_char();
int is_unerline(char c);
int is_valid_character();
int is_letter(char c);
void lexial_analyze(string filename);
void read_file(string filename);
void lexial_test();


//num
int to_num(string s);

//midcode
void gen(string op, string arg1, string arg2, string result);
std::string new_label();
std::string new_temp();

//table
bool contain_variable(string name);
void init_table();
void check_and_insert_variable(variable_symbol symbol);
void check_and_insert_function(function_symbol symblo);
variable_symbol check_and_get_variable(string name);
bool contain_function(string name);
function_symbol get_function(string name);

void get_next_token();
bool not_the_end();
Token no_get_next_token(int i);
bool match(string s);
bool match_type(TokenType t);
bool match_true(string s);
bool match_true_type(TokenType t);
// error deal with
void error(string s);
void error_type(TokenType t);

void assign_statement();
void if_statement();
void statement();
void while_statement();
void break_statement();
void continue_statement();
void return_statement();
void block();
void blockitem();
//decl and 
void call_function();
void compile_unit();
void function_def();
void function_parameters();
void function_real_parameters();
void function_parameter();
void int_function_def();
void void_function_def();
void main_func();
void declare();
void const_declare();
void variable_declare();
void const_def();
void varaible_def();
void const_init();
void variable_init();

void const_expression(); // check
void expression();
void term();
void factor();
void condition(string );

void grammer_test();
void symbol_table_test();



void algebraic_identity(); //代数 
void del_temp();
void del_common_expression();
void const_propogation();
void del_jump();
void unit_test();
void gen_test_mide_code();
bool isin_basic_block(midcode m);
void local_opt();
void opt_test();




void mips_to_text();
void midcode_to_mips();
void lw_mips(string register, string arg1);
void sw_mips(string register, string arg1);
int var_addr(string s);
int var_address(string name);
void ret_mips();
void int_call_mips();
void void_call_mips();
void para_mips();
void main_function_mips();
void algbra_mips();
void logic_mips();
void assign_mips();
void assign_array();
void equal_array();
void push_to_stack();
void jump_mips(string s);
void genmips(string s);
void function_mips();
void main_mips();
string allocate_register(string temp);
void init_register();
string find_in_register(string temp);
void save();

//tool
bool isnum(string s);
int to_num(string s);
bool isid(string s);


#endif
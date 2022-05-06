#include<iostream>
// #include"lexial.h"
#include<vector>
#include"global.h"
#include <fstream>
using namespace std;
// ofstream mipswrite;

int main()
{
    std::string filename ="sysyruntime/transpose0.sy";
    string outfilename = "test.asm";
    unsigned int i;
    int main_flag = 0;
    read_file(filename);
    cout << endl<<"File name:     " << filename << endl<<endl;
    cout << "--------Lexial Analysis-------" << endl;
    lexial_analyze(filename);
    if (error_num != 0)
    {
        cout << "Error in lexial analysis, compiling terminated!" << endl;
        return 0;
    }
    cout <<"Total token unit:"<<token_vector.size() << endl<<endl;
    //lexial_test();

    cout << "---------Grammatical analysis---------" << endl;

    compile_unit();
    cout << endl<<"That is the end of Grammatical Analysis!" << endl;
    cout << "Total error:" << error_num << endl;

    //???????????????????��????
    if (error_num == 0)
    {

    }

    grammer_test();

    symbol_table_test();

    // midcode

    opt_test();
    if (error_num == 0)
    {

        midcode_to_mips();
        mips_to_text();
    }
    else
    {
        cout << "Total error:" << error_num -1<<". Stop compiling" << endl;
    }

    return 0;


}
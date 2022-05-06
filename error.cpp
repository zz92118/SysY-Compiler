#include"global.h"

int error_num = 0;

void error(string s)
{
    cout << "Error in line: " << currenttoken.row << ",";
    error_num += 1;

    //词法分析
    if (s == "illegal character")
    {
        cout << "illegal character" << endl;
        exit(0);
    }


    if (s == ";")
    {
        cout << "a ; is expected" << endl;
    }



    else if (s == "a const must be initialize")
    {
        cout << "a const must be initialize" << endl;
    }

    else if (s == "must be init with a const expression")
    {
        cout << "a const must be init with a const expression" << endl;
    }

    else if (s == "declare error")
    {
        cout << "declare error"<<endl;
    }

    else if (s == "initialize error")
    {
        cout << "initialize error" << endl;
    }

    else if (s == "declare error,a ; is expected")
    {
        cout <<     "declare error,a ; is expected" << endl;
    }

    else if (s == "rename")
    {
        //原函数
    }
    else if (s == "expected a right value")
    {
        cout << "expected a right value" << endl;
    }
    else if (s == "compile error")
    {
        cout << "compile error" << endl;
    }
    else if (s == "ID")
    {
        cout << "type error" << endl;
    }
    else if (s == "return error")
    {
        cout << "return error" << endl;
    }
    else if (s == "void function can not contain return statement")
    {
        cout << "void function can not contain return statement" << endl;
    }
    else if (s == "no return statement")
    {
        cout << "int function miss return statement" << endl;
    }
    else if (s == "rename,cant insert function ")
    {

    }

    else if (s == "no return flag in main")
    {
        cout << "no return flag in main" << endl;
    }

    else if (s == "return value miss")
    {
        cout << "return value miss" << endl;
    }

    else if (s == "identifier not found")
    {
        cout << "identifier not found" << endl;
    }

    else if (s == "assign statement error")
    {
        cout << "assign statement error" << endl;
    }

    else if (s == "index of array out of bounds")
    {
        cout << "index of array out of bounds" << endl;
    }

    else if (s == "Wrong token input")
    {
        cout << "Wrong token input" << endl;
    }

    else if (s == "]")
    {
        cout << "a right bracket is expected" << endl;
    }

    else if (s == "real parameter nums do not match function defination!")
    {
        cout << "real parameter nums do not match function defination!"<< endl;
    }

    else if (s == "can not call a void function here")
    {
        cout << "can not call a void function here" << endl;
    }

    else if (s == "array size must be a positive number")
    {
        cout << "array size must be a positive number" << endl;
    }
    else if (s == "void function can not have a return value")
    {
        cout << "void function can not have a return value" << endl;
    }    
    else if (s == "main function miss")
    {
        cout << "main function miss" << endl;
    }

}
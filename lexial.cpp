#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<cstring>
#include<fstream>
// #include"global.h"
#include"global.h"

/* need to be done:
's' char
"ss" string
incomment
error deal
*/

using namespace std;
std::string buffer; //buffer 
int linepos = 0; /* current position in LineBuf */
unsigned static int buf_index = 0; /* current size of buffer string */
static int current_size = 0;


ifstream inFile; //if stream object
vector<Token> token_vector;//all token

// // void read_file(string filename);
// char get_next_char();
// char no_get_next_char();
// // void lexial_analyze(string filename);
// void error();

// int is_unerline(char c);

// int to_num(Token currenttoke); 
// int is_valid_character();
// int is_letter(char c);

// int main()
// {
//     char a;
//     int i;
//     read_file(filename);
//     // a=get_next_char();
//     // while((a=get_next_char())!=EOF)
//     // {
//     //     cout<<a;
//     // }

//     lexial_analyze(filename);

//     cout<<token_vector.size()<<endl;

//     for(i=0;i<token_vector.size();i++)
//     {
//         cout<<"Token"<<i<<": "<<token_vector[i].word<<"   "<<"token type:"<<token_vector[i].type<<endl;
//     }
//     return 0;
// }

void lexial_analyze(string filename)
{

    Token currenttoken;
    char current_char;
    current_char = get_next_char();// the first 

    while (current_char != EOF)
    {
        if (current_char == ' ' || current_char == '\n' || current_char == '\t')
        {
            current_char = get_next_char();
            continue;
        }
        //analysis for each word
        currenttoken.word = "";

        //1.ID and keyword
        if (is_letter(current_char))
        {
            while (is_letter(current_char) || isdigit(current_char))
            {
                currenttoken.word += current_char;
                current_char = get_next_char();
            }

            //if (!(is_letter(current_char) || isdigit(current_char)))
            //{
            //    error("Wrong token input");
            //    return;
            //}

            //key words
             if (currenttoken.word == "const")
            {
                currenttoken.type = CONST;
            }

            else if (currenttoken.word == "int")
            {
                currenttoken.type = INT;
            }

            else if (currenttoken.word == "char")
            {
                currenttoken.type = KWCHAR;
            }

            else if (currenttoken.word == "void")
            {
                currenttoken.type = VOID;
            }
            else if (currenttoken.word == "main")
            {
                currenttoken.type = MAIN;
            }
            else if (currenttoken.word == "while")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "if")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "else")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "break")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "continue")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "return")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "scanf")
            {
                currenttoken.type = KWSTRING;
            }
            else if (currenttoken.word == "printf")
            {
                currenttoken.type = KWSTRING;
            }


            else
            {
                currenttoken.type = ID;
            }

            // current_char=get_next_char();
            currenttoken.row = linepos;
            token_vector.push_back(currenttoken);


        }
        //2.digit error
        //error case :
        else if (isdigit(current_char))
        {

            currenttoken.type = NUM;
            char next_char = no_get_next_char();
            if (current_char != '\0')
            {
                while (isdigit(current_char))
                {
                    currenttoken.word += current_char;
                    current_char = get_next_char();
                }

                //if (!(isdigit(current_char)))
                //{
                //    error("Wrong token input");
                //    return;
                //}

            }
            //0 as the first digit
            else
            {
                if (isdigit(next_char))
                {
                    // error();
                }

                else
                {
                    currenttoken.word = '0';
                }
            }
            // current_char=get_next_char();
            currenttoken.row = linepos;
            token_vector.push_back(currenttoken);

        }

        //'
        else if (current_char == '\'')
        {
           currenttoken.type = CHAR;
           current_char = get_next_char();
           currenttoken.word += current_char;
           current_char = get_next_char();
           if (current_char != '\'')
           {
               // error();
           }
           currenttoken.row = linepos;
           current_char = get_next_char();

           token_vector.push_back(currenttoken);
        }
        //''
        else if (current_char == '"')
        {
           currenttoken.type = STRING;
           current_char = get_next_char();
           while (current_char != '"')
           {
               currenttoken.word += current_char;
               current_char = get_next_char();

               if (current_char == EOF)
               {
                   // error();
               }
           }
           currenttoken.row = linepos;
           current_char = get_next_char();
           token_vector.push_back(currenttoken);
        }
        // incomment to be done
        else
        {
            char next_char;
            currenttoken.type = ARTHMATIC;
            // / invert char
            if (current_char == '+')currenttoken.word = "+";
            else if (current_char == '-')currenttoken.word = "-";
            else if (current_char == '*')currenttoken.word = "*";

            else if (current_char == '/')currenttoken.word = "/";
            else if (current_char == '%')currenttoken.word = "%";
            else if (current_char == '(')currenttoken.word = "(";
            else if (current_char == ')')currenttoken.word = ")";
            else if (current_char == '[')currenttoken.word = "[";
            else if (current_char == ']')currenttoken.word = "]";
            else if (current_char == '{')currenttoken.word = "{";
            else if (current_char == '}')currenttoken.word = "}";
            else if (current_char == ',')currenttoken.word = ",";
            else if (current_char == '.')currenttoken.word = ".";
            else if (current_char == ';')currenttoken.word = ";";
            else if (current_char == ':')currenttoken.word = ":";

            else if (current_char == '=')
            {
                next_char = no_get_next_char();
                if (next_char == '=')
                {
                    currenttoken.word = "==";
                    current_char = get_next_char();
                }
                else
                {
                    currenttoken.word = "=";
                    currenttoken.type = ASSIGN;
                }

            }
            else if (current_char == '<')
            {
                next_char = no_get_next_char();
                if (next_char == '=')
                {
                    currenttoken.word = "<=";
                    current_char = get_next_char();
                }
                else
                {
                    currenttoken.word = "<";
                }

            }

            else if (current_char == '>')
            {
                next_char = no_get_next_char();
                if (next_char == '=')
                {
                    currenttoken.word = ">=";
                    current_char = get_next_char();
                }
                else
                {
                    currenttoken.word = ">";
                }

            }
            else if (current_char == '!')
            {
                next_char = no_get_next_char();
                if (next_char == '=')
                {
                    currenttoken.word = "!=";
                    current_char = get_next_char();
                }
                else
                {
                    currenttoken.word = "!";
                }

            }
            else if (current_char == '&')
            {
                next_char = no_get_next_char();
                if (next_char == '&')
                {
                    currenttoken.word = "&&";
                    current_char = get_next_char();
                }

                else
                {
                    currenttoken.word = "&";
                }
            }

            else if (current_char == '|')
            {
                next_char = no_get_next_char();
                if (next_char == '|')
                {
                    currenttoken.word = "||";
                    current_char = get_next_char();
                }
                else
                {
                    currenttoken.word = "|";
                }

            }

            else if (current_char == '/')
            {
                next_char = no_get_next_char();
                if (next_char == '/')
                {
                    currenttoken.word = "&&";
                    current_char = get_next_char();
                    break;
                }

                else
                {
                    currenttoken.word = "/";
                }
            }

            else {
            error("illegal character");
}
            

            currenttoken.row = linepos;
            current_char = get_next_char();
            token_vector.push_back(currenttoken);

        }



    }


    if (current_char == EOF)
    {
        //cout << "---------Lexial Analysis---------"<<endl;
        cout << "The lexial analysis has done!" <<endl;
        // exit(0);
    }
}

int is_letter(char c)
{
    if (c == '_' || isalpha(c))
    {
        return 1;
    }
    else return 0;
}


void read_file(string filename)
{

    inFile.open(filename);
    if (!inFile.is_open())
    {
        cout << "Can not open souce file" << endl;
        exit(EXIT_FAILURE);//if the file is opened successfully
    }

    else
    {
        cout << "The source file has benn successfully opened!"<<endl;
    }
}

//return the current char
//  line
char get_next_char()
{
    //a new line
    if (buf_index >= buffer.size())
    {
        linepos++;
        if (getline(inFile, buffer))
        {
            buf_index = 0;
            return '\n';
        }
        else
        {
            return EOF;
            // end of the file
        }
    }
    //read from buffer,into currenttoken
    else
    {
        return buffer[buf_index++];
    }
}
char no_get_next_char()
{
    if (buf_index < buffer.size() - 1)
    {
        return buffer[buf_index];
    }

    return '\n';
}

int is_valid_character(char CHAR) {
    if (CHAR == 32)
        return 1;
    else if (CHAR == 33)
        return 1;
    // dont take \n into consideraion
    else if ((CHAR >= 35) && (CHAR <= 126) && CHAR != 39)
        return 1;
    else
        return 0;
}

void lexial_test()
{
    int i;
    for (i = 0; i < token_vector.size(); i++)
    {
        cout << "Token" << i << ": " << token_vector[i].word << "   " << "token type:" << token_vector[i].type <<"row:"<<token_vector[i].row<< endl;
    }
}
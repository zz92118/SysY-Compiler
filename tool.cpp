#include"global.h"
#include<iostream>
using namespace std;

bool isnum(string s)
{
    if ((s[0] - '0') >= 0 && (s[0] - '0') <= 9)
    {
        return true;
    }

    else if ( ((s[1] - '0') >= 0 && (s[1] - '0') <= 9 ) && (s[0]=='+' || s[0] == '-'))
    {
        return true;
    }
    return false;
}

bool isid(string s)
{
    if (isalpha(s[0]) || s[0] == '_')
    {
        return 1;
    }
    return 0;
}

int to_num(string s)
{
    unsigned int i;
    int result;
    result = 0;
    for (i = 0; i < s.size(); i++)
    {
        result = result * 10 + (s[i] - '0');
    }
    return result;
}
#include<iostream>
#include<string.h>

using namespace std;

bool isnum(string s)
{
    if((s[0]-'0')>=0 && (s[0]-'0')<=9)
    {
        return true;
    }
    return false;
}

bool isid(string s)
{
    if(isalpha(s[0]) || s[0]=='_')
    {
        return 1;
    }
    return 0;
}


int main()
{
    string s="1234";
    string s2="s";
    cout<<isnum(s);
    cout<<isnum(s2);
    cout<<isid(s2);
    cout<<isid(s);
}
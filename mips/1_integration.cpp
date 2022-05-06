int x;
int y;

int compare(int x1,int x2)
{
        x=2;

    if(x1>x2)
    {
        x=10;
        return 7;
    }

    else
    {
        y=20;
        return 2;
    }

}

int main()
{
    int a;
    int b;
    int result;
    a=1*5+1+10;
    b=1*6+1;
    a=a+b;
    result=compare(1,10);
    putint(result);
    putint(x);
    putint(y);
    return 0;
}
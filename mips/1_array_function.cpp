int x;

int compare(int x1,int x2)
{
    if(x1>x2)
    {
        x=10;
        return 10;
    }

    else
    {
        x=20;
        return 20;
    }
}

int main()
{
    int begin=2;
    int begin1=3;
    int a[10];
    int b[3];
    int c[4];
    a[0]=0;
    a[1]=1;
    a[2]=2;
    a[3]=3;
    a[4]=4;
    a[5]=5;
    a[6]=6;
    a[7]=7;
    a[8]=8;
    a[9]=9;
    b[0]=a[2];
    b[1]=a[3];
    b[2]=a[4];
    c[0]=0;
    c[2]=10*10+b[2];
    a[0]=begin1+begin;
    a[1]=begin*begin1+begin;
    begin1=110;
    a[0]=compare(a[9],a[8]);
    putint(a[0]);
    putint(c[2]);
    return 0;
}
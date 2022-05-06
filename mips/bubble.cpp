
int main()
{
    int a[5];
    int i;
    int j;
    int t;
    a[0]=9;
    a[1]=3;
    a[2]=4;
    a[3]=2;
    a[4]=7;
    i=0;
    j=0;
    while(i<4)
    {
        j=0;
        while(j<4)
        {
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
            j=j+1;
        }
        i=i+1;
    }
    i=0;
    putint(a[0]);
    putint(a[1]);
    putint(a[2]);
    putint(a[3]);
    putint(a[4]);

    return 0;

    
}	
        
        
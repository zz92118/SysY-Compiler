int ret;
int Fibon1(int n)
{
	if (n == 1)
	{
		return 1;
	}

    if(n==2)
    {
        return 1;
    }
	else
	{
		return Fibon1(n - 1) + Fibon1(n - 2);
	}
}

int main()
{
	int n = 6;
	ret = Fibon1(7);
	putint(ret);
	return 0;
}
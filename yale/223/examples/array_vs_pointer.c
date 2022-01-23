int
sumArray(int n, const int a[])
{
    const int *an;	/* pointer to first element not in a */
    int sum;

    sum = 0;
    an = a+n;

    while(a < an) {
	sum += *a++;
    }

    return sum;
}

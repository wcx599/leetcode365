/* return the number of times the function has been called */
int
counter(void)
{
    static count = 0;

    return ++count;
}

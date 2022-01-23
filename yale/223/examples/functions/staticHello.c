static void
helloHelper(void)
{
    puts("hi!");
}

void
hello(int repetitions)
{
    int i;

    for(i = 0; i < repetitions; i++) {
        helloHelper();
    }
}

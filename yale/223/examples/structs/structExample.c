struct string {
    int length;
    char *data;
};

int
main(int argc, char **argv)
{
    struct string s;

    s.length = 4;
    s.data = "this string is a lot longer than you think";

    puts(s.data);

    return 0;
}

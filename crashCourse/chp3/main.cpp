/* ************************************************************************
> File Name:     main.cpp
> Author:        Lawrence
> Created Time:  Tue Jan 18 10:23:57 2022
> Description:   
 ************************************************************************/


#include <cstdio>


struct College {
    char name[256];

};


void print_names (College* name_ptr) {
    printf("%s College\n", name_ptr->name);
}


int main(){
    College names[] = {"first name", "second name def", "ghi"};
    printf("size of names is %lu\n", sizeof(names));
    print_names(names); // array essentially is a pointer
}

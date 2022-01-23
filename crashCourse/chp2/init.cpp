/* ************************************************************************
> File Name:     init.cpp
> Author:        Lawrence
> Created Time:  Mon Jan 17 20:08:21 2022
> Description:   
 ************************************************************************/


#include <cstdio>
struct SampleInit {
    bool gold = true;
    int year_of_age = {100};
    char name_of_person[100] = {"acebdc"};
    int *ptr_of_persion;
};

int main() {
    SampleInit init_1;
    SampleInit* init_ptr = &init_1;
    //init_1.name_of_person = {"a", "c", "e"};
    printf("initilized person's name is  %s\n", init_1.name_of_person);
    printf("pointer to the init persion is %p vs classptr  %p \n", init_1.ptr_of_persion);

};


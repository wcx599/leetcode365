/* ************************************************************************
> File Name:     main.cpp
> Author:        Lawrence
> Created Time:  Sat Jan 15 21:14:32 2022
> Description:   
 ************************************************************************/
#include <cstdio>

int step_function(int x){
    
    if(x==0){
        return 0;
    }
    else if (x < 0){
        return -1;
    }
    else if (x > 0){

        return 1;
    }
    return 0;
}

int main(){
//  printf("Hello, world!");
//  return 0;
    int x1 = 43;
    int x2 = 8989;
    int x3 = -999;

    printf("value %d, Steps: %d\n", x1, step_function(x1));
    printf("value %d, Steps: %d\n", x2, step_function(x2));
    printf("value %d, Steps: %d\n", x3, step_function(x3));


}

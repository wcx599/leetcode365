/* ************************************************************************
> File Name:     main.cpp
> Author:        Lawrence
> Created Time:  Mon Jan 17 17:17:24 2022
> Description:   
 ************************************************************************/
#include <cstdio>
#include <cstdint>


struct ClockOfTheLongNow {
    int clockyear;
    bool set_year( int year ){
        if ( !(year > 2018)) {return false;}
        clockyear = year;
        return true;
    }
    void add_year(){
       clockyear++;
    }
    int get_year(){
        return clockyear;   
    }
    ClockOfTheLongNow (int year){
        if (!set_year(year)){
           clockyear = 2020;
        }
    };

};


struct PodStruct{
    uint64_t a;
    char b[256];
    bool c;
   
};


void add_year(ClockOfTheLongNow& clock){

   // clock_in_class.set_year(clock_in_class.get_year() + 1);
   clock.set_year(clock.get_year() + 1);

}


int main(){
    ClockOfTheLongNow clock(2018);
    //clock.set_year(2018);
    //clock.add_year();
    
    add_year(clock);
    printf("This year is %d\n", clock.get_year());
    
    

    PodStruct init_pod1 = {};

    PodStruct init_pod2 = {};

    PodStruct init_pod3 = {34, "Hello"};

    PodStruct init_pod4 = {45, "Hello", true};

    PodStruct init_pod5 = {0};
    printf("size of init pod 4 %lu\n", sizeof(init_pod4));
}



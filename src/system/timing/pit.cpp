#pragma once

#include "../../Kernel.cpp"

/*void FakePIT_WaitSeconds(uint_32 seconds){
    read_rtc();
    uint_32 done = false;
    uint_32 is = second;
    while(!done){
        read_rtc();
        if(second == is + seconds){
            done = true;
            return;
        }
    }
}*/
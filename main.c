#include <stdio.h>
#include <stdlib.h>

#include "TrafficControl.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        printf("args %s \n", argv[1]);
        trafficControl_init(argv[1]); // Initialize variables
    }
    else
    {
        trafficControl_init(NULL); // Initialize variables
    }

    while(1)
    {
       trafficControl_monitor();
    };

    return 0;
}

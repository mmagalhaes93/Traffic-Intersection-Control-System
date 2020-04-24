#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "TrafficControl.h"

#define CUB_0   0
#define CUB_1   1
#define CUB_2   2
#define CUB_3   3

typedef enum { false, true } bool;
typedef enum {Red, Green} TrafficLight;
typedef enum {NS_TURN, NS_THROUGH, EW_TURN, EW_THROUGH, MAX_PATTERN} TrafficPattern;


typedef struct
{
    bool vehSensor;
    TrafficLight trafficLight;
} Lane;

typedef struct
{
   Lane laneThrough;
   Lane laneTurn;
} Road;

static TrafficPattern trafficState;
clock_t start_t, difTime;
int testCase;

static void trafficControl_readVehSensors(void);
static void trafficControl_clearTrafficLights(void);
static void trafficControl_updateTrafficLights(void);
static Road North, South, East, West;

/* Read Vehicle Sensors */
static void trafficControl_readVehSensors(void)
{
    // Do nothing - This function would read the vehicle queue sensors and update the corresponding variables
    bool sensorValue;

    if(testCase == CUB_1)
        sensorValue = true;
    else
        sensorValue = false;

    switch (trafficState)
    {
        case NS_TURN:
          if(testCase == CUB_2)
              North.laneTurn.vehSensor = true;
          else
              North.laneTurn.vehSensor = sensorValue;

          South.laneTurn.vehSensor = sensorValue;
          break;

        case NS_THROUGH:
          North.laneThrough.vehSensor = sensorValue;
          South.laneThrough.vehSensor = sensorValue;
          break;

        case EW_TURN:
          East.laneTurn.vehSensor = sensorValue;
          West.laneTurn.vehSensor = sensorValue;
          break;

        case EW_THROUGH:
          East.laneThrough.vehSensor = sensorValue;
          West.laneThrough.vehSensor = sensorValue;
          break;

        default:
          // Do nothing
          break;
    }
};

static void trafficControl_clearTrafficLights(void)
{
    North.laneThrough.trafficLight = Red;
    North.laneTurn.trafficLight = Red;
    South.laneThrough.trafficLight = Red;
    South.laneTurn.trafficLight = Red;
    East.laneThrough.trafficLight = Red;
    East.laneTurn.trafficLight = Red;
    West.laneThrough.trafficLight = Red;
    West.laneTurn.trafficLight = Red;
};

/* Update traffic Lights according to monitor info*/
static void trafficControl_updateTrafficLights(void)
{
    printf("\nState %d\n",trafficState);
    trafficControl_clearTrafficLights();

    sleep(CUB_3); // Upper bound limit

    switch (trafficState)
    {
        case NS_TURN:
          North.laneTurn.trafficLight = Green;
          South.laneTurn.trafficLight = Green;
          break;

        case NS_THROUGH:
          North.laneThrough.trafficLight = Green;
          South.laneThrough.trafficLight = Green;
          break;

        case EW_TURN:
          East.laneTurn.trafficLight = Green;
          West.laneTurn.trafficLight = Green;
          break;

        case EW_THROUGH:
          East.laneThrough.trafficLight = Green;
          West.laneThrough.trafficLight = Green;
          break;

        default:
          // Do nothing
          break;
    }
    start_t = clock();
};


/* Initialize road info*/
void trafficControl_init(char* testCaseValue)
{
    int value = atoi(testCaseValue);

    if (CUB_1 <= value && value < CUB_3)
    {
        testCase = value;
    }
    else
    {
        testCase = 0;
    }
    trafficState = NS_TURN;
    trafficControl_updateTrafficLights();
};

/* Monitors traffic conditions for the intersections and
set the traffic signal accordingly*/
void trafficControl_monitor(void)
{
    bool vehInQueue;

    trafficControl_readVehSensors(); // read sensors
    difTime = (int)(clock() - start_t) / CLOCKS_PER_SEC;

    if(trafficState == NS_TURN)
    {
        vehInQueue = (North.laneTurn.vehSensor || South.laneTurn.vehSensor);

        if(((difTime >= NS_TURN_MIN_TIME) && (vehInQueue == false)) || (difTime >= NS_TURN_MAX_TIME))
        {
           goto next_state;
        }
    }
    else if(trafficState == NS_THROUGH)
    {
        vehInQueue = (North.laneThrough.vehSensor || South.laneThrough.vehSensor);

        if(((difTime >= NS_THROUGH_MIN_TIME) && (vehInQueue == false)) || (difTime >= NS_THROUGH_MAX_TIME))
        {
           goto next_state;
        }

    }
    else if(trafficState == EW_TURN)
    {
        vehInQueue = (East.laneTurn.vehSensor || West.laneTurn.vehSensor);

        if(((difTime >= EW_TURN_MIN_TIME) && (vehInQueue == false)) || (difTime >= EW_TURN_MAX_TIME))
        {
            goto next_state;
        }

    }
    else if(trafficState == EW_THROUGH)
    {
        vehInQueue = (East.laneThrough.vehSensor || West.laneThrough.vehSensor);

        if(((difTime >= EW_THROUGH_MIN_TIME) && (vehInQueue == false)) || (difTime >= EW_THROUGH_MAX_TIME))
        {
           goto next_state;
        }
    }
    printf("%ld",difTime);
    sleep(CUB_1);
    return;

    next_state:
        trafficState=(trafficState+CUB_1)%MAX_PATTERN;
        trafficControl_updateTrafficLights();
};

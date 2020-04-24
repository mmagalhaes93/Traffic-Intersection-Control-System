#ifndef TRAFFICCONTROL_H_INCLUDED
#define TRAFFICCONTROL_H_INCLUDED

#include <stdio.h>

#define NS_TURN_MIN_TIME       (10)
#define NS_TURN_MAX_TIME       (60)
#define NS_THROUGH_MIN_TIME    (30)
#define NS_THROUGH_MAX_TIME    (120)
#define EW_TURN_MIN_TIME       (10)
#define EW_TURN_MAX_TIME       (30)
#define EW_THROUGH_MIN_TIME    (30)
#define EW_THROUGH_MAX_TIME    (60)


extern void trafficControl_init(char* testCaseValue);
extern void trafficControl_monitor(void);

#endif // TRAFFICCONTROL_H_INCLUDED

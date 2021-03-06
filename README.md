# Traffic-Intersection-Control-System

Traffic control algorithm for a a 4-way traffic intersection with the following configuration:

• Four roads (North, South, East, and West) intersecting at right angles 

• Each road has two lanes: a through lane and a left turn lane 

• Each lane has a dedicated traffic light and vehicle sensor

Intructions to test:
- Run the executable (./bin/Debug/TrafficLightController.exe) through the command line
- To walk through different test cases add a second argument correspondig to the following test cases

Test Cases:

1. Arg = 0 , No vehicles queued in any lane
Expected behavior: Min time for every traffic pattern

2. Arg = 1, Vehicles queued in every lanes (rush hour)
Expected behavior: Max time for every traffic pattern

3. Arg = 2, Vehicles queued in one of opposing lanes (Ex: Vehicles queued in Nouth Turn lane but not in South Turn Lane)
Expected behavior: Max time for North-South-Turn traffic pattern,  Min time for remaining traffic patterns

In the command line, it will be printed the active status of the traffic pattern and corresponding active times. An upper bound time of 3 seconds is used to wait for any car travelling through the intersection.

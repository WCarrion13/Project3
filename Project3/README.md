# Natural Disaster's Project

This project is meant to help governments take the best course of action during a Natural Disaster. We all live in the state of Florida and believe it essential that everybody is able to evacuate from a city safely when the time comes.

## How to start up Project

The entire project will be run from terminal or command line.

### 1.

On terminal or command line you must be in the directory that contains this README file and the Makefile are located

```bash
cd Code_Group43
ls
CMakeLists.txt			Project3.vcxproj.filters
City.h				      PushRelabel.h
DataGenerator.cpp		README.md
DataGenerator.h			Randomizer.cpp
FordFulkerson.h			Randomizer.h
Graph.cpp			      Reader.cpp
Graph.h				      Reader.h
Makefile			      main.cpp
NetworkFlow.cpp			test.csv
Project3.vcxproj
```
### 2.

Once you have moved to the correct directory you need to run the make file that will compile and link all of the .cpp and .h files
You will likely receive some warnings but they shouldn't affect the performance of the program

```bash
make
```

When everything gets compiled and linked together you then run the executable file

```bash
./main
```
## Using the Program as intended

The program should now be running properly and you should see the following main menu:

```bash
Welcome to Natural Disaster\'s Project!
Please enter one of the following options (e.g. 1):
[1] Generate random Road Network
[2] Enter your own parameters
[3] Generate Max Flow of 10,000 Road Networks
[4] Toggle Hurricane output
[5] Exit program
```
The only valid inputs are the integers specified.
If a string or char is entered the program may or may not fail.
We have had mixed success with containing this so it is better that you only enter integers. 

1. The first option creates a random Road Network for the user and then they can choose to either have the Ford-Fulkerson, Push-Relabel, or both output the maximum flow of the random road network.

2. The second option will allow you to enter your own parameters that enables the user to partially personalize the road network they want to see the algorithms solve.

3. The third option will output the max flow of 10,000 road networks each consisting of 10 cities. This was built to fulfill the 100,000 row data set requirement. This output will not give the hurricane scenario even if the user has it toggle on fro performance reasons.

  3. a. The user can alter the number of Cities, the minimum and maximum possible value for a road capacity, and the minimum and maximum possible population of each city.

4. The user can choose toggle on or off the hurricane scenario. Won't affect option 3.

5. When the user is done utilizing the program they can end it by choosing this option.

## Example of what output should look like

```bash
Welcome to Natural Disaster\'s Project!
Please enter one of the following options (e.g. 1):
[1] Generate random Road Network
[2] Enter your own parameters
[3] Generate Max Flow of 10,000 Road Networks
[4] Toggle Hurricane output
[5] Exit program
1
You\'ve selected Option 1:
Choose whether you want to get max flow from FF, PR, or both:
[1] Ford Fulkerson:
[2] Push Relabel:
[3] Both:
[4] Main menu:

3
FF: Up to 1222 people per hour can evacuate from City of Xibbdfrz to Dgpljfis
PR: Up to 1222 people per hour can evacuate from City of Xibbdfrz to Dgpljfis

The hurricane\'s speed is 259 per hour
It falls into Category 5

DANGER: THE HURRICANE IS DESTRUCTIVE.
PREPERATION AND EVACUATION REQUIRED IN ADVANCE
HURRICANE WILL HIT BEFORE FULL EVACUATION
Total shelter capacity of City of Xibbdfrz is 0
244286 people will be left out of City of Xibbdfrz\'s shelters

The people of City of Xibbdfrz are unprotected.
Producing list of nearby Cities and their shelter capacities
Name: City of UrqfxgqlTotal capacity: 10000
Name: City of ZhbuxhwTotal capacity: 10000
Name: Vpfdfb
Total capacity: 0 Doesn\'t have shelter. AVOID AT ALL COST!

Please enter one of the following options (e.g. 1):
[1] Generate random Road Network
[2] Enter your own parameters
[3] Generate Max Flow of 10,000 Road Networks
[4] Toggle Hurricane output
[5] Exit program
5
Terminating Program. Good Bye!
```

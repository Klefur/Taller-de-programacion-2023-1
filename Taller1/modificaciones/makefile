testCrossingRiver: Load.o State.o Stack.o CrossingRiver.o testCrossingRiver.cpp
	g++ -o testCrossingRiver Load.o State.o Stack.o CrossingRiver.o testCrossingRiver.cpp
testLoad: Load.o testLoad.cpp
	g++ -o testLoad Load.o testLoad.cpp
testState: State.o testState.cpp
	g++ -o testState State.o testState.cpp
testStack: State.o Stack.o testStack.cpp
	g++ -o testStack State.o Stack.o testStack.cpp
CrossingRiver.o: CrossingRiver.h CrossingRiver.cpp
	g++ -c CrossingRiver.cpp
State.o: State.cpp State.h
	g++ -c State.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
Load.o: Load.h Load.cpp
	g++ -c Load.cpp
clean:
	rm -f *.o testState testLoad 
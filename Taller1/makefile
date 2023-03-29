testCrossingRiver: State.o Stack.o CrossingRiver.o testCrossingRiver.cpp
	g++ -o testCrossingRiver State.o Stack.o CrossingRiver.o testCrossingRiver.cpp
CrossingRiver.o: CrossingRiver.h CrossingRiver.cpp
	g++ -c CrossingRiver.cpp
testStack: State.o Stack.o testStack.cpp
	g++ -o testStack State.o Stack.o testStack.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
testState: State.o testState.cpp
	g++ -o testState State.o testState.cpp
	ls *
State.o: State.cpp State.h
	g++ -c State.cpp
clean:
	rm -f *.o testState testLoad 
run_testState:
	./testState
testCrossingRiver: Load.o State.o Stack.o Operacion.o CrossingRiver.o testCrossingRiver.cpp
	g++ -o testCrossingRiver Load.o State.o Stack.o Operacion.o CrossingRiver.o testCrossingRiver.cpp
main: Load.o State.o Stack.o Operacion.o CrossingRiver.o main.cpp
	g++ -o main Load.o State.o Stack.o Operacion.o CrossingRiver.o main.cpp
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
Operacion.o: Operacion.cpp Operacion.h
	g++ -c Operacion.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
Load.o: Load.h Load.cpp
	g++ -c Load.cpp
clean:
	rm -f *.o testState testLoad 
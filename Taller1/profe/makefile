all: testLCR testStack testState testHeap main

testLCR: State.o Stack.o LCR.o testLCR.cpp
	g++ -o testLCR State.o Stack.o LCR.o testLCR.cpp
LCR.o: LCR.h LCR.cpp
	g++ -c LCR.cpp
testStack: State.o Stack.o testStack.cpp
	g++ -o testStack State.o Stack.o testStack.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
testState: State.o testState.cpp
	g++ -o testState State.o testState.cpp
State.o: State.cpp State.h
	g++ -c State.cpp
testHeap: State.o Heap.o testHeap.cpp
	g++ -o testHeap State.o Heap.o testHeap.cpp
Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp
main: State.o Stack.o LCR.o main.cpp
	g++ -o main State.o Stack.o LCR.o main.cpp
clean:
	rm -f *.o testLCR testStack testState testHeap main
run_all:
	./testState
	./testStack
	./testLCR
	./testHeap
	./main

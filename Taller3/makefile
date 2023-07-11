FLAGS = -g
all: testSimplex main testHeap testNode testBB
main: main.cpp BB.o Simplex.o Node.o Heap.o
	g++ $(FLAGS) BB.o Simplex.o Node.o Heap.o main.cpp -o main
testSimplex: Simplex.o testSimplex.cpp 
	g++ $(FLAGS) Simplex.o testSimplex.cpp -o testSimplex
testHeap: BB.o testHeap.cpp Node.o Heap.o Simplex.o
	g++ $(FLAGS) BB.o Node.o Heap.o Simplex.o testHeap.cpp -o testHeap
testNode: Node.o Simplex.o testNode.cpp
	g++ $(FLAGS) Node.o Simplex.o testNode.cpp -o testNode
testBB: BB.o testBB.cpp Node.o Heap.o Simplex.o
	g++ $(FLAGS) BB.o Node.o Heap.o Simplex.o testBB.cpp -o testBB
Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp
Heap.o: Heap.cpp Heap.h
	g++ $(FLAGS) -c Heap.cpp
Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp
BB.o: BB.cpp BB.h
	g++ $(FLAGS) -c BB.cpp
clean:
	rm -f *.o testSimplex testHeap main testNode testBB

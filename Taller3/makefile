FLAGS = -g
all: testSimplex
testSimplex: Simplex.o testSimplex.cpp
	g++ $(FLAGS) Simplex.o testSimplex.cpp -o testSimplex
Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp
clean:
	rm -f *.o testSimplex

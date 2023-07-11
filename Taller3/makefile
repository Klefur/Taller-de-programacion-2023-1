FLAGS = -g
all: testSimplex main
testSimplex: Simplex.o testSimplex.cpp
	g++ $(FLAGS) Simplex.o testSimplex.cpp -o testSimplex
Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp
Solve.o: Solve.cpp Solve.h
	g++ $(FLAGS) -c Solve.cpp
main: main.cpp Solve.o Simplex.o
	g++ $(FLAGS) Solve.o Simplex.o main.cpp
clean:
	rm -f *.o testSimplex a.out

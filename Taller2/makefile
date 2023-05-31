Main: Node.o Node_Operation.o Node_Variable.o Node_Number.o 
	g++ -o main Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.cpp
Node.o:
	g++ -c Node.cpp
Node_Operation.o:
	g++ -c Node_Operation.cpp
Node_Number.o:
	g++ -c Node_Number.cpp
Node_Variable.o:
	g++ -c Node_Variable.cpp
clean:
	rm main *.o
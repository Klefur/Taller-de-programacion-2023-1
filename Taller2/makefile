Main: Node.o Node_Operation.o Node_Variable.o Node_Number.o AST.o 
	g++ -o main Node.o Node_Operation.o Node_Variable.o Node_Number.o AST.o loadFile.cpp
AST.o:
	g++ -c AST.cpp
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
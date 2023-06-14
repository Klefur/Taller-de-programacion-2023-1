Main: Node.o Node_Operation.o Node_Variable.o Node_Number.o AST.o 
	g++ -o main Node.o Node_Operation.o Node_Variable.o Node_Number.o AST.o main.cpp
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
testNode_Operation: Node_Operation.o Node.o Node_Number.o
	g++ -o testNode_Operation Node_Operation.o Node_Number.o Node.o testNode_Operation.cpp
testNode_Number: Node_Number.o Node.o
	g++ -o testNode_Number Node_Number.o Node.o testNode_Number.cpp
testNode_Variable: Node_Variable.o Node.o
	g++ -o testNode_Variable Node_Variable.o Node.o testNode_Variable.cpp
testAST: AST.o Node.o Node_Operation.o Node_Variable.o Node_Number.o
	g++ -o testAST AST.o Node.o Node_Operation.o Node_Variable.o Node_Number.o testAST.cpp
clean:
	rm main testNode_Number testNode_Operation testNode_Variable testAST *.o
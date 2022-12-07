headers = Matrix.h Exception.h MatrixStruct.h
sources = Matrix.cpp TestMatrix.cpp MatrixStruct.cpp
executable = TestMatrix
$(executable): $(headers) $(sources)
	g++ -g -Wall -pedantic $(sources) -o $(executable)
.PHONY: clean
	rm $(executable)
.PHONY: check
check: $(executable)
	valgrind --leak-check=full --track-origins=yes ./$(executable)
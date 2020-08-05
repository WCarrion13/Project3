main: main.o Reader.o Randomizer.o DataGenerator.o Graph.o
	g++ -o main main.o Reader.o Randomizer.o DataGenerator.o Graph.o

main.o: main.cpp DataGenerator.h Reader.h FordFulkerson.h PushRelabel.h
	g++ -c main.cpp

Reader.o: Reader.cpp Reader.h
	g++ -c Reader.cpp

Randomizer.o: Randomizer.cpp Randomizer.h
	g++ -c Randomizer.cpp

DataGenerator.o: DataGenerator.cpp DataGenerator.h
	g++ -c DataGenerator.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp
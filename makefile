CC = g++
all: golfgraph
golfgraph: golfgraph.o
	${CC} -o golfgraph golfgraph.o
golfgraph.co: golfgraph.cpp
	${CC} -c golfgraph.cpp

run: golfgraph
	./golfgraph golftest.txt

clean:
	rm golfgraph.o golfgraph

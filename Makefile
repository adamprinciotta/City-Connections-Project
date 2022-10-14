
all: project5

project5:	project5.o province.o road.o city.o
	g++ -o  $@ $^

test1: project5
	./project5 < t01.in > t01.out

test2: project5
	./project5 < t08.in > t08.out

test3: project5
	./project5 < t05.in > t05.out

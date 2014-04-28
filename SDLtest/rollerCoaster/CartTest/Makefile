all: main

main: main.o Cart.o Cart.h
	g++ Cart.o Force.o main.cpp -lSDL -lSDL_gfx -o main
Cart.o: Cart.cpp Cart.h
	g++ -c Cart.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -f *.o main

all: main

main: main.o RollerCoaster.o TrackPiece.o Rating.o Button.o Menu.o Cart.o Cart.h RollerCoaster.h TrackPiece.h Rating.h Button.h Menu.h
	g++ RollerCoaster.o TrackPiece.o Rating.o main.cpp -lSDL -lSDL_gfx -lSDL_image -o main
RollerCoaster.o: RollerCoaster.cpp RollerCoaster.h
	g++ -c RollerCoaster.cpp
TrackPiece.o: TrackPiece.cpp TrackPiece.h
	g++ -c TrackPiece.cpp
Rating.o: Rating.cpp Rating.h
	g++ -c Rating.cpp
Button.o: Button.cpp Button.h
	g++ -c Button.cpp
Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp
Cart.o: Cart.cpp Cart.h
	g++ -c Cart.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -f *.o main

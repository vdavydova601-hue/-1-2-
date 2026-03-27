all: theater

theater: main.o theater_db.o
 g++ -o theater main.o theater_db.o

main.o: main.cpp theater_db.h
 g++ -c main.cpp

theater_db.o: theater_db.cpp theater_db.h
 g++ -c theater_db.cpp

clean:
 rm -f *.o theater

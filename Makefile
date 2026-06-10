CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
TARGET = theatre_db
OBJS = main.o theater.o database.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp database.h list.h theatre.h
	$(CXX) $(CXXFLAGS) -c main.cpp

theater.o: theater.cpp theatre.h
	$(CXX) $(CXXFLAGS) -c theater.cpp

database.o: database.cpp database.h list.h theatre.h
	$(CXX) $(CXXFLAGS) -c database.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

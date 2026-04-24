CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = theater_db
SOURCES = main.cpp theater_db.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = theater_db.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

theater_db.o: theater_db.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c theater_db.cpp

clean:
	rm -f $(OBJECTS) $(TARGET) theater.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

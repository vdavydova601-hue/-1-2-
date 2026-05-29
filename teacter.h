#ifndef THEATRE_H
#define THEATRE_H

#include <string>
#include <iostream>

struct TheatreRecord {
    int customerNumber;
    std::string date;
    std::string time;
    std::string playName;
    int row;
    int seat;
    
    TheatreRecord();
    TheatreRecord(int num, const std::string& d, const std::string& t, 
                  const std::string& name, int r, int s);
    
    void print() const;
    std::string toString() const;
    static TheatreRecord fromString(const std::string& line);
};

#endif

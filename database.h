#ifndef DATABASE_H
#define DATABASE_H

#include "list.h"
#include "theatre.h"
#include <string>

class TheatreDatabase {
private:
    List<TheatreRecord> records;
    std::string filename;
    int nextCustomerNumber;
    
    int generateCustomerNumber();
    void updateNextNumber();
    bool isSeatTaken(const std::string& date, int row, int seat) const;
    
public:
    TheatreDatabase(const std::string& file);
    
    bool loadFromFile();
    bool saveToFile() const;
    void displayAll() const;
    void searchByPlayName(const std::string& playName) const;
    void searchByDate(const std::string& date) const;
    void searchByRowAndSeat(int row, int seat) const;
    void addRecord(const std::string& date, const std::string& time,
                   const std::string& playName, int row, int seat);
    bool deleteRecord(int customerNumber);
    bool editRecord(int customerNumber);
    size_t getSize() const;
};

#endif

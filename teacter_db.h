#ifndef THEATER_DB_H
#define THEATER_DB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class Date {
public:
    int day, month, year;
    Date(int d = 1, int m = 1, int y = 2024);
    bool isValid() const;
    string toString() const;
    bool operator==(const Date& other) const;
};

class Time {
public:
    int hour, minute;
    Time(int h = 0, int m = 0);
    bool isValid() const;
    string toString() const;
};

class TheaterRecord {
private:
    int id;
    Date date;
    Time startTime;
    string showName;
    int row;
    int seat;
    
public:
    TheaterRecord(int id = -1, const Date& d = Date(), const Time& t = Time(),
                  const string& name = "", int r = 1, int s = 1);
    
    int getId() const { return id; }
    Date getDate() const { return date; }
    Time getTime() const { return startTime; }
    string getShowName() const { return showName; }
    int getRow() const { return row; }
    int getSeat() const { return seat; }
    
    void setDate(const Date& d) { date = d; }
    void setTime(const Time& t) { startTime = t; }
    void setShowName(const string& name) { showName = name; }
    void setRow(int r) { row = r; }
    void setSeat(int s) { seat = s; }
    void setId(int newId) { id = newId; }
    
    void print() const;
    string toString() const;
    
    bool matchesSeat(int r, int s) const { return row == r && seat == s; }
    bool matchesId(int searchId) const { return id == searchId; }
};

class TheaterDatabase {
private:
    vector<TheaterRecord> records;
    int nextId;
    const string filename;
    
    int findIndexById(int id) const;
    void updateNextId();
    
public:
    TheaterDatabase(const string& file = "theater.txt");
    ~TheaterDatabase();
    
    bool loadFromFile();
    bool saveToFile() const;
    
    void addRecord(const TheaterRecord& record);
    bool removeRecord(int id);
    bool editRecord(int id, const TheaterRecord& newData);
    
    TheaterRecord* findById(int id);
    const TheaterRecord* findById(int id) const;
    vector<TheaterRecord> searchBySeat(int row, int seat) const;
    vector<TheaterRecord> searchByDateAndShow(const Date& date, const string& showName) const;
    
    void printAll() const;
    int getCount() const { return records.size(); }
    bool isEmpty() const { return records.empty(); }
};

Date inputDate();
Time inputTime();
void clearInputBuffer();

#endif

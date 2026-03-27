#ifndef THEATER_DB_H
#define THEATER_DB_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>

const int MAX_NAME = 100;
const std::string FILENAME = "theater.txt";

struct Record {
    int id;                     
    int day, month, year;       
    int hour, minute;           
    char show[MAX_NAME];        
    int row;                    
    int seat;                   
    Record* next;               
    
    Record();
    Record(int id, int d, int m, int y, int hr, int min, 
           const char* show, int r, int s);
};

void free_list(Record* head);
Record* add_record(Record* head, int& next_id);
Record* remove_record(Record* head, int id);
Record* find_by_id(Record* head, int id);
void print_all(Record* head);
void save_to_file(Record* head);
Record* load_from_file(int& next_id);

#endif

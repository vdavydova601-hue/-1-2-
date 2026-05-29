#include "theatre.h"
#include <sstream>
#include <iomanip>

TheatreRecord::TheatreRecord() 
    : customerNumber(0), date(""), time(""), playName(""), row(0), seat(0) {}

TheatreRecord::TheatreRecord(int num, const std::string& d, const std::string& t, 
                              const std::string& name, int r, int s)
    : customerNumber(num), date(d), time(t), playName(name), row(r), seat(s) {}

void TheatreRecord::print() const {
    std::cout << "┌─────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Номер покупателя: " << std::left << std::setw(35) << customerNumber << "│\n";
    std::cout << "├─────────────────────────────────────────────────────────────┤\n";
    std::cout << "│ Дата спектакля:   " << std::setw(35) << date << "│\n";
    std::cout << "│ Время начала:     " << std::setw(35) << time << "│\n";
    std::cout << "│ Название:         " << std::setw(35) << playName << "│\n";
    std::cout << "│ Ряд:              " << std::setw(35) << row << "│\n";
    std::cout << "│ Место:            " << std::setw(35) << seat << "│\n";
    std::cout << "└─────────────────────────────────────────────────────────────┘\n";
}

std::string TheatreRecord::toString() const {
    return std::to_string(customerNumber) + "|" + date + "|" + time + "|" + 
           playName + "|" + std::to_string(row) + "|" + std::to_string(seat);
}

TheatreRecord TheatreRecord::fromString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    TheatreRecord record;
    
    std::getline(ss, token, '|');
    record.customerNumber = std::stoi(token);
    std::getline(ss, record.date, '|');
    std::getline(ss, record.time, '|');
    std::getline(ss, record.playName, '|');
    std::getline(ss, token, '|');
    record.row = std::stoi(token);
    std::getline(ss, token, '|');
    record.seat = std::stoi(token);
    
    return record;
}

#include "theatre.h"
#include <sstream>
#include <iomanip>

TheatreRecord::TheatreRecord() 
    : customerNumber(0), date(""), time(""), playName(""), row(0), seat(0) {}

TheatreRecord::TheatreRecord(int num, const std::string& d, const std::string& t, 
                              const std::string& name, int r, int s)
    : customerNumber(num), date(d), time(t), playName(name), row(r), seat(s) {}

void TheatreRecord::print() const {
    std::cout << "в”Њв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”ђ\n";
    std::cout << "в”‚ РќРѕРјРµСЂ РїРѕРєСѓРїР°С‚РµР»СЏ: " << std::left << std::setw(35) << customerNumber << "в”‚\n";
    std::cout << "в”њв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”¤\n";
    std::cout << "в”‚ Р”Р°С‚Р° СЃРїРµРєС‚Р°РєР»СЏ:   " << std::setw(35) << date << "в”‚\n";
    std::cout << "в”‚ Р’СЂРµРјСЏ РЅР°С‡Р°Р»Р°:     " << std::setw(35) << time << "в”‚\n";
    std::cout << "в”‚ РќР°Р·РІР°РЅРёРµ:         " << std::setw(35) << playName << "в”‚\n";
    std::cout << "в”‚ Р СЏРґ:              " << std::setw(35) << row << "в”‚\n";
    std::cout << "в”‚ РњРµСЃС‚Рѕ:            " << std::setw(35) << seat << "в”‚\n";
    std::cout << "в””в”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”Ђв”\n";
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

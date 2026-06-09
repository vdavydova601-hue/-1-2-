#include "database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

TheatreDatabase::TheatreDatabase(const std::string& file) : filename(file), nextCustomerNumber(1) {
    loadFromFile();
}

int TheatreDatabase::generateCustomerNumber() {
    return nextCustomerNumber++;
}

void TheatreDatabase::updateNextNumber() {
    if (records.empty()) {
        nextCustomerNumber = 1;
        return;
    }
    
    int maxNum = 0;
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).customerNumber > maxNum) {
            maxNum = (*it).customerNumber;
        }
    }
    nextCustomerNumber = maxNum + 1;
}

bool TheatreDatabase::isSeatTaken(const std::string& date, int row, int seat) const {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).date == date && (*it).row == row && (*it).seat == seat) {
            return true;
        }
    }
    return false;
}

bool TheatreDatabase::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Р¤Р°Р№Р» РЅРµ РЅР°Р№РґРµРЅ. Р‘СѓРґРµС‚ СЃРѕР·РґР°РЅ РЅРѕРІС‹Р№.\n";
        return false;
    }
    
    records.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            TheatreRecord record = TheatreRecord::fromString(line);
            records.push_back(record);
        } catch (const std::exception& e) {
            std::cout << "РћС€РёР±РєР° С‡С‚РµРЅРёСЏ СЃС‚СЂРѕРєРё: " << line << "\n";
        }
    }
    
    file.close();
    updateNextNumber();
    std::cout << "Р—Р°РіСЂСѓР¶РµРЅРѕ " << records.size() << " Р·Р°РїРёСЃРµР№.\n";
    return true;
}

bool TheatreDatabase::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "РћС€РёР±РєР° РѕС‚РєСЂС‹С‚РёСЏ С„Р°Р№Р»Р° РґР»СЏ Р·Р°РїРёСЃРё!\n";
        return false;
    }
    
    for (auto it = records.begin(); it != records.end(); ++it) {
        file << (*it).toString() << "\n";
    }
    
    file.close();
    std::cout << "Р”Р°РЅРЅС‹Рµ СЃРѕС…СЂР°РЅРµРЅС‹ РІ С„Р°Р№Р».\n";
    return true;
}

void TheatreDatabase::displayAll() const {
    if (records.empty()) {
        std::cout << "Р‘Р°Р·Р° РґР°РЅРЅС‹С… РїСѓСЃС‚Р°.\n";
        return;
    }
    
    std::cout << "\n========== Р‘РђР—Рђ Р”РђРќРќР«РҐ РўР•РђРўР Рђ ==========\n";
    std::cout << "Р’СЃРµРіРѕ Р·Р°РїРёСЃРµР№: " << records.size() << "\n\n";
    
    int i = 1;
    for (auto it = records.begin(); it != records.end(); ++it) {
        std::cout << "Р—Р°РїРёСЃСЊ #" << i++ << "\n";
        (*it).print();
        std::cout << "\n";
    }
    std::cout << "========================================\n";
}

void TheatreDatabase::searchByPlayName(const std::string& playName) const {
    List<TheatreRecord> results;
    
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).playName.find(playName) != std::string::npos) {
            results.push_back(*it);
        }
    }
    
    if (results.empty()) {
        std::cout << "РЎРїРµРєС‚Р°РєР»Рё СЃ РЅР°Р·РІР°РЅРёРµРј \"" << playName << "\" РЅРµ РЅР°Р№РґРµРЅС‹.\n";
    } else {
        std::cout << "\nРќР°Р№РґРµРЅРѕ " << results.size() << " СЃРїРµРєС‚Р°РєР»РµР№:\n";
        for (auto it = results.begin(); it != results.end(); ++it) {
            (*it).print();
            std::cout << "\n";
        }
    }
}

void TheatreDatabase::searchByDate(const std::string& date) const {
    List<TheatreRecord> results;
    
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).date == date) {
            results.push_back(*it);
        }
    }
    
    if (results.empty()) {
        std::cout << "РЎРїРµРєС‚Р°РєР»Рё РЅР° РґР°С‚Сѓ \"" << date << "\" РЅРµ РЅР°Р№РґРµРЅС‹.\n";
    } else {
        std::cout << "\nРќР°Р№РґРµРЅРѕ " << results.size() << " СЃРїРµРєС‚Р°РєР»РµР№ РЅР° " << date << ":\n";
        for (auto it = results.begin(); it != results.end(); ++it) {
            (*it).print();
            std::cout << "\n";
        }
    }
}

void TheatreDatabase::searchByRowAndSeat(int row, int seat) const {
    List<TheatreRecord> results;
    
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).row == row && (*it).seat == seat) {
            results.push_back(*it);
        }
    }
    
    if (results.empty()) {
        std::cout << "РњРµСЃС‚Рѕ СЂСЏРґ " << row << ", РјРµСЃС‚Рѕ " << seat << " СЃРІРѕР±РѕРґРЅРѕ.\n";
    } else {
        std::cout << "\nРњРµСЃС‚Рѕ Р·Р°РЅСЏС‚Рѕ:\n";
        for (auto it = results.begin(); it != results.end(); ++it) {
            (*it).print();
            std::cout << "\n";
        }
    }
}

void TheatreDatabase::addRecord(const std::string& date, const std::string& time,
                                 const std::string& playName, int row, int seat) {
    if (isSeatTaken(date, row, seat)) {
        std::cout << "РћС€РёР±РєР°: РјРµСЃС‚Рѕ СЂСЏРґ " << row << ", РјРµСЃС‚Рѕ " << seat 
                  << " РЅР° " << date << " СѓР¶Рµ Р·Р°РЅСЏС‚Рѕ!\n";
        return;
    }
    
    int newNumber = generateCustomerNumber();
    TheatreRecord newRecord(newNumber, date, time, playName, row, seat);
    records.push_back(newRecord);
    saveToFile();
    
    std::cout << "Р‘РёР»РµС‚ СѓСЃРїРµС€РЅРѕ РґРѕР±Р°РІР»РµРЅ! РќРѕРјРµСЂ РїРѕРєСѓРїР°С‚РµР»СЏ: " << newNumber << "\n";
}

bool TheatreDatabase::deleteRecord(int customerNumber) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).customerNumber == customerNumber) {
            records.erase(it);
            saveToFile();
            std::cout << "Р—Р°РїРёСЃСЊ СЃ РЅРѕРјРµСЂРѕРј РїРѕРєСѓРїР°С‚РµР»СЏ " << customerNumber << " СѓРґР°Р»РµРЅР°.\n";
            return true;
        }
    }
    
    std::cout << "Р—Р°РїРёСЃСЊ СЃ РЅРѕРјРµСЂРѕРј РїРѕРєСѓРїР°С‚РµР»СЏ " << customerNumber << " РЅРµ РЅР°Р№РґРµРЅР°.\n";
    return false;
}

bool TheatreDatabase::editRecord(int customerNumber) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).customerNumber == customerNumber) {
            std::cout << "Р РµРґР°РєС‚РёСЂРѕРІР°РЅРёРµ Р·Р°РїРёСЃРё:\n";
            (*it).print();
            
            std::string input;
            std::cout << "\nР’РІРµРґРёС‚Рµ РЅРѕРІС‹Рµ РґР°РЅРЅС‹Рµ (РѕСЃС‚Р°РІСЊС‚Рµ РїСѓСЃС‚С‹Рј РґР»СЏ СЃРѕС…СЂР°РЅРµРЅРёСЏ С‚РµРєСѓС‰РёС…):\n";
            
            std::cout << "Р”Р°С‚Р° (С‚РµРєСѓС‰Р°СЏ: " << (*it).date << "): ";
            std::cin.ignore();
            std::getline(std::cin, input);
            if (!input.empty()) (*it).date = input;
            
            std::cout << "Р’СЂРµРјСЏ (С‚РµРєСѓС‰РµРµ: " << (*it).time << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).time = input;
            
            std::cout << "РќР°Р·РІР°РЅРёРµ СЃРїРµРєС‚Р°РєР»СЏ (С‚РµРєСѓС‰РµРµ: " << (*it).playName << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).playName = input;
            
            std::cout << "Р СЏРґ (С‚РµРєСѓС‰РёР№: " << (*it).row << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).row = std::stoi(input);
            
            std::cout << "РњРµСЃС‚Рѕ (С‚РµРєСѓС‰РµРµ: " << (*it).seat << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).seat = std::stoi(input);
            
            saveToFile();
            std::cout << "Р—Р°РїРёСЃСЊ СѓСЃРїРµС€РЅРѕ РѕС‚СЂРµРґР°РєС‚РёСЂРѕРІР°РЅР°!\n";
            return true;
        }
    }
    
    std::cout << "Р—Р°РїРёСЃСЊ СЃ РЅРѕРјРµСЂРѕРј РїРѕРєСѓРїР°С‚РµР»СЏ " << customerNumber << " РЅРµ РЅР°Р№РґРµРЅР°.\n";
    return false;
}

size_t TheatreDatabase::getSize() const {
    return records.size();
}

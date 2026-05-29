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
        std::cout << "Файл не найден. Будет создан новый.\n";
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
            std::cout << "Ошибка чтения строки: " << line << "\n";
        }
    }
    
    file.close();
    updateNextNumber();
    std::cout << "Загружено " << records.size() << " записей.\n";
    return true;
}

bool TheatreDatabase::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла для записи!\n";
        return false;
    }
    
    for (auto it = records.begin(); it != records.end(); ++it) {
        file << (*it).toString() << "\n";
    }
    
    file.close();
    std::cout << "Данные сохранены в файл.\n";
    return true;
}

void TheatreDatabase::displayAll() const {
    if (records.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    
    std::cout << "\n========== БАЗА ДАННЫХ ТЕАТРА ==========\n";
    std::cout << "Всего записей: " << records.size() << "\n\n";
    
    int i = 1;
    for (auto it = records.begin(); it != records.end(); ++it) {
        std::cout << "Запись #" << i++ << "\n";
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
        std::cout << "Спектакли с названием \"" << playName << "\" не найдены.\n";
    } else {
        std::cout << "\nНайдено " << results.size() << " спектаклей:\n";
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
        std::cout << "Спектакли на дату \"" << date << "\" не найдены.\n";
    } else {
        std::cout << "\nНайдено " << results.size() << " спектаклей на " << date << ":\n";
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
        std::cout << "Место ряд " << row << ", место " << seat << " свободно.\n";
    } else {
        std::cout << "\nМесто занято:\n";
        for (auto it = results.begin(); it != results.end(); ++it) {
            (*it).print();
            std::cout << "\n";
        }
    }
}

void TheatreDatabase::addRecord(const std::string& date, const std::string& time,
                                 const std::string& playName, int row, int seat) {
    if (isSeatTaken(date, row, seat)) {
        std::cout << "Ошибка: место ряд " << row << ", место " << seat 
                  << " на " << date << " уже занято!\n";
        return;
    }
    
    int newNumber = generateCustomerNumber();
    TheatreRecord newRecord(newNumber, date, time, playName, row, seat);
    records.push_back(newRecord);
    saveToFile();
    
    std::cout << "Билет успешно добавлен! Номер покупателя: " << newNumber << "\n";
}

bool TheatreDatabase::deleteRecord(int customerNumber) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).customerNumber == customerNumber) {
            records.erase(it);
            saveToFile();
            std::cout << "Запись с номером покупателя " << customerNumber << " удалена.\n";
            return true;
        }
    }
    
    std::cout << "Запись с номером покупателя " << customerNumber << " не найдена.\n";
    return false;
}

bool TheatreDatabase::editRecord(int customerNumber) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it).customerNumber == customerNumber) {
            std::cout << "Редактирование записи:\n";
            (*it).print();
            
            std::string input;
            std::cout << "\nВведите новые данные (оставьте пустым для сохранения текущих):\n";
            
            std::cout << "Дата (текущая: " << (*it).date << "): ";
            std::cin.ignore();
            std::getline(std::cin, input);
            if (!input.empty()) (*it).date = input;
            
            std::cout << "Время (текущее: " << (*it).time << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).time = input;
            
            std::cout << "Название спектакля (текущее: " << (*it).playName << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).playName = input;
            
            std::cout << "Ряд (текущий: " << (*it).row << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).row = std::stoi(input);
            
            std::cout << "Место (текущее: " << (*it).seat << "): ";
            std::getline(std::cin, input);
            if (!input.empty()) (*it).seat = std::stoi(input);
            
            saveToFile();
            std::cout << "Запись успешно отредактирована!\n";
            return true;
        }
    }
    
    std::cout << "Запись с номером покупателя " << customerNumber << " не найдена.\n";
    return false;
}

size_t TheatreDatabase::getSize() const {
    return records.size();
}

#include "database.h"
#include <iostream>
#include <limits>

void showMenu() {
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║           УПРАВЛЕНИЕ БАЗОЙ ДАННЫХ ТЕАТРА      ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║  1. Вывести все записи                        ║\n";
    std::cout << "║  2. Добавить новый билет                      ║\n";
    std::cout << "║  3. Поиск по спектаклю                        ║\n";
    std::cout << "║  4. Поиск по дате                             ║\n";
    std::cout << "║  5. Поиск по месту (ряд+место)                ║\n";
    std::cout << "║  6. Удалить запись по номеру покупателя       ║\n";
    std::cout << "║  7. Редактировать запись                      ║\n";
    std::cout << "║  8. Сохранить и выйти                         ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "Выберите действие: ";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::string dbFilename;
    std::cout << "Введите имя файла базы данных: ";
    std::cin >> dbFilename;
    
    TheatreDatabase db(dbFilename);
    
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                db.displayAll();
                break;
                
            case 2: {
                std::string date, time, playName;
                int row, seat;
                
                std::cout << "\n=== ДОБАВЛЕНИЕ НОВОГО БИЛЕТА ===\n";
                std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
                std::cin >> date;
                std::cout << "Введите время начала (ЧЧ:ММ): ";
                std::cin >> time;
                std::cout << "Введите название спектакля: ";
                clearInput();
                std::getline(std::cin, playName);
                std::cout << "Введите ряд: ";
                std::cin >> row;
                std::cout << "Введите место: ";
                std::cin >> seat;
                
                db.addRecord(date, time, playName, row, seat);
                break;
            }
            
            case 3: {
                std::string playName;
                std::cout << "\n=== ПОИСК ПО НАЗВАНИЮ СПЕКТАКЛЯ ===\n";
                std::cout << "Введите название: ";
                clearInput();
                std::getline(std::cin, playName);
                db.searchByPlayName(playName);
                break;
            }
            
            case 4: {
                std::string date;
                std::cout << "\n=== ПОИСК ПО ДАТЕ ===\n";
                std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
                std::cin >> date;
                db.searchByDate(date);
                break;
            }
            
            case 5: {
                int row, seat;
                std::cout << "\n=== ПОИСК ПО МЕСТУ ===\n";
                std::cout << "Введите ряд: ";
                std::cin >> row;
                std::cout << "Введите место: ";
                std::cin >> seat;
                db.searchByRowAndSeat(row, seat);
                break;
            }
            
            case 6: {
                int number;
                std::cout << "\n=== УДАЛЕНИЕ ЗАПИСИ ===\n";
                std::cout << "Введите номер покупателя: ";
                std::cin >> number;
                db.deleteRecord(number);
                break;
            }
            
            case 7: {
                int number;
                std::cout << "\n=== РЕДАКТИРОВАНИЕ ЗАПИСИ ===\n";
                std::cout << "Введите номер покупателя: ";
                std::cin >> number;
                db.editRecord(number);
                break;
            }
            
            case 8:
                std::cout << "\nСохранение данных...\n";
                db.saveToFile();
                std::cout << "До свидания!\n";
                break;
                
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
                break;
        }
        
    } while (choice != 8);
    
    return 0;
}

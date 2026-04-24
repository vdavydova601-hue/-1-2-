#include "theater_db.h"

void printMenu() {
    cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "║                  ТЕАТРАЛЬНАЯ БАЗА ДАННЫХ                     ║\n";
    cout << "╠═══════════════════════════════════════════════════════════════╣\n";
    cout << "║ 1. Показать все записи                                       ║\n";
    cout << "║ 2. Добавить новую запись                                     ║\n";
    cout << "║ 3. Найти запись по ID                                        ║\n";
    cout << "║ 4. Поиск по ряду и месту                                     ║\n";
    cout << "║ 5. Редактировать запись                                      ║\n";
    cout << "║ 6. Удалить запись                                            ║\n";
    cout << "║ 0. Выход                                                     ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "Выберите действие: ";
}

TheaterRecord inputNewRecord() {
    cout << "\n=== ВВОД ДАННЫХ ===\n";
    
    Date date = inputDate();
    Time time = inputTime();
    
    cin.ignore();
    string showName;
    cout << "Введите название спектакля: ";
    getline(cin, showName);
    
    int row, seat;
    while (true) {
        cout << "Введите ряд (1-50) и место (1-100): ";
        cin >> row >> seat;
        if (row >= 1 && row <= 50 && seat >= 1 && seat <= 100) {
            break;
        }
        cout << "Некорректный ряд или место! Попробуйте снова.\n";
        clearInputBuffer();
    }
    
    return TheaterRecord(-1, date, time, showName, row, seat);
}

void searchBySeatMenu(TheaterDatabase& db) {
    cout << "\n=== ПОИСК ПО РЯДУ И МЕСТУ ===\n";
    int row, seat;
    cout << "Введите ряд: ";
    cin >> row;
    cout << "Введите место: ";
    cin >> seat;
    
    vector<TheaterRecord> results = db.searchBySeat(row, seat);
    
    if (results.empty()) {
        cout << "Записей не найдено.\n";
    } else {
        cout << "\nНайдено записей: " << results.size() << "\n\n";
        for (const auto& record : results) {
            record.print();
            cout << endl;
        }
    }
}

void searchByIdMenu(TheaterDatabase& db) {
    cout << "\n=== ПОИСК ПО ID ===\n";
    int id;
    cout << "Введите ID: ";
    cin >> id;
    
    const TheaterRecord* record = db.findById(id);
    if (record) {
        record->print();
    } else {
        cout << "Запись с ID " << id << " не найдена.\n";
    }
}

void editRecordMenu(TheaterDatabase& db) {
    cout << "\n=== РЕДАКТИРОВАНИЕ ЗАПИСИ ===\n";
    int id;
    cout << "Введите ID записи для редактирования: ";
    cin >> id;
    
    const TheaterRecord* existing = db.findById(id);
    if (!existing) {
        cout << "Запись с ID " << id << " не найдена.\n";
        return;
    }
    
    cout << "Текущая запись:\n";
    existing->print();
    
    cout << "\nВведите новые данные:\n";
    TheaterRecord newData = inputNewRecord();
    
    if (db.editRecord(id, newData)) {
        cout << "Запись успешно обновлена!\n";
    } else {
        cout << "Ошибка при обновлении записи.\n";
    }
}

void deleteRecordMenu(TheaterDatabase& db) {
    cout << "\n=== УДАЛЕНИЕ ЗАПИСИ ===\n";
    int id;
    cout << "Введите ID записи для удаления: ";
    cin >> id;
    
    if (db.removeRecord(id)) {
        cout << "Запись удалена.\n";
    } else {
        cout << "Запись с ID " << id << " не найдена.\n";
    }
}

int main() {
    TheaterDatabase db;
    
    cout << "\nДобро пожаловать в театральную базу данных!\n";
    
    int choice;
    do {
        printMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                db.printAll();
                break;
                
            case 2: {
                TheaterRecord newRecord = inputNewRecord();
                db.addRecord(newRecord);
                break;
            }
                
            case 3:
                searchByIdMenu(db);
                break;
                
            case 4:
                searchBySeatMenu(db);
                break;
                
            case 5:
                editRecordMenu(db);
                break;
                
            case 6:
                deleteRecordMenu(db);
                break;
                
            case 0:
                cout << "\nВыход из программы...\n";
                break;
                
            default:
                cout << "\nНеверный выбор! Попробуйте снова.\n";
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}

#include "theater_db.h"

void print_menu() {
    std::cout << "\n=== ТЕАТР ===\n";
    std::cout << "1. Показать все\n";
    std::cout << "2. Добавить\n";
    std::cout << "3. Найти по ID\n";
    std::cout << "4. Поиск по ряду и месту\n";
    std::cout << "5. Удалить\n";
    std::cout << "6. Сохранить\n";  
    std::cout << "0. Выход\n";      
    std::cout << "Выбор: ";
}

void search_by_seat(Record* head) {
    int target_row, target_seat;
    
    std::cout << "\n=== ПОИСК ПО РЯДУ И МЕСТУ ===\n";
    std::cout << "Введите ряд для поиска: ";
    std::cin >> target_row;
    std::cout << "Введите место для поиска: ";
    std::cin >> target_seat;
    
    Record* current = head;
    int found_count = 0;
    
    std::cout << "\nРезультаты поиска (Ряд " << target_row << ", Место " << target_seat << "):\n";
    std::cout << "------------------------------------------------\n";
    
    while (current != nullptr) {
        if (current->row == target_row && current->seat == target_seat) {
            std::cout << "ID: " << current->id << "\n";
            printf("Дата: %02d.%02d.%d\n", 
                   current->day, current->month, current->year);
            printf("Время: %02d:%02d\n", 
                   current->hour, current->minute);
            std::cout << "Спектакль: " << current->show << "\n";
            std::cout << "---\n";
            found_count++;
        }
        current = current->next;
    }
    
    if (found_count == 0) {
        std::cout << "Записей не найдено\n";
    } else {
        std::cout << "Найдено записей: " << found_count << "\n";
    }
}

int main() {
    Record* database = nullptr;
    int next_id = 1;
    int choice;

    database = load_from_file(next_id);
    if (database) {
        std::cout << "Данные загружены из файла '" << FILENAME << "'\n";
    } else {
        std::cout << "Файл '" << FILENAME << "' не найден. Создана новая база данных.\n";
    }
    
    do {
        print_menu();
        std::cin >> choice;
        
        // Очищаем буфер ввода
        std::cin.ignore();
        
        switch(choice) {
            case 1:  
                print_all(database);
                break;
                
            case 2:  
                database = add_record(database, next_id);
                break;
                
            case 3: {  
                int id;
                std::cout << "\n=== ПОИСК ПО ID ===\n";
                std::cout << "Введите ID для поиска: ";
                std::cin >> id;
                
                Record* found = find_by_id(database, id);
                if (found) {
                    std::cout << "\nНайдена запись:\n";
                    std::cout << "ID: " << found->id << "\n";
                    printf("Дата: %02d.%02d.%d\n", 
                           found->day, found->month, found->year);
                    printf("Время: %02d:%02d\n", 
                           found->hour, found->minute);
                    std::cout << "Спектакль: " << found->show << "\n";
                    std::cout << "Ряд: " << found->row << ", Место: " << found->seat << "\n";
                } else {
                    std::cout << "Запись с ID " << id << " не найдена\n";
                }
                break;
            }
                
            case 4:  
                search_by_seat(database);
                break;
                
            case 5: { 
                int id;
                std::cout << "\n=== УДАЛЕНИЕ ===\n";
                std::cout << "Введите ID для удаления: ";
                std::cin >> id;
                database = remove_record(database, id);
                std::cout << "Запись удалена (если существовала)\n";
                break;
            }
                
            case 6:  
                save_to_file(database);
                break;
                
            case 0:  
                std::cout << "\nВыход из программы...\n";
                break;
                
            default:
                std::cout << "\nНеверный выбор! Попробуйте снова.\n";
        }
f (choice != 0) {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
        
    } while(choice != 0);
    
    save_to_file(database);
    free_list(database);
    
    std::cout << "Данные сохранены в файл '" << FILENAME << "'\n";
    return 0;
} 

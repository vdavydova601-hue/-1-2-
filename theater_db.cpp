#include "theater_db.h"

Record::Record() : id(0), day(0), month(0), year(0), 
                   hour(0), minute(0), row(0), seat(0), next(nullptr) {
    show[0] = '\0';
}

Record::Record(int id, int d, int m, int y, int hr, int min, 
               const char* show_name, int r, int s) 
    : id(id), day(d), month(m), year(y), hour(hr), minute(min), 
      row(r), seat(s), next(nullptr) {
    strncpy(show, show_name, MAX_NAME - 1);
    show[MAX_NAME - 1] = '\0';
}

Record* add_record(Record* head, int& next_id) {
    int d, m, y, hr, min, r, s;
    char show[MAX_NAME];
    
    std::cout << "Дата (д м г): "; 
    std::cin >> d >> m >> y;
    std::cout << "Время (ч м): "; 
    std::cin >> hr >> min;
    std::cout << "Спектакль: "; 
    std::cin.ignore();
    std::cin.getline(show, MAX_NAME);
    std::cout << "Ряд и место: "; 
    std::cin >> r >> s;
    
    Record* new_record = new Record(next_id++, d, m, y, hr, min, show, r, s);
    
    if (!head) return new_record;
    
    Record* current = head;
    while (current->next) current = current->next;
    current->next = new_record;
    return head;
}

Record* remove_record(Record* head, int id) {
    if (!head) return nullptr;
    
    if (head->id == id) {
        Record* temp = head->next;
        delete head;
        return temp;
    }
    
    Record* current = head;
    while (current->next && current->next->id != id) {
        current = current->next;
    }
    
    if (current->next) {
        Record* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
    }
    
    return head;
}

Record* find_by_id(Record* head, int id) {
    Record* current = head;
    while (current && current->id != id) {
        current = current->next;
    }
    return current;
}

void print_all(Record* head) {
    if (!head) {
        std::cout << "База пуста\n";
        return;
    }
    
    std::cout << "ID\tДата\t\tВремя\tСпектакль\t\tРяд\tМесто\n";
    std::cout << "------------------------------------------------------------\n";
    
    Record* current = head;
    while (current) {
        printf("%d\t%02d.%02d.%d\t%02d:%02d\t%-20s\t%d\t%d\n",
               current->id,
               current->day, current->month, current->year,
               current->hour, current->minute,
               current->show,
               current->row, current->seat);
        current = current->next;
    }
}

void save_to_file(Record* head) {
    std::ofstream file(FILENAME);
    if (!file.is_open()) return;
    
    Record* current = head;
    while (current) {
        file << current->id << " "
             << current->day << " " << current->month << " " << current->year << " "
             << current->hour << " " << current->minute << " "
             << current->show << " "
             << current->row << " " << current->seat << "\n";
        current = current->next;
    }
    
    file.close();
    std::cout << "Сохранено\n";
}

Record* load_from_file(int& next_id) {
    std::ifstream file(FILENAME);
    if (!file.is_open()) return nullptr;
    
    Record* head = nullptr;
    Record* tail = nullptr;
    next_id = 1;
    
    int id, d, m, y, hr, min, r, s;
    char show[MAX_NAME];
    
    while (file >> id >> d >> m >> y >> hr >> min >> show >> r >> s) {
        Record* new_record = new Record(id, d, m, y, hr, min, show, r, s);
        
        if (!head) {
            head = new_record;
            tail = new_record;
        } else {
            tail->next = new_record;
            tail = new_record;
        }
        
        if (id >= next_id) next_id = id + 1;
    }
    
    file.close();
    return head;
}

void free_list(Record* head) {
    Record* current = head;
    while (current) {
        Record* next = current->next;
        delete current;
        current = next;
    }
}

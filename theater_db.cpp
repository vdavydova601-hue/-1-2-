#include "theater_db.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

bool Date::isValid() const {
    if (year < 2023 || year > 2030) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        daysInMonth[1] = 29;
    }
    
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "."
       << setw(2) << month << "."
       << year;
    return ss.str();
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

Time::Time(int h, int m) : hour(h), minute(m) {}

bool Time::isValid() const {
    return (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59);
}

string Time::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << hour << ":" << setw(2) << minute;
    return ss.str();
}

TheaterRecord::TheaterRecord(int id, const Date& d, const Time& t,
                             const string& name, int r, int s)
    : id(id), date(d), startTime(t), showName(name), row(r), seat(s) {}

void TheaterRecord::print() const {
    cout << "╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "║ ID: " << setw(57) << left << id << "║\n";
    cout << "║ Дата: " << setw(57) << left << date.toString() << "║\n";
    cout << "║ Время: " << setw(56) << left << startTime.toString() << "║\n";
    cout << "║ Спектакль: " << setw(48) << left << showName << "║\n";
    cout << "║ Ряд: " << setw(4) << row << " Место: " << setw(4) << seat 
         << "                                 ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════╝\n";
}

string TheaterRecord::toString() const {
    stringstream ss;
    ss << id << ";" << date.toString() << ";" << startTime.toString() 
       << ";" << showName << ";" << row << ";" << seat;
    return ss.str();
}

TheaterDatabase::TheaterDatabase(const string& file) : filename(file), nextId(1) {
    loadFromFile();
}

TheaterDatabase::~TheaterDatabase() {
    saveToFile();
}

int TheaterDatabase::findIndexById(int id) const {
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void TheaterDatabase::updateNextId() {
    nextId = 1;
    for (const auto& record : records) {
        if (record.getId() >= nextId) {
            nextId = record.getId() + 1;
        }
    }
}

bool TheaterDatabase::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл '" << filename << "' не найден. Создана новая база данных.\n";
        return false;
    }
    
    records.clear();
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        
        int id, row, seat;
        string dateStr, timeStr, showName;
        
        getline(ss, token, ';');
        id = stoi(token);
        
        getline(ss, dateStr, ';');
        getline(ss, timeStr, ';');
        getline(ss, showName, ';');
        
        getline(ss, token, ';');
        row = stoi(token);
        
        getline(ss, token, ';');
        seat = stoi(token);
        
        int day, month, year;
        stringstream dateStream(dateStr);
        getline(dateStream, token, '.');
        day = stoi(token);
        getline(dateStream, token, '.');
        month = stoi(token);
        getline(dateStream, token, '.');
        year = stoi(token);
        
        int hour, minute;
        stringstream timeStream(timeStr);
        getline(timeStream, token, ':');
        hour = stoi(token);
        getline(timeStream, token, ':');
        minute = stoi(token);
        
        TheaterRecord record(id, Date(day, month, year), 
                            Time(hour, minute), showName, row, seat);
        records.push_back(record);
    }
    
    file.close();
    updateNextId();
    cout << "Загружено записей: " << records.size() << endl;
    return true;
}

bool TheaterDatabase::saveToFile() const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи!\n";
        return false;
    }
    
    for (const auto& record : records) {
        file << record.toString() << endl;
    }
    
    file.close();
    cout << "Сохранено записей: " << records.size() << endl;
    return true;
}

void TheaterDatabase::addRecord(const TheaterRecord& record) {
    TheaterRecord newRecord = record;
    newRecord.setId(nextId++);
    records.push_back(newRecord);
    cout << "Запись добавлена! ID: " << newRecord.getId() << endl;
}

bool TheaterDatabase::removeRecord(int id) {
    int index = findIndexById(id);
    if (index == -1) return false;
    
    records.erase(records.begin() + index);
    cout << "Запись с ID " << id << " удалена.\n";
    return true;
}

bool TheaterDatabase::editRecord(int id, const TheaterRecord& newData) {
    int index = findIndexById(id);
    if (index == -1) return false;
    
    TheaterRecord edited = newData;
    edited.setId(id);
    records[index] = edited;
    cout << "Запись с ID " << id << " обновлена.\n";
    return true;
}

TheaterRecord* TheaterDatabase::findById(int id) {
    int index = findIndexById(id);
    return (index != -1) ? &records[index] : nullptr;
}

const TheaterRecord* TheaterDatabase::findById(int id) const {
    int index = findIndexById(id);
    return (index != -1) ? &records[index] : nullptr;
}

vector<TheaterRecord> TheaterDatabase::searchBySeat(int row, int seat) const {
    vector<TheaterRecord> results;
    for (const auto& record : records) {
        if (record.matchesSeat(row, seat)) {
            results.push_back(record);
        }
    }
    return results;
}

vector<TheaterRecord> TheaterDatabase::searchByDateAndShow(const Date& date, 
                                                           const string& showName) const {
    vector<TheaterRecord> results;
    for (const auto& record : records) {
        if (record.getDate() == date) {
            string recShow = record.getShowName();
            string searchShow = showName;
            transform(recShow.begin(), recShow.end(), recShow.begin(), ::tolower);
            transform(searchShow.begin(), searchShow.end(), searchShow.begin(), ::tolower);
            
            if (recShow.find(searchShow) != string::npos) {
                results.push_back(record);
            }
        }
    }
    return results;
}

void TheaterDatabase::printAll() const {
    if (records.empty()) {
        cout << "\nБаза данных пуста.\n";
        return;
    }
    
    cout << "\n╔════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         ВСЕ ЗАПИСИ В БАЗЕ ДАННЫХ                       ║\n";
    cout << "╠═════╦════════════╦══════════╦════════════════════════════════╦══════╦══════╣\n";
    cout << "║ ID ║    Дата    ║  Время   ║         Спектакль              ║ Ряд  ║ Место║\n";
    cout << "╠═════╬════════════╬══════════╬════════════════════════════════╬══════╬══════╣\n";
    
    for (const auto& record : records) {
        cout << "║ " << setw(3) << record.getId() << " ║ "
             << record.getDate().toString() << " ║ "
             << record.getTime().toString() << " ║ "
             << setw(30) << left << record.getShowName() << " ║ "
             << setw(4) << record.getRow() << " ║ "
             << setw(4) << record.getSeat() << " ║\n";
    }
    
    cout << "╚═════╩════════════╩══════════╩════════════════════════════════╩══════╩══════╝\n";
    cout << "Всего записей: " << records.size() << endl;
}

Date inputDate() {
    int d, m, y;
    while (true) {
        cout << "Введите дату (день месяц год): ";
        cin >> d >> m >> y;
        
        Date date(d, m, y);
        if (date.isValid()) {
            return date;
        }
        cout << "Некорректная дата! Попробуйте снова.\n";
        clearInputBuffer();
    }
}

Time inputTime() {
    int h, m;
    while (true) {
        cout << "Введите время (часы минуты): ";
        cin >> h >> m;
        
        Time time(h, m);
        if (time.isValid()) {
            return time;
        }
        cout << "Некорректное время! Попробуйте снова.\n";
        clearInputBuffer();
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

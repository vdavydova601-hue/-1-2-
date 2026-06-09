#include "database.h"
#include <iostream>
#include <limits>

void showMenu() {
    std::cout << "\nв•”в•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•—\n";
    std::cout << "в•‘           РЈРџР РђР’Р›Р•РќРР• Р‘РђР—РћР™ Р”РђРќРќР«РҐ РўР•РђРўР Рђ      в•‘\n";
    std::cout << "в• в•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•Ј\n";
    std::cout << "в•‘  1. Р’С‹РІРµСЃС‚Рё РІСЃРµ Р·Р°РїРёСЃРё                        в•‘\n";
    std::cout << "в•‘  2. Р”РѕР±Р°РІРёС‚СЊ РЅРѕРІС‹Р№ Р±РёР»РµС‚                      в•‘\n";
    std::cout << "в•‘  3. РџРѕРёСЃРє РїРѕ СЃРїРµРєС‚Р°РєР»СЋ                        в•‘\n";
    std::cout << "в•‘  4. РџРѕРёСЃРє РїРѕ РґР°С‚Рµ                             в•‘\n";
    std::cout << "в•‘  5. РџРѕРёСЃРє РїРѕ РјРµСЃС‚Сѓ (СЂСЏРґ+РјРµСЃС‚Рѕ)                в•‘\n";
    std::cout << "в•‘  6. РЈРґР°Р»РёС‚СЊ Р·Р°РїРёСЃСЊ РїРѕ РЅРѕРјРµСЂСѓ РїРѕРєСѓРїР°С‚РµР»СЏ       в•‘\n";
    std::cout << "в•‘  7. Р РµРґР°РєС‚РёСЂРѕРІР°С‚СЊ Р·Р°РїРёСЃСЊ                      в•‘\n";
    std::cout << "в•‘  8. РЎРѕС…СЂР°РЅРёС‚СЊ Рё РІС‹Р№С‚Рё                         в•‘\n";
    std::cout << "в•љв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ђв•ќ\n";
    std::cout << "Р’С‹Р±РµСЂРёС‚Рµ РґРµР№СЃС‚РІРёРµ: ";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::string dbFilename;
    std::cout << "Р’РІРµРґРёС‚Рµ РёРјСЏ С„Р°Р№Р»Р° Р±Р°Р·С‹ РґР°РЅРЅС‹С…: ";
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
                
                std::cout << "\n=== Р”РћР‘РђР’Р›Р•РќРР• РќРћР’РћР“Рћ Р‘РР›Р•РўРђ ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ РґР°С‚Сѓ (Р”Р”.РњРњ.Р“Р“Р“Р“): ";
                std::cin >> date;
                std::cout << "Р’РІРµРґРёС‚Рµ РІСЂРµРјСЏ РЅР°С‡Р°Р»Р° (Р§Р§:РњРњ): ";
                std::cin >> time;
                std::cout << "Р’РІРµРґРёС‚Рµ РЅР°Р·РІР°РЅРёРµ СЃРїРµРєС‚Р°РєР»СЏ: ";
                clearInput();
                std::getline(std::cin, playName);
                std::cout << "Р’РІРµРґРёС‚Рµ СЂСЏРґ: ";
                std::cin >> row;
                std::cout << "Р’РІРµРґРёС‚Рµ РјРµСЃС‚Рѕ: ";
                std::cin >> seat;
                
                db.addRecord(date, time, playName, row, seat);
                break;
            }
            
            case 3: {
                std::string playName;
                std::cout << "\n=== РџРћРРЎРљ РџРћ РќРђР—Р’РђРќРР® РЎРџР•РљРўРђРљР›РЇ ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ РЅР°Р·РІР°РЅРёРµ: ";
                clearInput();
                std::getline(std::cin, playName);
                db.searchByPlayName(playName);
                break;
            }
            
            case 4: {
                std::string date;
                std::cout << "\n=== РџРћРРЎРљ РџРћ Р”РђРўР• ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ РґР°С‚Сѓ (Р”Р”.РњРњ.Р“Р“Р“Р“): ";
                std::cin >> date;
                db.searchByDate(date);
                break;
            }
            
            case 5: {
                int row, seat;
                std::cout << "\n=== РџРћРРЎРљ РџРћ РњР•РЎРўРЈ ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ СЂСЏРґ: ";
                std::cin >> row;
                std::cout << "Р’РІРµРґРёС‚Рµ РјРµСЃС‚Рѕ: ";
                std::cin >> seat;
                db.searchByRowAndSeat(row, seat);
                break;
            }
            
            case 6: {
                int number;
                std::cout << "\n=== РЈР”РђР›Р•РќРР• Р—РђРџРРЎР ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ РЅРѕРјРµСЂ РїРѕРєСѓРїР°С‚РµР»СЏ: ";
                std::cin >> number;
                db.deleteRecord(number);
                break;
            }
            
            case 7: {
                int number;
                std::cout << "\n=== Р Р•Р”РђРљРўРР РћР’РђРќРР• Р—РђРџРРЎР ===\n";
                std::cout << "Р’РІРµРґРёС‚Рµ РЅРѕРјРµСЂ РїРѕРєСѓРїР°С‚РµР»СЏ: ";
                std::cin >> number;
                db.editRecord(number);
                break;
            }
            
            case 8:
                std::cout << "\nРЎРѕС…СЂР°РЅРµРЅРёРµ РґР°РЅРЅС‹С…...\n";
                db.saveToFile();
                std::cout << "Р”Рѕ СЃРІРёРґР°РЅРёСЏ!\n";
                break;
                
            default:
                std::cout << "РќРµРІРµСЂРЅС‹Р№ РІС‹Р±РѕСЂ! РџРѕРїСЂРѕР±СѓР№С‚Рµ СЃРЅРѕРІР°.\n";
                break;
        }
        
    } while (choice != 8);
    
    return 0;

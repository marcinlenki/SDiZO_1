#include <iostream>
#include <chrono>
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
#include "TimeTest.cpp"

using namespace std;
const char* ERROR_MESSAGE = "Nie udało się wykonać operacji.\n";
const char* FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt/dane.txt";

Tablica *tablica;
Lista *lista;
Kopiec *kopiec;

void menuGlowne() {
    cout<<"Struktury do wyboru: "<<endl;
    cout<<"1. Tablica"<<endl;
    cout<<"2. Lista dwukierunkowa"<<endl;
    cout<<"3. Kopiec."<<endl;
    cout<<"4. Wyjdź z programu"<<endl;
    cout<<"Wybór: ";
}
void menuLT() {
    cout<<"Naciśnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyświetl."<<endl;
    cout<<"3. Dodaj na początku."<<endl;
    cout<<"4. Usuń na początku."<<endl;
    cout<<"5. Dodaj na końcu."<<endl;
    cout<<"6. Usuń na końcu."<<endl;
    cout<<"7. Dodaj w dowolnym miejscu."<<endl;
    cout<<"8. Usun w dowolnym miejscu."<<endl;
    cout<<"9. Wyszkaj"<<endl;
    cout<<"10. Wyczyść listę"<<endl;
    cout<<"11. Zmien strukture"<<endl;
    cout<<"Wybór: ";
}
void menuDrzewa() {
    cout<<"Naciśnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyświetl."<<endl;
    cout<<"3. Dodaj element."<<endl;
    cout<<"4. Usuń korzeń."<<endl;
    cout<<"5. Wyszkaj"<<endl;
    cout<<"6. Wyczyść drzewo"<<endl;
    cout<<"7. Zmien strukture"<<endl;
    cout<<"Wybór: ";
}

int main() {
    int menuChoice, choice, value = 0, index = 0;
    bool changeStruct, quit = false;

    if(false) {
        cout<<"1. Test ręczny"<<endl;
        cout<<"2. Test automatyczny"<<endl;
        cout<<"Wybór: ";
        cin>>choice;

        if (choice == 1) {
            while (!quit) {
                changeStruct = false;
                menuGlowne();
                cin >> menuChoice;
                switch (menuChoice) {
                    case 1:
                        tablica = new Tablica;
                        while (!changeStruct) {
                            menuLT();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    tablica->fillFromFile(FILE_PATH);
                                    break;
                                case 2:
                                    tablica->show();
                                    cout << "Naciśnij dowolony znak, aby przejść dalej.";
                                    cin.get();
                                    cin.get();
                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    tablica->addBeginning(value);
                                    break;
                                case 4:
                                    if (!tablica->removeBeginning()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    tablica->addEnd(value);
                                    break;
                                case 6:
                                    if (!tablica->removeEnd()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 7:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    cout << "Podaj indeks na którum chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!tablica->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakończone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na którum chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!tablica->removeIndex(index)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 9:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (tablica->search(value) == nullptr) {
                                        cout << "Nie udało się znaleźć szukanej wartości." << endl;
                                    } else {
                                        cout << "Wartość znaleziona." << endl;
                                    }
                                    break;
                                case 10:
                                    tablica->clear();
                                    break;
                                case 11:
                                    changeStruct = true;
                                    delete tablica;
                                    break;
                                default:
                                    cout << "Błędny wybór!" << endl;
                            }
                        }
                        break;
                    case 2:
                        lista = new Lista;
                        while (!changeStruct) {
                            menuLT();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    lista->fillFromFile(FILE_PATH);
                                    break;
                                case 2:
                                    lista->show();
                                    cout << "Naciśnij dowolony znak, aby przejść dalej.";
                                    cin.get();
                                    cin.get();
                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    lista->addBeginning(value);
                                    break;
                                case 4:
                                    if (!lista->removeBeginning()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    lista->addEnd(value);
                                    break;
                                case 6:
                                    if (!lista->removeEnd()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 7:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    cout << "Podaj indeks na którum chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!lista->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakończone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na którum chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!lista->removeIndex(index)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 9:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (lista->search(value) == nullptr) {
                                        cout << "Nie udało się znaleźć szukanej wartości." << endl;
                                    } else {
                                        cout << "Wartość znaleziona." << endl;
                                    }
                                    break;
                                case 10:
                                    lista->clear();
                                    break;
                                case 11:
                                    changeStruct = true;
                                    delete lista;
                                    break;
                                default:
                                    cout << "Błędny wybór!" << endl;
                            }
                        }
                        break;
                    case 3:
                        kopiec = new Kopiec;
                        while (!changeStruct) {
                            menuDrzewa();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    kopiec->fillFromFile(FILE_PATH);
                                    break;
                                case 2:
                                    kopiec->show();
                                    cout << "Naciśnij dowolony znak, aby przejść dalej.";
                                    cin.get();

                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartość do wpisania do struktury: ";
                                    cin >> value;
                                    kopiec->add(value);
                                    break;
                                case 4:
                                    if (!kopiec->removeRoot()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usunięcie zakończone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (kopiec->search(value) == nullptr) {
                                        cout << "Nie udało się znaleźć szukanej wartości." << endl;
                                    } else {
                                        cout << "Wartość znaleziona." << endl;
                                    }
                                    break;
                                case 6:
                                    kopiec->clear();
                                    break;
                                case 7:
                                    changeStruct = true;
                                    delete kopiec;
                                    break;
                                default:
                                    cout << "Błędny wybór!" << endl;
                            }
                        }
                        break;
                    case 4:
                        quit = true;
                        cout << "Wychodzenie z programu..." << endl;
                        break;
                    default:
                        cout << "Błędny wybór!" << endl;
                }
            }
        }
        else if(choice == 2) {
            TimeTest timeTest;
            timeTest.run();
        } else
            cout << "Błędny wybór!" << endl;
    }

    lista = new Lista;
    TimeTest timeTest;

    timeTest.generateInputData(10000, 1000);
    lista->fillFromFile(FILE_PATH);

    lista->show();

//    lista->addBeginning(-300);
//    lista->addBeginning(100);
//    lista->addBeginning(1300);
//    lista->addBeginning(300);
//    lista->addBeginning(-242);

    auto begin = std::chrono::high_resolution_clock::now();
    lista->addBeginning(1000);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    cout<<"Time measured for 10000 elements: "<<elapsed.count()<<endl;
//
//    timeTest.generateInputData(20000, 1000);
//    lista->fillFromFile(FILE_PATH);
//
//    begin = std::chrono::high_resolution_clock::now();
//    lista->removeBeginning();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//
//    cout<<"Time measured for 20000 elements: "<<elapsed.count()<<endl;
//
//    timeTest.generateInputData(30000, 1000);
//    lista->fillFromFile(FILE_PATH);
//
//    begin = std::chrono::high_resolution_clock::now();
//    lista->removeBeginning();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//
//    cout<<"Time measured for 30000 elements: "<<elapsed.count()<<endl;
//
//    timeTest.generateInputData(40000, 1000);
//    lista->fillFromFile(FILE_PATH);
//
//    begin = std::chrono::high_resolution_clock::now();
//    lista->removeBeginning();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//
//    cout<<"Time measured for 40000 elements: "<<elapsed.count()<<endl;
//
//    timeTest.generateInputData(50000, 1000);
//    lista->fillFromFile(FILE_PATH);
//
//    begin = std::chrono::high_resolution_clock::now();
//    lista->removeBeginning();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//
//    cout<<"Time measured for 50000 elements: "<<elapsed.count()<<endl;

    return 0;
}
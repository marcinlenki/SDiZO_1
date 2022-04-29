#include <iostream>
#include <fstream>
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
#include "DrzewoCC.h"

using namespace std;
const char* ERROR_MESSAGE = "Nie udalo sie wykonac zadanej operacji.\n";
const char* FILE_NAME = "../dane.txt";

Tablica *tablica;
Lista *lista;
Kopiec *kopiec;
DrzewoCC *drzewo;

void menuGlowne() {
    cout<<"Struktury do wyboru: "<<endl;
    cout<<"1. Tablica"<<endl;
    cout<<"2. Lista dwukierunkowa"<<endl;
    cout<<"3. Kopiec."<<endl;
    cout<<"4. Drzewo czerwono czarne."<<endl;
    cout<<"5. Wyjdz z programu"<<endl;
    cout<<"Wybor: ";
}
void menuLT() {
    cout<<"Nacisnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyswietl."<<endl;
    cout<<"3. Dodaj na poczatku."<<endl;
    cout<<"4. Usun na poczatku."<<endl;
    cout<<"5. Dodaj na koncu."<<endl;
    cout<<"6. Usun na koncu."<<endl;
    cout<<"7. Dodaj w dowolnym miejscu."<<endl;
    cout<<"8. Usun w dowolnym miejscu."<<endl;
    cout<<"9. Wyszukaj."<<endl;
    cout<<"10. Wyczysc liste."<<endl;
    cout<<"11. Zmien strukture."<<endl;
    cout<<"Wybor: ";
}
void menuKopiec() {
    cout<<"Nacisnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyswietl."<<endl;
    cout<<"3. Dodaj element."<<endl;
    cout<<"4. Usun korzeń."<<endl;
    cout<<"5. Wyszukaj."<<endl;
    cout<<"6. Wyczysc drzewo."<<endl;
    cout<<"7. Zmien strukture."<<endl;
    cout<<"Wybor: ";
}
void menuDrzewoCzCzar() {
    cout<<"Nacisnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyswietl."<<endl;
    cout<<"3. Dodaj element."<<endl;
    cout<<"4. Usun element."<<endl;
    cout<<"5. Wyszukaj."<<endl;
    cout<<"6. Wyczysc drzewo."<<endl;
    cout<<"7. Zmien strukture."<<endl;
    cout<<"Wybor: ";
};

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout<<"QueryPerformanceFrequency failed!"<<endl;

    PCFreq = double(li.QuadPart)/1000000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
};
double GetCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double (li.QuadPart - CounterStart)/PCFreq;
};

int main() {
    int menuChoice, choice, value = 0, index = 0;
    bool changeStruct, quit = false;

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
                                    tablica->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    tablica->show();
                                    cout << "Nacisnij ENTER, aby przejsc dalej.";
                                    cin.get();
                                    cin.get();
                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    tablica->addBeginning(value);
                                    break;
                                case 4:
                                    if (!tablica->removeBeginning()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    tablica->addEnd(value);
                                    break;
                                case 6:
                                    if (!tablica->removeEnd()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 7:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    cout << "Podaj indeks na ktorym chcesz wykonac operacje: ";
                                    cin >> index;
                                    if (!tablica->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakonczone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na ktorym chcesz wykonac operacje: ";
                                    cin >> index;
                                    if (!tablica->removeIndex(index)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 9:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (tablica->search(value) == nullptr) {
                                        cout << "Nie udało się znalezc szukanej wartosci." << endl;
                                    } else {
                                        cout << "Wartosc znaleziona." << endl;
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
                                    cout << "Bledny wybor!" << endl;
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
                                    lista->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    lista->show();
                                    cout << "Nacisnij dowolny znak, aby przejsc dalej.";
                                    cin.get();
                                    cin.get();
                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    lista->addBeginning(value);
                                    break;
                                case 4:
                                    if (!lista->removeBeginning()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    lista->addEnd(value);
                                    break;
                                case 6:
                                    if (!lista->removeEnd()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 7:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    cout << "Podaj indeks na ktorym chcesz wykonac operacje: ";
                                    cin >> index;
                                    if (!lista->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakonczone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na ktorym chcesz wykonac operacje: ";
                                    cin >> index;
                                    if (!lista->removeIndex(index)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 9:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (lista->search(value) == nullptr) {
                                        cout << "Nie udało się znalezc szukanej wartosci." << endl;
                                    } else {
                                        cout << "Wartosc znaleziona." << endl;
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
                                    cout << "Bledny wybor!" << endl;
                            }
                        }
                        break;
                    case 3:
                        kopiec = new Kopiec;
                        while (!changeStruct) {
                            menuKopiec();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    kopiec->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    kopiec->show();
                                    cout << "Nacisnij ENTER, aby przejsc dalej.";
                                    cin.get();
                                    cin.get();

                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    kopiec->add(value);
                                    break;
                                case 4:
                                    if (!kopiec->removeRoot()) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (kopiec->search(value) == nullptr) {
                                        cout << "Nie udało się znalezc szukanej wartosci." << endl;
                                    } else {
                                        cout << "Wartosc znaleziona." << endl;
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
                                    cout << "Bledny wybor!" << endl;
                            }
                        }
                        break;
                    case 4:
                        drzewo = new DrzewoCC;
                        while (!changeStruct) {
                            menuDrzewoCzCzar();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    drzewo->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    drzewo->showInOrder();
                                    cout << "Nacisnij ENTER, aby przejsc dalej.";
                                    cin.get();
                                    cin.get();

                                    cout << endl;
                                    break;
                                case 3:
                                    cout << "Podaj wartosc do wpisania do struktury: ";
                                    cin >> value;
                                    drzewo->add(value);
                                    break;
                                case 4:
                                    cout << "Podaj wartość elementu, ktory chcesz usunac: ";
                                    cin >> value;
                                    if (!drzewo->remove(value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Usuniecie zakonczone sukcesem" << endl;
                                    break;
                                case 5:
                                    cout << "Podaj wartość którą chcesz wyszukać: ";
                                    cin >> value;
                                    if (drzewo->search(value) == nullptr) {
                                        cout << "Nie udało się znalezc szukanej wartosci." << endl;
                                    } else {
                                        cout << "Wartosc znaleziona." << endl;
                                    }
                                    break;
                                case 6:
                                    drzewo->clear();
                                    break;
                                case 7:
                                    changeStruct = true;
                                    delete drzewo;
                                    break;
                                default:
                                    cout << "Bledny wybor!" << endl;
                            }
                        }
                        break;
                    case 5:
                        quit = true;
                        cout << "Wychodzenie z programu..." << endl;
                        break;
                    default:
                        cout << "Bledny wybor!" << endl;
                }
            }




    return 0;
}
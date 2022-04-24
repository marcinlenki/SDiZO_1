#include <iostream>
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
#include "TimeTest.cpp"
#include "DrzewoCC.h"

using namespace std;
const char* ERROR_MESSAGE = "Nie udało się wykonać operacji.\n";
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
    cout<<"9. Wyszukaj"<<endl;
    cout<<"10. Wyczysc listę"<<endl;
    cout<<"11. Zmien strukture"<<endl;
    cout<<"Wybor: ";
}
void menuKopiec() {
    cout<<"Naciśnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyswietl."<<endl;
    cout<<"3. Dodaj element."<<endl;
    cout<<"4. Usun korzeń."<<endl;
    cout<<"5. Wyszukaj"<<endl;
    cout<<"6. Wyczysc drzewo"<<endl;
    cout<<"7. Zmien strukture"<<endl;
    cout<<"Wybor: ";
}
void menuDrzewoCzCzar() {
    cout<<"Naciśnij: "<<endl;
    cout<<"1. Wczytaj z pliku."<<endl;
    cout<<"2. Wyswietl."<<endl;
    cout<<"3. Dodaj element."<<endl;
    cout<<"4. Usun element."<<endl;
    cout<<"5. Wyszukaj"<<endl;
    cout<<"6. Wyczysc drzewo"<<endl;
    cout<<"7. Zmien strukture"<<endl;
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

    goto b;

    cout<<"1. Test reczny"<<endl;
    cout<<"2. Test automatyczny"<<endl;
    cout<<"Wybor: ";
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
                                    tablica->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    tablica->show();
                                    cout << "Naciśnij ENTER, aby przejść dalej.";
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
                                    cout << "Podaj indeks na który chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!tablica->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakończone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na który chcesz wykonać operację: ";
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
                                    lista->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    lista->show();
                                    cout << "Naciśnij dowolny znak, aby przejść dalej.";
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
                                    cout << "Podaj indeks na który chcesz wykonać operację: ";
                                    cin >> index;
                                    if (!lista->addIndex(index, value)) {
                                        cout << ERROR_MESSAGE << endl;
                                    } else
                                        cout << "Dodawanie zakończone sukcesem" << endl;
                                    break;
                                case 8:
                                    cout << "Podaj indeks na który chcesz wykonać operację: ";
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
                            menuKopiec();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    kopiec->fillFromFile(FILE_NAME);
                                    break;
                                case 2:
                                    kopiec->show();
                                    cout << "Naciśnij ENTER, aby przejść dalej.";
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
            cout << "Bledny wybór!" << endl;



    b:
    drzewo = new DrzewoCC;

    drzewo->add(10);

    drzewo->fillFromFile(FILE_NAME);

    drzewo->showInOrder();


    drzewo->remove(1);
    cout<<endl;
    drzewo->showInOrder();
    delete drzewo;

//    srand(time(NULL));
//
//    //TEST 1
//    cout<<"TEST 1"<<endl;
//    int maxRand = 10000;
//    double avgTime = 0;
//    lista = new Lista;
//    TimeTest t;
//
//    for(int i = 0; i < t.NUMBER_OF_REPETITIONS; i++) {
//        int testNumber = t.getRandomNumber(maxRand);
//        int testIndex = t.DATA_SET_SIZES[i] / 2;
//
//        for(int j = 0; j < t.NUMBER_OF_REPETITIONS_PER_OPERATION; j++) {
//            t.generateInputData(t.DATA_SET_SIZES[i], maxRand);
//
//            lista->fillFromFile(FILE_NAME);
//
//            StartCounter();
//            lista->addBeginning(testNumber);
//            avgTime += GetCounter();
//        }
//
//        cout<<"Time measure for "<<t.DATA_SET_SIZES[i]<<" elements: "<<avgTime/t.NUMBER_OF_REPETITIONS_PER_OPERATION<<endl;
//        avgTime = 0;
//    }
//
//    cout<<endl;
//
//    //TEST 2
//    cout<<"TEST 2"<<endl;
//    for(int i = 0; i < t.NUMBER_OF_REPETITIONS; i++) {
//        lista->zmierz(t.DATA_SET_SIZES[i], maxRand);
//    }

    return 0;
}
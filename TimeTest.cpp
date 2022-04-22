#include <iostream>
#include<cstdlib>
#include<chrono>
#include<ctime>
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
using namespace std;


class TimeTest {
public:
    const char* FILE_NAME = "../dane.txt";
    const char* RESULTS_FILE_NAME = "../wyniki.txt";
    ofstream structFile, results;
    int NUMBER_OF_REPETITIONS;
    int NUMBER_OF_REPETITIONS_PER_OPERATION;
    int *DATA_SET_SIZES;
    double resultsMatrix[3][7] = {{0}};
    double finalResults[5][3][7] = {{{0}}};
    
    
    //                            ZEGAR
    //___________________________________________________________________
    double PCFreq = 0.0;
    __int64 CounterStart = 0;

    void StartCounter() {
        LARGE_INTEGER li;
        if(!QueryPerformanceFrequency(&li))
            cout<<"QueryPerformanceFrequency failed!"<<endl;

        PCFreq = double(li.QuadPart)/1000000000.0;

        QueryPerformanceCounter(&li);
        CounterStart = li.QuadPart;
    }

    double GetCounter() {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return double (li.QuadPart - CounterStart)/PCFreq;
    }
    //___________________________________________________________________

    
    void generateInputData(int size, int maxRand) {
        structFile.open(FILE_NAME);

        int randNum;

        structFile<<size<<endl;

        for(int i = 0; i<size-1; i++) {
            randNum = getRandomNumber(maxRand);
            structFile<<randNum<<endl;
        }
        structFile << randNum;

        structFile.close();
    }

    void generateResultsFile() {
        results.open(RESULTS_FILE_NAME);
        bool flag = false;

        for(int i = 0; i <NUMBER_OF_REPETITIONS; i++) {
            results<<"Liczba elementów w strukturze: ";
            results<<DATA_SET_SIZES[i]<<endl;

            for(int k = 0; k < 3; k++) {
                if (k == 0)
                    results<<"TABLICA"<<endl;
                else if (k == 1)
                    results<<"LISTA"<<endl;
                else {
                    results<<"KOPIEC"<<endl;
                    flag = true;
                }


                for(int j = 0; j<7; j++) {
                    switch (j) {
                        case 0:
                            if(flag) {
                                results<<"Dodawanie: ";
                            } else
                                results<<"Dodawanie na początku: ";

                            results<<finalResults[i][k][j]<<endl;

                            break;
                        case 1:
                            if (flag) {
                                results<<"Usuwanie korzenia: ";
                            } else
                                results<<"Usuwanie na początku: ";

                            results<<finalResults[i][k][j]<<endl;
                            break;
                        case 2:
                            if (flag) {
                                results<<"Wyszukiwanie: ";
                                results<<finalResults[i][k][j]<<endl;
                                flag = false;
                                goto jump;
                            }
                            results<<"Dodawanie na końcu: ";
                            results<<finalResults[i][k][j]<<endl;
                            break;
                        case 3:
                            results<<"Usuwanie na końcu: ";
                            results<<finalResults[i][k][j]<<endl;
                            break;
                        case 4:
                            results<<"Dodawanie na dowolnym miejscu: ";
                            results<<finalResults[i][k][j]<<endl;
                            break;
                        case 5:
                            results<<"Usuwanie na dowolnym miejscu: ";
                            results<<finalResults[i][k][j]<<endl;
                            break;
                        case 6:
                            results<<"Wyszukiwanie: ";
                            results<<finalResults[i][k][j]<<endl;
                            break;
                        default: ;
                    }
                }
                results<<endl;
            }
            jump:
            results<<endl;
            results<<endl;
        }
        results.close();
    }

    int getRandomNumber(int maxRand) {
        return (rand() % (2 * maxRand + 1)) - maxRand;
    }

    void getInputDataAndTest() {
        int maxRand = 10000, finalResultsIndex = 0;
        Tablica *tablica = new Tablica;
        Lista *lista = new Lista;
        Kopiec *kopiec = new Kopiec;

        for(int i = 0; i < NUMBER_OF_REPETITIONS; i++) {

            int testNumber = getRandomNumber(maxRand);
            int testIndex = DATA_SET_SIZES[i] / 2;

            
            for(int j = 0; j < NUMBER_OF_REPETITIONS_PER_OPERATION; j++) {

                generateInputData(DATA_SET_SIZES[i], maxRand);
                tablica->fillFromFile(FILE_NAME);
                lista->fillFromFile(FILE_NAME);
                kopiec->fillFromFile(FILE_NAME);


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //                                      TABLICA
                //DODAWANIE NA POCZĄTKU
                StartCounter();
                tablica->addBeginning(testNumber);
                double measurement = GetCounter();
                resultsMatrix[0][0] += measurement;

                //USUWANIE NA POCZĄTKU
                StartCounter();
                tablica->removeBeginning();
                measurement = GetCounter();
                resultsMatrix[0][1] += measurement;

                //DODAWANIE NA KOŃCU
                StartCounter();
                tablica->addEnd(testNumber);
                measurement = GetCounter();
                resultsMatrix[0][2] += measurement;

                //USUWANIE NA KOŃCU
                StartCounter();
                tablica->removeEnd();
                measurement = GetCounter();
                resultsMatrix[0][3] += measurement;

                //DODAWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                StartCounter();
                tablica->addIndex(testIndex, testNumber);
                measurement = GetCounter();
                resultsMatrix[0][4] += measurement;

                //USUWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                StartCounter();
                tablica->removeIndex(testIndex);
                measurement = GetCounter();
                resultsMatrix[0][5] += measurement;

                //WYSZUKIWANIE
                StartCounter();
                tablica->search(testNumber);
                measurement = GetCounter();
                resultsMatrix[0][6] += measurement;


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //                                         LISTA
                //DODAWANIE NA POCZĄTKU
                StartCounter();
                lista->addBeginning(testNumber);
                measurement = GetCounter();
                cout<<"DODAWANIE NA POCZĄTKU POMIAR "<<j+1<<": "<<measurement<<endl;
                resultsMatrix[1][0] += measurement;

                //USUWANIE NA POCZĄTKU
                StartCounter();
                lista->removeBeginning();
                measurement = GetCounter();
                resultsMatrix[1][1] += measurement;

                //DODAWANIE NA KOŃCU
                StartCounter();
                lista->addEnd(testNumber);
                measurement = GetCounter();
                resultsMatrix[1][2] += measurement;

                //USUWANIE NA KOŃCU
                StartCounter();
                lista->removeEnd();
                measurement = GetCounter();
                resultsMatrix[1][3] += measurement;

                //DODAWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                StartCounter();
                lista->addIndex(testIndex, testNumber);
                measurement = GetCounter();
                resultsMatrix[1][4] += measurement;

                //USUWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                StartCounter();
                lista->removeIndex(testIndex);
                measurement = GetCounter();
                resultsMatrix[1][5] += measurement;

                //WYSZUKIWANIE
                StartCounter();
                lista->search(testNumber);
                measurement = GetCounter();
                resultsMatrix[1][6] += measurement;


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //                                         KOPIEC

                //DODAWANIE
                StartCounter();
                kopiec->add(testNumber);
                measurement = GetCounter();
                resultsMatrix[2][0] += measurement;

                //USUWANIE KORZENIA
                StartCounter();
                kopiec->removeRoot();
                measurement = GetCounter();
                resultsMatrix[2][1] += measurement;

                //WYSZUKIWANIE
                StartCounter();
                kopiec->search(testNumber);
                measurement = GetCounter();
                resultsMatrix[2][2] += measurement;
            }

            for(int k = 0; k < 3; k++) {
                for(int j = 0; j<7; j++) {
                    resultsMatrix[k][j] = resultsMatrix[k][j] / NUMBER_OF_REPETITIONS_PER_OPERATION;
                    if(resultsMatrix[k][j] != 0) {
//                        cout<<resultsMatrix[k][j]<<" ";
                        finalResults[i][k][j] = resultsMatrix[k][j];
                    }
                    resultsMatrix[k][j] = 0;
                }
                cout<<endl;
            }
        }

        tablica->clear();
        lista->clear();
        kopiec->clear();
    }

public:
    TimeTest() {
        NUMBER_OF_REPETITIONS = 5;
        DATA_SET_SIZES = new int[NUMBER_OF_REPETITIONS];
        NUMBER_OF_REPETITIONS_PER_OPERATION = 100;
        DATA_SET_SIZES[0] = 10000;
        DATA_SET_SIZES[1] = 20000;
        DATA_SET_SIZES[2] = 30000;
        DATA_SET_SIZES[3] = 40000;
        DATA_SET_SIZES[4] = 50000;
    }

    void run() {
        srand(time(nullptr));
        cout<<"Rozpocznięcie testu"<<endl;
        getInputDataAndTest();
//        generateResultsFile();
        cout<<"Test zakończony."<<endl;
        delete [] DATA_SET_SIZES;
    }
};
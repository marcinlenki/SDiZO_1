#include <iostream>
#include<cstdlib>
#include<ctime>
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
using namespace std;


class TimeTest {
public:
    const char* FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt/dane.txt";
    const char* RESULTS_FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt/wyniki.txt";
    ofstream structFile, results;
    int NUMBER_OF_REPETITIONS;
    int NUMBER_OF_REPETITIONS_PER_OPERATION;
    int *DATA_SET_SIZES;
    long resultsMatrix[3][7] = {{0}};
    long finalResults[5][3][7] = {{{0}}};

    void generateInputData(int size, int maxRand) {
        structFile.open(FILE_PATH);
        int randNum;

        structFile<<size<<endl;

        for(int i = 0; i<size-1; i++) {
            randNum = (rand() % (2 * maxRand + 1)) - maxRand;
            structFile<<randNum<<endl;
        }
        structFile << randNum;

        structFile.close();
    }

    void generateResultsFile() {
        results.open(RESULTS_FILE_PATH);
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
        return (rand() % 2 * maxRand) + 1 - maxRand;
    }

    void getInputDataAndTest() {
        int maxRand = 100, finalResultsIndex = 0;
        Tablica *tablica = new Tablica;
        Lista *lista = new Lista;
        Kopiec *kopiec = new Kopiec;

        for(int i = 0; i < NUMBER_OF_REPETITIONS; i++) {
            generateInputData(DATA_SET_SIZES[i], maxRand);

            int testNumber = getRandomNumber(maxRand);
            int testIndex = DATA_SET_SIZES[i] / 2;

            
            for(int j = 0; j<NUMBER_OF_REPETITIONS_PER_OPERATION; j++) {

                tablica->fillFromFile(FILE_PATH);
                lista->fillFromFile(FILE_PATH);
                kopiec->fillFromFile(FILE_PATH);


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                                                        //TABLICA
                //DODAWANIE NA POCZĄTKU
                auto begin = std::chrono::high_resolution_clock::now();
                tablica->addBeginning(testNumber);
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][0] += (long)elapsed.count();

                //USUWANIE NA POCZĄTKU
                begin = std::chrono::high_resolution_clock::now();
                tablica->removeBeginning();
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][1] += (long)elapsed.count();

                //DODAWANIE NA KOŃCU
                begin = std::chrono::high_resolution_clock::now();
                tablica->addEnd(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][2] += (long)elapsed.count();

                //USUWANIE NA KOŃCU
                begin = std::chrono::high_resolution_clock::now();
                tablica->removeEnd();
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][3] += (long)elapsed.count();

                //DODAWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                begin = std::chrono::high_resolution_clock::now();
                tablica->addIndex(testIndex, testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][4] += (long)elapsed.count();

                //USUWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                begin = std::chrono::high_resolution_clock::now();
                tablica->removeIndex(testIndex);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][5] += (long)elapsed.count();

                //WYSZUKIWANIE
                begin = std::chrono::high_resolution_clock::now();
                tablica->search(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[0][6] += (long)elapsed.count();


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //                                         LISTA
                //DODAWANIE NA POCZĄTKU
                begin = std::chrono::high_resolution_clock::now();
                lista->addBeginning(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][0] += (long)elapsed.count();

                //USUWANIE NA POCZĄTKU
                begin = std::chrono::high_resolution_clock::now();
                lista->removeBeginning();
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][1] += (long)elapsed.count();

                //DODAWANIE NA KOŃCU
                begin = std::chrono::high_resolution_clock::now();
                lista->addEnd(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][2] += (long)elapsed.count();

                //USUWANIE NA KOŃCU
                begin = std::chrono::high_resolution_clock::now();
                lista->removeEnd();
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][3] += (long)elapsed.count();

                //DODAWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                begin = std::chrono::high_resolution_clock::now();
                lista->addIndex(testIndex, testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][4] += (long)elapsed.count();

                //USUWANIE NA DOWOLNYM MIEJSCU (środek struktury)
                begin = std::chrono::high_resolution_clock::now();
                lista->removeIndex(testIndex);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][5] += (long)elapsed.count();

                //WYSZUKIWANIE
                begin = std::chrono::high_resolution_clock::now();
                lista->search(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[1][6] += (long)elapsed.count();


                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //--------------------------------------------------------------------------------------------------
                //                                         KOPIEC

                //DODAWANIE
                begin = std::chrono::high_resolution_clock::now();
                kopiec->add(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[2][0] += (long)elapsed.count();

                //USUWANIE KORZENIA
                begin = std::chrono::high_resolution_clock::now();
                kopiec->removeRoot();
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[2][1] += (long)elapsed.count();

                //WYSZUKIWANIE
                begin = std::chrono::high_resolution_clock::now();
                kopiec->search(testNumber);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                resultsMatrix[2][2] += (long)elapsed.count();

                generateInputData(DATA_SET_SIZES[i], maxRand);
            }

            for(int k = 0; k < 3; k++) {
                for(int j = 0; j<7; j++) {
                    resultsMatrix[k][j] /= NUMBER_OF_REPETITIONS_PER_OPERATION;
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
        generateResultsFile();
        cout<<"Test zakończony."<<endl;
        delete [] DATA_SET_SIZES;
    }
};
// Chloe Chung
// Project 3 - Sorting Contest
// March 6, 2025

// I certify that this program is my own original work. I did not copy any part of this program from 
// any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;

long long SWAP_COUNT = 0; // cannot be int > 2.1 billion
mutex m;

void bubble(int A[], int size, int processName){
    long long swaps = 0;
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){
            if (A[j] > A[j + 1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                swaps++;
            }
        }
    }
    m.lock();
    SWAP_COUNT += swaps;
    cout << "Process: " << processName << " Swap Count: " << swaps << endl;
    m.unlock();
}

void merge(int* left, int* right, int size){
    int* tempArray = new int[size * 2];
    int* leftEnd = left + size;
    int* rightEnd = right + size;
    int i = 0;

    while (left < leftEnd && right < rightEnd){
        if (*left < *right) {
            tempArray[i++] = *left++;
        }else{
            tempArray[i++] = *right++;
        }
    }
    while (left < leftEnd) tempArray[i++] = *left++;
    while(right < rightEnd) tempArray[i++] = *right++;

    for (int j = 0; j < size * 2; j++)
        *(leftEnd - size + j) = tempArray[j];

    delete[] tempArray;

}


void writeArray(int A[], int size, ofstream& file)
{
    for (int i=0; i<size; i++){
        file << A[i] << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " numbers.dat mysort.out" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    int size = 1000000;

    // initialize number of threads (default = 16) 
    int numberOfThreads = 16;   

    // take in number of threads from command line, otherwise default = 16
    if(argc == 4){
        // checks if test run
        if (string(argv[3]) == "-test"){
            size = 10000;
        }else{
            numberOfThreads = stoi(argv[3]);
        }
    }

    int* A =  new int[size];

    // Read numbers from the file
    ifstream file(inputFile);

    if(!file.is_open()){
        cerr << "Error - the file of random numbers could not be opened." << endl;
        return 1;
    }

    int count = 0;
    while (file >> A[count] && count < size){
        count++;
    }

    size = count;
    int sectionSize = size / numberOfThreads;
    int remainder = size % numberOfThreads;

    file.close();

    // split into threads to bubble
    thread* arrayOfThreads = new thread[numberOfThreads];
    for (int i = 0; i < numberOfThreads; ++i){
        int currentSectionSize = sectionSize + (i < remainder ? 1 : 0);
        arrayOfThreads[i] = thread(bubble, A + (i * sectionSize), currentSectionSize, i);
    }
        
    // join back together
    for (int i = 0; i<numberOfThreads; ++i)
        arrayOfThreads[i].join();
    
    //merge sections
    for (int step = 2; step <= numberOfThreads; step *= 2){ 
        for (int i=0; i < numberOfThreads; i += step){
            if (i + step / 2 < numberOfThreads) //check bounds
                merge(A + (i * sectionSize), A + ((i + step / 2) * sectionSize), sectionSize * step / 2);
        }
    }

    ofstream outFile(outputFile);
    if (!outFile.is_open()){
        cerr << "Error - cannot open mysort.out" << endl;
        delete[] A;
        return 1;
    }

    writeArray(A,size,outFile); // write sorted A into file mysort.out

    delete[] arrayOfThreads;
    delete[] A;
    
    outFile.close();

    cout << "Number of total swaps: " << SWAP_COUNT << endl;

    return 0;
}
  

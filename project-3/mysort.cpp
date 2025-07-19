// Chloe Chung
// Project 3 - Sorting Contest
// March 6, 2025

// I certify that this program is my own original work. I did not copy any part of this program from 
// any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <fstream>
using namespace std;

void bubble(int A[], int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < (size - 1) - i; j++)
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
}

void writeArray(int A[], int size, ofstream& file)
{
    for (int i=0; i<size; i++){
        file << A[i] << endl;
    }

}

int main()
{
    const int size = 1000000;
    int* A =  new int[size];

    ifstream file("numbers.dat");

    if(!file.is_open()){
        cerr << "Error - the file of random numbers could not be opened." << endl;
        return 1;
    }

    int count = 0;
    while (file >> A[count] && count < size){
        count++;
    }
    cout << endl;

    file.close();

    bubble(A,size); // make sure it sorts the original A


    ofstream outFile("mysort.out");
    if (!outFile.is_open()){
        cerr << "Error - cannot open mysort.out" << endl;
        delete[] A;
        return 1;
    }

    writeArray(A,size,outFile); // write sorted A into file mysort.out

    delete[] A;

    file.close();

    return 0;
}

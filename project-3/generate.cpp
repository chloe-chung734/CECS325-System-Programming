
#include <iostream>
#include <random>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]){
    
    try{
        if(argc == 4){
            int COUNT = stoi(argv[1]);
            int MIN = stoi(argv[2]);
            int MAX = stoi(argv[3]);

            int* numbers = new int[COUNT];

            ofstream file("numbers.dat");

            if(!file.is_open()){
                delete[] numbers;
                throw("Error - cannot open file.");
            }

            srand(time(0));

            for (int i=0; i<COUNT; i++)
                numbers[i] = MIN + (rand() % (MAX - MIN + 1));

            for(int i = 0; i<COUNT; i++)
                file << numbers[i] << " ";

            file.close();

            delete[] numbers;

        }else{
            throw("Error - inaccurate number of arguments.");
        }
    }catch(const char* message){
        cerr << message << endl;
    }

    return 0;
}
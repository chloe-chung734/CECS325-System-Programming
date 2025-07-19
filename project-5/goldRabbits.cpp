// Chloe Chung
//Project 5 - Gold Rabbits
//April 22, 2025

// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <time.h>
#include <iomanip>
#include <map>
#include <limits>

using namespace std;

//#define integer short
#define integer int
//#define integer long long


// this is the goldRabbits function
integer goldRabbits(integer n) // you need to add a static map to “remember” previous values
{
    static map<integer, integer> rabbitMap;

    //print map if n is -1
    if(n == -1){
        cout << "\nFibo Rabbit Map contents: " << endl;
        for (auto it = rabbitMap.begin(); it != rabbitMap.end(); ++it)
            cout << it->first << ": " << it->second << endl;
        cout << "end of Rabbit map\n" << endl;
        return 0;
    }

    //assign initial fibonacci values if empty
    if (rabbitMap.empty()){
        rabbitMap[0] = 1;
        rabbitMap[1] = 1;
    }

    //memoization
    if (rabbitMap.count(n)){
        return rabbitMap[n];
    }

    // calculate recursion, throw if overflow error
    integer val1 = goldRabbits(n-1);
    integer val2 = goldRabbits(n-2);

    rabbitMap[n] = val1 + val2;

    if (val1 > numeric_limits<integer>::max() - val2)
        throw overflow_error("Integer overflow occurred at goldRabbits(" + to_string(n) + "): " + to_string(rabbitMap[n]));

    return rabbitMap[n];

}

int main(int argc, char* argv[])
{
    // part of the original code to calculate for 10 years
    // int const months = 12 * 10; // this is 10 years or 120 months
    // int start = time(0); // number of seconds since Jan 1, 1970

    // for(int i=0; i<months; i++)
    // {
    // int current = time(0); // number of seconds since program started
    // cout << setw(5)<<current-start<<":"; // print elapsed seconds
    // cout << " GoldRabbits("<<setw(2)<<i<<") = ";
    // cout << setw(11)<< goldRabbits(i) <<endl;// the call to goldRabbits
    // }

    for (integer i=1; i<argc; i++){
        
        try{
            integer years = stoi(argv[i]);

            cout << "goldRabbits(" << to_string(years) << "): ";
            
            if (goldRabbits(years) != 0)
                cout << goldRabbits(years) << endl;

        }catch (const invalid_argument & e){
            cerr << argv[i] << " is not an integer" << endl;
        }catch(const overflow_error & e){
            cerr << e.what() << endl;
        }

    };

    return 0;
}

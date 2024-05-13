#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Open the file
    ifstream inputfile(argv[1]);
    if (!inputfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    // Initialize variables
    string queryParams[] = {argv[2], argv[3], argv[4], argv[5]};
    int capacity = 10; // Initial capacity
    int recordIdx = 0; // Number of records added
    int doublingCounter = 0; // How many times the array was doubled

    // Dynamically allocate the array
    AirlinePassenger* passengers = new AirlinePassenger[capacity];

    // Parse the file and fill the passengers array
    parseFile(inputfile, queryParams, passengers, capacity, recordIdx, doublingCounter);

    // Close the file
    inputfile.close();

    // Sort and print queried passengers
    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of passengers returned after the query: " << recordIdx << endl;
    printQueriedPassengers(passengers, recordIdx);

    // Cleanup
    delete[] passengers;

    return 0; // Successful execution
}

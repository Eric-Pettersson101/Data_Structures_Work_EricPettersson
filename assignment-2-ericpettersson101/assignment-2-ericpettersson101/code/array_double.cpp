#include "array_double.hpp"
#include <sstream>
using namespace std;

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    string tempLine;
    stringstream tempStream;

    string tempName, tempAirline, tempLocation, tempAge;

    string name;
    while(getline(input, tempLine)) {

        stringstream tempStream(tempLine);
        getline(tempStream, tempName, ',');
        getline(tempStream, tempAirline, ',');
        getline(tempStream, tempLocation, ',');
        getline(tempStream, tempAge, ',');

        int startAge = stoi(queryParams[2]);
        int endAge = stoi(queryParams[3]);

        AirlinePassenger passenger;

        passenger.name = tempName;
        passenger.airline = tempAirline;
        passenger.location =tempLocation;
        passenger.age = stoi(tempAge);
        if (isPassengerQueried(passenger, queryParams[0], queryParams[1], startAge, endAge)) {
            addPassenger(passengers, passenger, arrCapacity, recordIdx, doublingCounter);
        } 
    }
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
        return passenger.location == queryLocation && passenger.airline == queryAirline && passenger.age >= startAge && passenger.age <= endAge;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
    int newSize = *arraySize;
    newSize = newSize*2;
    AirlinePassenger *newArray = new AirlinePassenger[newSize];
    
    for (int i = 0; i < *arraySize; ++i) {
        newArray[i] = passengers[i];
    }
    
    delete[] passengers;
    passengers = newArray;
    *arraySize = newSize;
}


/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
   if (recordIdx >= arrCapacity) {
        resizeArr(passengers, &arrCapacity);
        doublingCounter++;
    }
    passengers[recordIdx++] = airlinePassenger;
    
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {
    //TODO
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (passengers[j].age < passengers[j + 1].age || (passengers[j].age == passengers[j + 1].age && passengers[j].name > passengers[j + 1].name)) {
                swap(passengers[j], passengers[j + 1]);
            }
        }
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    sortPassengers(passengers, numOfRecords);
    cout << "Queried Passengers\n---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; ++i) {
        cout << passengers[i].name << " " << passengers[i].age << endl;
    }
}

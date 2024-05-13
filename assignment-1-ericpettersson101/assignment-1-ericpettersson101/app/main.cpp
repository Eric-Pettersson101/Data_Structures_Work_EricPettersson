#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>


using std::stringstream;
using std::getline;



using namespace std;

int main(int argc, char* argv[]) {

    //opens both file
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening files!" << endl;
        return 1;
    }

    stockInfo stocks[6];
    string line;
    int index = 0;

    while (getline(inputFile, line) && index < 6) {
        stringstream ss(line);
        string company_name, price;
        double prices[5];
        getline(ss, company_name, ',');
        for (int i = 0; i < 5; i++) {
            getline(ss, price, ',');
            prices[i] = stod(price);
        }
        insertStockInfo(stocks, company_name, prices, index);
        index++;
    }

    for (int i = 0; i < index; i++) {
        displaySortedStocks(stocks[i], outputFile);
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
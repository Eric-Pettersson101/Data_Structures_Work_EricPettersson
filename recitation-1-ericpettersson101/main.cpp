#include "addEmployee.hpp"

int main(int argc, char *argv[])
{
    // check for number of arguments
    if (argc < 2)
    {
        cout << "file name missing" << endl;
        return -1;
    }

    string fileName = argv[1]; //passed "employees.csv" into arg 1
    employee array[4];

    // open the file
    ifstream myfile;
    myfile.open(fileName);

    string line;
    string name;
    string emailid;
    string birthday;
    int length = 0;

    if (myfile.is_open())
    {
        string name;
        string birthday;
        string emailid;
        int count=0;
        while (getline(myfile, line) && length < 4) //makes sure that while loop only runs four times
        {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, birthday, ',');
            getline(ss, emailid, ',');
            length = addAnEmployee(array, name, birthday, emailid, length);
        }
        myfile.close();
    }   else    {
        cout << "err: can not open file" << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        cout << "name:" << array[i].name << " email:" << array[i].email << " bday:" << array[i].birthday << endl;
    }
    return 0;
}
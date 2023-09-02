#include <iostream>
#include <fstream> // file stream
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;
void outputLine(int, const string, double); // prototype
int main()
{
    // ifstream constructor opens the file
    ifstream inClientFile("clients.dat", ios::in);
    // exit program if ifstream could not open file
    if (!inClientFile)
    {
        cerr << "File could not be opened" << endl;
        exit(1);
    } // end if
    int account;
    char name[30];
    double balance;
    cout << left << setw(10) << "Account" << setw(13)
         << "Name"
         << "Balance" << endl
         << fixed << showpoint;
    // display each record in file
    while (inClientFile >> account >> name >> balance)
    {
        outputLine(account, name, balance);
    }
    return 0; // ifstream destructor closes the file
}
// display single record from file
void outputLine(int account, const string name, double balance)
{
    cout << left << setw(10) << account << setw(13) << name
         << setw(7) << setprecision(2) << right << balance << endl;
}
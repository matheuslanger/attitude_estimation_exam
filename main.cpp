#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

class SteeringData
{

public:
        string Timestamp;
        string Acc_x;
        string Acc_y;
        string Acc_z;

};

int main()
{
    ifstream file;

    ofstream writeFile;

    file.open("attitude_exam.log");
    writeFile.open("processed_data.log", ofstream::out | ofstream::trunc);

    if (file.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    int current_line = 1;
    string line;

    do
    {
        SteeringData data;

        stringstream inputString(line);
        current_line++;

        getline(file, line);

        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        getline(inputString, data.Timestamp, ';');
        getline(inputString, data.Acc_x, ';');
        getline(inputString, data.Acc_y, ';');
        getline(inputString, data.Acc_z, ';');

        writeFile << data.Timestamp << " " << data.Acc_x << " " << data.Acc_y << " " << data.Acc_z << endl;

    }
    while (!file.eof());


    file.close();
    writeFile.close();

    return 0;
}
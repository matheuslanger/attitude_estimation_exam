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
    SteeringData(
        string timestamp,
        string acc_x,
        string acc_y,
        string acc_z)
    {
        Timestamp = timestamp;
        Acc_x = acc_x;
        Acc_y = acc_y;
        Acc_z = acc_z;
    }

    void display()
    {
        cout << "Timestamp: " << Timestamp << endl;
        cout << "Acc_x: " << Acc_x << endl;
        cout << "Acc_y: " << Acc_y << endl;
        cout << "Acc_z: " << Acc_z << endl;
        cout << endl;
    }

    string Timestamp;
    string Acc_x;
    string Acc_y;
    string Acc_z;
};

void displayData(vector<SteeringData> &data)
{

    for (auto steer : data)
    {
        steer.display();
    }
}

SteeringData dataParser(string line, SteeringData steer)
{

    stringstream inputString(line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    getline(inputString, steer.Timestamp, ';');
    getline(inputString, steer.Acc_x, ';');
    getline(inputString, steer.Acc_y, ';');
    getline(inputString, steer.Acc_z, ';');
    return steer;
}

int main()
{
    ifstream file;

    int line_number;
    line_number = 50000;

    file.open("attitude_exam.log");

    if (file.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    int current_line = 0;
    string line;

    while (!file.eof())
    {
        current_line++;

        getline(file, line);

        cout << "Line: " << line << endl;
    }


    file.close();

    return 0;
}




























/*
int main()
{

    string line;
    ifstream ifs;

    ifs.open("attitude_exam.log");

    vector<SteeringData> steers;

    while(getline(ifs, line))
    {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        stringstream inputString(line);

        string timestamp;
        string acc_x;
        string acc_y;
        string acc_z;

        getline(inputString, timestamp, ';');
        getline(inputString, acc_x, ';');
        getline(inputString, acc_y, ';');
        getline(inputString, acc_z, ';');

        SteeringData steer(timestamp, acc_x, acc_y, acc_z);

        steers.push_back(steer);

    displayData(steers);
    }

}
*/

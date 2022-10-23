#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;

// Creates a class for getting info from the file
class SteeringData
{

public:
        string Timestamp;
        string Acc_x;
        string Acc_y;
        string Acc_z;

};

// Function that calculates the pitch angle
double pitchEstimator(int x, int y, int z)
{
    return atan((x * (-1)) / (sqrt(pow(y, 2) + pow(z, 2))));
}

// Function that calculates the roll angle
double rollEstimator(int x, int y, int z, int sign, double multiplier)
{
    return atan((y) / ((sign) * (sqrt(pow(z, 2) + (multiplier * pow(x, 2))))));
}

int main()
{
    ifstream file;

    ofstream writeFile;
    
    int aX, aY, aZ, sign_Z;

    double pitchEst, rollEst;
    double u = 0.01;

    // Open files
    file.open("attitude_exam.log");

    // This file will be erased each time the code runs so that it can be overwritten
    writeFile.open("processed_data.log", ofstream::out | ofstream::trunc);




    // Checks if the files opened successfully
    if (file.fail() || writeFile.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    // String that will receive the content of a line
    string line;

    do
    {
        SteeringData data;

        stringstream inputString(line);

        getline(file, line);

        // Removes whitespaces from a line
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        // Parses the data from the file to a object
        getline(inputString, data.Timestamp, ';');
        getline(inputString, data.Acc_x, ';');
        getline(inputString, data.Acc_y, ';');
        getline(inputString, data.Acc_z, ';');

        try
        {
        // Converts string to int
        aX = stoi(data.Acc_x);
        aY = stoi(data.Acc_y);
        aZ = stoi(data.Acc_z);
        }
        //Prevents invalid conversion from happening
        catch (const invalid_argument e) {}
        
        // Determines the value of the sign_z
        if(aZ >= 0)
            sign_Z = 1;

        else if(aZ < 0)
            sign_Z = -1;

        // Formula for the estimated roll
        pitchEst = pitchEstimator(aX, aY, aZ);

        // Formula for the estimated pitch
        rollEst = rollEstimator(aX, aY, aZ, sign_Z, u);

        // Prevents writing empty lines
        if(data.Timestamp != "")
        // Writes file with raw data separated by semicolons
        writeFile<< data.Timestamp << ";" << rollEst << ";" << pitchEst << endl;

    }
    // Stops when the code reaches the final line
    while (!file.eof());

    // Closes files
    file.close();
    writeFile.close();

    return 0;
}
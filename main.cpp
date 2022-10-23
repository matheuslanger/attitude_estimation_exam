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

int main()
{
    ifstream file;

    ofstream writeFile;

    int aX, aY, aZ;

    int sign_z;

    double pitch_est, roll_est;
    double u = 0.01;

    // Open files
    file.open("attitude_exam.log");
    writeFile.open("processed_data.log", ofstream::out | ofstream::trunc);

    // Checks if the files opened
    if (file.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    if (writeFile.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    string line;

    do
    {
        SteeringData data;

        stringstream inputString(line);

        getline(file, line);

        // Removes whitespaces from the lines
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
        //writeFile << data.Timestamp << endl;
        }
        //Prevents invalid conversion from happening
        catch (const invalid_argument e) {}
        
        // Determines the value of the sign_z
        if(aZ >= 0)
            sign_z = 1;

        else if(aZ < 0)
            sign_z = -1;

        // Formula for the estimated roll
        roll_est = atan((aX*(-1))/(sqrt(pow(aY,2) + pow(aZ,2))));

        // Formula for the estimated pitch
        pitch_est = atan((aY)/((sign_z)*(sqrt(pow(aZ, 2) + (u * pow(aX, 2))))));

        // Prevents writing empty lines
        if(data.Timestamp != "")
        // Writes file with raw data separated by semicolons
        writeFile <<data.Timestamp << ";" << roll_est << ";" << pitch_est << endl;

    }
    // Stops when the code reaches the final line
    while (!file.eof());

    // Closes files
    file.close();
    writeFile.close();

    return 0;
}
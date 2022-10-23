# Attitude Estimation Exam
This project receives a file with a timestamp as well as accelerometer values from each axis (x, y, z).
The code utilizes this data to make calculations that can estimate the pitch and roll angles from a accelerometer and put the values in a new file.

## How was it made
To make calculations by working with the data on the file, it was necessary to parse the information removing whitespaces and getting the data between semicolons,
this was done using _stringstreams_ and converting it to int type.

After getting the data and converting it to int, the code will calculate the pitch and roll with the following formulas respectively:

![equation](https://latex.codecogs.com/png.image?%5Cdpi%7B110%7D%5Cbg%7Bblack%7Dtan(%5Ctheta)xyz=%5Cfrac%7B-Gpx%7D%7B%5Csqrt%7BGpy%5E%7B2%7D%20&plus;%20Gpz%5E%7B2%7D%7D%7D)

![equation](https://latex.codecogs.com/png.image?%5Cdpi%7B110%7D%5Cbg%7Bblack%7Dtan(%5Cphi%20)xyz%20=%20%5Cfrac%7BGpy%7D%7Bsign(Gpz)%5Csqrt%7BGpz%5E%7B2%7D%20&plus;%20%5Cmu%20Gpx%5E%7B2%7D%7D%7D)

To find the angle value of a tangent, it is necessary to calculate the inverse of the tangent, wich will give the desired angle value.

After that the code writes the pitch and roll angles to the _processed_data.log_ file with the respective timestamp. The lines follow the pattern below:

_<time_stamp_ms;roll_angle;pitch_angle>_ for example: **54741;0.0223994;-0.0274811**

## How to compile and run the code
### Windows
Download and install MinGW64 through _https://www.msys2.org/_

```<
cd {folder_dir}

g++ main.cpp -o main

main
```


### Linux
```<sudo apt install build-essential

g++ main.cpp -o main

./main

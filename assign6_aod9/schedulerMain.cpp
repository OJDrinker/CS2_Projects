// File Name: schedulerMain.cpp
//
// Author: Andrew Daly
// Date: 04/29/2020
// Assignment Number: 6
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Scheduler.h"

using namespace std;

vector <PendingProcess> readPendingProcessList(ifstream& in);

int main()
{
    int seconds = 0;
    ifstream in;

    in.open("pendingProcessList.csv");

    if (!in)
    {
        cout << endl << endl
            << " ***Program Terminated.*** " << endl << endl
            << "Input file failed to open." << endl;

        return 1;
    }

    vector <PendingProcess> list = readPendingProcessList(in);

    Scheduler obj;
    for (PendingProcess& toDo : list) obj.add(toDo);

    while (obj.empty())
    {
        cout << "Second " << seconds << ": " << obj.next() << endl;
        seconds++;
    }

    return 0;
}

//Function Definitions:

//***********************************************************
// readPendingProcessList: read the .csv file with list of
//                         pending processes and put them
//                         into a vector
// in - input file
// returns: vector of the list to be processed
//***********************************************************

vector <PendingProcess> readPendingProcessList(ifstream& in)
{
    vector<PendingProcess> processList;
    
    string processName, 
           line, 
           token;

    int runningTime;

    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, processName, ',');
        getline(ss, token);
        stringstream digit(token);
        digit >> runningTime;
        PendingProcess newProcess(processName, runningTime);
        processList.push_back(newProcess);
    }
    return processList;
}
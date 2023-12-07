//bankers

#include <iostream>
using namespace std;

int need[100][100];
int safeSequence[100], executed[100];

int allocation[100][100], maximum[100][100], available[100][100];

//! hardcoded stuff for debug
// int available[100][100] = {{7, 7, 10}};
// int allocation[100][100] = {{2, 2, 3},
//                             {2, 0, 3},
//                             {1, 2, 4}}; // P4
// int maximum[100][100] = {{3, 6, 8},     // P0 // MAX Matrix
//                          {4, 3, 3},     // P1
//                          {3, 4, 4}};    // P2

int nProcesses = 3, nResources = 3;

void printMat(int nProcesses, int nResources, int mat[][100])
{
    for (int i = 0; i < nProcesses; i++)
    {
        for (int j = 0; j < nResources; j++)
        {
            cout << " " << mat[i][j];
        }
        cout << "\n";
    }
}

bool safetyAlgo()
{
    int n = 0, i, j, state = 0;

    // initilaising values:
    for (i = 0; i < nProcesses; i++)
    {
        safeSequence[i] = 0;
        executed[i] = 0;
    }

    // main loop calculating everything
    while (n < nProcesses)
    {

        // loop to scan processes to see which can be executed safely next:
        for (i = 0; i < nProcesses; i++)
        {
            // checking if process has already been executed or not:
            // if the process has already been executed, find another process
            if (executed[i])
                continue;

            // checking for the process, looping over each resource value
            // to find if its needs can be satisfied by available or not
            for (j = 0; j < nResources; j++)
            {
                if (need[i][j] <= available[state][j])
                    continue;
                else
                    break;
            }

            // if the proces can be safely executed:
            if (j == nResources)
            {
                // add the process number to safe sequence
                safeSequence[state] = i;
                state++;

                // update executed[]
                executed[i] = 1;

                // update available vector:
                for (int j = 0; j < nResources; j++)
                {
                    available[state][j] = available[state - 1][j] + allocation[i][j];
                }
            }
        }

        n++;
    }

    if (state != nProcesses)
    {
        cout << "\nNo safe sequence...\n: ";
        return false;
    }
    return true;
}

int main()
{
    // Input stuff------------------------------------------------
    cout << "Enter N processes: \n";
    cin >> nProcesses;

    cout << "Enter N Resources: \n";
    cin >> nResources;

    cout << "Enter allocation Matrix: \n";
    for (int i = 0; i < nProcesses; i++)
    {
        executed[i] = 0;
        for (int j = 0; j < nResources; j++)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter Max matrix: \n";
    for (int i = 0; i < nProcesses; i++)
    {
        for (int j = 0; j < nResources; j++)
        {
            cin >> maximum[i][j];
        }
    }

    cout << "Enter available vector: \n";
    for (int i = 0; i < nResources; i++)
        cin >> available[0][i];
    //------------------------------------------------------------------

    // computing need matrix:
    for (int i = 0; i < nProcesses; i++)
    {

        for (int j = 0; j < nResources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            // available[i][j] = 0;
        }
    }
    cout << endl;

    if (!safetyAlgo())
    {
        exit(0);
    }

    // output stuff
    cout << "\nAvaliable matrix: \n";
    printMat(nProcesses + 1, nResources, available);

    cout << "\nNeed matrix: \n";
    printMat(nProcesses, nResources, need);

    cout << "\nAllocation matrix: \n";
    printMat(nProcesses, nResources, allocation);

    cout << endl;

    cout << "Safe sequence: ";
    for (int i = 0; i < nProcesses; i++)
        cout << "P" << safeSequence[i] << ", ";

    while (1)
    {
        cout << "\n\nEnter 1 to allocate additional resources." << endl;
        cout << "Enter 2 to exit." << endl;
        int choice;
        int temp[100], flag = 0;

        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter process number to allocate additional resources to: ";

            int additionalProcess;
            cin >> additionalProcess;

            cout << "\nEnter additional resource values: \n";

            for (int j = 0; j < nResources; j++)
            {
                cin >> temp[j];

                // updating all values with additional resource values
                allocation[additionalProcess][j] += temp[j];
                available[0][j] -= temp[j];
                need[additionalProcess][j] -= temp[j];

                // if the requested resource exceeds max, or available drops below 0:
                if (allocation[additionalProcess][j] + need[additionalProcess][j] > maximum[additionalProcess][j] or available[0][j] < 0)
                {
                    flag = 1;
                }
            }

            if (flag)
                cout << "Requested resources cannot be allocated, reverting to previous state: \n";

            // check if safe sequence exists:
            else if (safetyAlgo())
            {

                // output stuff
                //cout << "\nAvaliable matrix: \n";
                //printMat(nProcesses + 1, nResources, available);

                cout << "\nNeed matrix: \n";
                printMat(nProcesses, nResources, need);

                //cout << "\nAllocation matrix: \n";
                //printMat(nProcesses, nResources, allocation);

                cout << endl;

                for (int i = 0; i < nProcesses; i++)
                    cout << "P" << safeSequence[i] << ", ";
            }

            // reverting all states to original
            for (int j = 0; j < nResources; j++)
            {
                allocation[additionalProcess][j] -= temp[j];
                available[0][j] += temp[j];
                need[additionalProcess][j] += temp[j];
            }

            break;

        case 2:
            exit(1);

        default:
            cout << "Error in input!" << endl;
        }
    }
}
 
// 5

// 4
 
// 0 1 1 0
// 1 4 4 1
// 1 3 6 5
// 0 6 3 2
// 0 0 1 4

// 0 2 1 0
// 1 6 5 2
// 2 3 6 6
// 0 6 5 2
// 0 6 5 6
 
// 1 3 1 0

//after
// 2 1 1 0
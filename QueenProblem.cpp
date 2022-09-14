// QueenProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>

using namespace std;

int numQ = 0;

struct Board {
    const int w = 8;
    bool b[8 * 8];
};

int countAdjacencies(array<bool, 64> &arr, int index) {
    int adj = 0;
    int qX = index % 8;
    int qY = index / 8;

    for (int i = 0; i < 64; i++) {
        if (arr[i]) {
            int rX = i % 8;
            int rY = i / 8;
            if (qX == rX && qY == rY) // make sure we aren't comparing itself
                continue;
            if (qX == rX) { // we know it's in the same column. Let's learn more
                if (qY - rY < 0) { // OUR QUEEN is NORTH of threatened queen
                    int c = i - 8; // c is set to the spot directly ABOVE threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c -= 8; // we move to tile above previous
                    } if (c == index) adj++;
                }
                else { // OUR QUEEN is SOUTH of threatened queen
                    int c = i + 8; // c is set to the spot directly BELOW threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c += 8; // we move to tile below previous
                    } if (c == index) adj++;
                }
            }

            else if (qY == rY) { // we know it's in the same row. Let's learn more
                if (qX - rX < 0) { // OUR QUEEN is WEST of threatened queen
                    int c = i - 1; // c is set to the spot directly LEFT of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c -= 1; // we move to tile left of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
                else { // OUR QUEEN is EAST of threatened queen
                    int c = i + 1; // c is set to the spot directly RIGHT of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c += 1; // we move to tile right of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
            }
                
            else if (qX + qY == rX + rY) { // we know it's in the UPWARD DIAGONAL. let's learn more.
                if (qX - qY < rX - rY) { //OUR QUEEN is SOUTHWEST of threatened queen
                    int c = i + 8 - 1; // c is set to the spot directly SOUTHWEST of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c = c + 8 - 1; // we move to tile SOUTHWEST of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
                else { //OUR QUEEN is NORTHEAST of threatened queen
                    int c = i - 8 + 1; // c is set to the spot directly NORTHEAST of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c = c - 8 + 1; // we move to tile NORTHEAST of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
            }

            else if (qX - rX == qY - rY) { // we know it's in the same DOWNWARD DIAGONAL.
                if (qX - rX < 0) { // OUR QUEEN is NORTHWEST of threatened queen
                    int c = i - 8 - 1; // c is set to the spot directly NORTHWEST of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c = c - 8 - 1; // we move to tile NORTHWEST of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
                else { // OUR QUEEN is SOUTHEAST of threatened queen
                    int c = i + 8 + 1; // c is set to the spot directly SOUTHEAST of threatened queen
                    while (c != index) { // while c does not point to OUR QUEEN
                        if (arr[c]) // if there is a queen IN THE WAY
                            break; // this is not a valid threaten.
                        c = c + 8 + 1; // we move to tile southeast of previous
                    } if (c == index) adj++; // if c == index, then we didn't break unnaturally.
                }
            }
        }
    }
    return adj;
}
void fillBoard(array<bool, 64> arr, int index) {
    if (index == 64) { // we have a full board
        for (int i = 0; i < 64; i++) // let's check if this board satisfies constraints
            if (arr[i]) // if there is a queen at this index
                if (countAdjacencies(arr, i) != 2) // and this queen does not threaten exactly 2 others
                    return; // this board will not work.

        // if we have gone through the whole board and no invalid queens

        int temp = 0;
        for (int i = 0; i < 64; i++)
            if (arr[i]) temp++;

        if (temp > numQ) {
            numQ = temp;
            cout << "\n========\n";
            for (int x = 0; x < 64; x++) {
                if (x % 8 == 0)
                    cout << endl;
                cout << arr[x];
            }
        }
            
        

       

        return;
    }
    arr[index] = 0;
    fillBoard(arr, index + 1);
    arr[index] = 1;
    fillBoard(arr, index + 1);

    return;
}

int main()
{
    array<bool, 64> arr;
    for (int x = 0; x < 64; x++)
        arr[x] = 0;
    fillBoard(arr, 0);

    cout << numQ;
}

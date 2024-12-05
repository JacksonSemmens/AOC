// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

vector<vector<string>> readAndSplitFile(const string& filename) {
    vector<vector<string>> result;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        for (char c : line) {
            // Convert each character into a string and add to the row vector
            row.push_back(string(1, c));
        }
        result.push_back(row);
    }

    file.close();
    return result;
}

bool isWordFound(const vector<vector<string>>& grid, const string& wordToFind, int xCoord, int yCoord, int xDirection, int yDirection) {
    int loopLength = wordToFind.length();
    bool result = true;

    for (int i = 0; i < loopLength; i++) {
        int maxX = xCoord + i * xDirection;
        int maxY = yCoord + i * yDirection;

        if (maxX < 0 || maxX >= grid.size() || maxY < 0 || maxY >= grid[0].size()) {
            result = false; 
            break;
        }

        if (grid[maxX][maxY] != string(1, wordToFind[i])) {
            result =  false;
            break;
        }
    }

    return result;
}

int FindTotalNumberOfXMas(const vector<vector<string>>& grid) {
    int totalCounter = 0;

    int numOfRows = grid.size();
    int numOfColumns = grid[0].size();

    for (int xCoord = 1; xCoord < numOfColumns - 1; xCoord++) {
        for (int yCoord = 1; yCoord < numOfRows - 1; yCoord++) {
            if (grid[yCoord][xCoord] == "A") {
                int localCounter = 0;
                for (int xOffSet = -1; xOffSet <= 1; xOffSet += 2) {
                    for (int yOffSet = -1; yOffSet <= 1; yOffSet += 2) {
                        if (grid[yCoord + yOffSet][xCoord + xOffSet] == "M" && grid[yCoord + (yOffSet* -1)][xCoord + (xOffSet*-1)] == "S") {
                            localCounter++;
                        }
                    }
                }
                if (localCounter == 2) {
                    totalCounter++;
                }
            }
        }
    }

    return totalCounter;
}

int FindTotalNumberOfWords(const vector<vector<string>>& grid, const string& wordToFind) {
    int total = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {

                    if (i == 0 && j == 0) {
                        continue;
                    }

                    if (isWordFound(grid, wordToFind, x, y, i, j)) {
                        total++;
                    }
                }
            }
        }
    }

    return total;
}



int main()
{
    string fileName = "D:/Projects/AOC2024/Day4/data.txt";

    vector<vector<string>> grid = readAndSplitFile(fileName);
    cout << "Part 1: " << FindTotalNumberOfWords(grid, "XMAS") << endl;

    cout << "Part 2: " << FindTotalNumberOfXMas(grid) << endl;

    return 0;
}

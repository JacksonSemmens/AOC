// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include <stack>

vector<vector<int>> numLists;
unordered_map<int, unordered_set<int>> hashMap;

void readInFile(string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find('|') != string::npos) {
            stringstream ss(line);
            string keyStr, valueStr;

            getline(ss, keyStr, '|');
            getline(ss, valueStr);

            int key = stoi(keyStr);   
            int value = stoi(valueStr);

            hashMap[key].insert(value);
        }
        else {
            stringstream ss(line);
            string value;
            vector<int> row;

            while (getline(ss, value, ',')) {
                row.push_back(stoi(value));
            }

            numLists.push_back(row);
        }
    }

    file.close();
}

bool rowIsValid(vector<int> row) {
    bool result = false;
    for (int i = 1; i < row.size(); i++)
    {
        if (hashMap[row[i - 1]].find(row[i]) != hashMap[row[i - 1]].end()) {
            result = true;
        }
        else {
            result = false;
            break;
        }
    }
    return result;
}

bool rowIsSorted(vector<int> row) {
    bool result = false;
    for (int i = 1; i < row.size(); i++) {
        if (row[i - 1] > row[i]) {
            result = true;
        }
        else {
            result = false;
            break;
        }
    }
    return result;
}

int Part1() {
    int result = 0;
    for (int i = 0; i < numLists.size(); i++) {
        if (rowIsValid(numLists[i])) {
            int midNumber = numLists[i].size()/2;
            result += numLists[i][midNumber];
        }
    }
    return result;
}

bool dfs(int node, unordered_map<int, unordered_set<int>>& hashMap, unordered_map<int, int>& visitStatus, vector<int>& result, unordered_set<int>& inputSet) {
    if (inputSet.find(node) == inputSet.end()) {
        return true;
    }

    visitStatus[node] = 1;  

    for (const int& neighbor : hashMap[node]) {
        if (visitStatus[neighbor] == 0) {
            if (!dfs(neighbor, hashMap, visitStatus, result, inputSet)) {
                return false; 
            }
        }
        else if (visitStatus[neighbor] == 1) {
            return false;
        }
    }

    visitStatus[node] = 2; 
    result.push_back(node); 

    return true; 
}

vector<int> rowSorting(vector<int> inputRow) {
    unordered_map<int, int> visitStatus;  // 0: unvisited, 1: visiting, 2: visited
    vector<int> result;
    unordered_set<int> inputSet(inputRow.begin(), inputRow.end()); 

    for (int node : inputRow) {
        if (visitStatus[node] == 0) {
            if (!dfs(node, hashMap, visitStatus, result, inputSet)) {
                return {};
            }
        }
    }

    reverse(result.begin(), result.end());
    return result;
}


int Part2() {
    int result = 0;
    for (int i = 0; i < numLists.size(); i++) {
        if (numLists[i].size() > 0) {
            if (!rowIsValid(numLists[i])) {
                vector<int> sortedRow = rowSorting(numLists[i]);
               int midNumber = sortedRow.size() / 2;
                result += sortedRow[midNumber];
            } 
        }        
    }
    return result;
}


int main()
{
    string fileName = "D:/Projects/AOC2024/Day5/data.txt";
    readInFile(fileName);
    cout << "Part 1: " << Part1() << endl;
    cout << "Part 2: " << Part2() << endl;
}


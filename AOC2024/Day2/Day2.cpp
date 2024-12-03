// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<int>> parseInputFromLargeBuffer(const string& filename) {
    vector<vector<int>> result;

    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return result;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> buffer(fileSize);

    file.read(buffer.data(), fileSize);
    file.close();

    istringstream stream(string(buffer.begin(), buffer.end()));
    string line;

    while (getline(stream, line)) {
        vector<int> row;
        istringstream lineStream(line);
        string token;

        while (lineStream >> token) {
            row.push_back(stoi(token));
        }

        result.push_back(row);
    }

    return result;
}

bool isSafe(vector<int> dataRow) {
    bool result = true;
    for (int j = 0; j < dataRow.size() - 1; j++) {
        if ((abs(dataRow[j] - dataRow[j + 1]) > 3) || dataRow[j] == dataRow[j + 1]) {
            result = false;
        }
    }
    if (!(is_sorted(dataRow.begin(), dataRow.end()) || is_sorted(dataRow.begin(), dataRow.end(), greater<int>()))) {
        result = false;
    }
    return result;
}

bool checkEachPermutation(vector<int> dataRow) {
    bool result = false;
    for (size_t i = 0; i < dataRow.size(); ++i) {
        
        vector<int> modifiedVec = dataRow;
        modifiedVec.erase(modifiedVec.begin() + i);

        result = isSafe(modifiedVec);

        if (result) break;
    }
    return result;
}



int findSafeReports(string fileName) {
    int total=0;
    vector<vector<int>> data = parseInputFromLargeBuffer(fileName);

    for (int i = 0; i < data.size(); i++) {
        bool result = checkEachPermutation(data[i]);
        
        if (result) {
            total++;
        }
    }
    return total;
}

int main()
{
    string fileName = "D:/Projects/AOC2024/Day2/data.txt";
    int result = findSafeReports(fileName);
    cout << result;
}

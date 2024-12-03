// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <fstream>

vector<int> splitNumbers(string inputString, char delimiter) {
    vector<int> result;
    stringstream ss(inputString);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(stoi(token));
    }

    return result;
}

int splitStringRegex(string inputData) {
    int result = 0;
    regex pattern(R"(mul\((\d+(,\d+)*)\))");
    smatch match;

    string::const_iterator searchStart(inputData.cbegin());
    while (regex_search(searchStart, inputData.cend(), match, pattern)) {
        string numbersInside = match[1];

        vector<int> numbers = splitNumbers(numbersInside, ',');
        result += numbers[0] * numbers[1];
        
        searchStart = match.suffix().first;
    }

    return result;
}

string readFileToString(const string& filePath) {
    ifstream file(filePath);

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

string removeAllRangesBetweenKeywords(const string& input) {
    string start_keyword = "don't()";
    string end_keyword = "do()";

    size_t start_pos = input.find(start_keyword);

    if (start_pos == string::npos) {
        return input;
    }

    size_t end_pos = input.find(end_keyword, start_pos + start_keyword.length());

    if (end_pos == string::npos) {
        return input.substr(0, start_pos + start_keyword.length());
    }

    string before_range = input.substr(0, start_pos);

    string after_range = input.substr(end_pos + end_keyword.length());

    return before_range + removeAllRangesBetweenKeywords(after_range);
}

int main()
{
    string sampleData = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

    string fileName = "D:/Projects/AOC2024/Day3/data.txt";
    string inputData = readFileToString(fileName);

    string trimmedData = removeAllRangesBetweenKeywords(inputData);

    int Part1 = splitStringRegex(inputData);
    cout << "Part 1: " << Part1 << endl;


    int Part2 = splitStringRegex(trimmedData);
    cout << "Part 2: " << Part2 << endl;
}
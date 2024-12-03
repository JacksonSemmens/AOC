using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    istringstream ss(str);
    string item;

    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

int CalculateDistance(string inputString) {
        vector<string> splitResult = splitString(inputString, ' ');
        int totalDistance = 0;
        vector<int> firstList;
        vector<int> secondList;
        for (int i = 0; i < splitResult.size(); i += 2) {
            firstList.push_back(stoi(splitResult[i]));
            secondList.push_back(stoi(splitResult[i + 1]));
        }
        sort(firstList.begin(), firstList.end());
        sort(secondList.begin(), secondList.end());

        for (int i = 0; i < firstList.size(); i++) {
            totalDistance += abs(secondList[i] - firstList[i]);
        }
        return totalDistance;
}

int CalculateSimilarityScore(string inputString) {
    vector<string> splitResult = splitString(inputString, ' ');
    int totalSimilarity = 0;
    vector<int> firstList;
    vector<int> secondList;
    for (int i = 0; i < splitResult.size(); i += 2) {
        firstList.push_back(stoi(splitResult[i]));
        secondList.push_back(stoi(splitResult[i + 1]));
    }
    sort(firstList.begin(), firstList.end());
    sort(secondList.begin(), secondList.end());

    unordered_map<int, int> frequencyMap;
    for (int num : secondList) {
        frequencyMap[num]++;
    }

    for (int i = 0; i < firstList.size(); i++) {
        totalSimilarity += firstList[i] * frequencyMap[firstList[i]];
    }

    return totalSimilarity;
}
 
int main()
{
    string sampleString = "3 4 4 3 2 5 1 3 3 9 3 3";
    int resultDistance = CalculateDistance(sampleString);
    int resultSimilarity = CalculateSimilarityScore(sampleString);

    cout << "Part 1: " << endl;
    cout << "Total Distance: " <<  resultDistance << endl;

    cout << "Part 2: " << endl;
    cout << "Total Similarity: " << resultSimilarity << endl;

}


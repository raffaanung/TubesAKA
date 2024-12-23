#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>

using namespace std;
using namespace std::chrono;

// Sample distance matrix for 7 cities
const vector<vector<int>> distanceMatrix = {
    {0, 10, 15, 20, 25, 30, 35},
    {10, 0, 35, 25, 30, 40, 45},
    {15, 35, 0, 30, 20, 25, 50},
    {20, 25, 30, 0, 15, 35, 40},
    {25, 30, 20, 15, 0, 10, 25},
    {30, 40, 25, 35, 10, 0, 20},
    {35, 45, 50, 40, 25, 20, 0}
};

const int N = distanceMatrix.size(); // Number of cities

// Recursive approach
int tspRecursive(vector<bool> &visited, int currentCity, int count, int cost, int &minCost, vector<int> &currentPath, vector<int> &bestPath) {
    if (count == N && distanceMatrix[currentCity][0]) {
        if (cost + distanceMatrix[currentCity][0] < minCost) {
            minCost = cost + distanceMatrix[currentCity][0];
            bestPath = currentPath;
            bestPath.push_back(0);
        }
        return minCost;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && distanceMatrix[currentCity][i]) {
            visited[i] = true;
            currentPath.push_back(i);
            tspRecursive(visited, i, count + 1, cost + distanceMatrix[currentCity][i], minCost, currentPath, bestPath);
            currentPath.pop_back();
            visited[i] = false;
        }
    }
    return minCost;
}

// Iterative approach
int tspIterative(vector<int> &bestPath) {
    vector<int> cities;
    for (int i = 1; i < N; i++) cities.push_back(i);

    int minCost = INT_MAX;
    do {
        int currentCost = 0;
        int currentCity = 0;

        for (int city : cities) {
            currentCost += distanceMatrix[currentCity][city];
            currentCity = city;
        }
        currentCost += distanceMatrix[currentCity][0];
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = {0};
            bestPath.insert(bestPath.end(), cities.begin(), cities.end());
            bestPath.push_back(0);
        }
    } while (next_permutation(cities.begin(), cities.end()));

    return minCost;
}

int main() {
    const int iterations = 1000; // Number of iterations for better timing accuracy

    // Recursive approach
    vector<bool> visited(N, false);
    visited[0] = true;
    int minCostRecursive = INT_MAX;
    vector<int> currentPath = {0};
    vector<int> bestPathRecursive;

    auto startRecursive = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        tspRecursive(visited, 0, 1, 0, minCostRecursive, currentPath, bestPathRecursive);
    }
    auto endRecursive = high_resolution_clock::now();

    auto durationRecursive = duration_cast<microseconds>(endRecursive - startRecursive);
    cout << "=== Recursive Approach ===\n";
    cout << "Minimum Cost: " << minCostRecursive << "\n";
    cout << "Optimal Path: ";
    for (int city : bestPathRecursive) cout << city << " -> ";
    cout << "END\n";
    cout << "Execution Time (average): " << durationRecursive.count() / iterations << " microseconds\n\n";

    // Iterative approach
    vector<int> bestPathIterative;
    auto startIterative = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        tspIterative(bestPathIterative);
    }
    auto endIterative = high_resolution_clock::now();

    auto durationIterative = duration_cast<microseconds>(endIterative - startIterative);
    cout << "=== Iterative Approach ===\n";
    cout << "Minimum Cost: " << tspIterative(bestPathIterative) << "\n";
    cout << "Optimal Path: ";
    for (int city : bestPathIterative) cout << city << " -> ";
    cout << "END\n";
    cout << "Execution Time (average): " << durationIterative.count() / iterations << " microseconds\n";

    return 0;
}

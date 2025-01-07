#include <bits/stdc++.h>
using namespace std;

// assumption: there is no negative weight road/city
// assumption: there is no self loop [CITY_A -> CITY_A is not present in the graph]
// assumption: there is no repeating road in input

struct City {
    string name;
    int visitCost;
    int reward;
};

unordered_map<string, vector<pair<string, int>>> graph;
unordered_map<string, City> cityDetails;

// to handle cycles
unordered_map<string, unordered_map<int, int>> visited;

// call: dfs(origin, destination, pointsAvailable, cityDetails[origin].reward - cityDetails[origin].visitCost, maxReward, visited);
// void dfs(const string &cur, const string &dest, int remPoints, int curReward, int &maxReward, unordered_map<string, bool> &visited) {
//     if (remPoints < 0) return; // prune paths exceeding cost
//     if (cur == dest) {
//         maxReward = max(maxReward, curReward);
//         return;
//     }
//     visited[cur] = true;
//     for (auto &[nextCity, travelCost] : graph[cur]) {
//         if (!visited[nextCity]) {
//             int newPoints = remPoints - travelCost - cityDetails[nextCity].visitCost;
//             dfs(nextCity, dest, newPoints, curReward + cityDetails[nextCity].reward, maxReward, visited);
//         }
//     }
//     visited[cur] = false; // backtrack
// }

pair<int,string> calcMaxReward(string& origin, string& dest, int pointsAvl) {

    // priority queue [max elems stay up, acc to reward]: {reward, city, remaining points}
    priority_queue<tuple<int, string, int ,string>> pq;

    int initialPoints = pointsAvl - cityDetails[origin].visitCost;
    if (initialPoints < 0) return {0,""};
    pq.push({cityDetails[origin].reward, origin, initialPoints, cityDetails[origin].name});

    int maxReward = 0;
    string finalPath;

    while(!pq.empty()) {
        auto [currentReward, currentCity, remainingPoints, curPath] = pq.top();
        pq.pop();

        // for checking q state
        // cout << currentReward << ' ' << currentCity << ' ' << remainingPoints << endl;

        // skip if weve already visited this city with equal or more remaining points
        if (visited[currentCity].count(remainingPoints) &&
            visited[currentCity][remainingPoints] >= currentReward) {
            continue;
        }
        visited[currentCity][remainingPoints] = currentReward;

        if (currentCity == dest && maxReward < currentReward) {
            maxReward = currentReward;
            finalPath = curPath;
        }

        // explore neighbors
        for (auto &[nextCity, travelCost] : graph[currentCity]) {
            int nextCityCost = travelCost + cityDetails[nextCity].visitCost;
            if (remainingPoints == INT_MIN) continue;
            if (remainingPoints >= nextCityCost) {
                // we can reach next city and spend time in it
                pq.push({
                    currentReward + cityDetails[nextCity].reward,
                    nextCity,
                    remainingPoints - nextCityCost,
                    curPath + "->" + cityDetails[nextCity].name
                });
            } else {
                // we can reah next city but cannot spend time in it --> make points negative so it prunes further calc
                pq.push({
                    currentReward,
                    nextCity,
                    INT_MIN,
                    curPath + "->" + cityDetails[nextCity].name
                });
            }
        }
    }

    return {maxReward, finalPath};

}

int main() {
/*
sample ip:
4
CITY_A 300 1000
CITY_B 500 900
CITY_C 250 1500
CITY_D 100 600
3
CITY_A CITY_B 250
CITY_A CITY_D 300
CITY_B CITY_C 500
1
CITY_A CITY_B 700
*/

/*
sample op:
1000
*/


    int n,t,showPath(0);
    string t1,t2;

    cin >> n;
    for(int i=n;i;i--){
        cin >> t1 >> n >> t;
        cityDetails[t1] = {t1,n,t};
    }

    cin >> n;
    for(int i=n;i;i--){
        cin >> t1 >> t2 >> t;
        graph[t1].push_back({t2,t});
    }

    cin >> n;
    // showPath = 1;
    for(int i=n;i;i--){
        cin >> t1 >> t2 >> t;

        auto [reward,path] = calcMaxReward(t1,t2,t);

        if(showPath){
            if(path!="")
                cout << reward << ":" << path << endl;
            else
                cout << reward << endl;
        } else {
            cout << reward << endl;
        }
    }

    return 0;
}

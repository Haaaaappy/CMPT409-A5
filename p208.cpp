#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int StreetNum = 21;
const int FireStation = 1;
vector<int> path;

bool isConnected(int vertex, vector<vector<int> > adjList, vector<bool> visit, int dest){
    vector<bool> used(StreetNum); 
    vector<int> queue;
    if(vertex == dest) return true;
    used[vertex] = true;
    queue.push_back(vertex);
    while(!queue.empty()){
        int v = queue.front();
        queue.erase(queue.begin());
        for(int i=0; i < adjList[v].size(); i++){
            if(adjList[v][i] == dest) return true;
            if(!visit[adjList[v][i]] && !used[adjList[v][i]]){
                queue.push_back(adjList[v][i]);
                used[adjList[v][i]] = true;
            }
        }
    }
    return false;
}

void findPath(vector<vector<int> >& adjList, vector<bool>& visit, int dest, int& count, int vertex){
    if(vertex == dest){
        count++;
        cout << FireStation;
        for(int i = 0; i < path.size(); i++){
            cout << " "<< path[i]; 
        }
        cout << endl;
        return;
    }
    for(int i = 0; i < adjList[vertex].size(); i++){
        if(!isConnected(adjList[vertex][i],adjList,visit,dest)) continue;
        if(!visit[adjList[vertex][i]]){
            visit[adjList[vertex][i]] = true;
            path.push_back(adjList[vertex][i]);
            findPath(adjList,visit, dest, count, adjList[vertex][i]);
            path.pop_back();
            visit[adjList[vertex][i]] = false;
        }
    }
    return;
}


int main(){
    int dest;
    int caseNum = 0;
    while(cin >> dest && dest){
        caseNum ++;
        vector<vector<int> > adjList(StreetNum, vector<int>(StreetNum));
        vector<bool> visit(StreetNum);
        int ps, pe;
        while(cin >> ps >> pe && ps && pe){
            adjList[ps].push_back(pe);
            adjList[pe].push_back(ps);
        }
        for(int i = 0 ; i < adjList.size(); i++){
            sort(adjList[i].begin(), adjList[i].end());
        }
        int count = 0;
        visit[FireStation] = true;
        cout << "CASE " << caseNum << ":" << endl;
        findPath(adjList, visit, dest, count, FireStation);
        cout << "There are " << count << " routes from the firestation to streetcorner " << dest << "." << endl;
        path.clear();
    }
}
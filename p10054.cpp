#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> path;
const int ColorNum = 51;

void removeEdge(int v, int u, vector<vector<int> >& adjList){
    vector<int>::iterator iv = find(adjList[v].begin(), adjList[v].end(), u);
    adjList[v].erase(iv);
    vector<int>::iterator iu = find(adjList[u].begin(), adjList[u].end(), v);
    adjList[u].erase(iu);
}

bool isConnected(int v,vector<vector<int> >& adjList){
    vector<bool> used(ColorNum); 
    vector<int> queue;
    int count = 0; 
    used[v] = true;
    queue.push_back(v);
    while(!queue.empty()){
        int tmpv = queue.front();
        queue.erase(queue.begin());
        for(int i=0; i < adjList[tmpv].size(); i++){
            if(!used[adjList[tmpv][i]]){
                queue.push_back(adjList[tmpv][i]);
                used[adjList[tmpv][i]] = true;
                count++;
            }
        }
    }
    int countVertex = 0;
    for(int i = 1; i < ColorNum; i++){
        if(!adjList[i].empty()){
            countVertex++;
        }
    }
    return count == (countVertex-1);
}

void findEulerCircle(int v, vector<vector<int> >& adjList){
    while( adjList[v].size() > 0){
        int edge = adjList[v].front();
        removeEdge(v, edge, adjList);
        findEulerCircle(edge, adjList);
    }
    path.push_back(v);
}

int main(){
    int t;
    cin >> t;
    int caseNum;
    for(caseNum = 0; caseNum < t; caseNum++){
        int N;
        cin >> N;
        int c1, c2;
        int flag = 0;
        int s = 0;
        vector<vector<int> > adjList(ColorNum,vector<int>());
        for(int i = 0; i < N; i++){
            cin >> c1 >> c2;
            adjList[c1].push_back(c2);
            adjList[c2].push_back(c1);
            if(i == 0) s = c1;
        }
        cout << "Case #" << caseNum+1 << endl;
        for(int i = 1; i < ColorNum; i++){
            if(adjList[i].size() & 1){
                cout << "some beads may be lost" << endl;
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            path.clear();
            if(caseNum < t-1) cout << endl;
            continue;
        }

        if(!isConnected(c1, adjList)){
            cout << "some beads may be lost" << endl;
            path.clear();
            continue;
        }
        findEulerCircle(s, adjList);
        for(int i = 0; i < path.size()-1; i++){
            cout << path[i] << " " << path[i+1] << endl;
        }
        if(caseNum < t-1) cout << endl;
        path.clear();
    }
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string> 
#include <array>

using namespace std;

int ans ,ansEnd; 
char mazeMap[20][20];
vector<pair<int,int> > boxPerson; 
int emptydegree;
vector<string> walkPath;
int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
char mapDir[4] = {'N', 'E', 'S', 'W'};
char mapdir[4] = {'n', 'e', 's', 'w'};
struct Point{
   int x;  
   int y;  
   int pre;
   int d;
   int personX;
   int personY;  
   int step;
   int total;
   int walk; 
};
struct Point p[40000];
struct Point person[40000];

string personPath( char mazeMap[20][20], int r, int c, int sx, int sy, int ex, int ey ){ 
    string result;
    result.append("A");
    int front , rear;
    int last, shortestNum;  
    front = 0 , rear = 1; 
    int visited[20][20];
    memset(visited , 0 , sizeof(visited)); 
    memset(person, 0, sizeof(person));
    person[front].x = sx , person[front].y = sy;  
    person[front].pre = 0 , person[front].step = 0;  
    visited[sx][sy] = 1;
    while(front < rear){  
       Point tmp = person[front]; 
       if(tmp.x == ex && tmp.y == ey){  
            last = front; 
            shortestNum = tmp.step;  
            int x = last;
            result.clear();
            while(shortestNum > 0){
                shortestNum--;
                if(person[x].d==0)  result.append("n");
                if(person[x].d==1)  result.append("e");
                if(person[x].d==2)  result.append("s");
                if(person[x].d==3)  result.append("w");
                x = person[x].pre;
            }
            break;
        }  
        front++;
        for(int i = 0 ; i < 4 ; i++){
            int tempX = tmp.x+dir[i][0];
            int tempY = tmp.y+dir[i][1];

            if(tempX < 0 || tempX >= r)  
                continue;  
            if(tempY < 0 || tempY >= c)  
                continue;  
            if( visited[tempX][tempY] || mazeMap[tempX][tempY]=='#' )
                continue;  
            visited[tempX][tempY] = 1;  
            person[rear].x = tempX , person[rear].y = tempY;  
            person[rear].pre = front-1; 
            person[rear].d = i;
            person[rear++].step = tmp.step+1; 
        }  
    }
    reverse(result.begin(),result.end());
    return result;
}


void output(int x){  
    if(x == 0) 
      return;  
    output(p[x].pre);
    cout << walkPath[p[x].walk];
    printf("%c" , mapDir[p[x].d]); 
}

void BoxPath( char mazeMap[20][20], int r, int c, int startX, int startY, int boxX, int boxY, int targetX, int targetY ){
    walkPath.clear();
    int walkPathPos = -1;
    int currentIt = 0;
    int found = 0;
    int shortestTotal = 0;
    int front , rear;  
    front = 0 , rear = 1;
    ansEnd = 0;
    ans = 0;
    int visited[20][20];
    memset(p, 0, sizeof(p));
    memset(visited, 0, sizeof(visited));
    p[front].x = boxX, p[front].y = boxY;
    p[front].pre = 0 , p[front].step = 0;
    p[front].total = 0;
    p[front].personX= startX, p[front].personY=startY;
    visited[boxX][boxY] = 1;
    while(front < rear){  
        Point tmp = p[front];
        if(tmp.step!=p[front-1].step){
            currentIt=0;
        }else{
            currentIt++;
        }
        if( tmp.x == targetX && tmp.y == targetY){  
            if(found == 0){
                ansEnd = front;  
                ans = tmp.step;  
                shortestTotal = tmp.total;
            } 
            found = 1;
            if( shortestTotal > tmp.total ){
                ansEnd = front; 
                ans = tmp.step; 
                shortestTotal = tmp.total;
            }
            front++;
            continue;  
        }  
        front++;
        for(int i = 0 ; i < 4 ; i++){
            char recType;
            int tempX = tmp.x+dir[i][0];
            int tempOppX = tmp.x-dir[i][0];
            int tempY = tmp.y+dir[i][1];
            int tempOppY = tmp.y-dir[i][1];
            if(tempX < 0 || tempX >= r || tempOppX < 0 || tempOppX >= r)  
                continue;
            if(tempY < 0 || tempY >= c || tempOppY < 0 || tempOppY >= c )  
                continue;
            if( visited[tempX][tempY]== 1 || mazeMap[tempX][tempY]=='#' || mazeMap[tempOppX][tempOppY]=='#')  
                continue;
            recType = mazeMap[tmp.x][tmp.y];
            mazeMap[tmp.x][tmp.y] = '#';
            string ttt = personPath(mazeMap,r,c,tmp.personX,tmp.personY,tempOppX,tempOppY);

            if( (tmp.personX != tempOppX || tmp.personY != tempOppY) && ttt == "A" )
                { mazeMap[tmp.x][tmp.y] = recType; continue;}
            pair<int,int> tempPair = make_pair(tmp.x*20+tmp.y,tempOppX*20+tempOppY);
            if( boxPerson.end() - find(boxPerson.begin(), boxPerson.end() ,tempPair) > currentIt ){
                mazeMap[tmp.x][tmp.y] = recType; 
                continue;
            }

            boxPerson.push_back(tempPair);
            walkPathPos++;
            walkPath.push_back(ttt);
            p[rear].total = tmp.total + ttt.length();
            mazeMap[tmp.x][tmp.y] = recType;
            p[rear].walk = walkPathPos; 
            visited[tempX][tempY] = 1; 
            p[rear].personX = tmp.x, p[rear].personY = tmp.y;  
            p[rear].x = tempX , p[rear].y = tempY;  
            p[rear].pre = front-1;
            p[rear].d = i; 
            p[rear++].step = tmp.step+1;
        }  
    }
    if(found == 0) 
        cout << "Impossible.";
}


int main(){
    int r, c;
    int mazeNum = 1;
    int boxX, boxY;
    int startX, startY;
    int targetX, targetY;
    cin >> r >> c;
    while( r != 0 && c!= 0 ){
        boxPerson.clear();
        emptydegree = 0;
        cout << "Maze #" << mazeNum << endl;
        for( int i = 0; i < r; i++ ){
            for( int j = 0; j < c; j++ ){
                cin >> mazeMap[i][j];
                if( mazeMap[i][j] == 'B'){
                    boxX = i;
                    boxY = j;
                } else if( mazeMap[i][j] == 'S' ){
                    startX = i;
                    startY = j;
                } else if( mazeMap[i][j] == 'T' ){
                    targetX = i;
                    targetY = j;
                }
            }
        }
        BoxPath( mazeMap, r, c, startX, startY, boxX, boxY, targetX, targetY ); 
        output(ansEnd); 
        cout << endl; 
        cout << endl; 
        mazeNum++;
        cin >> r >> c;
    }
    return 0;
}

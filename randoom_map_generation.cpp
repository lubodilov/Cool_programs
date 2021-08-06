#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int Size= 50;
bool maze[Size][Size];
unsigned long long put[100][100];


void print()
{
 for(int x=0; x<Size; ++x)
 {
    for(int y=0; y<Size; ++y)
    {
       cout << (maze[x][y]?' ':char(177));
       cout << (maze[x][y]?' ':char(177));

    }
    cout << endl;
 }
}
int brsyseda(int x, int y)
{
   int result=0;
   if(x>0){result += maze[x-1][y];}
   if(y>0){result += maze[x][y-1];}
   if(x<Size-1){result += maze[x+1][y];}
   if(y<Size-1){result += maze[x][y+1];}
   return result;
}
bool stavalizaprodylvenie(int x, int y)
{
   return x>=0 and y>=0 and x<Size and y<Size and brsyseda(x, y) <= 1 and !maze[x][y];
}
void dfs(int x, int y)
{
    if(maze[x][y])
    {
       return;
    }
    else{maze[x][y]=true;}
   int vx[4], vy[4];
   int vsize=101;
   while(vsize!=0)
   {
      vsize=0;
      if(stavalizaprodylvenie(x+1, y))
      {
         vx[vsize] = x+1;
         vy[vsize] = y;
         vsize++;
      }
      if(stavalizaprodylvenie(x-1, y))
      {
         vx[vsize] = x-1;
         vy[vsize] = y;
         vsize++;
      }
      if(stavalizaprodylvenie(x, y+1))
      {
         vx[vsize] = x;
         vy[vsize] = y+1;
         vsize++;
      }
      if(stavalizaprodylvenie(x, y-1))
      {
         vx[vsize] = x;
         vy[vsize] = y-1;
         vsize++;
      }
      if(vsize==0) {return;}
      else
      {
          int randindex=rand()%vsize;
          dfs(vx[randindex], vy[randindex]);
      }
   }


}
void bfs(pair<int, int> start)
{
   queue <pair<int, int>> nodes;
   pair<int, int> curr, next;
   nodes.push(start);
   put[start.first][start.second]=0;
   while(!nodes.empty())
   {
      curr=nodes.front();
      nodes.pop();
      for(int i=0; i<brsyseda(curr.first, curr.second); ++i)
      {
         if(maze[curr.first+1][curr.second]==true and put[curr.first+1][curr.second]==-1)
         {
            next.first=curr.first+1;
            next.second=curr.second;
            put[next.first][next.second]=put[curr.first][curr.second]+1;
            nodes.push(next);
         }
         if(maze[curr.first-1][curr.second]==true and put[curr.first-1][curr.second]==-1)
         {
            next.first=curr.first-1;
            next.second=curr.second;
            put[next.first][next.second]=put[curr.first][curr.second]+1;
            nodes.push(next);
         }
         if(maze[curr.first][curr.second+1]==true and put[curr.first][curr.second+1]==-1)
         {
            next.first=curr.first;
            next.second=curr.second+1;
            put[next.first][next.second]=put[curr.first][curr.second]+1;
            nodes.push(next);
         }
         if(maze[curr.first][curr.second-1]==true and put[curr.first][curr.second-1]==-1)
         {
            next.first=curr.first;
            next.second=curr.second-1;
            put[next.first][next.second]=put[curr.first][curr.second]+1;
            nodes.push(next);
         }
      }
   }

}

int main () {
   srand(time(NULL));
   for(int i=0; i<80; ++i)
   {
      for(int j=0; j<80; ++j)
         put[i][j]=-1;
      {
      }
   }
   dfs(5, 5);
   print();
   bfs(make_pair(5, 5));
   cout << "\n" << "\n";
   for(int x=0; x<Size; ++x)
   {
      for(int y=0; y<Size; ++y)
      {
         if(maze[x][y])
         {
            cout << x << " " << y << " -> " << put[x][y] << endl;
         }
      }
   }

return 0;
}


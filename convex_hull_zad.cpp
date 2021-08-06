#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
    double x;
    double y;
    point operator - (point a){
        return {x-a.x, y-a.y};
    }
    double operator * (point a){
        return {x*a.y - y*a.x};
    }
};

int n=0;
point p[100200];
vector<int> hull;

bool cmp(point a, point b){
    return (a-p[0])*(b-p[0])>0;
}

int main(){
    double lice=0;
    while(cin>>p[n].x>>p[n].y){
        if (p[n].y < p[0].y) swap(p[n], p[0]);
	n++;
    }
    sort(p+1, p+n, cmp);
    hull.push_back(0);
    hull.push_back(1);
    for(int i=2; i<n; ++i){
        while((p[hull[hull.size()-1]]-p[hull[hull.size()-2]]) *
              (p[i]-p[hull[hull.size()-2]]) < 0) hull.pop_back();
        hull.push_back(i);
    }
    for (int i=1; i<hull.size(); ++i){
        lice+=(p[hull[i-1]]-p[0])*(p[hull[i]]-p[0]);
        ///cout << p[hull[i]].x << " " << p[hull[i]].y << "\n";
    }
    cout << lice/2;
    return 0;
}

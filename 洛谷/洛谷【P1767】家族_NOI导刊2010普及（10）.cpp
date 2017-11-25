/*
// dfs 0ms , 2484kb
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

#define MAXN 110
#define MAXM 210

int G[MAXN][MAXM];
int cnt[MAXN];

const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};

int n;

void dfs(int x,int y) {
    for(int i=0;i<4;i++) {
        int p=x+dx[i],q=y+dy[i];
        if(p>=0&&p<n&&q>=0&&q<cnt[p]&&G[p][q]) {
            G[p][q]=0;
            dfs(p,q);
        }
    }
    return;
}

int main() {
    string ss;
    cin>>n;
    getline(cin,ss);
    for(int i=0;i<n;i++) {
        getline(cin,ss);
        cnt[i]=ss.size();
        for(int j=0;j<cnt[i];j++)
            if(ss[j]>='a'&&ss[j]<='z') G[i][j]=1;
    }
    int ans=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<cnt[i];j++)
            if(G[i][j]) {
                ans++;
                G[i][j]=0;
                dfs(i,j);
            }
    printf("%d",ans);
    return 0;
}
*/

// bfs 0ms , 2347kb
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

#define MAXN 110
#define MAXM 210

int G[MAXN][MAXM];
int cnt[MAXN];

const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};

struct Point {
    int x,y;
    Point(int x=0,int y=0):
        x(x),y(y) {}
};

int n;
queue<Point>q;

#define G(_) G[_.x][_.y]

void bfs(int x,int y) {
    q.push(Point(x,y));
    G[x][y]=0;
    while(!q.empty()) {
        Point u=q.front();
        q.pop();
        for(int i=0;i<4;i++) {
            Point v=Point(u.x+dx[i],u.y+dy[i]);
            if(v.x>=0&&v.x<n&&v.y>=0&&v.y<cnt[v.x]&&G(v)) {
                q.push(v);
                G(v)=0;
            }
        }
    }
    return;
}


int main() {
    string ss;
    cin>>n;
    getline(cin,ss);
    for(int i=0;i<n;i++) {
        getline(cin,ss);
        cnt[i]=ss.size();
        for(int j=0;j<cnt[i];j++)
            if(ss[j]>='a'&&ss[j]<='z') G[i][j]=1;
    }
    int ans=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<cnt[i];j++)
            if(G[i][j]) {
                ans++;
                bfs(i,j);
            }
    printf("%d",ans);
    return 0;
}
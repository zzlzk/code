#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<48||c>57;c=getchar())
        if(c==45) a=-1;
    for(;c>=48&&c<=57;c=getchar())
        x=x*10+c-48;
    x*=a;
    return;
}

#define MAXN 25
#define MAXM 110

struct Patch {
    int t;
    int b1,b2;
    int f1,f2;
    Patch(): t(0),b1(0),b2(0),f1(0),f2(0) {}
};

Patch p[MAXM];

char s[MAXN];

int n,m;
queue<int> q;
int dis[(1<<20)+10];
bool inq[(1<<20)+10];

#define inf 2147483647

int spfa() {
    for(int i=0;i<=(1<<n)-1;i++)
        dis[i]=inf;
    dis[(1<<n)-1]=0,q.push((1<<n)-1),inq[(1<<n)-1]=true;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=1,v;i<=m;i++)
            if(!(u&p[i].b2)&&(u|p[i].b1)==u) {
                v=(u&(~p[i].f1))|p[i].f2;
                if(dis[u]+p[i].t<dis[v]) {
                    dis[v]=dis[u]+p[i].t;
                    if(!inq[v]) {
                        q.push(v);
                        inq[v]=true;
                    }
                }
            }
    }
    return dis[0]==inf?0:dis[0];
}

int main() {
    input(n),input(m);
    for(int i=1;i<=m;i++) {
        input(p[i].t),scanf("%s",s);
        for(int j=0;j<n;j++)
            if(s[j]=='-') p[i].b2|=1<<j;
            else if(s[j]=='+') p[i].b1|=1<<j;
        scanf("%s",s);
        for(int j=0;j<n;j++)
            if(s[j]=='-') p[i].f1|=1<<j;
            else if(s[j]=='+') p[i].f2|=1<<j;
    }
    printf("%d\n",spfa());
    return 0;
}

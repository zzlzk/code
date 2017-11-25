#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 2010
#define MAXV 310
#define inf 0x7fffffff

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

int c[MAXN],d[MAXN];
double k[MAXN],f[MAXN][MAXN][2];
double dis[MAXV][MAXV];

int main() {
    int n,m,v,e;
    input(n),input(m),input(v),input(e);
    for(int i=1;i<=n;i++)
        input(c[i]);
    for(int i=1;i<=n;i++)
        input(d[i]);
    for(int i=1;i<=n;i++)
        scanf("%lf",&k[i]);
    for(int i=0;i<MAXV;i++)
        for(int j=0;j<MAXV;j++)
            if(i==j) dis[i][j]=0;
            else dis[i][j]=inf;
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXN;j++)
            f[i][j][0]=f[i][j][1]=inf;
    f[1][0][0]=0,f[1][1][1]=0;
    for(int i=1;i<=e;i++) {
        int U,V,W;
        input(U),input(V),input(W);
        if(W<dis[U][V]) dis[U][V]=dis[V][U]=W;
    }
    for(int kk=1;kk<=v;kk++)
        for(int i=1;i<=v;i++)
            for(int j=1;j<=v;j++)
                dis[i][j]=min(dis[i][j],dis[i][kk]+dis[kk][j]);
    for(int i=2;i<=n;i++) {
        f[i][0][0]=f[i-1][0][0]+dis[c[i-1]][c[i]];
        for(int j=1;j<=min(i,m);j++) {
            f[i][j][0]=min(f[i-1][j][0]+dis[c[i-1]][c[i]],f[i-1][j][1]+(1-k[i-1])*dis[c[i-1]][c[i]]+k[i-1]*dis[d[i-1]][c[i]]);
            f[i][j][1]=min(f[i-1][j-1][0]+k[i]*dis[c[i-1]][d[i]]+(1-k[i])*dis[c[i-1]][c[i]],f[i-1][j-1][1]+k[i-1]*k[i]*dis[d[i-1]][d[i]]+(1-k[i-1])*k[i]*dis[c[i-1]][d[i]]+k[i-1]*(1-k[i])*dis[d[i-1]][c[i]]+(1-k[i-1])*(1-k[i])*dis[c[i-1]][c[i]]);
        }
    }
    double ans=f[n][0][0];
    for(int i=1;i<=m;i++)
        ans=min(ans,min(f[n][i][0],f[n][i][1]));
    printf("%.2lf",ans);
    return 0;
}

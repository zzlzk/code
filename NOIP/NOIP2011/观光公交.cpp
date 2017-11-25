#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 300010

struct Person {
    int Time,u,v;
    Person(int Time=0,int u=0,int v=0):
        Time(Time),u(u),v(v) {}
}peo[maxn];
int d[maxn],last[maxn],Time[maxn],sum[maxn],f[maxn];

int main() {
    int n,m,k,ans=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<n;i++)
        scanf("%d",&d[i]);
    for(int i=1;i<=m;i++) {
        int u,v,t;
        scanf("%d%d%d",&t,&u,&v);
        peo[i]=Person(t,u,v);
        last[u]=max(last[u],t);
        sum[v]++;
    }
    for(int i=2;i<=n;i++) sum[i]+=sum[i-1];
    Time[1]=0;
    for(int i=2;i<=n;i++)
        Time[i]=max(Time[i-1],last[i-1])+d[i-1];
    for(int i=1;i<=m;i++)
        ans+=Time[peo[i].v]-peo[i].Time;
    while(k) {
        f[n]=f[n-1]=n;
        for(int i=n-2;i;i--)
            if(Time[i+1]<=last[i+1]) f[i]=i+1;
            else f[i]=f[i+1];
        int Max=0,id=0;
        for(int i=1;i<=n;i++)
            if(sum[f[i]]-sum[i]>Max&&d[i])
                Max=sum[f[i]]-sum[id=i];
        if(Max==0) break;
        k--;
        ans-=Max;
        d[id]--;
        Time[1]=0;
        for(int i=2;i<=n;i++)
            Time[i]=max(Time[i-1],last[i-1])+d[i-1];
    }
    printf("%d",ans);
    return 0;
}
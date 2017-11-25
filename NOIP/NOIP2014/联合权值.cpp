#include<cstdio>
#include<iostream>
using namespace std;
#define MAXN 200010
#define mod 10007

int w[MAXN],wsum[MAXN],x[MAXN],y[MAXN],maxw[MAXN];

int main() {
    int n,ans1=0,ans2=0;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    for(int i=1;i<n;i++) {
        int a=x[i],b=y[i];
        ans2=(ans2+w[a]*wsum[b]+w[b]*wsum[a])%mod;
        wsum[a]=(wsum[a]+w[b])%mod;
        wsum[b]=(wsum[b]+w[a])%mod;
        ans1=max(ans1,max(w[a]*maxw[b],w[b]*maxw[a]));
        if(w[a]>maxw[b])maxw[b]=w[a];
        if(w[b]>maxw[a])maxw[a]=w[b];
    }
    printf("%d %d\n",ans1,ans2*2%mod);
    return 0;
}
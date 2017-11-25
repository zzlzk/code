#include<bits/stdc++.h>
using namespace std;
#define MAXN 10005
#define MAXM 1005
#define inf 0x3f3f3f

int f[MAXN][MAXM];
int x[MAXN],y[MAXN],l[MAXN],h[MAXN];

int main() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;i++) {
        scanf("%d%d",&x[i],&y[i]);
        h[i]=m+1;l[i]=0;
    }
    h[n]=m+1,l[n]=0,f[0][0]=inf;
    for(int i=1;i<=k;i++) {
        int P,L,H;
        scanf("%d%d%d",&P,&L,&H);
        l[P]=L,h[P]=H;
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++) f[i][j]=inf;
    for(int i=1;i<=n;i++) {
        for(int j=x[i-1];j<=m;j++) {
            f[i][j]=min(f[i][j],f[i-1][j-x[i-1]]+1);
            f[i][j]=min(f[i][j],f[i][j-x[i-1]]+1);
        }
        for(int j=m-x[i-1];j<=m;j++) {
            f[i][m]=min(f[i][m],f[i-1][j]+1);
            f[i][m]=min(f[i][m],f[i][j]+1);
        }
        for(int j=l[i]+1;j<=h[i]-1;j++)
            if(j+y[i-1]<=m)
                f[i][j]=min(f[i][j],f[i-1][j+y[i-1]]);
        for(int j=1;j<=l[i];j++) f[i][j]=inf;
        for(int j=h[i];j<=m;j++) f[i][j]=inf;
    }
    int ans=inf,cnt=k;
    for(int i=n;i>=1;i--) {
        for(int j=l[i]+1;j<=h[i]-1;j++)
            ans=min(ans,f[i][j]);
        if(ans!=inf) break;
        if(h[i]!=m+1) cnt--;
    }
    if(cnt==k) printf("1\n%d",ans);
    else printf("0\n%d",cnt);
    return 0;
}
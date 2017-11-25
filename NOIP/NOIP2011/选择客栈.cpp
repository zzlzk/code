#include<cstdio>
using namespace std;
#define maxn 200010
#define maxk 55

int sum[maxk],last[maxk],can[maxk];

int main() {
    int n,k,p,x=0,ans=0;
    scanf("%d%d%d",&n,&k,&p);
    for(int i=1;i<=n;i++) {
        int color,cost;
        scanf("%d%d",&color,&cost);
        if(cost<=p) x=i;
        if(x>=last[color])
            can[color]=sum[color];
        ans+=can[color];
        sum[color]++;
        last[color]=i; 
    }
    printf("%d",ans);
    return 0;
}
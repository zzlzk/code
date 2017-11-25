#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const double eps=1e-10;
#define MAXN 25
#define inf 0x3f

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

int dp[(1<<20)+10],f[MAXN][MAXN];
double x[MAXN],y[MAXN];

int main() {
    int T;
    input(T);
    while(T--) {
        memset(f,0,sizeof(f));
        memset(dp,0x3f,sizeof(dp));
        int n,useless;
        input(n),input(useless);
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&x[i],&y[i]);
        double a,b;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++) {
                a=(y[j]*x[i]-y[i]*x[j])/((x[j]-x[i])*x[j]*x[i]);
                b=(y[j]*x[i]*x[i]-y[i]*x[j]*x[j])/((x[i]-x[j])*x[i]*x[j]);
                if(a>=-eps) continue;
                for(int k=i;k<n;k++)
                    if(fabs(a*x[k]*x[k]+b*x[k]-y[k])<=eps)
                        f[i][j]|=1<<k;
            }
        dp[0]=0;
        for(int s=0;s<(1<<n)-1;s++) {
            int i=0;
            while(s&(1<<i)) i++;
            dp[s|(1<<i)]=min(dp[s|(1<<i)],dp[s]+1);
            for(int j=i;j<n;j++)
                dp[s|f[i][j]]=min(dp[s|f[i][j]],dp[s]+1);
        }
        printf("%d\n",dp[(1<<n)-1]);
    }
    return 0;
}
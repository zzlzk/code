#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 2010
#define MAXM 2010

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

int C[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    int T,k;
    input(T),input(k);
    for(int i=1;i<=2000;i++) {
        C[i][i]=1,C[i][1]=i%k;
        if(C[i][1]==0) dp[i][1]=1;
    }
    for(int i=2;i<=2000;i++)
        for(int j=2;j<i;j++) {
            C[i][j]=(C[i-1][j]%k+C[i-1][j-1]%k)%k;
            dp[i][j]=dp[i][j-1];
            if(C[i][j]==0) dp[i][j]++;
        }
    for(int i=1;i<=2000;i++) dp[i][i]=dp[i][i-1];
    while(T--) {
        int n,m,ans=0;
        input(n),input(m);
        for(int i=1;i<=n;i++)
            ans+=dp[i][min(i,m)];
        printf("%d\n",ans);
    }
    return 0;
}

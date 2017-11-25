#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXM 210
#define MAXN 1010
#define mod 1000000007

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

ll f[MAXM][MAXM],sum[MAXM][MAXM];

char a[MAXN],b[MAXM];

int main() {
    int n,m,K;
    input(n),input(m),input(K);
    scanf("%s%s",a,b);
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            for(int k=K;k>=1;k--) {
                if(a[i-1]==b[j-1])
                    sum[j][k]=sum[j-1][k]+f[j-1][k-1];
                else sum[j][k]=0;
                f[j][k]=(f[j][k]+sum[j][k])%mod;
            }
    printf("%lld",f[m][K]);
    return 0;
}

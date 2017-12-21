#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
 
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
 
#define MAXN 10
#define MAXK 100
#define MAXS (1<<10)+10
 
ll f[MAXN][MAXK][MAXS];
 
int calc(int s) {
    int ans=0;
    for(;s;s>>=1)
        if(s&1) ans++;
    return ans;
}
 
bool Judge(int s1,int s2) {
    if(s1&s2) return true;
    if((s1>>1)&s2) return true;
    if((s1<<1)&s2) return true;
    return false;
}
 
int main() {
    int n,k;
    input(n),input(k);
    f[0][0][0]=1;
    int MaxS=(1<<n)-1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=k;j++)
            for(int s=0;s<=MaxS;s++) {
                int sum=calc(s);
                if(sum>j) continue;
                if(s&(s>>1)) continue;
                for(int ss=0;ss<=MaxS;ss++) {
                    if(ss&(ss>>1)) continue;
                    if(Judge(s,ss)) continue;
                    f[i][j][s]+=f[i-1][j-sum][ss];
                }
            }
    ll ans=0;
    for(int s=0;s<=MaxS;s++)
        ans+=f[n][k][s];
    printf("%lld\n",ans);
    return 0;
}
?
#include<cstdio>
using namespace std;
typedef long long ll;
#define mod 10007ll
#define maxn 1010

ll fac[maxn];

ll poow(ll x,ll k,ll p) {
    ll ret=1;
    for(;k;k>>=1,x=(x*x)%p)
        if(k&1) ret=(ret*x)%p;
    return ret;
}

ll inv(ll x,ll p) {
    return poow(x,p-2,p);
}

int main() {
    fac[0]=fac[1]=1ll;
    ll a,b,k,n,m;
    scanf("%lld%lld%lld%lld%lld",&a,&b,&k,&n,&m);
    for(int i=2;i<=k;i++) fac[i]=fac[i-1]*(ll)i%mod;
    ll ckn=fac[k]*inv(fac[k-n]*fac[n]%mod,mod)%mod;
    ll ans=ckn*poow(a,n,mod)%mod*poow(b,k-n,mod)%mod;
    printf("%lld",ans);
    return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
 
template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<48||c>57;c=getchar())
        if(c==45) a=-1;
    for(;c>=48&&c<=57;c=getchar())
        x=x*10+c-48;
    x*=a;
    return;
}
 
#define MAXN 10000010
#define mod 100000009
 
bool not_prime[MAXN];
int prime[MAXN],tot;
ll h[MAXN],sum[MAXN];
 
void LineShaker() {
    h[1]=1ll;
    for(int i=2;i<=10000000;i++) {
        if(!not_prime[i]) {
			prime[++tot]=i;
			h[i]=(i-(ll)i*i)%mod;
		}
        for(int j=1;j<=tot&&i*prime[j]<=10000000;j++) {
            not_prime[i*prime[j]]=true;
            if(i%prime[j]==0) {
				h[i*prime[j]]=(h[i]*prime[j])%mod;
                break;
            } else h[i*prime[j]]=(h[i]*h[prime[j]])%mod;
        }
    }
    for(int i=1;i<=10000000;i++)
        sum[i]=(sum[i-1]+h[i])%mod;
    return;
}
 
ll calc(ll x,ll y) {
	x%=mod,y%=mod;
	ll a=(x*(x+1)>>1)%mod,
	   b=(y*(y+1)>>1)%mod;
    return a*b%mod;
}
 
ll f(ll n,ll m) {
	if(n>m) swap(n,m);
    ll ans=0;
    for(ll l=1,r;l<=n;l=r+1) {
        r=min(n/(n/l),m/(m/l)),
        ans+=(sum[r]-sum[l-1])*calc(n/l,m/l)%mod;
		ans%=mod;
    }
    return (ans+mod)%mod;
}
 
int main() {
    LineShaker();
	int T;
	for(input(T);T;T--) {
	    ll n,m;
    	input(n),input(m);
    	printf("%lld\n",f(n,m));
	}
	return 0;
}

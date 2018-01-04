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
#define mod 20101009

bool not_prime[MAXN];
int prime[MAXN],tot;
int mu[MAXN];
ll sum[MAXN];

void LineShaker() {
	mu[1]=1;
	for(int i=2;i<=10000000;i++) {
		if(!not_prime[i]) mu[prime[++tot]=i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=10000000;j++) {
			not_prime[i*prime[j]]=true;
			if(i%prime[j]==0) {
				mu[i*prime[j]]=0;
				break;
			} else mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=10000000;i++)
		sum[i]=(sum[i-1]+(ll)i*i*mu[i]%mod)%mod;
	return;
}

ll calc(ll x,ll y) {
	return (((x*(x+1)/2)%mod)*((y*(y+1)/2)%mod))%mod;
}

ll f(ll n,ll m) {
	ll ans=0;
	for(ll l=1,r;l<=n&&l<=m;l=r+1) {
		r=min(n/(n/l),m/(m/l)),
		ans=(ans+(sum[r]-sum[l-1])*calc(n/l,m/l)%mod)%mod;
	}
	return ans;
}

int main() {
	LineShaker();
	ll n,m;
	input(n),input(m);
	ll ans=0;
	for(ll l=1,r;l<=n&&l<=m;l=r+1) {
		r=min(n/(n/l),m/(m/l)),
		ans=(ans+(ll)(l+r)*(r-l+1)/2%mod*f(n/l,m/l)%mod)%mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}

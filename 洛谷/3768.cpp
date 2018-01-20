#include<map>
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

int p,N;
int phi[MAXN];
int prime[MAXN],tot;
bool not_prime[MAXN];

ll poow(ll a,ll k) {
	ll ret=1;
	for(;k;k>>=1,a=a*a%p)
		if(k&1) ret=ret*a%p;
	return ret;
}

void prepare(ll n) {
	N=min(1ll*MAXN-10,n);
	not_prime[phi[1]=1]=true;
	for(int i=2;i<=N;i++) {
		if(!not_prime[i]) phi[prime[++tot]=i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++) {
			not_prime[i*prime[j]]=true;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=1ll*phi[i]*prime[j]%p;
				break;
			}
			phi[i*prime[j]]=1ll*phi[i]*(prime[j]-1)%p;
		}
	}
	for(int i=2;i<=N;i++)
		phi[i]=(1ll*phi[i]*i%p*i%p+phi[i-1])%p;
	return;
}

ll sum(ll x,int op) {
	static int inv2=poow(2,p-2),inv6=poow(6,p-2);
	if(op==2) return (x%p*(x+1)%p*inv2%p);
	return (x%p*(x+1)%p*(2*x%p+1)%p*inv6%p);
}

ll calc(ll n) {
	static map<ll,int> s;
	if(n<=N) return phi[n];
	if(s[n]) return s[n];
	ll ans=sum(n,2);
	ans=ans*ans%p;
	for(ll l=2,r;l<=n;l=r+1) {
		ans-=(sum(r=n/(n/l),6)-sum(l-1,6))*calc(n/l)%p,
		ans=(ans+p)%p;
	}
	return s[n]=ans%p;
}

int main() {
	ll ans=0,n;
	input(p),input(n);
	prepare(n);
	for(ll l=1,r,ret;l<=n;l=r+1) {
		ret=sum(n/l,2),ret=ret*ret%p,
		ans+=ret*(calc(r=n/(n/l))-calc(l-1))%p;
	}
	printf("%lld\n",ans%p);
	return 0;
}

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

#define MAXN 100010

ll p;

ll fac[MAXN];

ll poow(ll n,ll k) {
	ll ans=1;
	for(n%=p;k;k>>=1,n=n*n%p)
		if(k&1) ans=ans*n%p;
	return ans;
}

ll C(ll n,ll m) {
	return m>n?0:(fac[n]*poow(fac[m],p-2)%p*poow(fac[n-m],p-2)%p);
}

ll Lucas(ll n,ll m) {
	return !m?1:C(n%p,m%p)*Lucas(n/p,m/p)%p;
}

int main() {
	ll T,n,m;
	for(input(T);T;T--) {
		input(n),input(m),input(p);
		fac[0]=1;
		for(ll i=1;i<=p;i++)
			fac[i]=fac[i-1]*i,fac[i]%=p;
		printf("%lld\n",Lucas(n+m,m));
	}
	return 0;
}

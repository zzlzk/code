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

#define MAXN 50010

bool not_prime[MAXN];
int prime[MAXN],tot;
int mu[MAXN],sum[MAXN];

void LineShaker() {
	mu[1]=1;
	for(int i=2;i<=50000;i++) {
		if(!not_prime[i]) mu[prime[++tot]=i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=50000;j++) {
			not_prime[i*prime[j]]=true;
			if(i%prime[j]==0) {
				mu[i*prime[j]]=0;
				break;
			} else mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)
		sum[i]=sum[i-1]+mu[i];
	return;
}

ll t[MAXN];

void calc(int n) {
	ll ans=0;
	for(int l=1,r;l<=n;l=r+1)
		r=n/(n/l),ans+=(ll)(r-l+1)*(n/l);
	t[n]=ans;
	return;
}

ll calc(int n,int m) {
	if(n>m) swap(n,m);
	ll ans=0;
	for(int l=1,r;l<=n;l=r+1) {
		r=min(n/(n/l),m/(m/l)),
		ans+=(ll)(sum[r]-sum[l-1])*t[n/l]*t[m/l];
	}
	return ans;
}

int main() {
	for(int i=1;i<=50000;calc(i++));
	int T,n,m;
	for(input(T),LineShaker();T;T--)
		input(n),input(m),printf("%lld\n",calc(n,m));
	return 0;
}

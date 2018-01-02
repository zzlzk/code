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

int d;

int calc(int n,int m) {
	n/=d,m/=d;
	if(n>m) swap(n,m);
	int ans=0;
	for(int l=1,r;l<=n;l=r+1) {
		r=min(n/(n/l),m/(m/l)),
		ans+=(sum[r]-sum[l-1])*(n/l)*(m/l);
	}
	return ans;
}

int main() {
	int T,a,b;
	for(input(T),LineShaker();T;T--) {
		input(a),input(b),input(d),
		printf("%d\n",calc(a,b));
	}
	return 0;
}

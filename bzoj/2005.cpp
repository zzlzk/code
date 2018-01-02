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

ll f[MAXN];

int main() {
	int n,m;
	input(n),input(m);
	if(n>m) swap(n,m);
	ll ans=0;
	for(int i=n;i;i--) {
		f[i]=(ll)(n/i)*(m/i);
		for(int j=i*2;j<=n;j+=i) f[i]-=f[j];
		ans+=(ll)(i*2-1)*f[i];
	}
	printf("%lld\n",ans);
	return 0;
}

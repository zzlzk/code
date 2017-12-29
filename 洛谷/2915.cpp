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

#define MAXN 16
#define MAXS (1<<16)+10

ll f[MAXS][MAXN];

int id[MAXN];

#define check(i,j) ((id[i]-id[j]>k)||(id[j]-id[i]>k))

int main() {
	int n,k;
	input(n),input(k);
	for(int i=1;i<=n;i++)
		input(id[i]);
	for(int i=1;i<=n;i++)
		f[1<<i-1][i]=1;
	for(int s=0;s<(1<<n);s++)
		for(int i=1;i<=n;i++)
			if(s&(1<<i-1))
				for(int j=1;j<=n;j++)
					if(!(s&(1<<j-1))&&check(i,j))
						f[s|(1<<j-1)][j]+=f[s][i];
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=f[(1<<n)-1][i];
	printf("%lld\n",ans);
	return 0;
}

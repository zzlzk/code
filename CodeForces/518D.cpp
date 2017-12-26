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

#define MAXN 2010

double f[MAXN][MAXN];

int main() {
	double p;
	int n,t;
	scanf("%d%lf%d",&n,&p,&t);
	f[0][0]=1.00;
	for(int i=1;i<=t;i++) {
		f[i][0]=f[i-1][0]*(1-p),
		f[i][n]=f[i-1][n-1]*p+f[i-1][n];
		for(int j=1;j<n;j++)
			f[i][j]=f[i-1][j]*(1-p)+f[i-1][j-1]*p;
	}
	double ans=0.00;
	for(int i=0;i<=n;i++)
		ans+=i*f[t][i];
	printf("%lf\n",ans);
	return 0;
}

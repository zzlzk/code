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
double g[MAXN][MAXN];

int main() {
	int n;
	input(n);
	g[0][0]=1.00;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++) {
			g[i+1][j+1]+=g[i][j]*0.5,
			f[i+1][j+1]+=f[i][j]*0.5;
			if(!j) {
				f[i+1][j]+=f[i][j]*0.5,
				g[i+1][j]+=g[i][j]*0.5;
			} else {
				f[i+1][j-1]+=f[i][j]*0.5+g[i][j],
				g[i+1][j-1]+=g[i][j]*0.5;
			}
		}
	double ans=n;
	for(int i=0;i<=n;i++)
		ans-=f[n][i];
	printf("%.3lf\n",ans);
	return 0;
}

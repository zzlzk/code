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

double f[MAXN],g[MAXN],h[MAXN];

int main() {
	int n;
	input(n);
	for(int i=1;i<=n;i++) {
		double p;
		scanf("%lf",&p);
		f[i]=p*(f[i-1]+3*(g[i-1]+h[i-1])+1)+(1-p)*f[i-1];
		g[i]=p*(g[i-1]+2*h[i-1]+1);
		h[i]=p*(h[i-1]+1);
	}
	printf("%.1lf\n",f[n]);
	return 0;
}

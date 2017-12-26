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

#define MAXN 10010

double f[MAXN],g[MAXN];

int main() {
	int n;
	input(n);
	for(int i=n-1;i>=0;i--)
		g[i]=g[i+1]+1.00*n/(n-i);
	for(int i=n-1;i>=0;i--)
		f[i]=f[i+1]+g[i+1]+(1.00*n*i)/((1.00*n-i)*n*1.00)*g[i]+1.00*n/(n-i);
	printf("%.2lf\n",f[0]);
	return 0;
}

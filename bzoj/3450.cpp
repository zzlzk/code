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

#define MAXN 300010

char s[MAXN];
long double f[MAXN],g[MAXN];

int main() {
	int n;
	input(n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) {
		if(s[i]=='x') f[i]=f[i-1],g[i]=0.00;
		if(s[i]=='o') f[i]=f[i-1]+2*g[i-1]+1,g[i]=g[i-1]+1;
		if(s[i]=='?') f[i]=f[i-1]+g[i-1]+0.5,g[i]=0.5*g[i-1]+0.5;
	}
	printf("%.4lf\n",(double)f[n]);
	return 0;
}

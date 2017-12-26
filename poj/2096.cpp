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

#define MAXN 1010

double f[MAXN][MAXN];

int main() {
    int n,s;
    while(~scanf("%d%d",&n,&s)) {
		f[n][s]=0;
		for(int i=n;i>=0;i--)
			for(int j=s;j>=0;j--) {
			  if(i==n&&j==s) continue;
			  f[i][j]=(i*(s-j)*f[i][j+1]+(n-i)*j*f[i+1][j]+(n-i)*(s-j)*f[i+1][j+1]+n*s)/(n*s-i*j);
		  }
		printf("%.4lf\n",f[0][0]);
	}
	return 0;
}

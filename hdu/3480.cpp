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
#define MAXM 5010

int a[MAXN];
int f[MAXM][MAXN],s[MAXM][MAXN];

#define sqr(x) ((x)*(x))

int main() {
	int T;
	input(T);
	for(int Case=1,n,m;Case<=T;Case++) {
		input(n),input(m);
		for(int i=1;i<=n;i++)
			input(a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=247483647;
		for(int i=1;i<=n;i++)
			f[s[1][i]=1][i]=sqr(a[i]-a[1]);
		for(int i=2;i<=m;i++) {
			s[i][n+1]=n-1;
			for(int j=n;j>=i;j--)
				for(int k=s[i-1][j];k<=s[i][j+1];k++)
					if(f[i][j]>f[i-1][k]+sqr(a[j]-a[k+1]))
						f[i][j]=f[i-1][s[i][j]=k]+sqr(a[j]-a[k+1]);
		}
		printf("Case %d: %d\n",Case,f[m][n]);
	}
	return 0;
}

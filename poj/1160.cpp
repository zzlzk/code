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
#define MAXM 1010

int a[MAXN];

int Remember[MAXN][MAXN];
int Cost(int l,int r) {
	if(l>r) return 0;
	if(Remember[l][r])
		return Remember[l][r];
	for(int i=l,j=r;i<j;i++,j--)
		Remember[l][r]+=a[j]-a[i];
	return Remember[l][r];
}

int f[MAXM][MAXN],s[MAXM][MAXN];

int main() {
	int n,m;
	input(n),input(m);
	for(int i=1;i<=n;i++)
		input(a[i]);
	for(int i=1;i<=n;i++)
		f[1][i]=Cost(1,i),s[i][i]=i-1;
	for(int i=2;i<=m;i++) {
		s[i][n+1]=n-1;
		for(int j=n;j>=i;j--) {
			f[i][j]=2147483647;
			for(int k=s[i-1][j];k<=s[i][j+1];k++)
				if(f[i][j]>f[i-1][k]+Cost(k+1,j))
					f[i][j]=f[i-1][s[i][j]=k]+Cost(k+1,j);
		}
	}
	printf("%d\n",f[m][n]);
	return 0;
}

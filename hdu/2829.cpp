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

int f[MAXN][MAXN],s[MAXN][MAXN],cost[MAXN][MAXN];
int sum[MAXN];

int main() {
	for(int n,m;true;) {
		input(n),input(m);
		if(n+m++==0) break;
		sum[0]=0;
		for(int i=1;i<=n;i++)
			input(sum[i]),sum[i]+=sum[i-1];
		memset(cost,0,sizeof(cost));
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				cost[i][j]=cost[i][j-1]+(sum[j-1]-sum[i-1])*(sum[j]-sum[j-1]);
		for(int i=1;i<=n;i++)
			f[1][i]=cost[1][i],s[1][i]=0;
		for(int i=2;i<=m;i++) {
			s[i][n+1]=n;
			for(int j=n;j>i;j--) {
				f[i][j]=2147483647;
				for(int k=s[i-1][j];k<=s[i][j+1];k++)
					if(f[i][j]>f[i-1][k]+cost[k+1][j])
						f[i][j]=f[i-1][s[i][j]=k]+cost[k+1][j];
			}
		}
		printf("%d\n",f[m][n]);
	}
	return 0;
}

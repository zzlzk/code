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

#define MAXN 60][8][8][8

double f[MAXN],g[MAXN];

int main() {
	int T;
	input(T);
	for(int K,A,B,C;T;T--) {
		input(K),input(A),input(B),input(C);
		memset(f,0,sizeof(f)),
		memset(g,0,sizeof(g));
		g[0][A][B][C]=1.00;
		for(int i=0;i<K;i++)
			for(int a=0;a<=7;a++)
				for(int b=0;a+b<=7;b++)
					for(int c=0;a+b+c<=7;c++) {
						//hit yyq
						g[i+1][a][b][c]+=g[i][a][b][c]/(a+b+c+1),
						f[i+1][a][b][c]+=(f[i][a][b][c]+g[i][a][b][c])/(a+b+c+1);
						//hit a
						if(a) {
							g[i+1][a-1][b][c]+=g[i][a][b][c]*a/(a+b+c+1),
							f[i+1][a-1][b][c]+=f[i][a][b][c]*a/(a+b+c+1);
						}
						//hit b
						if(b) {
							if(a+b+c<7) {
								g[i+1][a+1][b-1][c+1]+=g[i][a][b][c]*b/(a+b+c+1),
								f[i+1][a+1][b-1][c+1]+=f[i][a][b][c]*b/(a+b+c+1);
							} else {
								g[i+1][a+1][b-1][c]+=g[i][a][b][c]*b/(a+b+c+1);
								f[i+1][a+1][b-1][c]+=f[i][a][b][c]*b/(a+b+c+1);
							}
						}
						//hit c
						if(c) {
							if(a+b+c<7) {
								g[i+1][a][b+1][c]+=g[i][a][b][c]*c/(a+b+c+1),
								f[i+1][a][b+1][c]+=f[i][a][b][c]*c/(a+b+c+1);
							} else {
								g[i+1][a][b+1][c-1]+=g[i][a][b][c]*c/(a+b+c+1),
								f[i+1][a][b+1][c-1]+=f[i][a][b][c]*c/(a+b+c+1);
							}
						}
					}
		double ans=0.00;
		for(int a=0;a<=7;a++)
			for(int b=0;a+b<=7;b++)
				for(int c=0;a+b+c<=7;c++)
					ans+=f[K][a][b][c];
		printf("%.2lf\n",ans);
	}
	return 0;
}

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

#define MAXN (1<<15)+10
#define MAXK 110

double f[MAXK][MAXN];

int P[20],S[20];

int main() {
	int n,k;
	input(k),input(n);
	for(int i=1,j;i<=n;i++) {
		input(P[i]);
		while(true) {
			input(j);
			if(!j) break;
			S[i]|=1<<j-1;
		}
	}
	double p=(double)1/n;
	for(int i=k;i;i--)
		for(int s=0;s<1<<n;s++)
			for(int j=1;j<=n;j++) {
				double x=f[i+1][s];
				if((s&S[j])==S[j])
					x=max(x,f[i+1][s|1<<j-1]+1.0*P[j]);
				f[i][s]+=x*p;
			}
	printf("%.6lf\n",f[1][0]);
	return 0;
}

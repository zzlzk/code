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
#define MAXW 20010

int w[MAXN],v[MAXN];
int f[MAXW];

int main() {
	int T;
	input(T);
	for(int W,n;T;T--) {
		memset(f,0,sizeof(f));
		input(W),input(n);
		int cnt=0,a,b,c;
		for(int i=0;i<n;i++) {
			input(a),input(b),input(c);
			for(int j=1;j<c;c-=j,j<<=1)
				w[++cnt]=a*j,v[cnt]=b*j;
			w[++cnt]=a*c,v[cnt]=b*c;
		}
		for(int i=1;i<=cnt;i++)
			for(int j=W;j>=w[i];j--)
				f[j]=max(f[j],f[j-w[i]]+v[i]);
		printf("%d\n",f[W]);
	}
	return 0;
}

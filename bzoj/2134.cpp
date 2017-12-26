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

#define MAXN 10000000

int a[MAXN];

int main() {
	int n,A,B,C;
	input(n),input(A),input(B),input(C),input(a[1]);
	for(int i=2;i<=n;i++)
		a[i]=((ll)a[i-1]*A+B)%100000001;
	for(int i=1;i<=n;i++)
		a[i]=a[i]%C+1;
	double ans=0.00;
	for(int i=1;i<=n;i++)
		ans+=(double)1/max(a[i],a[i+1>n?1:i+1]);
	printf("%.3lf\n",ans);
	return 0;
}

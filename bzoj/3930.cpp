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

#define mod 1000000007
#define MAXN 100010

int poow(int n,int k) {
	int ret=1;
	for(;k;k>>=1,n=(ll)n*n%mod)
		if(k&1) ret=(ll)ret*n%mod;
	return ret%mod;
}

int f[MAXN];

int main() {
	int n,k,H,L,flag=0;
	input(n),input(k),input(H),input(L);
	if(H<=k&&k<=L) flag=1;
	H--,H/=k,L/=k;
	for(int i=L-H,l,r;i;i--) {
		l=H/i,r=L/i;
		f[i]=(poow(r-l,n)-r+l)%mod;
		while(f[i]<0) f[i]+=mod;
		for(int j=i+i;j<=L-H;j+=i)
			f[i]=((f[i]-f[j])%mod+mod)%mod;
	}
	printf("%d\n",(f[1]+flag)%mod);
	return 0;
}

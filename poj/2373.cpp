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

#define MAXN 1000010
#define inf 214748364

int f[MAXN],tag[MAXN],num[MAXN];
int q[MAXN],head,tail;

int main() {
	int n,L,a,b;
	input(n),input(L),input(a),input(b);
	for(int i=1,l,r;i<=n;i++) {
		input(l),input(r);
		for(int j=l+1;j<r;j++)
			tag[j]=1;
	}
	for(int i=1;i<=L;i++)
		f[i]=inf;
	head=1,tail=f[0]=0;
	for(int i=2*a;i<=L;i+=2) {
		for(;head<=tail&&i-num[head]>2*b;head++);
		for(;head<=tail&&q[tail]>=f[i-2*a];tail--);
		q[++tail]=f[i-2*a],num[tail]=i-2*a;
		if(!tag[i]&&f[num[head]]!=inf)
			f[i]=f[num[head]]+1;
	}
	printf("%d\n",f[L]==inf?-1:f[L]);
    return 0;
}

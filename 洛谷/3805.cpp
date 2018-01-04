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

#define MAXN 51000100

char s[MAXN];
int p[MAXN<<1],n,m;

void Manacher() {
	n=strlen(s+1);
	for(int i=n;i>=1;--i)
		s[i*2]=s[i];
    for(int i=1;i<=n*2+1;i+=2)
		s[i]='~';
	int R,pos;
	s[0]='#',m=n*2+1,R=pos=0;
	for(int i=1;i<=m;++i) {
		if(R<i) {
			for(p[i]=0;s[i+p[i]+1]==s[i-p[i]-1];++p[i]);
			R=p[i]+i,pos=i;
			continue;
		}
		int j=pos*2-i;
		if(i+p[j]<R) {
			p[i]=p[j];
			continue;
		}
		for(p[i]=R-i;s[i+p[i]+1]==s[i-p[i]-1];++p[i]);
		R=p[i]+i,pos=i;
	}
	return;
}

int main() {
	scanf("%s",s+1);
	Manacher();
	int ans=0;
	for(int i=1;i<=m;i++)
		ans=max(ans,p[i]);
	printf("%d\n",ans);
	return 0;
}

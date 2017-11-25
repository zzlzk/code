#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 50010
int a[maxn],b[maxn],c[maxn];
int t1[maxn],t2[maxn];
bool vis[maxn];
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
int main() {
	int n=input(),ans;
	for(int i=1;i<=n;i++)
		a[i]=input(),b[i]=input();
	vis[c[1]=1]=vis[c[2]=a[1]]=true;
	for(int i=2;i<n;i++) {
		if(c[i-1]==a[c[i]]) c[i+1]=b[c[i]];
		else if(c[i-1]==b[c[i]]) c[i+1]=a[c[i]];
		else {
			printf("-1");
			return 0;
		}
		vis[c[i+1]]=true;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) {
			printf("-1");
			return 0;
		}
	for(int i=1;i<=n;i++) {
		int t=(c[i]-i+n)%n;
		t1[t]++;
		ans=max(ans,t1[t]);
		t=(c[n-i+1]-i+n)%n;
		t2[t]++;
		ans=max(ans,t2[t]);
	}
	printf("%d",n-ans);
	return 0;
}

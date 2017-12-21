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

int s[MAXN*MAXN],n,m;
int c[MAXN*MAXN<<1],X[MAXN*MAXN<<1],Y[MAXN*MAXN<<1];
int sa[MAXN*MAXN],rank[MAXN*MAXN],height[MAXN*MAXN];

void Get_Height() {
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
		if(rank[i]!=1) {
			for(k=max(k-1,0);s[i+k]==s[sa[rank[i]-1]+k];k++);
			height[rank[i]]=k;
		}
	return;
}

void Build_SuffixArray(int m) {
	int *x=X,*y=Y;
	for(int i=1;i<=m;i++) c[i]=0;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<n;k<<=1) {
		int p=0;
		for(int i=n;i>n-k;i--) y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
		swap(x,y),m=1;
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i+1]]&&y[sa[i]+k]==y[sa[i+1]+k]?m:m++;
		if(m>n) return Get_Height();
	}
	return Get_Height();
}

int L[MAXN],card[MAXN][MAXN],pos[MAXN*MAXN];

bool vis[MAXN];

int cnt=0,N;

bool Judge(int mid) {
	for(int i=1;i<=n;i++) {
		if(height[i]<mid) {
			memset(vis,0,sizeof(vis));
			cnt=0;
		}
		if(!vis[pos[sa[i]]]) {
			vis[pos[sa[i]]]=true;
			cnt++;
		}
		if(cnt==N) return true;
	}
	return false;
}

int main() {
	int l=0,r=2147483647;
	input(N);
	for(int i=1;i<=N;i++) {
		input(L[i]);
		for(int j=1;j<=L[i];j++) {
			input(card[i][j]);
			if(j!=1) m=max(card[i][j]-card[i][j-1],m);
		}
		r=min(L[i],r);
	}
	for(int i=1;i<=N;i++) {
		for(int j=2;j<=L[i];j++)
			s[++n]=card[i][j]-card[i][j-1],pos[n]=i;
		s[++n]=++m;
	}
	int Min=2147483647;
	for(int i=1;i<=n;i++) Min=min(Min,s[i]);
	for(int i=1;i<=n;i++) s[i]-=Min-1,m=max(s[i],m);
	Build_SuffixArray(m);
	int mid,ans=1;
	while(l<=r) {
		mid=l+r>>1;
		if(Judge(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans+1);
	return 0;
}

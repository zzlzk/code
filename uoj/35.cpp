#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 100010

char s[MAXN];
int X[MAXN<<1],Y[MAXN<<1],c[MAXN<<1];
int sa[MAXN],rank[MAXN],height[MAXN],n;

void Get_Height() {
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
		if(rank[i]!=n) {
			for(k=max(k-1,0);s[i+k]==s[sa[rank[i]+1]+k];k++);
			height[rank[i]]=k;
		}
	return;
}

void Build_SuffixArray(int m) {
	int *x=X,*y=Y;
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
			x[sa[i]]=y[sa[i]+k]==y[sa[i+1]+k]&&y[sa[i]]==y[sa[i+1]]?m:m++;
		if(m>n) return Get_Height();
	}
	return Get_Height();
}

int main() {
	gets(s+1);
	n=strlen(s+1);
	Build_SuffixArray(128);
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
	puts("");
	for(int i=1;i<n;i++)
		printf("%d ",height[i]);
	puts("");
	return 0;
}


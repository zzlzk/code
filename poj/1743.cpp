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

#define MAXN 20010

int s[MAXN],n,m;
int X[MAXN<<1],Y[MAXN<<1],c[MAXN<<1];
int sa[MAXN],rank[MAXN],height[MAXN];

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

void Build_SuffixArray() {
    int *x=X,*y=Y;
	m=200;
	for(int i=0;i<=m;i++) c[i]=0;
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<n;k<<=1) {
        int p=0;
        for(int i=n;i>n-k;i--) y[++p]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>k) y[++p]=sa[i]-k;
        for(int i=0;i<=m;i++) c[i]=0;
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

struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
}; 

Edge edge[MAXN];
int head[MAXN],cnt;

void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]),
	head[u]=cnt;
	return;
}

int fa[MAXN],Min[MAXN],Max[MAXN];

int Find(int x) {
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

void Union(int x,int y) {
	if((x=Find(x))!=(y=Find(y))) {
		fa[x]=y;
		Min[y]=min(Min[y],Min[x]),
		Max[y]=max(Max[y],Max[x]);
	}
	return;
}

int main() {
	while(scanf("%d",&n)!=EOF&&n) {
		int last;
		input(last),n--;
		for(int i=1,x;i<=n;i++) {
			input(x);
			s[i]=x-last+100,last=x;
		}
		Build_SuffixArray();
		int ans=0;
		memset(head,0,sizeof(head)),cnt=0;
		for(int i=1;i<=n;i++) {
			fa[i]=i,Min[i]=Max[i]=sa[i],
			addedge(height[i],i);
		}
		for(int L=n-1,x;L>=4;L--) {
			for(int i=head[L];i;i=edge[i].next)
				Union(edge[i].v,edge[i].v-1);
			if(head[L]) {
				x=Find(edge[head[L]].v);
				if(Max[x]-Min[x]>L) {
					ans=L+1;
					break;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

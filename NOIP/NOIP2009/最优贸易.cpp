#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 100010
#define maxm 500010
#define inf 0x7f
struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
}edge[maxm<<1],edges[maxm<<1];
int head[maxn],cnt,heads[maxn],cnts;
int Min[maxn],Max[maxn],price[maxn];
bool inq[maxn];
queue<int>q;
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]);
	head[u]=cnt;
	edges[++cnts]=Edge(v,u,heads[v]);
	heads[v]=cnts;
	return;
}
void spfa(int S) {
	Min[S]=price[S];
	q.push(S);
	inq[S]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		inq[u]=false;
		for(int i=head[u];i;i=edge[i].next) {
			int v=edge[i].v;
			if(Min[v]>Min[u]||price[v]<Min[v]) {
				Min[v]=min(Min[u],price[v]);
				if(!inq[v]) {
					q.push(v);
					inq[v]=true;
				}
			}
		}
	}
	return;
}
void spfas(int T) {
	memset(inq,0,sizeof(inq));
	Max[T]=price[T];
	q.push(T);
	inq[T]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		inq[u]=false;
		for(int i=heads[u];i;i=edges[i].next) {
			int v=edges[i].v;
			if(Max[u]>Max[v]||price[v]>Max[v]) {
				Max[v]=max(Max[u],price[v]);
				if(!inq[v]) {
					q.push(v);
					inq[v]=true;
				}

			}
		}
	}
}
int main() {
	int n=input(),m=input(),ans=0;
	for(int i=1;i<=n;i++)
		price[i]=input(),Max[i]=-inf,Min[i]=inf;
	for(int i=1;i<=m;i++) {
		int u=input(),v=input(),flag=input();
		addedge(u,v);
		if(flag==2) addedge(v,u);
	}
	spfa(1);
	spfas(n);
	for(int i=1;i<=n;i++)
		ans=max(ans,Max[i]-Min[i]);
	printf("%d",ans);
	return 0;
}

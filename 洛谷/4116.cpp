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

#define MAXN 100010

struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
};

Edge edge[MAXN<<1];
int head[MAXN],cnt;

void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]),
	head[u]=cnt;
	return;
}

int fa[MAXN],son[MAXN],size[MAXN],depth[MAXN];
int top[MAXN],dfn[MAXN],Map[MAXN],timee;

void dfs1(int u) {
	size[u]=1;
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]) {
			depth[v]=depth[fa[v]=u]+1;
			dfs1(v);
			size[u]+=size[v];
			if(!son[u]||size[son[u]]<size[v])
				son[u]=v;
		}
	}
	return;
}

void dfs2(int u,int topfa) {
	top[u]=topfa,Map[dfn[u]=++timee]=u;
	if(!son[u]) return;
	dfs2(son[u],topfa);
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
	return;
}

#define inf 2147483647

int Min[MAXN<<2],n,Q;

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
	Min[now]=min(Min[lc],Min[rc]);
	return;
}

void build(int now,int l,int r) {
	Min[now]=inf;
	if(l==r) return;
	int mid=l+r>>1;
	build(lson),build(rson);
	return;
}

void modify(int now,int l,int r,int pos) {
	if(l==r) {
		if(Min[now]==inf) Min[now]=l;
		else Min[now]=inf;
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid) modify(lson,pos);
	else modify(rson,pos);
	return updata(now);
}

int query(int now,int l,int r,int L,int R) {
	if(L>R) return inf;
	if(l==L&&R==r) return Min[now];
	int mid=l+r>>1;
	if(R<=mid) return query(lson,L,R);
	else if(L>mid) return query(rson,L,R);
	else return min(query(lson,L,mid),query(rson,mid+1,R));
}

int query(int u,int v=1) {
	int ans=inf;
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		ans=min(ans,query(1,1,n,dfn[top[u]],dfn[u]));
	}
	if(depth[u]>depth[v]) swap(u,v);
	return min(ans,query(1,1,n,dfn[u],dfn[v]));
}

int main() {
	input(n),input(Q);
	for(int i=1,u,v,w;i<n;i++) {
		input(u),input(v),
		addedge(u,v),addedge(v,u);
	}
	dfs1(1),dfs2(1,1),build(1,1,n);
	for(int op,x;Q;Q--) {
		input(op),input(x);
		if(!op) modify(1,1,n,dfn[x]);
		else {
			x=query(x);
			printf("%d\n",x==inf?-1:Map[x]);
		}
	}
	return 0;
}

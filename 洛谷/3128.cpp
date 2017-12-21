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

#define MAXN 50010

struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
};

Edge edge[MAXN<<1];
int head[MAXN],cnt;

void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]);
	head[u]=cnt;
	return;
}

int fa[MAXN],size[MAXN],depth[MAXN],son[MAXN];
int top[MAXN],pos[MAXN],timee;

void dfs1(int u) {
	size[u]=1,depth[u]=depth[fa[u]]+1;
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(fa[u]!=v) {
			fa[v]=u;
			dfs1(v);
			size[u]+=size[v];
			if(!son[u]||size[v]>size[son[u]])
				son[u]=v;
		}
	}
	return;
}

void dfs2(int u,int topfa) {
	top[u]=topfa,pos[u]=++timee;
	if(!son[u]) return;
	dfs2(son[u],topfa);
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
	return;
}

struct Segment_Tree {
	int Max,tag;
};

int n,m;
Segment_Tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
	t[now].Max=max(t[lc].Max,t[rc].Max);
	return;
}

void pushdown(int now) {
	if(t[now].tag) {
		int &tag=t[now].tag;
		t[lc].tag+=tag,t[rc].tag+=tag;
		t[lc].Max+=tag,t[rc].Max+=tag;
		tag=0;
	}
	return;
}

void build(int now,int l,int r) {
	t[now].Max=t[now].tag=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(lson),build(rson);
	return;
}

void modify(int now,int l,int r,int L,int R) {
	if(l==L&&R==r) {
		t[now].Max++;
		t[now].tag++;
		return;
	}
	pushdown(now);
	int mid=l+r>>1;
	if(R<=mid) modify(lson,L,R);
	else if(L>mid) modify(rson,L,R);
	else modify(lson,L,mid),modify(rson,mid+1,R);
	return updata(now);
}

void modify(int u,int v) {
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		modify(1,1,n,pos[top[u]],pos[u]);
	}
	if(depth[u]>depth[v]) swap(u,v);
	return modify(1,1,n,pos[u],pos[v]);
}

int main() {
	input(n),input(m);
	for(int i=1,u,v;i<n;i++) {
		input(u),input(v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1),dfs2(1,1),build(1,1,n);
	for(int u,v;m;m--) {
		input(u),input(v);
		modify(u,v);
	}
	printf("%d\n",t[1].Max);
	return 0;
}

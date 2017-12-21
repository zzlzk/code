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
	edge[++cnt]=Edge(u,v,head[u]);
	head[u]=cnt;
	return;
}

int fa[MAXN],son[MAXN],size[MAXN],depth[MAXN];
int pos[MAXN],top[MAXN],timee,sop[MAXN];

void dfs1(int u) {
	size[u]=1;
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]) {
			fa[v]=u;
			depth[v]=depth[u]+1;
			dfs1(v);
			size[u]+=size[v];
			if(!son[u]||size[v]>size[son[u]])
				son[u]=v;
		}
	}
	return;
}

void dfs2(int u,int topfa) {
	top[u]=topfa,pos[u]=++timee,sop[timee]=u;
	if(!son[u]) return;
	dfs2(son[u],topfa);
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
	return;
}

struct Segment_Tree {
	int sum,tag,l_col,r_col;
};

int col[MAXN],n,m;
Segment_Tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
	t[now].sum=t[lc].sum+t[rc].sum;
	if(t[lc].r_col==t[rc].l_col) t[now].sum--;
	t[now].l_col=t[lc].l_col,
	t[now].r_col=t[rc].r_col;
	return;
}

void pushdown(int now) {
	if(t[now].tag!=-1) {
		int &tag=t[now].tag;
		t[lc].tag=t[rc].tag=tag,
		t[lc].sum=t[rc].sum=1,
		t[lc].l_col=t[lc].r_col=tag,
		t[rc].l_col=t[rc].r_col=tag;
		tag=-1;
	}
	return;
}

void build(int now,int l,int r) {
	t[now].tag=-1;
	if(l==r) {
		t[now].sum=1;
		t[now].l_col=t[now].r_col=col[sop[l]];
		return;
	}
	int mid=l+r>>1;
	build(lson),build(rson);
	return updata(now);
}

void modify(int now,int l,int r,int L,int R,int x) {
	if(l==L&&R==r) {
		t[now].sum=1;
		t[now].l_col=t[now].r_col=t[now].tag=x;
		return;
	}
	pushdown(now);
	int mid=l+r>>1;
	if(R<=mid) modify(lson,L,R,x);
	else if(L>mid) modify(rson,L,R,x);
	else modify(lson,L,mid,x),modify(rson,mid+1,R,x);
	return updata(now);
}

int query(int now,int l,int r,int L,int R) {
	if(l==L&&R==r) return t[now].sum;
	pushdown(now);
	int mid=l+r>>1;
	if(R<=mid) return query(lson,L,R);
	else if(L>mid) return query(rson,L,R);
	else {
		int ans=query(lson,L,mid)+query(rson,mid+1,R);
		if(t[lc].r_col==t[rc].l_col) ans--;
		return ans;
	}
}

int query(int now,int l,int r,int p) {
	if(l==r) return t[now].l_col;
	pushdown(now);
	int mid=l+r>>1;
	if(p<=mid) return query(lson,p);
	else return query(rson,p);
}

void modify(int u,int v,int x) {
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		modify(1,1,n,pos[top[u]],pos[u],x);
	}
	if(depth[u]>depth[v]) swap(u,v);
	return modify(1,1,n,pos[u],pos[v],x);
}

int query(int u,int v) {
	int ans=0;
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		ans+=query(1,1,n,pos[top[u]],pos[u]);
		if(query(1,1,n,pos[top[u]])==query(1,1,n,pos[fa[top[u]]])) ans--;
	}
	if(depth[u]>depth[v]) swap(u,v);
	ans+=query(1,1,n,pos[u],pos[v]);
	return ans;
}

int main() {
	input(n),input(m);
	for(int i=1;i<=n;i++) input(col[i]);
	for(int i=1,u,v;i<n;i++) {
		input(u),input(v);
		addedge(u,v),addedge(v,u);
	}
	dfs1(1),dfs2(1,1),build(1,1,n);
	char op[3];
	for(int a,b,c;m;m--) {
		scanf("%s",op),
		input(a),input(b);
		if(op[0]=='C') {
			input(c);
			modify(a,b,c);
		} else printf("%d\n",query(a,b));
	}
	return 0;
}

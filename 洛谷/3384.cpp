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

int fa[MAXN],depth[MAXN],son[MAXN],size[MAXN];
int top[MAXN],pos[MAXN],sop[MAXN],pos_;

void dfs1(int u) {
	size[u]=1;
	depth[u]=depth[fa[u]]+1;
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(!depth[v]) {
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
	top[u]=topfa,pos[u]=++pos_,sop[pos_]=u;
	if(!son[u]) return;
	dfs2(son[u],topfa);
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
	return;
}

struct Segment_Tree {
	ll sum,tag;
};

Segment_Tree t[MAXN<<2];
ll w[MAXN];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

int n,m,root,p;

void updata(int now) {
	t[now].sum=(t[lc].sum+t[rc].sum)%p;
	return;
}

void build(int now,int l,int r) {
	t[now].tag=0;
	if(l==r) {
		t[now].sum=w[sop[l]]%p;
		return;
	}
	int mid=l+r>>1;
	build(lson),build(rson);
	return updata(now);
}

void pushdown(int now,int l,int r) {
	if(t[now].tag) {
		ll &tag=t[now].tag;
		t[lc].tag=(t[lc].tag+tag)%p,
		t[rc].tag=(t[rc].tag+tag)%p;
		int mid=l+r>>1;
		t[lc].sum+=(mid-l+1)*tag,t[lc].sum%=p;
		t[rc].sum+=(r-mid)*tag,t[rc].sum%=p;
		tag=0;
	}
	return;
}

void modify(int now,int l,int r,int L,int R,ll x) {
	if(l==L&&r==R) {
		t[now].tag=(t[now].tag+x)%p;
		t[now].sum+=(r-l+1)*x;
		t[now].sum%=p;
		return;
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	if(R<=mid) modify(lson,L,R,x);
	else if(L>mid) modify(rson,L,R,x);
	else modify(lson,L,mid,x),modify(rson,mid+1,R,x);
	return updata(now);
}

ll query(int now,int l,int r,int L,int R) {
	if(l==L&&r==R) return t[now].sum%p;
	pushdown(now,l,r);
	int mid=l+r>>1;
	if(R<=mid) return query(lson,L,R)%p;
	else if(L>mid) return query(rson,L,R)%p;
	else return (query(lson,L,mid)+query(rson,mid+1,R))%p;
}

void modify(int u,int v,ll x) {
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		modify(1,1,n,pos[top[u]],pos[u],x);
	}
	if(depth[u]>depth[v]) swap(u,v); 
	return modify(1,1,n,pos[u],pos[v],x);
}

ll query(int u,int v) {
	ll ans=0;
	for(;top[u]!=top[v];u=fa[top[u]]) {
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		ans=(ans+query(1,1,n,pos[top[u]],pos[u]))%p;
	}
	if(depth[u]>depth[v]) swap(u,v);
	ans=(ans+query(1,1,n,pos[u],pos[v]))%p;
	return ans;
}

void modify(int u,ll x) {
	return modify(1,1,n,pos[u],pos[u]+size[u]-1,x);
}

ll query(int u) {
	return query(1,1,n,pos[u],pos[u]+size[u]-1);
}

int main() {
	input(n),input(m),input(root),input(p);
	for(int i=1;i<=n;i++)
		input(w[i]);
	for(int i=1,u,v;i<n;i++) {
		input(u),input(v);
		addedge(u,v),addedge(v,u);
	}
	dfs1(root),dfs2(root,root);
	build(1,1,n);
	for(int op,x,y;m;m--) {
		input(op);
		if(op==1) {
			ll z;
			input(x),input(y),input(z);
			modify(x,y,z%p);
		} else if(op==2) {
			input(x),input(y);
			printf("%lld\n",query(x,y)%p);
		} else if(op==3) {
			ll z;
			input(x),input(z);
			modify(x,z%p);
		} else {
			input(x);
			printf("%lld\n",query(x)%p);
		}
	}
	return 0;
}

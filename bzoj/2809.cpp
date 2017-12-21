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

struct Leftist_Tree {
	int lc,rc,dis,val;
	bool operator < (const Leftist_Tree &q) const {
		return val>q.val;
	}
};

Leftist_Tree t[MAXN];
int fa[MAXN];

#define Lc t[x].lc
#define Rc t[x].rc

int Merge(int x,int y) {
	if(!x||!y) return x+y;
	if(t[y]<t[x]) swap(x,y);
	if(t[y].val==t[x].val&&x>y) swap(x,y);
	fa[Rc=Merge(Rc,y)]=x;
	if(t[Lc].dis<t[Rc].dis) swap(Lc,Rc);
	t[x].dis=t[Rc].dis+1;
	return x;
}

int pop(int x) {
	fa[Lc]=fa[Rc]=0;
	int ans=Merge(Lc,Rc);
	Lc=Rc=0;
	return ans;
}

#undef Lc
#undef Rc

struct Edge {
	int u,v,next;
	Edge(int u=0,int v=0,int next=0):
		u(u),v(v),next(next) {}
};

Edge edge[MAXN];
int head[MAXN],cnt;

void addedge(int u,int v) {
	edge[++cnt]=Edge(u,v,head[u]);
	head[u]=cnt;
	return;
}

int n;
int root[MAXN],tot;
int size[MAXN];

ll m,ans;
ll L[MAXN],C[MAXN];
ll sum[MAXN];

void dfs(int u) {
	root[u]=++tot;
	t[tot].val=C[u];
	size[u]=1,sum[u]=C[u];
	for(int i=head[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		dfs(v);
		sum[u]+=sum[v];
		size[u]+=size[v];
		root[u]=Merge(root[u],root[v]);
	}
	while(sum[u]>m) {
		sum[u]-=t[root[u]].val;
		root[u]=pop(root[u]);
		size[u]--;
	}
	ans=max(ans,L[u]*size[u]);
	return;
}

int main() {
	input(n),input(m);
	t[0].dis=-1;
	int Root;
	for(int i=1,Bi;i<=n;i++) {
		input(Bi),input(C[i]),input(L[i]);
		if(Bi) addedge(Bi,i);
		else Root=i;
	}
	dfs(Root);
	printf("%lld\n",ans);
	return 0;
}

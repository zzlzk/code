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

#define MAXN 300010

int fa[MAXN],ch[MAXN][2];
int Max[MAXN],w[MAXN],tag[MAXN];
int st[MAXN],top;
bool rev[MAXN];

bool isroot(int x) {
	return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
}

#define lc ch[k][0]
#define rc ch[k][1]

void updata(int k) {
	Max[k]=max(Max[lc],Max[rc]),
	Max[k]=max(Max[k],w[k]);
	return;
}

void pushdown(int k) {
	if(rev[k]) {
		rev[lc]^=1,rev[rc]^=1,
		swap(lc,rc),rev[k]=0;
	}
	if(tag[k]) {
		int &d=tag[k];
		if(lc) tag[lc]+=d,Max[lc]+=d,w[lc]+=d;
		if(rc) tag[rc]+=d,Max[rc]+=d,w[rc]+=d;
		d=0;
	}
	return;
}

void rotate(int x) {
	int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
	if(!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z;
	ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y;
	ch[x][d]=y,fa[y]=x;
	updata(y),updata(x);
	return;
}

void splay(int x) {
	top=0,st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
	while(top) pushdown(st[top--]);
	while(!isroot(x)) {
		int y=fa[x],z=fa[y];
		if(!isroot(y)) {
			if(ch[z][0]==y^ch[y][0]==x) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	return;
}

void access(int x) {
	for(int t=0;x;x=fa[t=x])
		splay(x),ch[x][1]=t,updata(x);
	return;
}

void makeroot(int x) {
	access(x),splay(x),rev[x]^=1;
	return;
}

void link(int x,int y) {
	makeroot(x),fa[x]=y;
	return splay(x);
}

void split(int x,int y) {
	makeroot(x),access(y);
	return splay(y);
}

void cut(int x,int y) {
	split(x,y);
	ch[y][0]=fa[ch[y][0]]=0;
	return updata(y);
}

int find(int x) {
	access(x),splay(x);
	for(;ch[x][0];x=ch[x][0]);
	return x;
}

void modify(int x,int y,int val) {
	split(x,y);
	tag[y]+=val,Max[y]+=val,w[y]+=val;
	return;
}

int query(int x,int y) {
	split(x,y);
	return Max[y];
}

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

int main() {
	for(int n,m;~scanf("%d",&n);puts("")) {
		for(int i=0;i<=n;i++)
			head[i]=fa[i]=tag[i]=ch[i][0]=ch[i][1]=rev[i]=0;
		Max[cnt=top=0]=-2147483647;
		for(int i=1,u,v;i<n;i++) {
			input(u),input(v),
			addedge(u,v),addedge(v,u);
		}
		for(int i=1;i<=n;i++)
			input(w[i]),Max[i]=w[i];
		st[++top]=1;
		for(int k=1;k<=top;k++) {
			int u=st[k];
			for(int i=head[u],v;i;i=edge[i].next) {
				v=edge[i].v;
				if(v!=fa[u]) {
					fa[v]=u;
					st[++top]=v;
				}
			}
		}
		input(m);
		for(int op,x,y,z;m;m--) {
			input(op);
			if(op==1) {
				input(x),input(y);
				if(find(x)==find(y)) puts("-1");
				else link(x,y);
			} else if(op==2) {
				input(x),input(y);
				if(x==y||find(x)!=find(y)) puts("-1");
				else cut(x,y);
			} else if(op==3) {
				input(z),input(x),input(y);
				if(find(x)!=find(y)) puts("-1");
				else modify(x,y,z);
			} else {
				input(x),input(y);
				if(find(x)!=find(y)) puts("-1");
				else printf("%d\n",query(x,y));
			}
		}
	}
	return 0;
}

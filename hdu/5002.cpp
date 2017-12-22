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

int fa[MAXN],ch[MAXN][2],st[MAXN],top;
int Max[MAXN],Sax[MAXN],cMax[MAXN],cSax[MAXN],val[MAXN];
int size[MAXN],Set[MAXN],Plus[MAXN];
bool rev[MAXN];

bool isroot(int x) {
	return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}

#define lc ch[x][0]
#define rc ch[x][1]
#define inf 2147483647

void updata(int x) {
	size[x]=size[lc]+size[rc]+1,
	Sax[x]=-inf,cSax[x]=0,
	Max[x]=val[x],cMax[x]=1;
	if(lc) {
		int v=Max[lc],c=cMax[lc];
		if(v>Max[x]) {
			Sax[x]=Max[x],cSax[x]=cMax[x],
			Max[x]=v,cMax[x]=c;
		} else if(v==Max[x]) cMax[x]+=c;
		else if(v>Sax[x])
			Sax[x]=v,cSax[x]=c;
		else if(v==Sax[x]) cSax[x]+=c;
		v=Sax[lc],c=cSax[lc];
		if(v>Max[x]) {
			Sax[x]=Max[x],cSax[x]=cMax[x],
			Max[x]=v,cMax[x]=c;
		} else if(v==Max[x]) cMax[x]+=c;
		else if(v>Sax[x])
			Sax[x]=v,cSax[x]=c;
		else if(v==Sax[x]) cSax[x]+=c;
	}
	if(rc) {
		int v=Max[rc],c=cMax[rc];
		if(v>Max[x]) {
			Sax[x]=Max[x],cSax[x]=cMax[x],
			Max[x]=v,cMax[x]=c;
		} else if(v==Max[x]) cMax[x]+=c;
		else if(v>Sax[x])
			Sax[x]=v,cSax[x]=c;
		else if(v==Sax[x]) cSax[x]+=c;
		v=Sax[rc],c=cSax[rc];
		if(v>Max[x]) {
			Sax[x]=Max[x],cSax[x]=cMax[x],
			Max[x]=v,cMax[x]=c;
		} else if(v==Max[x]) cMax[x]+=c;
		else if(v>Sax[x])
			Sax[x]=v,cSax[x]=c;
		else if(v==Sax[x]) cSax[x]+=c;
	}
	return;
}

void pushdown(int x) {
	if(rev[x]) {
		rev[x]=0,rev[lc]^=1,rev[rc]^=1,
		swap(lc,rc);
	}
	if(Set[x]!=-inf) {
		int &tag=Set[x];
		Set[lc]=Set[rc]=tag,
		Plus[lc]=Plus[rc]=0,
		val[lc]=val[rc]=tag,
		Max[lc]=Max[rc]=tag,
		cMax[lc]=size[lc],
		cMax[rc]=size[rc],
		Sax[lc]=Sax[rc]=-inf,
		cSax[lc]=cSax[rc]=0,
		tag=-inf;
	}
	if(Plus[x]) {
		int &tag=Plus[x];
		Plus[lc]+=tag,Plus[rc]+=tag,
		Max[lc]+=tag,Max[rc]+=tag,
		val[lc]+=tag,val[rc]+=tag;
		if(Sax[lc]!=-inf) Sax[lc]+=tag;
		if(Sax[rc]!=-inf) Sax[rc]+=tag;
		tag=0;
	}
	return;
}

void rotate(int x) {
	int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
	if(!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z,
	ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y,
	ch[x][d]=y,fa[y]=x,
	updata(y),updata(x);
	return;
}

void splay(int x) {
	st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])
		st[++top]=fa[i];
	while(top) pushdown(st[top--]);
	while(!isroot(x)) {
		int y=fa[x],z=fa[y];
		if(!isroot(y)) {
			if(ch[z][1]==y^ch[y][1]==x) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	return;
}

void access(int x) {
	for(int t=0;x;x=fa[t=x])
		splay(x),ch[x][1]=t,updata(t);
	return;
}

void makeroot(int x) {
	access(x),splay(x),rev[x]^=1;
	return;
}

void split(int x,int y) {
	makeroot(x),access(y);
	return splay(y);
}

void link(int x,int y) {
	makeroot(x),fa[x]=y,updata(x);
	return splay(x);
}

void cut(int x,int y) {
	split(x,y);
	ch[y][0]=fa[ch[y][0]]=0;
	return updata(y);
}

void modify_set(int x,int y,int z) {
	split(x,y);
	Set[y]=z,val[y]=z,Max[y]=z,cMax[y]=size[y],
	cSax[y]=-inf,cSax[y]=0,Plus[y]=0;
	return;
}

void modify_Plus(int x,int y,int z) {
	split(x,y);
	Plus[y]+=z,Max[y]+=z,val[y]+=z;
	if(Sax[y]!=-inf) Sax[y]+=z;
	return;
};

void query(int x,int y) {
	split(x,y);
	if(cMax[y]==size[y]) puts("ALL SAME");
	else printf("%d %d\n",Sax[y],cSax[y]);
	return;
}

int main() {
	int T;
	input(T);
	for(int Case=1;Case<=T;Case++) {
		printf("Case #%d:\n",Case);
		int n,m;
		input(n),input(m);
		for(int i=1;i<=n;i++) {
			input(val[i]),Max[i]=val[i],
			Set[i]=Sax[i]=-inf,
			size[i]=cMax[i]=1,
			cSax[i]=Plus[i]=fa[i]=0,
			ch[i][0]=ch[i][1]=rev[i]=0;
		}
		for(int i=1,u,v;i<n;i++) {
			input(u),input(v);
			link(u,v);
		}
		for(int op,x,y,z;m;m--) {
			input(op);
			if(op==1) {
				input(x),input(y),cut(x,y),
				input(x),input(y),link(x,y);
			} else if(op==2) {
				input(x),input(y),input(z);
				modify_set(x,y,z);
			} else if(op==3) {
				input(x),input(y),input(z);
				modify_Plus(x,y,z);
			} else input(x),input(y),query(x,y);
		}
	}
	return 0;
}

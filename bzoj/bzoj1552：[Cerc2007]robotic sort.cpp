#include<cstdio>
#include<algorithm>
using namespace std;
#define inf 0x7fffffff
#define maxn 100010
struct Data {
	int data,pos;
	Data(int data=0,int pos=0):
		data(data),pos(pos) {}
	bool operator < (const Data&a)const {
		if(data==a.data) return pos<a.pos;
		return data<a.data;
	}
}a[maxn];
int rev[maxn],mn[maxn],ch[maxn][2],mnpos[maxn],data[maxn],fa[maxn],size[maxn];
int n,root=1;
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void updata(int x) {
	int l=ch[x][0],r=ch[x][1];
	mn[x]=min(data[x],min(mn[l],mn[r]));
	if(mn[x]==data[x]) mnpos[x]=x;
	else if(mn[x]==mn[l]) mnpos[x]=mnpos[l];
	else mnpos[x]=mnpos[r];
	size[x]=size[l]+size[r]+1;
	return;
}
inline void pushdown(int x) {
	if(rev[x]) {
		int l=ch[x][0],r=ch[x][1];
		rev[x]=0;
		rev[l]^=1;
		swap(ch[l][0],ch[l][1]);
		rev[r]^=1;
		swap(ch[r][0],ch[r][1]);
	}
	return;
}
inline int son(int x) {
	return ch[fa[x]][1]==x;
}
inline void rotate(int x) {
	int y=fa[x],z=fa[y],b=son(x),c=son(y),a=ch[x][!b];
	if(z) ch[z][c]=x;
	else root=x;
	fa[x]=z;
	if(a) fa[a]=y;
	ch[y][b]=a;
	ch[x][!b]=y;
	fa[y]=x;
	updata(y);
	updata(x);
	return;
}
void splay(int &x,int i) {
	while(fa[x]!=i) {
		int y=fa[x],z=fa[y];
		if(z==i) rotate(x);
		else {
			pushdown(z);
			pushdown(y);
			pushdown(x);
			if(son(x)==son(y)) {
				rotate(y);
				rotate(x);
			} else {
				rotate(x);
				rotate(x);
			}
		}
	}
	return;
}
inline int getkth(int k,int rt) {
	pushdown(rt);
	if(k==size[ch[rt][0]]+1) return rt;
	if(k<size[ch[rt][0]]+1) return getkth(k,ch[rt][0]);
	return getkth(k-1-size[ch[rt][0]],ch[rt][1]);
}
inline void reverse(int l,int r) {
	int ll=getkth(l-1,root),rr=getkth(r+1,root),p;
	splay(ll,0);
	splay(rr,ll);
	p=ch[rr][0];
	rev[p]^=1;
	swap(ch[p][0],ch[p][1]);
	return;
}
inline int getmnpos(int l,int r) {
	int ll=getkth(l-1,root);
	int rr=getkth(r+1,root);
	splay(ll,0);
	splay(rr,ll);
	return mnpos[ch[rr][0]];
}
int main() {
	n=input();
	for(int i=2;i<=n+1;i++) {
		data[i]=input();
		a[i]=Data(data[i],i);
	}
	sort(a+2,a+n+2);
	for(int i=2;i<=n+1;i++)
		data[a[i].pos]=i;
	for(int i=0;i<=n+2;i++) mn[i]=inf; 
	data[0]=data[1]=data[n+2]=inf;
	for(int i=1;i<=n+2;i++)
		fa[i]=i-1,ch[i][1]=i+1;
	ch[n+2][1]=0;
	for(int i=n+2;i>=1;i--) updata(i);
	for(int i=1;i<=n;i++) {
		int p=getmnpos(i+1,n+1);
		splay(p,0);
		printf("%d",size[ch[p][0]]);
		reverse(i+1,size[ch[p][0]]+1);
		if(i!=n) printf(" ");
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 50010
#define inf 0x7fffffff
#define lc now<<1
#define rc now<<1|1
#define mid (l+r>>1)
struct Data {
	int x,id;
	Data(int x=0,int id=0):
		x(x),id(id) {}
	bool operator <(const Data &a)const {
		return x<a.x;
	}
}data[maxn];
struct Segment_tree {
	int l,r,sum,Max,Min;
}t[maxn<<2];
int a[maxn],d[maxn];
inline int input() {
	char c=getchar();int a=1,x=0;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void updata(int now) {
	t[now].sum=t[lc].sum+t[rc].sum;
	t[now].Max=max(t[lc].Max,t[rc].Max);
	t[now].Min=min(t[lc].Min,t[rc].Min);
	return;
}
void Build(int now,int l,int r) {
	t[now].l=l;t[now].r=r;
	t[now].Max=-1;t[now].Min=inf-1;
	if(l==r) return;
	if(l<=mid) Build(lc,l,mid);
	if(r>mid) Build(rc,mid+1,r);
	return;
}
void Modify(int now,int pos) {
	int l=t[now].l,r=t[now].r;
	if(l==r) {
		t[now].sum=1;
		t[now].Min=t[now].Max=t[now].l;
		return;
	}
	if(pos<=mid) Modify(lc,pos);
	else Modify(rc,pos);
	updata(now);
	return;
}
int QueryMax(int now,int L,int R) {
	int l=t[now].l,r=t[now].r;
	if(t[now].sum==0||R<L) return -1;
	if(l>=L&&r<=R) return t[now].Max;
	int ret=-2;
	if(L<=mid) ret=max(ret,QueryMax(lc,L,R));
	if(R>mid) ret=max(ret,QueryMax(rc,L,R));
	return ret;
}
int QueryMin(int now,int L,int R) {
	int l=t[now].l,r=t[now].r;
	if(t[now].sum==0||R<L) return inf-1;
	if(l>=L&&r<=R) return t[now].Min;
	int ret=inf;
	if(L<=mid) ret=min(ret,QueryMin(lc,L,R));
	if(R>mid) ret=min(ret,QueryMin(rc,L,R));
	return ret;
}
int main() {
	int n=input(),id=1;
	for(int i=1;i<=n;++i){
		if(scanf("%d",&a[i])==EOF) a[i]=0;
		data[i]=Data(a[i],i);
	}
	sort(data+1,data+1+n);
	d[1]=data[1].x;a[data[1].id]=id;
	for(int i=2;i<=n;++i) {
		if(data[i].x!=data[i-1].x) id++;
		a[data[i].id]=id;d[id]=data[i].x;
	}
	Build(1,1,id);
	int ans=d[a[1]];
	Modify(1,a[1]);
	for(int i=2;i<=n;++i) {
		int x=QueryMax(1,1,a[i]-1);
		int y=QueryMin(1,a[i],n),t=inf;
		if(x!=-1) t=min(t,d[a[i]]-d[x]);
		if(y!=inf-1) t=min(t,d[y]-d[a[i]]);
		ans+=t;
		Modify(1,a[i]);
	}
	printf("%d",ans);
	return 0;
}

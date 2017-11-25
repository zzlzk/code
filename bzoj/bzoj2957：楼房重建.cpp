#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 100010
#define lc now<<1
#define rc now<<1|1
#define mid ((l+r)>>1)
struct Segment_tree {
	int l,r,sum;
	double Max;
}t[maxn<<2];
inline int input() {
	char c=getchar();int x=0,a=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
int calc(double k,int now) {
	if(t[now].l==t[now].r) return t[now].Max>k;
	if(t[lc].Max>k) return calc(k,lc)+t[now].sum-t[lc].sum;
	else return calc(k,rc);
}
inline void updata(int now) {
	t[now].Max=max(t[lc].Max,t[rc].Max);
	t[now].sum=t[lc].sum+calc(t[lc].Max,rc);
	return;
}
void Build(int now,int l,int r) {
	t[now].l=l,t[now].r=r;
	if(l==r) return;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	return;
}
void Modify(int now,int pos,double c) {
	int l=t[now].l,r=t[now].r;
	if(l==r) {
		t[now].Max=c;
		t[now].sum=1;
		return;
	}
	if(pos<=mid) Modify(lc,pos,c);
	else Modify(rc,pos,c);
	updata(now);
	return;
}
int main() {
	int n=input(),m=input();
	Build(1,1,n);
	for(int i=1;i<=m;++i) {
		double x,y;
		scanf("%lf%lf",&x,&y);
		Modify(1,(int)x,y/x);
		printf("%d\n",t[1].sum);
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define maxn 100010
#define lc now<<1
#define rc now<<1|1
#define mid (l+r>>1)
struct Segment_tree {
	int l,r;
	ll sum[5],tag;
}t[maxn<<3];
ll pre[maxn][5],ans[5];
inline ll input() {
	char c=getchar();ll x=0,a=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline ll Pre(Segment_tree a,int i) {
	return pre[a.r][i]-pre[a.l-1][i];
}
inline void updata(int now) {
	for(int i=0;i<3;++i)
		t[now].sum[i]=t[lc].sum[i]+t[rc].sum[i];
	return;
}
inline void pushdown(int now) {
	if(t[now].tag!=0) {
		ll &d=t[now].tag;
		Segment_tree &a=t[lc],&b=t[rc];
		a.tag+=d,b.tag+=d;
		for(int i=0;i<3;++i) {
			a.sum[i]+=d*Pre(a,i);
			b.sum[i]+=d*Pre(b,i);
		}
		d=0;
	} else return;
}
void Build(int now,int l,int r) {
	t[now].l=l,t[now].r=r;
	if(l==r) return;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	return;
}
void Modify(int now,int L,int R,ll x) {
	pushdown(now);
	int l=t[now].l,r=t[now].r;
	if(l==L&&R==r) {
		t[now].tag+=x;
		for(int i=0;i<3;++i)
			t[now].sum[i]+=x*Pre(t[now],i);
		return;
	}
	if(R<=mid) Modify(lc,L,R,x);
	else if(L>mid) Modify(rc,L,R,x);
	else {
		Modify(lc,L,mid,x);
		Modify(rc,mid+1,R,x);
	}
	updata(now);
	return;
}
ll query(int now,int L,int R,int i) {
	pushdown(now);
	int l=t[now].l,r=t[now].r;
	if(l==L&&R==r) return t[now].sum[i];
	if(R<=mid) return query(lc,L,R,i);
	else if(L>mid) return query(rc,L,R,i);
	else {
		ll a=query(lc,L,mid,i);
		ll b=query(rc,mid+1,R,i);
		return a+b;
	}
}
ll gcd(ll a,ll b) {
	return b==0ll?a:gcd(b,a%b);
}
int main() {
	for(int i=1;i<=100000;++i) {
		pre[i][0]=pre[i-1][0]+1ll;
		pre[i][1]=pre[i-1][1]+(ll)i;
		pre[i][2]=pre[i-1][2]+(ll)i*i;
	}
	int n=(int)input(),m=(int)input();
	Build(1,1,n-1);
	while(m--) {
		char op[10];ll x;
		scanf("%s",op);
		ll l=input(),r=input();
		if(op[0]=='C') {
			x=input();
			Modify(1,l,r-1,x);
		} else {
			for(int i=0;i<3;++i)
				ans[i]=query(1,l,r-1,i);
			ll a=(r-l*r)*ans[0]+(l+r-1)*ans[1]-ans[2];
			ll b=((r-l+1)*(r-l))>>1,c=gcd(a,b);
			printf("%lld/%lld\n",a/c,b/c);
		}
	}
	return 0;
}

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

#define MAXN 25
#define MAXM 1000010

struct Segment_Tree {
	int sum,Min,Max;
	int tag1,tag2;
};

struct Ans {
	int sum,Min,Max;
	Ans(int sum=0,int Min=0,int Max=0):
		sum(sum),Min(Min),Max(Max) {}
	Ans operator + (const Ans &q) {
		Ans ret=*this;
		ret.sum+=q.sum;
		ret.Min=min(ret.Min,q.Min);
		ret.Max=max(ret.Max,q.Max);
		return ret;
	}
};

struct Segment_Forest {
	Segment_Tree t[MAXM<<2];

#define lc now<<1
#define rc now<<1|1

	void updata(int now) {
		t[now].sum=t[lc].sum+t[rc].sum;
		t[now].Min=min(t[lc].Min,t[rc].Min);
		t[now].Max=max(t[lc].Max,t[rc].Max);
		return;
	}
	void pushdown(int now,int l,int r) {
		if(t[now].tag1!=-1) {
			int &tag=t[now].tag1;
			t[lc].tag1=t[rc].tag1=tag,
			t[lc].tag2=t[rc].tag2=0,
			t[lc].Min=t[rc].Min=tag,
			t[lc].Max=t[rc].Max=tag;
			int mid=l+r>>1;
			t[lc].sum=tag*(mid-l+1),
			t[rc].sum=tag*(r-mid),
			tag=-1;
		}
		if(t[now].tag2) {
			int &tag=t[now].tag2;
			t[lc].tag2+=tag,t[rc].tag2+=tag,
			t[lc].Min+=tag,t[rc].Min+=tag,
			t[lc].Max+=tag,t[rc].Max+=tag;
			int mid=l+r>>1;
			t[lc].sum+=tag*(mid-l+1),
			t[rc].sum+=tag*(r-mid);
			tag=0;
		}
		return;
	}

#define lson lc,l,mid
#define rson rc,mid+1,r
	
	void build(int now,int l,int r) {
		t[now].sum=t[now].Min=t[now].Max=0;
		t[now].tag1=-1,t[now].tag2=0;
		if(l==r) return;
		int mid=l+r>>1;
		build(lson),build(rson);
		return;
	}

	void modify(int now,int l,int r,int L,int R,int v,int op) {
		if(l==L&&R==r) {
			if(op==1) {
				t[now].tag2+=v;
				t[now].Min+=v,t[now].Max+=v;
				t[now].sum+=v*(r-l+1);
			} else {
				t[now].tag1=v,t[now].tag2=0;
				t[now].Min=v,t[now].Max=v,
				t[now].sum=v*(r-l+1);
			}
			return;
		}
		pushdown(now,l,r);
		int mid=l+r>>1;
		if(R<=mid) modify(lson,L,R,v,op);
		else if(L>mid) modify(rson,L,R,v,op);
		else {
			modify(lson,L,mid,v,op),
			modify(rson,mid+1,R,v,op);
		}
		updata(now);
		return;
	}
	Ans query(int now,int l,int r,int L,int R) {
		if(l==L&&R==r) return Ans(t[now].sum,t[now].Min,t[now].Max);
		pushdown(now,l,r);
		int mid=l+r>>1;
		if(R<=mid) return query(lson,L,R);
		else if(L>mid) return query(rson,L,R);
		else return query(lson,L,mid)+query(rson,mid+1,R);
	}

#undef lc
#undef rc
#undef lson
#undef rson

};

Segment_Forest t[MAXN];

int main() {
	int n,m,q;
	while(scanf("%d%d%d",&n,&m,&q)!=EOF) {
		for(int i=1;i<=n;i++)
			t[i].build(1,1,m);
		for(int x,y,xx,yy,op,v;q;q--) {
			input(op),input(x),input(y),input(xx),input(yy);
			if(op!=3) {
				input(v);
				for(int i=x;i<=xx;i++)
					t[i].modify(1,1,m,y,yy,v,op);
			} else {
				Ans ans=Ans(0,2147483647,-2147483647);
				for(int i=x;i<=xx;i++)
					ans=ans+t[i].query(1,1,m,y,yy);
				printf("%d %d %d\n",ans.sum,ans.Min,ans.Max);
			}
		}
	}
	return 0;
}

#include<cstdio>

void input(int &x) {
	x=0; register char c=getchar();
	for(;c<48||c>57;c=getchar());
	for(;c>=48&&c<=57;c=getchar())
		x=x*10+c-48;
	return;
}

#define MAXN 10000001
#define MAXM 1001

struct Segment_tree {
	int l,r;
	bool col;
};

Segment_tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define mid (l+r>>1)

void build(int now,int l,int r) {
	t[now].l=l,t[now].r=r;
	if(l==r) return;
	build(lc,l,mid),build(rc,mid+1,r),
	t[now].col=t[lc].col&&t[rc].col;
	return;
}

bool Can_draw=false;

#define l t[now].l
#define r t[now].r

void modify(int now,int L,int R) {
	if(t[now].col) return;
	if(l==L&&R==r) {
		Can_draw=t[now].col=true;
		return;
	}
	if(R<=mid) modify(lc,L,R);
	else if(L>mid) modify(rc,L,R);
	else modify(lc,L,mid),modify(rc,mid+1,R);
	t[now].col=t[lc].col&&t[rc].col;
	return;
}

#undef lc
#undef rc

int L[MAXM],R[MAXM];

int main() {
	int n,m;
	input(n),input(m);
	build(1,1,n);
	for(n=1;n<=m;n++)
		input(L[n]),input(R[n]);
	n=0;
	for(;m;m--) {
		Can_draw=false;
		modify(1,L[m],R[m]);
		n+=Can_draw;
	}
	printf("%d\n",n);
	return 0;
}

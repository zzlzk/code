#include<cmath>
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

struct Segment_Tree {
    ll sum,Max;
};

Segment_Tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
    t[now].sum=t[lc].sum+t[rc].sum,
    t[now].Max=max(t[lc].Max,t[rc].Max);
    return;
}

void build(int now,int l,int r) {
    if(l==r) {
        input(t[now].sum),
        t[now].Max=t[now].sum;
        return;
    }
    int mid=l+r>>1;
    build(lson),build(rson);
    return updata(now);
}

void modify(int now,int l,int r,int L,int R) {
    if(t[now].Max<=1) return;
    if(l==r) {
        t[now].Max=t[now].sum=sqrt(t[now].sum);
        return;
    }
    int mid=l+r>>1;
    if(R<=mid) modify(lson,L,R);
    else if(L>mid) modify(rson,L,R);
    else modify(lson,L,mid),modify(rson,mid+1,R);
    return updata(now);
}

ll query(int now,int l,int r,int L,int R) {
    if(l==L&&R==r) return t[now].sum;
    int mid=l+r>>1;
    if(R<=mid) return query(lson,L,R);
    else if(L>mid) return query(rson,L,R);
    else return query(lson,L,mid)+query(rson,mid+1,R);
}

int main() {
    int n,m,k,l,r;
    input(n),build(1,1,n);
    for(input(m);m;m--) {
        input(k),input(l),input(r);
        if(l>r) swap(l,r);
        if(k) printf("%lld\n",query(1,1,n,l,r));
        else modify(1,1,n,l,r);
    }
    return 0;
}

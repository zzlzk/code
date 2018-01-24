#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
 
template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}
 
#define MAXN 100010
 
int n,m,p;
 
struct Segment_tree {
    int l,r;
    ll sum,tag1,tag2;
};
 
Segment_tree t[MAXN<<2];
 
#define lc now<<1
#define rc now<<1|1
 
void updata(int now) {
    t[now].sum=(t[lc].sum+t[rc].sum)%p;
    return;
}
 
void build(int now,int l,int r) {
    t[now].l=l,t[now].r=r,t[now].tag1=1,t[now].tag2=0;
    if(l==r) {
        input(t[now].sum);
        t[now].sum%=p;
        return;
    }
    int mid=l+r>>1;
    build(lc,l,mid),
    build(rc,mid+1,r);
    updata(now);
    return;
}
 
#define len(x) (x.r-x.l+1)
 
void pushdown(int now) {
    if(t[now].tag1!=1) {
        ll &d=t[now].tag1;
        t[lc].tag1=(t[lc].tag1*d)%p;
        t[rc].tag1=(t[rc].tag1*d)%p;
        t[lc].sum=(t[lc].sum*d)%p;
        t[rc].sum=(t[rc].sum*d)%p;
        t[lc].tag2=(t[lc].tag2*d)%p;
        t[rc].tag2=(t[rc].tag2*d)%p;
        d=1ll;
    }
    if(t[now].tag2) {
        ll &d=t[now].tag2;
        t[lc].tag2=(t[lc].tag2+d)%p;
        t[rc].tag2=(t[rc].tag2+d)%p;
        t[lc].sum=(t[lc].sum+len(t[lc])*d)%p;
        t[rc].sum=(t[rc].sum+len(t[rc])*d)%p;
        d=0ll;
    }
    return;
}
 
#undef len
 
void modify(int now,int L,int R,ll x) {
    if(t[now].l==L&&R==t[now].r) {
        t[now].sum=(t[now].sum+(R-L+1)*x)%p;
        t[now].tag2=(t[now].tag2+x)%p;
        return;
    }
    pushdown(now);
    int mid=t[now].l+t[now].r>>1;
    if(R<=mid) modify(lc,L,R,x);
    else if(L>mid) modify(rc,L,R,x);
    else {
        modify(lc,L,mid,x),
        modify(rc,mid+1,R,x);
    }
    updata(now);
    return;
}
 
void change(int now,int L,int R,ll x) {
    if(t[now].l==L&&t[now].r==R) {
        t[now].sum=(t[now].sum*x)%p;
        t[now].tag1=(t[now].tag1*x)%p;
        t[now].tag2=(t[now].tag2*x)%p;
        return;
    }
    pushdown(now);
    int mid=t[now].l+t[now].r>>1;
    if(R<=mid) change(lc,L,R,x);
    else if(L>mid) change(rc,L,R,x);
    else {
        change(lc,L,mid,x),
        change(rc,mid+1,R,x);
    }
    updata(now);
    return;
}
 
ll query(int now,int L,int R) {
    if(t[now].l==L&&R==t[now].r) return t[now].sum%p;
    pushdown(now);
    int mid=t[now].l+t[now].r>>1;
    if(R<=mid) return query(lc,L,R)%p;
    else if(L>mid) return query(rc,L,R)%p;
    else return (query(lc,L,mid)+query(rc,mid+1,R))%p;
}
 
int main() {
    input(n),input(p);
    build(1,1,n);
    input(m);
    ll k;
    for(int op,x,y;m;m--) {
        input(op),input(x),input(y);
        if(op==1) {
            input(k);
            change(1,x,y,k);
        } else if(op==2) {
            input(k);
            modify(1,x,y,k);
        } else printf("%lld\n",query(1,x,y));
    }
    return 0;
}
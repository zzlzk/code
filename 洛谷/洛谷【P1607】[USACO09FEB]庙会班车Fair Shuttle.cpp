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

#define MAXK 50010
#define MAXN 20010
#define MAXM 110

struct Data {
    int l,r,sum;
    Data(int l=0,int r=0,int sum=0):
        l(l),r(r),sum(sum) {}
    bool operator < (const Data &q) const {
        if(r!=q.r) return r<q.r;
        return l<q.l;
    }
};

Data mon[MAXK];

struct Segment_Tree {
    int l,r,tag,Max;
};

Segment_Tree t[MAXN<<2];

void updata(int now) {
    t[now].Max=max(t[now<<1].Max,t[now<<1|1].Max);
    return;
}

void build(int now,int l,int r) {
    t[now].l=l,t[now].r=r;
    if(l==r) {
        t[now].Max=0;
        return;
    }
    int mid=l+r>>1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    updata(now);
    return;
}

void pushdown(int now) {
    int &d=t[now].tag;
    t[now<<1].tag+=d;
    t[now<<1|1].tag+=d;
    t[now<<1].Max+=d;
    t[now<<1|1].Max+=d;
    d=0;
    return;
}

void Modify(int now,int L,int R,int x) {
    int l=t[now].l,r=t[now].r;
    if(l==L&&R==r) {
        t[now].tag+=x;
        t[now].Max+=x;
        return;
    }
    if(t[now].tag) pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) Modify(now<<1,L,R,x);
    else if(L>mid) Modify(now<<1|1,L,R,x);
    else {
        Modify(now<<1,L,mid,x);
        Modify(now<<1|1,mid+1,R,x);
    } 
    updata(now);
    return;
}

int query(int now,int L,int R) {
    int l=t[now].l,r=t[now].r;
    if(l==L&&R==r) return t[now].Max;
    if(t[now].tag) pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) return query(now<<1,L,R);
    else if(L>mid) return query(now<<1|1,L,R);
    else {
        int a=query(now<<1,L,mid),
            b=query(now<<1|1,mid+1,R);
        return max(a,b);
    }
}

int main() {
    int k,n,m;
    input(k),input(n),input(m);
    for(int i=1,x,y,c;i<=k;i++) {
        input(x),input(y),input(c);
        mon[i]=Data(x,y-1,c);
    }
    sort(mon+1,mon+k+1);
    build(1,1,n);
    int ans=0;
    for(int i=1,l,r,Max;i<=k;i++) {
        l=mon[i].l,r=mon[i].r;
        Max=min(mon[i].sum,m-query(1,l,r));
        ans+=Max;
        Modify(1,l,r,Max);
    }
    printf("%d\n",ans);
    return 0;
}

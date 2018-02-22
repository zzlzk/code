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
 
struct Data {
    int f[2][2];
    int l,r;
    Data() { memset(f,0,sizeof(f)); }
    Data operator + (const Data &q) {
        Data ret;
        ret.l=l,ret.r=q.r;
        ret.f[0][0]=min(f[0][1]+q.f[1][0]-(r==q.l),min(f[0][0]+q.f[1][0],f[0][1]+q.f[0][0]));
        ret.f[0][1]=min(f[0][1]+q.f[1][1]-(r==q.l),min(f[0][1]+q.f[0][1],f[0][0]+q.f[1][1]));
        ret.f[1][0]=min(f[1][1]+q.f[1][0]-(r==q.l),min(f[1][1]+q.f[0][0],f[1][0]+q.f[1][0]));
        ret.f[1][1]=min(f[1][1]+q.f[1][1]-(r==q.l),min(f[1][1]+q.f[0][1],f[1][0]+q.f[1][1]));
        return ret;
    }
};
 
struct Segment_Tree {
    Data x;
    int tag;
};
 
int a[MAXN];
Segment_Tree t[MAXN<<2];
 
#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
 
void updata(int now) {
    t[now].x=t[lc].x+t[rc].x;
    return;
}
 
void pushdown(int now) {
    if(t[now].tag) {
        t[lc].tag+=t[now].tag,t[rc].tag+=t[now].tag,
        t[lc].x.l+=t[now].tag,t[rc].x.l+=t[now].tag,
        t[lc].x.r+=t[now].tag,t[rc].x.r+=t[now].tag,
        t[now].tag=0;
    }
    return;
}
 
void build(int now,int l,int r) {
    t[now].tag=0;
    if(l==r) {
        t[now].x.l=t[now].x.r=a[l],
        t[now].x.f[0][0]=0,t[now].x.f[0][1]=1,
        t[now].x.f[1][0]=1,t[now].x.f[1][1]=1;
        return;
    }
    int mid=l+r>>1;
    build(lson),build(rson);
    return updata(now);
}
 
void modify(int now,int l,int r,int L,int R,int v) {
    if(l==L&&R==r) {
        t[now].x.l+=v,t[now].x.r+=v,t[now].tag+=v;
        return;
    }
    pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) modify(lson,L,R,v);
    else if(L>mid) modify(rson,L,R,v);
    else modify(lson,L,mid,v),modify(rson,mid+1,R,v);
    return updata(now);
}
 
Data query(int now,int l,int r,int L,int R) {
    if(l==L&&R==r) return t[now].x;
    pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) return query(lson,L,R);
    if(L>mid) return query(rson,L,R);
    return query(lson,L,mid)+query(rson,mid+1,R);
}
 
int main() {
    int n,m;
    input(n);
    for(int i=1;i<=n;i++) input(a[i]);
    for(int i=1;i<n;i++) a[i]=a[i+1]-a[i];
    char op[3];
    if(n==1) {
        input(m);
        for(int l,r,a,b;m;m--) {
            scanf("%s",op);
            if(op[0]=='A') input(l),input(r),input(a),input(b);
            else input(l),input(r),puts("1");
        }
        return 0;
    }
    build(1,1,n-1),input(m);
    for(int l,r,a,b;m;m--) {
        scanf("%s",op);
        if(op[0]=='A') {
            input(l),input(r),input(a),input(b);
            if(l^1) modify(1,1,n-1,l-1,l-1,a);
            if(l^r) modify(1,1,n-1,l,r-1,b);
            if(r^n) modify(1,1,n-1,r,r,-(a+(r-l)*b));
        } else {
            input(l),input(r),
            printf("%d\n",l==r?1:(query(1,1,n-1,l,r-1).f[1][1]));
        }
    }
    return 0;
}

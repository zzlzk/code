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

#define MAXN 200010
#define inf 2147483647

int a[MAXN],b[MAXN];
int mex[MAXN],Next[MAXN],Last[MAXN];
bool exist[MAXN];

struct Query {
    int l,r,id;
    bool operator < (const Query &q) const {
        return l<q.l;
    }
};

Query q[MAXN];
int ans[MAXN];

int Rank;
int Lower_bound(int x) {
    int l=1,r=Rank;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(b[mid]<x) l=mid+1;
        else r=mid-1;
    }
    return l;
}

int Min[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void build(int now,int l,int r) {
    Min[now]=inf;
    if(l==r) {
        Min[now]=mex[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson),build(rson);
    return;
}

void pushdown(int now,int l,int r) {
    if(l==r||Min[now]==inf) return;
    Min[lc]=min(Min[now],Min[lc]);
    Min[rc]=min(Min[now],Min[rc]);
    return;
}

void modify(int now,int l,int r,int L,int R,int x) {
    pushdown(now,l,r);
    if(l==L&&R==r) {
        Min[now]=min(Min[now],x);
        return;
    }
    int mid=(l+r)>>1;
    if(R<=mid) modify(lson,L,R,x);
    else if(L>mid) modify(rson,L,R,x);
    else modify(lson,L,mid,x),modify(rson,mid+1,R,x);
    return;
}

int query(int now,int l,int r,int pos) {
    pushdown(now,l,r);
    if(l==r) return Min[now];
    int mid=(l+r)>>1;
    if(pos<=mid) return query(lson,pos);
    return query(rson,pos);
}

int main() {
    int n,m;
    input(n),input(m);
    for(int i=1;i<=n;i++)
        input(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    Rank=1;
    for(int i=2;i<=n;i++)
        if(b[i]!=b[i-1]) b[++Rank]=b[i];
    for(int i=1,j,k=0;i<=n;i++) {
        exist[j=Lower_bound(a[i])]=1;
        if(a[i]==k)
            while(exist[j]) {
                k++;
                if(b[++j]!=k) break;
            }
        mex[i]=k;
    }
    build(1,1,n);
    for(int i=n,j;i;i--) {
        j=Lower_bound(a[i]),
        Next[i]=Last[j],Last[j]=i;
    }
    for(int i=1;i<=m;i++)
        input(q[i].l),input(q[q[i].id=i].r);
    sort(q+1,q+m+1);
    for(int i=1,L=1;i<=m;i++) {
        for(;L<q[i].l;L++) {
            if(!Next[L]) Next[L]=n+1;
            modify(1,1,n,L,Next[L]-1,a[L]);
        }
        ans[q[i].id]=query(1,1,n,q[i].r);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
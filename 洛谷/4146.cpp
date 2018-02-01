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

#define MAXN 50010
#define inf 2147483647

int a[MAXN];
int fa[MAXN],ch[MAXN][2],root,tot;
int val[MAXN],Max[MAXN],size[MAXN];
int rev[MAXN],tag[MAXN];

#define lc ch[now][0]
#define rc ch[now][1]

void updata(int now) {
    if(!now) return;
    Max[now]=val[now];
    if(lc) Max[now]=max(Max[now],Max[lc]);
    if(rc) Max[now]=max(Max[now],Max[rc]);
    size[now]=1;
    if(lc) size[now]+=size[lc];
    if(rc) size[now]+=size[rc];
    return;
}

void pushdown(int now) {
    if(tag[now]) {
#define d tag[now]
        if(lc) tag[lc]+=d,Max[lc]+=d,val[lc]+=d;
        if(rc) tag[rc]+=d,Max[rc]+=d,val[rc]+=d;
        d=0;
#undef d
    }
    if(rev[now]) {
        swap(lc,rc);
        if(lc) rev[lc]^=1;
        if(rc) rev[rc]^=1;
        rev[now]=0;
    }
    return;
}

int build(int l,int r,int dad) {
    if(l>r) return 0;
    int mid=l+r>>1,now=++tot;
    rev[now]=tag[now]=0,
    size[now]=1,fa[now]=dad,
    val[now]=Max[now]=a[mid],
    lc=build(l,mid-1,now),
    rc=build(mid+1,r,now),
    updata(now);
    return now;
}

#define get(x) (ch[fa[x]][1]==x)

void rotate(int x) {
    int y=fa[x],z=fa[y],d=get(x);
    pushdown(y),pushdown(x),
    ch[y][d]=ch[x][d^1],fa[ch[y][d]]=y;
    ch[x][d^1]=y,fa[y]=x,fa[x]=z;
    if(z) ch[z][ch[z][1]==y]=x;
    return updata(y),updata(x);
}

void splay(int x,int dad) {
    while(fa[x]!=dad) {
        int y=fa[x],z=fa[y];
        if(z!=dad) {
            if(get(y)^get(x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!dad) root=x;
    return;
}

int getkth(int k) {
    for(int now=root,t;true;) {
        pushdown(now);
        if(lc&&size[lc]>=k) now=lc;
        else {
            t=1;
            if(lc) t+=size[lc];
            if(k<=t) return now;
            k-=t,now=rc;
        }
    }
    return 0;
}

void split(int l,int r) {
    l=getkth(l-1),r=getkth(r+1);
    return splay(l,0),splay(r,l);
}

#define interval ch[ch[root][1]][0]

void modify(int l,int r,int v) {
    split(l,r),tag[interval]+=v,
    Max[interval]+=v,val[interval]+=v;
    return updata(ch[root][1]),updata(root);
}

void reverse(int l,int r) {
    split(l,r);
    return (void)(rev[interval]^=1);
}

int query(int l,int r) {
    split(l,r);
    return Max[interval];
}

int main() {
    int n,m;
    input(n),input(m),
    a[1]=-inf,a[n+2]=inf,
    root=build(1,n+2,0);
    for (int op,l,r,v;m;m--) {
        input(op),input(l),input(r),l++,r++;
        switch(op) {
            case 1: input(v),modify(l,r,v); break;
            case 2: reverse(l,r); break;
            case 3: printf("%d\n",query(l,r)); break;
        }
    }
    return 0;
}
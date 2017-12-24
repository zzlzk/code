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

struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};

Edge edge[MAXN<<1];
int head[MAXN],cnt;

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}

int fa[MAXN],size[MAXN],son[MAXN],depth[MAXN];
int pos[MAXN],top[MAXN],timee;

void dfs1(int u) {
    size[u]=1;
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(v!=fa[u]) {
            fa[v]=u;
            depth[v]=depth[u]+1;
            dfs1(v);
            size[u]+=size[v];
            if(!son[u]||size[v]>size[son[u]])
                son[u]=v;
        }
    }
    return;
}

void dfs2(int u,int topfa) {
    top[u]=topfa,pos[u]=++timee;
    if(!son[u]) return;
    dfs2(son[u],topfa);
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
    return;
}

struct Segment_Tree {
    int sum,tag;
    Segment_Tree(): sum(0),tag(-1) {}
};

int n,m;
Segment_Tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
    t[now].sum=t[lc].sum+t[rc].sum;
    return;
}

void pushdown(int now,int l,int r) {
    if(t[now].tag!=-1) {
        int &tag=t[now].tag;
        t[lc].tag=tag,t[rc].tag=tag;
        int mid=l+r>>1;
        t[lc].sum=tag*(mid-l+1),
        t[rc].sum=tag*(r-mid),
        tag=-1;
    }
    return;
}

void modify(int now,int l,int r,int L,int R,int x) {
    if(l==L&&R==r) {
        t[now].tag=x;
        t[now].sum=x*(r-l+1);
        return;
    }
    pushdown(now,l,r);
    int mid=l+r>>1;
    if(R<=mid) modify(lson,L,R,x);
    else if(L>mid) modify(rson,L,R,x);
    else modify(lson,L,mid,x),modify(rson,mid+1,R,x);
    return updata(now);
}

void modify(int u,int v,int x) {
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        modify(1,1,n,pos[top[u]],pos[u],x);
    }
    if(depth[u]>depth[v]) swap(u,v);
    return modify(1,1,n,pos[u],pos[v],x);
}

void modify(int u,int x) {
    return modify(1,1,n,pos[u],pos[u]+size[u]-1,x);
}

int main() {
    input(n);
    for(int u=2,v;u<=n;u++) {
        input(v);
        v++;
        addedge(u,v),addedge(v,u);
    }
    dfs1(1),dfs2(1,1);
    input(m);
    char op[15];
    for(int x,ans;m;m--) {
        scanf("%s",op),input(x);
        if(op[0]=='i') {
            ans=t[1].sum;
            modify(1,x+1,1);
            ans-=t[1].sum;
            printf("%d\n",ans>0?ans:-ans);
        } else {
            ans=t[1].sum;
            modify(x+1,0);
            ans-=t[1].sum;
            printf("%d\n",ans>0?ans:-ans);
        }
    }
    return 0;
}

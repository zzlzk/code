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

#define MAXN 30010

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
int pos[MAXN],sop[MAXN],top[MAXN],timee;

void dfs1(int u) {
    size[u]=1,depth[u]=depth[fa[u]]+1;
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(v!=fa[u]) {
            fa[v]=u;
            dfs1(v);
            size[u]+=size[v];
            if(!son[u]||size[v]>size[son[u]])
                son[u]=v;
        }
    }
    return;
}

void dfs2(int u,int topfa) {
    top[u]=topfa,pos[u]=++timee,sop[timee]=u;
    if(!son[u]) return;
    dfs2(son[u],topfa);
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
    return;
}

struct Segment_Tree {
    int sum,Max;
};

Segment_Tree t[MAXN<<2];
int w[MAXN],n,Q;

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
    t[now].sum=t[lc].sum+t[rc].sum;
    t[now].Max=max(t[lc].Max,t[rc].Max);
    return;
}

void build(int now,int l,int r) {
    if(l==r) {
        t[now].sum=t[now].Max=w[sop[l]];
        return;
    }
    int mid=l+r>>1;
    build(lson),build(rson);
    return updata(now);
}

void modify(int now,int l,int r,int p,int x) {
    if(l==r) {
        t[now].sum=t[now].Max=x;
        return;
    }
    int mid=l+r>>1;
    if(p<=mid) modify(lson,p,x);
    else modify(rson,p,x);
    return updata(now);
}

int querysum(int now,int l,int r,int L,int R) {
    if(l==L&&R==r) return t[now].sum;
    int mid=l+r>>1;
    if(R<=mid) return querysum(lson,L,R);
    else if(L>mid) return querysum(rson,L,R);
    else return querysum(lson,L,mid)+querysum(rson,mid+1,R);
}

int querymax(int now,int l,int r,int L,int R) {
    if(l==L&&R==r) return t[now].Max;
    int mid=l+r>>1;
    if(R<=mid) return querymax(lson,L,R);
    else if(L>mid) return querymax(rson,L,R);
    else return max(querymax(lson,L,mid),querymax(rson,mid+1,R));
}

int QSUM(int u,int v) {
    int ans=0;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        ans+=querysum(1,1,n,pos[top[u]],pos[u]);
    }
    if(depth[u]>depth[v]) swap(u,v);
    ans+=querysum(1,1,n,pos[u],pos[v]);
    return ans;
}

int QMAX(int u,int v) {
    int ans=-2147483647;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        ans=max(ans,querymax(1,1,n,pos[top[u]],pos[u]));
    }
    if(depth[u]>depth[v]) swap(u,v);
    ans=max(ans,querymax(1,1,n,pos[u],pos[v]));
    return ans;
}

char op[10];

int main() {
    input(n);
    for(int i=1,u,v;i<n;i++) {
        input(u),input(v);
        addedge(u,v),addedge(v,u);
    }
    for(int i=1;i<=n;i++) input(w[i]);
    dfs1(1),dfs2(1,1),build(1,1,n);
    input(Q);
    for(int x,y;Q;Q--) {
        scanf("%s",op);
        input(x),input(y);
        if(op[1]=='H') modify(1,1,n,pos[x],y);
        else if(op[1]=='M') printf("%d\n",QMAX(x,y));
        else printf("%d\n",QSUM(x,y));
    }
    return 0;
}


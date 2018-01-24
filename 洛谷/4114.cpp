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
    int u,v,w,next;
    Edge(int u=0,int v=0,int w=0,int next=0):
        u(u),v(v),w(w),next(next) {}
};

Edge edge[MAXN<<1];
int head[MAXN],cnt;

void addedge(int u,int v,int w) {
    edge[++cnt]=Edge(u,v,w,head[u]);
    head[u]=cnt;
    return;
}

int fa[MAXN],son[MAXN],size[MAXN],depth[MAXN];
int top[MAXN],dfn[MAXN],timee;

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
    top[u]=topfa,dfn[u]=++timee;
    if(!son[u]) return;
    dfs2(son[u],topfa);
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
    return;
}

int Max[MAXN<<2],n;

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
    Max[now]=max(Max[lc],Max[rc]);
    return;
}

void build(int now,int l,int r) {
    Max[now]=0;
    if(l==r) return;
    int mid=l+r>>1;
    build(lson),build(rson);
    return;
}

void modify(int now,int l,int r,int pos,int x) {
    if(l==r) {
        Max[now]=x;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid) modify(lson,pos,x);
    else modify(rson,pos,x);
    return updata(now);
}

int query(int now,int l,int r,int L,int R) {
    if(L>R) return 0;
    if(l==L&&r==R) return Max[now];
    int mid=l+r>>1;
    if(R<=mid) return query(lson,L,R);
    else if(L>mid) return query(rson,L,R);
    else return max(query(lson,L,mid),query(rson,mid+1,R));
}

int query(int u,int v) {
    if(u==v) return 0;
    int ans=0;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        ans=max(ans,query(1,1,n,dfn[top[u]],dfn[u]));
    }
    if(depth[u]>depth[v]) swap(u,v);
    ans=max(ans,query(1,1,n,dfn[u]+1,dfn[v]));
    return ans;
}

int main() {
    input(n);
    for(int i=1,u,v,w;i<n;i++) {
        input(u),input(v),input(w),
        addedge(u,v,w),addedge(v,u,w);
    }
    dfs1(1),dfs2(1,1),build(1,1,n);
    for(int i=1;i<=2*(n-1);i+=2) {
        if(depth[edge[i].v]<depth[edge[i].u]) swap(edge[i].u,edge[i].v);
        modify(1,1,n,dfn[edge[i].v],edge[i].w);
    }
    char s[10];
    for(int a,b;true;) {
        scanf("%s",s);
        if(s[0]=='D') break;
        input(a),input(b);
        if(s[0]=='C') modify(1,1,n,dfn[edge[2*a-1].v],b);
        else printf("%d\n",query(a,b));
    }
    return 0;
}

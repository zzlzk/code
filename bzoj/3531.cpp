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
    size[u]=1,depth[u]=depth[fa[u]]+1;
    for(int i=head[u],v;i;i=edge[i].next) {
        v=edge[i].v;
        if(fa[u]!=v) {
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
    int sum,Max;
};

Segment_Tree t[MAXN*20];
int root[MAXN],LC[MAXN*20],RC[MAXN*20],tot;
int w[MAXN],c[MAXN],n,m;

#define lc LC[now]
#define rc RC[now]
#define lson lc,l,mid
#define rson rc,mid+1,r

void updata(int now) {
    t[now].sum=t[lc].sum+t[rc].sum;
    t[now].Max=max(t[lc].Max,t[rc].Max);
    return;
}

void change(int &now,int l,int r,int p,int x) {
    if(!now) now=++tot;
    if(l==r) {
        t[now].sum=t[now].Max=x;
        return;
    }
    int mid=l+r>>1;
    if(p<=mid) change(lson,p,x);
    else change(rson,p,x);
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

int querysum(int C,int u,int v) {
    int ans=0;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        ans+=querysum(root[C],1,n,pos[top[u]],pos[u]);
    }
    if(depth[u]>depth[v]) swap(u,v);
    ans+=querysum(root[C],1,n,pos[u],pos[v]);
    return ans;
}

int querymax(int C,int u,int v) {
    int ans=-2147483647;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        ans=max(ans,querymax(root[C],1,n,pos[top[u]],pos[u]));
    }
    if(depth[u]>depth[v]) swap(u,v);
    ans=max(ans,querymax(root[C],1,n,pos[u],pos[v]));
    return ans;
}

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++)
        input(w[i]),input(c[i]);
    for(int i=1,u,v;i<n;i++) {
        input(u),input(v);
        addedge(u,v),addedge(v,u);
    }
    dfs1(1),dfs2(1,1);
    for(int i=1;i<=n;i++)
        change(root[c[i]],1,n,pos[i],w[i]);
    for(int x,y;m;m--) {
        char op[5];
        scanf("%s",op),input(x),input(y);
        if(op[1]=='C') {
            change(root[c[x]],1,n,pos[x],0),
            change(root[c[x]=y],1,n,pos[x],w[x]);
        } else if(op[1]=='W') change(root[c[x]],1,n,pos[x],w[x]=y);
        else if(op[1]=='S') printf("%d\n",querysum(c[x],x,y));
        else printf("%d\n",querymax(c[x],x,y));
    }
    return 0;
}


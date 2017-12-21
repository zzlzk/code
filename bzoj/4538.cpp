#include<queue>
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
#define MAXM 200010

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
    priority_queue<int> heap1,heap2;
    void push1(int x) {
        heap1.push(x);
        return;
    }
    void push2(int x) {
        heap2.push(x);
        return;
    }
    int get() {
        while(!heap2.empty()&&heap1.top()==heap2.top())
            heap2.pop(),heap1.pop();
        return heap1.empty()?-1:heap1.top();
    }
};

int n,m;
Segment_Tree t[MAXN<<2];

#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r

void modify(int now,int l,int r,int L,int R,int x,int op) {
    if(l==L&&R==r) {
        if(!op) t[now].push1(x);
        else t[now].push2(x);
        return;
    }
    int mid=l+r>>1;
    if(R<=mid) return modify(lson,L,R,x,op);
    else if(L>mid) return modify(rson,L,R,x,op);
    else modify(lson,L,mid,x,op),modify(rson,mid+1,R,x,op);
    return;
}

int ans;

void query(int now,int l,int r,int p) {
    ans=max(ans,t[now].get());
    if(l==r) return;
    int mid=l+r>>1;
    if(p<=mid) return query(lson,p);
    else return query(rson,p);
}

struct Segment {
    int l,r;
    Segment(int l=0,int r=0):
        l(l),r(r) {}
    bool operator < (const Segment &q)const {
        return l<q.l;
    }
};

Segment seg[MAXN];

void modify(int u,int v,int x,int op) {
    int _=0;
    for(;top[u]!=top[v];u=fa[top[u]]) {
        if(depth[top[u]]<depth[top[v]]) swap(u,v);
        seg[++_]=Segment(pos[top[u]],pos[u]);
    }
    if(depth[u]>depth[v]) swap(u,v);
    seg[++_]=Segment(pos[u],pos[v]);
    sort(seg+1,seg+_+1);
    int last=0;
    for(int i=1;i<=_;last=seg[i++].r)
        if(last+1<=seg[i].l-1)
            modify(1,1,n,last+1,seg[i].l-1,x,op);
    if(last+1<=n) modify(1,1,n,last+1,n,x,op);
    return;
}

struct _modify {
    int u,v,w;
    _modify(int u=0,int v=0,int w=0):
        u(u),v(v),w(w) {}
};

_modify M[MAXM];

int main() {
    input(n),input(m);
    for(int i=1,u,v;i<n;i++) {
        input(u),input(v);
        addedge(u,v),addedge(v,u);
    }
    dfs1(1),dfs2(1,1);
    for(int op,x,y,z,i=1;i<=m;i++) {
        input(op),input(x);
        if(op==0) {
            input(y),input(z);
            M[i]=_modify(x,y,z);
            modify(x,y,z,op);
        } else if(op==1)
            modify(M[x].u,M[x].v,M[x].w,op);
        else if(op==2) {
            ans=-1;
            query(1,1,n,pos[x]);
            printf("%d\n",ans);
        }
    }
    return 0;
}

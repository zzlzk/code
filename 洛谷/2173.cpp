#include<map>
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

#define MAXC 12
#define MAXN 10010

int val[MAXN];
int cnt[MAXN][MAXC];
int st[MAXN],top;

struct Link_Cut_Tree {
    
    int fa[MAXN],ch[MAXN][2];
    int Max[MAXN],val[MAXN];
    bool rev[MAXN];

#define lc ch[x][0]
#define rc ch[x][1]

    bool isroot(int x) {
        return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
    }

    void updata(int x) {
        Max[x]=max(val[x],max(Max[lc],Max[rc]));
        return;
    }

    void pushdown(int x) {
        if(rev[x]) {
            rev[lc]^=1,rev[rc]^=1,rev[x]=0,
            swap(lc,rc);
        }
        return;
    }

    void rotate(int x) {
        int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
        if(!isroot(y)) ch[z][ch[z][1]==y]=x;
        fa[x]=z,
        ch[y][d^1]=ch[x][d],fa[ch[x][d]]=y,
        ch[x][d]=y,fa[y]=x,
        updata(y),updata(x);
        return;
    }

    void splay(int x) {
        st[++top]=x;
        for(int i=x;!isroot(i);i=fa[i])
            st[++top]=fa[i];
        while(top) pushdown(st[top--]);
        while(!isroot(x)) {
            int y=fa[x],z=fa[y];
            if(!isroot(y)) {
                if(ch[z][1]==y^ch[y][1]==x) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
        return;
    }

    void access(int x) {
        for(int t=0;x;x=fa[t=x])
            splay(x),ch[x][1]=t,updata(x);
        return;
    }

    void makeroot(int x) {
        access(x),splay(x),rev[x]^=1;
        return;
    }

    void split(int x,int y) {
        makeroot(x),access(y);
        return splay(y);
    }

    void link(int x,int y) {
        makeroot(x),fa[x]=y;
        return splay(x);
    }

    void cut(int x,int y) {
        split(x,y);
        ch[y][0]=fa[ch[y][0]]=0;
        return updata(y);
    }

    void modify(int x,int y) {
        access(x),splay(x),val[x]=y;
        return;
    }

    int query(int x,int y) {
        split(x,y);
        return Max[y];
    }

    int find(int x) {
        access(x),splay(x);
        while(lc) x=lc;
        return x;
    }

#undef lc
#undef rc

};

Link_Cut_Tree LCT[MAXC];

struct Edge {
    int u,v;
    Edge(int u=0,int v=0):
        u(u),v(v) {}
    bool operator < (const Edge &q) const {
        if(u!=q.u) return u<q.u;
        return v<q.v;
    }
};

map<Edge,int> color;

int main() {
    int n,m,c,q;
    input(n),input(m),input(c),input(q);
    val[0]=-2147483647;
    for(int i=1;i<=n;i++)
        input(val[i]);
    for(int i=1;i<=c;i++)
        for(int j=0;j<=n;j++)
            LCT[i].val[j]=LCT[i].Max[j]=val[j];
    for(int i=1,u,v,w;i<=m;i++) {
        input(u),input(v),input(w),++w,
        LCT[w].link(u,v),
        cnt[u][w]++,cnt[v][w]++,
        color[Edge(u,v)]=w,color[Edge(v,u)]=w;
    }
    for(int op,x,y,z;q;q--) {
        input(op);
        if(op==0) {
            input(x),input(y);
            val[x]=y;
            for(int i=1;i<=c;i++)
                LCT[i].modify(x,y);
        } else if(op==1) {
            input(x),input(y),input(z),++z;
            int col=color[Edge(x,y)];
            if(!col) puts("No such edge.");
            else if(col==z) puts("Success.");
            else if(cnt[x][z]>1||cnt[y][z]>1) puts("Error 1.");
            else if(LCT[z].find(x)==LCT[z].find(y)) puts("Error 2.");
            else {
                puts("Success.");
                cnt[x][z]++,cnt[y][z]++,
                cnt[x][col]--,cnt[y][col]--,
                color[Edge(x,y)]=z,color[Edge(y,x)]=z,
                LCT[col].cut(x,y),LCT[z].link(x,y);
            }
        } else if(op==2) {
            input(z),input(x),input(y),++z;
            if(LCT[z].find(x)!=LCT[z].find(y)) puts("-1");
            else printf("%d\n",LCT[z].query(x,y));
        }
    }
    return 0;
}
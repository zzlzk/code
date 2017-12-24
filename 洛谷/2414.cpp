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

struct Query {
    
    int id,x,y;
    
    void scan(int _id) {
        id=_id,input(x),input(y);
        return;
    }

    bool operator < (const Query &q) const {
        return y<q.y;
    }

};

Query ask[MAXN];
int ql[MAXN],qr[MAXN];

struct Fenwick_Tree {
    
    int t[MAXN],n;

    Fenwick_Tree(): n(MAXN) {
        memset(t,0,sizeof(t));
    }

    int lowbit(int x) {
        return x&(-x);
    }

    void modify(int k,int x) {
        for(;k<=n;k+=lowbit(k))
            t[k]+=x;
        return;
    }

    int query(int k) {
        int ans=0;
        for(;k;k-=lowbit(k))
            ans+=t[k];
        return ans;
    }

    int query(int l,int r) {
        return query(r)-query(l-1);
    }

};

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

int L[MAXN],R[MAXN],timee;

void get_dfn(int x) {
    L[x]=++timee;
    for(int i=head[x];i;i=edge[i].next)
        get_dfn(edge[i].v);
    R[x]=timee;
    return;
}

struct Trie {
    
    Trie *ch[26];
    Trie *fail;
    Trie *fa;
    int end,id;

    Trie(): end(0) {
        for(int i=0;i<26;i++)
            ch[i]=NULL;
        fa=fail=NULL;
    }

};

int ans[MAXN];

Trie memory_pool[MAXN],*gg=memory_pool;

struct AC_automaton {
    
    Trie *root;
    Trie *Id[MAXN];
    queue<Trie*> q;
    Fenwick_Tree bit;
    int cnt,timee;

    AC_automaton(): cnt(0),timee(0) {
        root=gg++;
        root->id=cnt++;
    }

    void insert() {
        Trie *now=root;
        char c=getchar();
        for(;!(c>='a'&&c<='z'||c=='B'||c=='P');c=getchar());
        for(int id;c>='a'&&c<='z'||c=='B'||c=='P';c=getchar())
            if(c>='a'&&c<='z') {
                id=c-'a';
                if(now->ch[id]==NULL) {
                    now->ch[id]=gg++;
                    now->ch[id]->id=cnt++;
                    now->ch[id]->fa=now;
                }
                now=now->ch[id];
            } else {
                if(c=='B') now=now->fa;
                else Id[now->end=++timee]=now;
            }
        return;
    }

    void get_fail() {
        q.push(root);
        while(!q.empty()) {
            Trie *now=q.front();
            q.pop();
            if(now->fail!=NULL)
                addedge(now->fail->id,now->id);
            for(int i=0;i<26;i++) {
                if(now->ch[i]==NULL) continue;
                if(now==root) now->ch[i]->fail=root;
                else {
                    Trie *pos;
                    for(pos=now->fail;pos;pos=pos->fail)
                        if(pos->ch[i]!=NULL) {
                            now->ch[i]->fail=pos->ch[i];
                            break;
                        }
                    if(pos==NULL) now->ch[i]->fail=root;
                }
                q.push(now->ch[i]);
            }
        }
        return get_dfn(0);
    }

    void dfs(Trie *now) {
        bit.modify(L[now->id],1);
        if(now->end) {
            for(int i=ql[now->end];i<=qr[now->end];i++)
                ans[ask[i].id]=bit.query(L[Id[ask[i].x]->id],R[Id[ask[i].x]->id]);
        }
        for(int i=0;i<26;i++)
            if(now->ch[i]) dfs(now->ch[i]);
        bit.modify(L[now->id],-1);
        return;
    }
};

AC_automaton ac;

int main() {
    ac.insert();
    ac.get_fail();
    int Q;
    input(Q);
    for(int i=0;i<Q;i++)
        ask[i].scan(i);
    sort(ask,ask+Q);
    memset(qr,-1,sizeof(qr));
    for(int i=0;i<Q;i++) {
        if(!i||ask[i-1].y!=ask[i].y)
            ql[ask[i].y]=i;
        if(i==Q-1||ask[i+1].y!=ask[i].y)
            qr[ask[i].y]=i;
    }
    ac.dfs(ac.root);
    for(int i=0;i<Q;i++)
        printf("%d\n",ans[i]);
    return 0;
}

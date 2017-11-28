#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 100010

struct Leftist_Tree {
    int lc,rc,val,dis;
    bool operator < (const Leftist_Tree &q)const {
        return val<q.val;
    }
    bool operator == (const Leftist_Tree &q)const {
        return val==q.val;
    }
};

Leftist_Tree t[MAXN];

int fa[MAXN];

#define Lc t[x].lc
#define Rc t[x].rc

int Merge(int x,int y) {
    if(!x||!y) return x+y;
    if(t[y]<t[x]) swap(x,y);
    if(t[x]==t[y]&&x>y) swap(x,y);
    fa[Rc=Merge(Rc,y)]=x;
    if(t[Lc].dis<t[Rc].dis)
        swap(Lc,Rc);
    t[x].dis=t[Rc].dis+1;
    return x;
}

bool not_intree[MAXN];

void pop(int x) {
    not_intree[x]=true;
    fa[Lc]=fa[Rc]=0;
    Merge(Lc,Rc);
    return;
}

#undef Lc
#undef Rc

int Find(int x) {
    for(;fa[x];x=fa[x]);
    return x;
}

int main() {
    int n,m;
    input(n),input(m);
    for(int i=1;i<=n;i++)
        input(t[i].val);
    t[0].dis=-1;
    for(int op,x,y;m;m--) {
        input(op);
        if(op==1) {
            input(x),input(y);
            if(x==y) continue;
            if(not_intree[x]||not_intree[y]) continue;
            Merge(Find(x),Find(y));
        } else {
            input(x);
            if(not_intree[x]) puts("-1");
            else {
                printf("%d\n",t[y=Find(x)].val),
                pop(y);
            }
        }
    }
    return 0;
}

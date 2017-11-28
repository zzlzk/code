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

struct Leftist_Tree {
    int lc,rc,val,dis;
    bool operator < (const Leftist_Tree &q)const {
        return val>q.val;
    }
    bool operator == (const Leftist_Tree &q)const {
        return val==q.val;
    }
};

Leftist_Tree t[MAXN];

int fa[MAXN];

int Find(int x) {
    for(;fa[x];x=fa[x]);
    return x;
}

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

int pop(int x) {
    fa[Lc]=fa[Rc]=0;
    int ans=Merge(Lc,Rc);
    Lc=0,Rc=0;
    return ans;
}

#undef Lc
#undef Rc

int n;

void Clear() {
    for(int i=0;i<=n;i++) {
        fa[i]=0;
        t[i].lc=t[i].rc=t[i].dis=0;
    }
    t[0].dis=-1;
    return;
}

int main() {
    while(~scanf("%d",&n)) {
        Clear();
        for(int i=1;i<=n;i++)
            input(t[i].val);
        int m;
        input(m);
        for(int x,y;m;m--) {
            input(x),input(y);
            x=Find(x),y=Find(y);
            if(x==y) puts("-1");
            else {
                t[x].val>>=1,t[y].val>>=1;
                int rt1=Merge(x,y),
                    rt2=Merge(pop(x),pop(y));
                printf("%d\n",t[Merge(rt1,rt2)].val);
            }
        }
    }
    return 0;
}
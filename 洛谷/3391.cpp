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

struct Splay_Tree {
    int val,size;
    int tag_rev;
    int fa,ch[2];
};

Splay_Tree t[MAXN];
int SIZE,root;
int a[MAXN];

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void updata(int k) {
    t[k].size=t[lc].size+t[rc].size+1;
    return;
}

void pushdown(int k) {
    if(t[k].tag_rev) {
        swap(lc,rc);
        t[lc].tag_rev^=1;
        t[rc].tag_rev^=1;
        t[k].tag_rev=0;
    }
    return;
}

void rotate(int x) {
    int y=t[x].fa,z=t[y].fa;
    int d=(t[y].ch[1]==x)^1;
    pushdown(y),pushdown(x);
    t[y].ch[d^1]=t[x].ch[d],t[t[x].ch[d]].fa=y;
    t[x].ch[d]=y,t[y].fa=x;
    t[z].ch[t[z].ch[1]==y]=x,t[x].fa=z;
    updata(y),updata(x);
    return;
}

void splay(int x,int fa=0) {
    while(t[x].fa!=fa) {
        int y=t[x].fa,z=t[y].fa;
        if(z!=fa) {
            if((t[y].ch[1]==x)^(t[z].ch[1]==y))
                rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!fa) root=x;
    return;
}

int build(int l,int r,int fa) {
    if(l>r) return 0;
    int mid=l+r>>1;
    int k=++SIZE;
    t[k].val=a[mid],t[k].fa=fa,t[k].tag_rev=0;
    lc=build(l,mid-1,k),rc=build(mid+1,r,k);
    updata(k);
    return k;
}

int getkth(int x) {
    for(int k=root;true;) {
        pushdown(k);
        if(t[lc].size>=x) k=lc;
        else if(t[lc].size+1==x)return k;
        else x-=t[lc].size+1,k=rc;
    }
}

void flip(int l,int r) {
    l=getkth(l),r=getkth(r+2);
    splay(l),splay(r,l);
    t[t[t[root].ch[1]].ch[0]].tag_rev^=1;
    return;
}

#define inf 2147483647

void Print(int k) {
    pushdown(k);
    if(lc) Print(lc);
    if(t[k].val!=inf&&t[k].val!=-inf)
        printf("%d ",t[k].val);
    if(rc) Print(rc);
    return;
}

int main() {
    int n,m;
    input(n),input(m);
    a[1]=-inf,a[n+2]=inf;
    for(int i=1;i<=n;i++)
        a[i+1]=i;
    root=build(1,n+2,0);
    for(int l,r;m;m--) {
        input(l),input(r);
        flip(l,r);
    }
    Print(root);puts("");
    return 0;
}


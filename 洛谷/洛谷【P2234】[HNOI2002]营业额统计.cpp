/*
treap:

#include<cstdio>
#include<cstdlib>
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

#define MAXN 33000

struct Treap {
    int val,pri;
    int size;
    int ch[2];
};

Treap t[MAXN];
int SIZE,root;

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void updata(int k) {
    t[k].size=t[lc].size+t[rc].size+1;
    return;
}

void rotate(int &y,int d) {
    int x=t[y].ch[d^1];
    t[y].ch[d^1]=t[x].ch[d];
    t[x].ch[d]=y;
    updata(y),updata(x);
    y=x;
    return;
}

void insert(int &k,int val) {
    if(!k) {
        k=++SIZE;
        t[k].val=val;
        t[k].pri=rand();
        t[k].size=1;
        return;
    }
    t[k].size++;
    if(t[k].val<val) {
        insert(rc,val);
        if(t[rc].pri<t[k].pri) rotate(k,0);
    } else {
        insert(lc,val);
        if(t[lc].pri<t[k].pri) rotate(k,1);
    }
    return;
}

int pre,suf;

void getpre(int k,int val) {
    if(!k) return;
    if(t[k].val<val) {
        pre=k;
        getpre(rc,val);
    } else getpre(lc,val);
    return;
}

void getsuf(int k,int val) {
    if(!k) return;
    if(t[k].val<val) getsuf(rc,val);
    else {
        suf=k;
        getsuf(lc,val);
    }
    return;
}

int main() {
    int n,ans;
    input(n),input(ans);
    insert(root,ans);
    for(int i=1,a;i<n;i++) {
        input(a);
        pre=0,getpre(root,a);
        suf=0,getsuf(root,a);
        if(pre&&!suf) ans+=a-t[pre].val;
        else if(!pre&&suf) ans+=t[suf].val-a;
        else if(pre&&suf) ans+=min(a-t[pre].val,t[suf].val-a);
        insert(root,a);
    }
    printf("%d\n",ans);
    return 0;
}


*/


// splay


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

#define MAXN 33000

struct Splay_Tree {
    int val;
    int ch[2],fa;
};

Splay_Tree t[MAXN];
int root,SIZE;

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void rotate(int x) {
    int y=t[x].fa,z=t[y].fa;
    int d=(t[y].ch[1]==x)^1;
    t[y].ch[d^1]=t[x].ch[d],t[t[x].ch[d]].fa=y;
    t[x].ch[d]=y,t[y].fa=x;
    t[z].ch[t[z].ch[1]==y]=x,t[x].fa=z;
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
    if(fa==0) root=x;
    return;
}

void insert(int x) {
    int k=root,fa=0;
    while(k&&t[k].val!=x)
        k=t[fa=k].ch[t[k].val<x];
    if(!k) {
        k=++SIZE;
        if(fa) t[fa].ch[t[fa].val<x]=k;
        t[k].fa=fa,lc=rc=0;
        t[k].val=x;
    }
    return splay(k);
}

void getrank(int x) {
    int k=root;
    if(k==0) return;
    while(t[k].ch[t[k].val<x]&&t[k].val!=x)
        k=t[k].ch[t[k].val<x];
    return splay(k);
}

int getpre(int x) {
    getrank(x);
    int k=root;
    if(t[k].val<=x) return k;
    for(k=lc;rc;k=rc);
    return k;
}

int getsuf(int x) {
    getrank(x);
    int k=root;
    if(t[k].val>=x) return k;
    for(k=rc;lc;k=lc);
    return k;
}

#define inf 2147483640

int main() {
    int n,ans;
    input(n),input(ans);
    insert(-inf),insert(inf),insert(ans);
    for(int i=1,x;i<n;i++) {
        input(x);
        int pre=t[getpre(x)].val;
        int suf=t[getsuf(x)].val;
        ans+=min(abs(x-pre),abs(x-suf));
        insert(x);
    }
    printf("%d\n",ans);
    return 0;
}
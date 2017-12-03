/*

splay

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
    int ch[2],fa;
    int val,size,cnt;
};

Splay_Tree t[MAXN];
int SIZE,root;

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void updata(int k) {
    t[k].size=t[lc].size+t[rc].size+t[k].cnt;
    return;
}

void rotate(int x) {
    int y=t[x].fa,z=t[y].fa;
    int d=(t[y].ch[1]==x)^1;
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
    if(fa==0) root=x;
    return;
}

void insert(int x) {
    int k=root,fa=0;
    while(k&&t[k].val!=x)
        k=t[fa=k].ch[t[k].val<x];
    if(k) t[k].cnt++;
    else {
        k=++SIZE;
        if(fa) t[fa].ch[t[fa].val<x]=k;
        t[k].fa=fa,lc=rc=0;
        t[k].size=t[k].cnt=1;
        t[k].val=x;
    }
    return splay(k);
}

int getrank(int x) {
    int k=root;
    if(k==0) return -1;
    while(t[k].ch[t[k].val<x]&&t[k].val!=x)
        k=t[k].ch[t[k].val<x];
    splay(k);
    return t[t[root].ch[0]].size;
}

int getkth(int x) {
    int k=root;
    if(t[k].size<x) return -1;
    while(true) {
        if(x>t[lc].size+t[k].cnt) {
            x-=t[lc].size+t[k].cnt;
            k=rc;
        } else if(x<=t[lc].size) k=lc;
        else break;
    }
    return t[k].val;
}

int getpre(int x) {
    getrank(x);
    int k=root;
    if(t[k].val<x) return k;
    for(k=lc;rc;k=rc);
    return k;
}

int getsuf(int x) {
    getrank(x);
    int k=root;
    if(t[k].val>x) return k;
    for(k=rc;lc;k=lc);
    return k;
}

void del(int x) {
    int pre=getpre(x),suf=getsuf(x);
    splay(pre),splay(suf,pre);
    int del_pos=t[suf].ch[0];
    if(t[del_pos].cnt>1) {
        t[del_pos].cnt--;
        splay(del_pos);
    } else t[suf].ch[0]=0,t[del_pos].fa=0;
    return;
}

#define inf 2147483647

int main() {
    insert(-inf),insert(inf);
    int n;
    input(n);
    for(int op,x;n;n--) {
        input(op),input(x);
        if(op==1) insert(x);
        else if(op==2) del(x);
        else if(op==3) printf("%d\n",getrank(x));
        else if(op==4) printf("%d\n",getkth(x+1));
        else if(op==5) printf("%d\n",t[getpre(x)].val);
        else printf("%d\n",t[getsuf(x)].val);
    }
    return 0;
}


*/


//treap

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

#define MAXN 100010

struct Treap {
    int val,pri;
    int size,cnt;
    int ch[2];
};

Treap t[MAXN];
int SIZE,root;

void updata(int x) {
    t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+t[x].cnt;
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

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void insert(int &k,int val) {
    if(!k) {
        k=++SIZE;
        t[k].val=val,t[k].pri=rand(),
        t[k].size=t[k].cnt=1;
        return;
    }
    t[k].size++;
    if(t[k].val==val) t[k].cnt++;
    else if(t[k].val<val) {
        insert(rc,val);
        if(t[rc].pri>t[k].pri) rotate(k,0);
    } else {
        insert(lc,val);
        if(t[lc].pri>t[k].pri) rotate(k,1);
    }
    return;
}

void del(int &k,int val) {
    if(!k) return;
    if(t[k].val==val) {
        if(t[k].cnt>1) {
            t[k].size--;
            t[k].cnt--;
            return;
        }
        if(lc*rc==0) k=lc+rc;
        else {
            rotate(k,t[lc].pri>t[rc].pri);
            del(k,val);
        }
    } else {
        t[k].size--;
        if(t[k].val<val) del(rc,val);
        else del(lc,val);
    }
    return;
}

int getkth(int k,int x) {
    if(k==0) return 0;
    if(x<=t[lc].size) return getkth(lc,x);
    if(x>t[lc].size+t[k].cnt)
        return getkth(rc,x-t[lc].size-t[k].cnt);
    else return t[k].val;
}

int getrank(int k,int x) {
    if(k==0) return 0;
    if(t[k].val==x) return t[lc].size+1;
    if(t[k].val<x)
        return t[lc].size+t[k].cnt+getrank(rc,x);
    return getrank(lc,x);
}

int ans;

void getpre(int k,int x) {
    if(k==0) return;
    if(t[k].val<x) {
        ans=k;
        getpre(rc,x);
    } else getpre(lc,x);
}

void getsuf(int k,int x) {
    if(k==0) return;
    if(t[k].val>x) {
        ans=k;
        getsuf(lc,x);
    } else getsuf(rc,x);
}

int main() {
    int n;
    input(n);
    for(int op,x;n;n--) {
        input(op),input(x);
        if(op==1) insert(root,x);
        else if(op==2) del(root,x);
        else if(op==3) printf("%d\n",getrank(root,x));
        else if(op==4) printf("%d\n",getkth(root,x));
        else if(op==5) {
            getpre(root,x);
            printf("%d\n",t[ans].val);
        } else {
            getsuf(root,x);
            printf("%d\n",t[ans].val);
        }
    }
    return 0;
}
#include<cstdio>
#include<cstring>
#include<cstdlib>
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

#define MAXN 300010

struct Treap {
    int val,pri;
    int ch[2],size,cnt;
};

Treap t[MAXN];
int root,size;

#define lc t[k].ch[0]
#define rc t[k].ch[1]

void updata(int k) {
    t[k].size=t[lc].size+t[rc].size+t[k].cnt;
    return;
}

void rotate(int &y,int d) {
    int x=t[y].ch[d^1];
    t[y].ch[d^1]=t[x].ch[d],
    t[x].ch[d]=y;
    updata(y),updata(x);
    y=x;
    return;
}

void insert(int &k,int x) {
    if(!k) {
        k=++size;
        t[k].val=x,t[k].pri=rand();
        t[k].cnt=t[k].size=1;
        lc=rc=0;
        return;
    }
    t[k].size++;
    if(t[k].val==x) t[k].cnt++;
    else if(t[k].val>x) {
        insert(lc,x);
        if(t[lc].pri>t[k].pri) rotate(k,1);
    } else {
        insert(rc,x);
        if(t[rc].pri>t[k].pri) rotate(k,0);
    }
    return;
}

void del(int &k,int x) {
    if(!k) return;
    if(t[k].val==x) {
        if(t[k].cnt>1) t[k].cnt--,t[k].size--;
        else {
            if(lc*rc==0) k=lc+rc;
            else {
                if(t[lc].pri>t[rc].pri) rotate(k,1);
                else rotate(k,0);
                del(k,x);
            }
        }
    } else {
        t[k].size--;
        if(t[k].val>x) del(lc,x);
        else del(rc,x);
    }
    return;
}

int getkth(int k,int x) {
    if(!k) return 0;
    if(x<=t[lc].size) return getkth(lc,x);
    if(x>t[lc].size+t[k].cnt)
        return getkth(rc,x-t[lc].size-t[k].cnt);
    return t[k].val;
}

int getrank(int k,int x) {
    if(k==0) return 0;
    if(t[k].val==x) return t[lc].size+1;
    if(t[k].val>x) return getrank(lc,x);
    return t[lc].size+t[k].cnt+getrank(rc,x);
}

int pre,suf;

void getpre(int k,int x) {
    if(!k) return;
    if(t[k].val<x) {
        pre=k;
        getpre(rc,x);
    } else getpre(lc,x);
    return;
}

void getsuf(int k,int x) {
    if(!k) return;
    if(t[k].val>x) {
        suf=k;
        getsuf(lc,x);
    } else getsuf(rc,x);
    return;
}

int main() {
    int n;
    input(n);
    for(int op,x;n;n--) {
        input(op),input(x);
        if(op==1) insert(root,x);
        if(op==2) del(root,x);
        if(op==3) printf("%d\n",getrank(root,x));
        if(op==4) printf("%d\n",getkth(root,x));
        if(op==5) getpre(root,x),printf("%d\n",t[pre].val);
        if(op==6) getsuf(root,x),printf("%d\n",t[suf].val);
    }
    return 0;
}
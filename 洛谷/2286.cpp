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

#define MAXN 80010

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
        if(t[k].pri>t[rc].pri) rotate(k,0);
    } else {
        insert(lc,val);
        if(t[k].pri>t[lc].pri) rotate(k,1);
    }
    return;
}

void del(int &k,int val) {
    if(!k) return;
    if(t[k].val==val) {
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

int flag;

#define mod 1000000

#define Abs(x) ((x)>0?(x):(-(x)))

int main() {
    int n;
    input(n);
    int ans=0;
    for(int a,b;n;n--) {
        input(a),input(b);
        if(flag==a) insert(root,b);
        else {
            if(t[root].size) {
                pre=0,getpre(root,b);
                suf=0,getsuf(root,b);
                int c;
                if(!pre||!suf) c=pre+suf;
                else if(b-t[pre].val<=t[suf].val-b) c=pre;
                else c=suf;
                ans=(ans+Abs(t[c].val-b))%mod;
                del(root,t[c].val);
            } else flag=a,insert(root,b);
        }
    }
    printf("%d\n",ans%mod);
    return 0;
}

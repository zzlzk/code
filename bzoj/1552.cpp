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

int fa[MAXN],ch[MAXN][2],size[MAXN];
int st[MAXN],top,root;
bool rev[MAXN];

#define lc ch[k][0]
#define rc ch[k][1]

void flip(int k) {
    rev[k]^=1,swap(lc,rc);
    return;
}

void pushdown(int k) {
    if(rev[k]) {
        rev[k]=false;
        if(lc) flip(lc);
        if(rc) flip(rc);
    }
    return;
}

void updata(int k) {
    size[k]=size[lc]+size[rc]+1;
    return;
}

void rotate(int x) {
    int y=fa[x],z=fa[y],d=(ch[y][1]==x)^1;
    if(z) ch[z][ch[z][1]==y]=x;
    fa[x]=z,ch[y][d^1]=ch[x][d];
    if(ch[x][d]) fa[ch[x][d]]=y;
    ch[x][d]=y,fa[y]=x;
    updata(y),updata(x);
    return;
}

void splay(int x,int dad=0) {
    st[++top]=x;
    for(int i=x;i!=dad;i=fa[i])
        st[++top]=fa[i];
    while(top) pushdown(st[top--]);
    while(fa[x]!=dad) {
        int y=fa[x],z=fa[y];
        if(z!=dad) {
            if(ch[z][1]==y^ch[y][1]==x) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!dad) root=x;
    return;
}

int getkth(int k,int x) {
    pushdown(k);
    if(size[lc]+1==x) return k;
    if(x<=size[lc]) return getkth(lc,x);
    return getkth(rc,x-size[lc]-1);
}

void reverse(int l,int r) {
    l=getkth(root,l-1),r=getkth(root,r+1);
    splay(l),splay(r,ch[l][1]);
    rev[ch[r][0]]^=1,
    swap(ch[ch[r][0]][0],ch[ch[r][0]][1]);
    return;
}

void getsuf(int k) {
    pushdown(k);
    k=rc;
    while(true) {
        pushdown(k);
        if(lc) k=lc;
        else break;
    }
    return splay(k);
}

void del(int k) {
    fa[lc]=fa[k],ch[fa[k]][0]=lc;
    return updata(fa[k]);
}

int build(int l,int r,int dad) {
    if(l>r) return 0;
    int mid=l+r>>1;
    fa[mid]=dad,size[mid]=r-l+1;
    if(l==r) return l;
    ch[mid][0]=build(l,mid-1,mid),
    ch[mid][1]=build(mid+1,r,mid);
    return mid;
}

struct Data {
    int x,id;
    bool operator < (const Data &q) const {
        if(x!=q.x) return x<q.x;
        return id<q.id;
    }
};

Data a[MAXN];

int main() {
    int n;
    input(n);
    for(int i=1;i<=n;i++)
        input(a[i].x),a[i].id=i;
    sort(a+1,a+n+1);
    root=build(1,n+1,0);
    for(int i=1;i<=n;i++) {
        splay(a[i].id);
        flip(ch[root][0]);
        printf("%d%c",size[ch[root][0]]+i,i==n?'\n':' ');
        getsuf(root),del(ch[root][0]);
    }
    return 0;
}

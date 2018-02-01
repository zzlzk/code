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
 
#define MAXN 300010
#define MAXQ 300010
 
int a[MAXN];
int dfn[MAXN],Map[MAXN],timee;
int Next[MAXN],End[MAXN],fa[MAXN];
 
int Find(int x) {
    return fa[x]==x?x:fa[x]=Find(fa[x]);
}
 
struct Query {
    int op,x,y;
    void get_Query() {
        char s[3];
        scanf("%s",s);
        switch(s[0]) {
            case 'U': op=1,input(x),input(y); break;
            case 'A': {
                switch(s[1]) {
                    case '1': op=2,input(x),input(y); break;
                    case '2': op=3,input(x),input(y); break;
                    case '3': op=4,input(x); break;
                }
                break;
            }
            case 'F': {
                switch(s[1]) {
                    case '1': op=5,input(x); break;
                    case '2': op=6,input(x); break;
                    case '3': op=7; break;
                }
                break;
            }
        }
        return;
    }
};
 
Query q[MAXQ];
 
int Max[MAXN<<2],tag[MAXN<<2];
 
#define lc now<<1
#define rc now<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
 
void updata(int now) {
    Max[now]=max(Max[lc],Max[rc]);
    return;
}
 
void pushdown(int now) {
    if(tag[now]) {
        tag[lc]+=tag[now];
        tag[rc]+=tag[now];
        Max[lc]+=tag[now];
        Max[rc]+=tag[now];
        tag[now]=0;
    }
    return;
}
 
void build(int now,int l,int r) {
    if(l==r) {
        Max[now]=Map[l];
        return;
    }
    int mid=l+r>>1;
    build(lson),build(rson);
    return updata(now);
}
 
void modify(int now,int l,int r,int L,int R,int v) {
    if(l==L&&R==r) {
        tag[now]+=v,Max[now]+=v;
        return;
    }
    pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) modify(lson,L,R,v);
    else if(L>mid) modify(rson,L,R,v);
    else modify(lson,L,mid,v),modify(rson,mid+1,R,v);
    return updata(now);
}
 
int query(int now,int l,int r,int L,int R) {
    if(l==L&&R==r) return Max[now];
    pushdown(now);
    int mid=l+r>>1;
    if(R<=mid) return query(lson,L,R);
    if(L>mid) return query(rson,L,R);
    return max(query(lson,L,mid),query(rson,mid+1,R));
}
 
int main() {
    int n,m;
    input(n);
    for(int i=1;i<=n;i++)
        input(a[fa[i]=End[i]=i]);
    input(m);
    for(int i=1;i<=m;i++) {
        q[i].get_Query();
        if(q[i].op==1) {
            int fx=Find(q[i].x),fy=Find(q[i].y);
            if(fx==fy) continue;
            Next[End[fa[fy]=fx]]=fy,End[fx]=End[fy];
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=i*(Find(i)==i);j;j=Next[j])
            Map[dfn[j]=++timee]=a[j];
    build(1,1,n);
    for(int i=1;i<=n;i++)
        fa[i]=End[i]=i;
    for(int i=1,x,y,op,l,r,v;i<=m;i++) {
        x=q[i].x,y=q[i].y,op=q[i].op;
        switch(op) {
            case 1: {
                int fx=Find(x),fy=Find(y);
                if(fx!=fy) End[fa[fy]=fx]=End[fy];
                break;
            }
            case 2: l=r=dfn[x],v=y; break;
            case 3: l=dfn[Find(x)],r=dfn[End[Find(x)]],v=y; break;
            case 4: l=1,r=n,v=x; break;
            case 5: l=r=dfn[x]; break;
            case 6: l=dfn[Find(x)],r=dfn[End[Find(x)]]; break;
            case 7: l=1,r=n; break;
        }
        if(op>1&&op<5) modify(1,1,n,l,r,v);
        else if(op!=1) printf("%d\n",query(1,1,n,l,r));
    }
    return 0;
}
?
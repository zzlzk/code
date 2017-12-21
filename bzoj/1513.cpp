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
 
#define MAXN 2050
#define MAXM 2050
 
#define lson now<<1,l,mid
#define rson now<<1|1,mid+1,r
 
int n,m,q;
 
struct Segment_Tree_y {
    int Max[MAXM],tag[MAXM];
    void modify(int now,int l,int r,int L,int R,int v) {
        Max[now]=max(Max[now],v);
        if(l==L&&R==r) {
            tag[now]=max(tag[now],v);
            return;
        }
        int mid=l+r>>1;
        if(R<=mid) modify(lson,L,R,v);
        else if(L>mid) modify(rson,L,R,v);
        else {
            modify(lson,L,mid,v),
            modify(rson,mid+1,R,v);
        }
        return;
    }
    int query(int now,int l,int r,int L,int R) {
        if(l==L&&R==r) return Max[now];
        int mid=l+r>>1;
        if(R<=mid) return max(tag[now],query(lson,L,R));
        else if(L>mid) return max(tag[now],query(rson,L,R));
        else return max(tag[now],max(query(lson,L,mid),query(rson,mid+1,R)));
    }
};
 
struct Segment_Tree_x {
    Segment_Tree_y Max[MAXN],tag[MAXN];
    void modify(int now,int l,int r,int L,int R,int yL,int yR,int v) {
        Max[now].modify(1,1,m,yL,yR,v);
        if(l==L&&R==r) {
            tag[now].modify(1,1,m,yL,yR,v);
            return;
        }
        int mid=l+r>>1;
        if(R<=mid) modify(lson,L,R,yL,yR,v);
        else if(L>mid) modify(rson,L,R,yL,yR,v);
        else {
            modify(lson,L,mid,yL,yR,v),
            modify(rson,mid+1,R,yL,yR,v);
        }
        return;
    }
    int query(int now,int l,int r,int L,int R,int yL,int yR) {
        if(l==L&&R==r) return Max[now].query(1,1,m,yL,yR);
        int mid=l+r>>1;
        int ans=tag[now].query(1,1,m,yL,yR);
        if(R<=mid) return max(ans,query(lson,L,R,yL,yR));
        else if(L>mid) return max(ans,query(rson,L,R,yL,yR));
        else return max(ans,max(query(lson,L,mid,yL,yR),query(rson,mid+1,R,yL,yR)));
    }
};
 
Segment_Tree_x tree;
 
int main() {
    input(n),input(m),input(q);
    for(int d,w,s,x,y;q;q--) {
        input(d),input(s),input(w),input(x),input(y);
        tree.modify(1,1,n,x+1,x+d,y+1,y+s,tree.query(1,1,n,x+1,x+d,y+1,y+s)+w);
    }
    printf("%d\n",tree.query(1,1,n,1,n,1,m));
    return 0;
}
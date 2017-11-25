#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1000010

struct Segment_tree {
    int l,r,Min,tag;
}t[maxn<<2];

void input(int &x) {
    x=0;
    int flag=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') flag=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    if(flag==-1) x=-x;
    return;
}

void PushDown(int now) {
    t[now<<1].tag+=t[now].tag;
    t[now<<1|1].tag+=t[now].tag;
    t[now<<1].Min-=t[now].tag;
    t[now<<1|1].Min-=t[now].tag;
    t[now].tag=0;
    return;
}

void Build(int now,int l,int r) {
    t[now].l=l,t[now].r=r,t[now].tag=0;
    if(l==r) {
        input(t[now].Min);
        return;
    }
    int mid=l+r>>1;
    Build(now<<1,l,mid),
    Build(now<<1|1,mid+1,r);
    t[now].Min=min(t[now<<1].Min,t[now<<1|1].Min);
    return;
}

void Modify(int now,int L,int R,int x) {
    if(t[now].l==L&&R==t[now].r) {
        t[now].tag+=x;
        t[now].Min-=x;
        return;
    }
    if(t[now].tag!=0) PushDown(now);
    int mid=t[now].l+t[now].r>>1;
    if(L>mid) Modify(now<<1|1,L,R,x);
    else if(R<=mid) Modify(now<<1,L,R,x);
    else {
        Modify(now<<1,L,mid,x),
        Modify(now<<1|1,mid+1,R,x);
    }
    t[now].Min=min(t[now<<1].Min,t[now<<1|1].Min);
    return;
}

int main() {
    int n,m;
    input(n),input(m);
    Build(1,1,n);
    for(register int i=1;i<=m;++i) {
        int x,l,r;
        input(x),input(l),input(r);
        Modify(1,l,r,x);
        if(t[1].Min<0) {
            printf("-1\n%d",i);
            return 0;
        }
    }
    printf("0");
    return 0;
}
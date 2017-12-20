#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

#define MAXN 200010
ll Max[MAXN<<2];
int cnt;

void updata(int now) {
    Max[now]=max(Max[now<<1],Max[now<<1|1]);
    return;
}

void Modify(int now,int l,int r,int pos,ll x) {
    if(l==r) {
        Max[now]=x;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid) Modify(now<<1,l,mid,pos,x);
    else Modify(now<<1|1,mid+1,r,pos,x);
    updata(now);
    return;
}

ll query(int now,int l,int r,int L,int R) {
    if(l==L&&r==R) return Max[now];
    int mid=l+r>>1;
    if(R<=mid) return query(now<<1,l,mid,L,R);
    else if(L>mid) return query(now<<1|1,mid+1,r,L,R);
    else {
        ll a=query(now<<1,l,mid,L,mid),
           b=query(now<<1|1,mid+1,r,mid+1,R);
        return max(a,b);
    }
}

int main() {
    int M,D;
    input(M),input(D);
    char op[5];
    ll LastQueryAns=0;
    for(int i=1,x;i<=M;i++) {
        scanf("%s%d",op,&x);
        if(op[0]=='A')
            Modify(1,1,M,++cnt,(ll)(LastQueryAns+x)%D);
        else {
            LastQueryAns=query(1,1,M,cnt-x+1,cnt);
            printf("%lld\n",LastQueryAns);
        }
    }
    return 0;
}

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

#define MAXN 500010

int n,m;
int t[MAXN];

inline int lowbit(int x) {
    return x&(-x);
}

void Modify(int k,int x) {
    for(;k<=n;k+=lowbit(k))
        t[k]+=x;
    return;
}

void Modify(int x,int y,int k) {
    Modify(x,k),Modify(y+1,-k);
    return;
}

int query(int k) {
    int ans=0;
    for(;k;k-=lowbit(k))
        ans+=t[k];
    return ans;
}


int main() {
    input(n),input(m);
    for(int i=1,now,last=0;i<=n;i++,last=now) {
        input(now);
        Modify(i,now-last);
    }
    for(int op,x,y,k;m;m--) {
        input(op);
        if(op==1) {
            input(x),input(y),input(k);
            Modify(x,y,k);
        } else {
            input(x);
            printf("%d\n",query(x));
        }
    }
    return 0;
}

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

#define MAXN 50010

int n,L;

ll c[MAXN];
ll f[MAXN],g[MAXN],h[MAXN];

int q[MAXN],head,tail;

#define inf 9223372036854775807LL

#define sqr(x) (1ll*(x)*(x))

ll calc(int i,int j) {
    return (f[i]-f[j]+sqr(g[i])-sqr(g[j]))/(g[i]-g[j]<<1);
}

int main() {
    input(n),input(L);
    for(int i=1;i<=n;i++) {
        input(c[i]),
        c[i]+=c[i-1],f[i]=inf,
        g[i]=c[i]+i,h[i]=g[i]-L-1;
    }
    for(int i=1;i<=n;i++) {
        for(;head<tail&&calc(q[head],q[head+1])<=h[i];head++);
        f[i]=f[q[head]]+sqr(h[i]-g[q[head]]);
        for(;head<tail&&calc(q[tail-1],q[tail])>=calc(q[tail],i);tail--);
        q[++tail]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}

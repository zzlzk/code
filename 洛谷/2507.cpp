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

#define MAXN 100010
#define inf 1000000000000000ll

ll f[MAXN];
ll a[MAXN],b[MAXN];

ll cost(int i,int j) {
    if(a[i]==b[j]) return inf;
    return abs(a[i]-b[j]);
}

int main() {
    int n;
    input(n);
    for(int i=1;i<=n;i++)
        input(a[i]),input(b[i]);
    if(n==1&&a[1]==b[1]) {
        printf("-1\n");
        return 0;
    }
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) {
        f[i]=f[i-1]+cost(i,i);
        if(i>1)
            f[i]=min(f[i],f[i-2]+cost(i,i-1)+cost(i-1,i));
        if(i>2) {
            f[i]=min(f[i],f[i-3]+cost(i,i-2)+cost(i-1,i-1)+cost(i-2,i));
            f[i]=min(f[i],f[i-3]+cost(i,i-2)+cost(i-1,i)+cost(i-2,i-1));
            f[i]=min(f[i],f[i-3]+cost(i,i-1)+cost(i-2,i)+cost(i-1,i-2));
        }
    }
    printf("%lld",f[n]);
    return 0;
}

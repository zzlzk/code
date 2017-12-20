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

#define MAXN 110
#define MAXK 100010

int prime[MAXN];
int a[MAXK],cnt;
int Count[MAXN];

int main() {
    int n,k;
    input(n),input(k);
    for(int i=1;i<=n;Count[i]=1,i++)
        input(prime[i]);
    for(a[++cnt]=1;cnt!=k+1;) {
        int Min=~0u>>1,pos;
        for(int i=1;i<=n;i++)
            if(a[Count[i]]*prime[i]<Min) {
                Min=a[Count[i]]*prime[i];
                pos=i;
            }
        ++Count[pos];
        if(Min!=a[cnt])
            a[++cnt]=Min;
    }
    printf("%d",a[k+1]);
    return 0;
}

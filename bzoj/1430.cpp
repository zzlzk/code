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
 
#define mod 9999991
 
int main() {
    int n;
    input(n);
    ll ans=1;
    for(int i=1;i<=n-2;i++) ans=(ans*n)%mod;
    for(int i=1;i<=n-1;i++) ans=(ans*i)%mod;
    printf("%lld\n",ans%mod);
    return 0;
}
?
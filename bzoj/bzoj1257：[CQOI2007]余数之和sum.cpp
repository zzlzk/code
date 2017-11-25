#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
 
int main() {
    ll n,k;
    scanf("%lld%lld",&n,&k);
    ll ans=n*k;
    for(ll l=1,r;l<=n;l=r+1) {
        if(k/l!=0) r=min(k/(k/l),n); 
        else r=n;
        ans-=(k/l)*(r-l+1)*(l+r)/2;
    }
    printf("%lld",ans);
    return 0;
}

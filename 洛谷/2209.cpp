#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 50010

template<typename T>
struct Gas_Station {
    T dis,price;
    bool operator < (const Gas_Station&q)const {
        return dis<q.dis;
    }
};

Gas_Station<ll> s[MAXN];

int main() {
    ll N,G,B,D;
    scanf("%lld%lld%lld%lld",&N,&G,&B,&D);
    for(int i=1;i<=N;i++)
        scanf("%lld%lld",&s[i].dis,&s[i].price);
    sort(s+1,s+N+1);
    s[N+1].dis=D;
    s[N+2].price=~0u>>1;
    ll pos=N+2;
    for(int i=1;s[i].dis<=B;i++)
        if(s[i].price<s[pos].price) pos=i;
    if(pos==N+2) {
        printf("-1");
        return 0;
    }
    ll ans=0;
    for(int i=pos,j,k=B-s[i].dis;i<=N;i=pos) {
        bool flag=false;
        for(j=i+1,pos=N+2;s[j].dis<s[i].dis+G;j++) {
            if(s[j].price<s[pos].price) pos=j;
            if(s[j].price<s[i].price) {
                ans+=(s[j].dis-s[i].dis-k)*s[i].price;
                flag=true;
                k=0;
                break;
            }
        }
        if(pos==N+2) {
            printf("-1");
            return 0;
        }
        if(!flag) {
            ans+=(G-k)*s[i].price;
            k=G-(s[pos].dis-s[i].dis);
        }
    }
    printf("%lld",ans);
    return 0;
}

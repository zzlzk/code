#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define maxn 200010
#define inf (1ll<<60) 

template<typename T>
void input(T &x) {
    T a=1;x=0;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    if(a==-1) x=-x;
    return;
}

ll s;
int n,m;
int l[maxn],r[maxn];
int w[maxn],v[maxn];
ll sum[maxn],cnt[maxn];

ll Judge(int W) {
    for(int i=1;i<=n;i++) {
        sum[i]=sum[i-1];
        cnt[i]=cnt[i-1];
        if(w[i]>=W) {
            sum[i]+=v[i];
            cnt[i]++;
        }
    }
    ll ret=0;
    for(int i=1;i<=m;i++) {
        ll a=cnt[r[i]]-cnt[l[i]-1];
        ll b=sum[r[i]]-sum[l[i]-1];
        ret+=a*b;
    }
    return ret;
}

int main() {
    input(n),input(m),input(s);
    int Max=0;
    for(int i=1;i<=n;i++) {
        input(w[i]),input(v[i]);
        Max=max(Max,w[i]);
    }
    for(int i=1;i<=m;i++)
        input(l[i]),input(r[i]);
    int l=0,r=Max+1;
    ll ans=inf;
    while(l<=r) {
        int mid=l+r>>1;
        ll a=Judge(mid);
        ans=min(ans,abs(a-s));
        if(a<s) r=mid-1;
        else l=mid+1;
    }
    printf("%lld",ans);
    return 0;
}
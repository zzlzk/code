#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define mod 99999997
#define MAXN 100010

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

struct Data {
    
    int x,id;
    
    bool operator < (const Data &q)const {
        return x<q.x;
    }
    
}a[MAXN],b[MAXN];

ll ans=0;
int s[MAXN],t[MAXN];

void Merge(int l,int m,int r) {
    int i=l,j=m+1;
    int k=l;
    while(i<=m&&j<=r)
        if(s[i]<=s[j]) t[k++]=s[i++];
        else {
            t[k++]=s[j++];
            ans+=(ll)(m-i+1)%mod;
        }
    while(i<=m) t[k++]=s[i++];
    while(j<=r) t[k++]=s[j++];
    for(int i=l;i<=r;i++)
        s[i]=t[i];
    return;
}

void Merge_Sort(int l,int r) {
    if(l<r) {
        int mid=l+r>>1;
        Merge_Sort(l,mid);
        Merge_Sort(mid+1,r);
        Merge(l,mid,r);
    }
    return;
}

int main() {
    int n;
    input(n);
    for(int i=1;i<=n;i++) 
        input(a[a[i].id=i].x);
    for(int i=1;i<=n;i++)
        input(b[b[i].id=i].x);
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
        s[a[i].id]=b[i].id;
    Merge_Sort(1,n);
    printf("%lld",ans%mod);
    return 0;
}
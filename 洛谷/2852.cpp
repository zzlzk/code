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

#define MAXC 1000010
#define MAXN 20010

int n,k;
int c[MAXC],X[MAXC],Y[MAXC];
int a[MAXN],sa[MAXN],rank[MAXN],height[MAXN];

void Get_Height() {
    for(int i=1;i<=n;i++) rank[sa[i]]=i;
    int k=0;
    for(int i=1;i<=n;i++)
        if(rank[i]!=n) {
            for(k=max(k-1,0);a[i+k]==a[sa[rank[i]+1]+k];k++);
            height[rank[i]]=k;
        }
    return;
}

void Build_SuffixArray(int m) {
    int *x=X,*y=Y;
    for(int i=1;i<=n;i++) c[x[i]=a[i]]++;
    for(int i=1;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<n;k<<=1) {
        int p=0;
        for(int i=n;i>n-k;i--) y[++p]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>k) y[++p]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) c[x[i]]++;
        for(int i=1;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
        swap(x,y),m=1;
        for(int i=1;i<=n;i++)
            x[sa[i]]=y[sa[i]]==y[sa[i+1]]&&y[sa[i]+k]==y[sa[i+1]+k]?m:m++;
        if(m>n) return Get_Height();
    }
    return Get_Height();
}

bool Judge(int mid) {
    int cnt=0;
    for(int i=1;i<n;i++)
        if(height[i]>=mid) cnt++;
        else {
            if(cnt+1>=k) return true;
            cnt=0;
        }
    return cnt+1>=k;
}

int main() {
    input(n),input(k);
    for(int i=1;i<=n;i++)
        input(a[i]);
    Build_SuffixArray(MAXN-10);
    int l=0,r=n,ans,mid;
    while(l<=r) {
        mid=l+r>>1;
        if(Judge(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}

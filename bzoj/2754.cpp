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

#define MAXN 300010

int s[MAXN],n,m;
int X[MAXN<<1],Y[MAXN<<1],c[MAXN<<1];
int sa[MAXN],rank[MAXN],height[MAXN];

void Get_Height() {
    for(int i=1;i<=n;i++) rank[sa[i]]=i;
    int k=0;
    for(int i=1;i<=n;i++)
        if(rank[i]!=1) {
            for(k=max(k-1,0);s[i+k]==s[sa[rank[i]-1]+k];k++);
            height[rank[i]]=k;
        }
    return;
}

void Build_SuffixArray() {
    int *x=X,*y=Y;
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
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

int pos[MAXN];

#define MAXM 50010

struct Query {
    int L,p;
    Query(int L=0,int p=0):
        L(L),p(p) {}
};

Query q[MAXM];
int ans[20010],vis[20010];

int main() {
    int N,M;
    input(N),input(M);
    n=0,m=10000;
    for(int i=1,L;i<=N;i++) {
        input(L);
        while(L--) input(s[++n]),pos[n]=i;
        s[++n]=++m;
        input(L);
        while(L--) input(s[++n]),pos[n]=i;
        s[++n]=++m;
    }
    int Name=n;
    for(int i=1,L;i<=M;i++) {
        input(L);
        q[i]=Query(L,n+1);
        while(L--) input(s[++n]);
        s[++n]=++m;
    }
    Build_SuffixArray();
    for(int i=1,l,r;i<=M;i++) {
        l=rank[q[i].p],r=rank[q[i].p]+1;
        while(height[l]>=q[i].L) --l;
        while(height[r]>=q[i].L) ++r;
        --r;
        int cnt=0;
        for(int j=l;j<=r;j++) {
            if(sa[j]>Name) continue;
            if(vis[pos[sa[j]]]==i) continue;
            cnt++;
            ans[pos[sa[j]]]++;
            vis[pos[sa[j]]]=i;
        }
        printf("%d\n",cnt);
    }
    for(int i=1;i<=N;i++)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}


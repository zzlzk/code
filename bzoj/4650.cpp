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

#define MAXN 30010

char s[MAXN];
int c[MAXN<<1],X[MAXN<<1],Y[MAXN<<1];
int Log[MAXN],n;

struct Suffix_Array {
    int height[MAXN],sa[MAXN],rank[MAXN];
    int f[MAXN][22];
    void init_st() {
        memset(f,127,sizeof(f));
        for(int i=n;i;i--) {
            f[i][0]=height[i];
            for(int j=1;(i+(1<<j)-1)<=n;j++)
                f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
        }
        return;
    }
    void Get_Height() {
        for(int i=1;i<=n;i++) rank[sa[i]]=i;
        int k=0;
        for(int i=1;i<=n;i++) 
            if(rank[i]!=1) {
                for(k=max(k-1,0);s[i+k]==s[sa[rank[i]-1]+k];k++);
                height[rank[i]]=k;
            }
        return init_st();
    }
    void build(int m) {
        int *x=X,*y=Y;
        for(int i=1;i<=m;i++) c[i]=0;
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
    int query_LCP(int l,int r) {
        l=rank[l],r=rank[r];
        if(l>r) swap(l,r);
        l++;
        int k=Log[r-l+1];
        return min(f[l][k],f[r-(1<<k)+1][k]);
    }
};

Suffix_Array p,q;

int AA[MAXN],BB[MAXN];

int main() {
    for(int i=1;i<=30000;i++) {
        Log[i]=Log[i-1];
        if((1<<Log[i]+1)==i) Log[i]++;
    }
    int T;
    input(T);
    while(T--) {
        scanf("%s",s+1);
        n=strlen(s+1);
        p.build(128);
        for(int i=1,j=n;i<=j;i++,j--)
            swap(s[i],s[j]);
        q.build(128);
        memset(AA,0,sizeof(AA));
        memset(BB,0,sizeof(BB));
        for(int L=1;L<=n;L++)
            for(int k=1;k+L<=n;k+=L) {
                int a=p.query_LCP(k,k+L);
                int b=q.query_LCP(n-k+1,n-k-L+1);
                a=min(a,L),b=min(b,L);
                if(a+b>L) {
                    AA[k+L+L-b]++,AA[k+L+a]--;
                    BB[k-b+1]++,BB[k+a-L+1]--;
                }
            }
        for(int i=1;i<=n;i++)
            AA[i]+=AA[i-1],BB[i]+=BB[i-1];
        ll ans=0;
        for(int i=1;i<n;i++)
            ans+=1ll*AA[i]*BB[i+1];
        printf("%lld\n",ans);
    }
    return 0;
}


#include<cstdio>
#include<cstring>
#include<iostream>
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

#define MAXN 1100010

string str;
int s[MAXN],n=0,m=26;
int c[MAXN<<1],X[MAXN<<1],Y[MAXN<<1];
int sa[MAXN],height[MAXN],rank[MAXN];

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

void Build_SuffixArray(int m) {
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

struct Word {
    int p,L;
    Word(int p=0,int L=0):
        p(p),L(L) {}
};

Word a[210];

int main() {
    int N;
    input(N);
    for(int i=1;i<=N;i++) {
        cin>>str;
        int L=str.size();
        a[i]=Word(n+1,L);
        for(int j=0;j<L;j++)
            s[++n]=str[j]-'a'+1;
        s[++n]=++m;
    }
    Build_SuffixArray(m);
    for(int i=1;i<=N;i++) {
        int l=rank[a[i].p],r=l+1;
        while(height[l]>=a[i].L) l--;
        while(height[r]>=a[i].L) r++;
        r--;
        printf("%d\n",r-l+1);
    }
    return 0;
}


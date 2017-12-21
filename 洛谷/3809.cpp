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

#define MAXN 1000010

char s[MAXN];
int X[MAXN],Y[MAXN],c[MAXN],a[MAXN],n;
int sa[MAXN];

void Build_SuffixArray(int m) {
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
        x[sa[i]]=y[sa[i]+k]==y[sa[i+1]+k]&&y[sa[i]]==y[sa[i+1]]?m:m++;
        if(m>n) return;
    }
    return;
}

int main() {
    scanf("%s",s+1);
    n=strlen(s+1);
    Build_SuffixArray(128);
    for(int i=1;i<=n;i++)
        printf("%d ",sa[i]);
    puts("");
    return 0;
}


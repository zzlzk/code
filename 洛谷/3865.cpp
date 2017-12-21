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

#define MAXN 100010

int Log[MAXN];
int f[MAXN][22];
int a[MAXN];

int query(int l,int r) {
    int k=Log[r-l+1];
    return max(f[l][k],f[r-(1<<k)+1][k]);
}

int main() {
    for(int i=1;i<=100000;i++) {
        Log[i]=Log[i-1];
        if((1<<Log[i]+1)==i) Log[i]++;
    }
    int n,m;
    input(n),input(m);
    for(int i=1;i<=n;i++)
        input(a[i]);
    for(int i=n;i;i--) {
        f[i][0]=a[i];
        for(int j=1;i+(1<<j)-1<=n;j++)
            f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
    }
    for(int l,r;m;m--) {
        input(l),input(r);
        printf("%d\n",query(l,r));
    }
    return 0;
}


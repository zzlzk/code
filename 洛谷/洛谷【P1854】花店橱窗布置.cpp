#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

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

#define MAXN 110
#define MAXM 110

int n,m;
int beauty[MAXN][MAXM];
int pro[MAXN][MAXM];
int remember[MAXN][MAXM];

int dfs(int k,int last) {
    if(k>n) return 0;
    if(remember[k][last])
        return remember[k][last];
    int ans=-999999999,tmp;
    for(int i=last+1;i<=m;i++) {
        tmp=dfs(k+1,i)+beauty[k][i];
        if(tmp>ans) {
            ans=tmp;
            pro[k][last]=i;
        }
    }
    return remember[k][last]=ans;
}

void Print(int k,int last) {
    if(k>n) return;
    printf("%d ",pro[k][last]);
    Print(k+1,pro[k][last]);
    return;
}

int main() {
    input(n),input(m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            input(beauty[i][j]);
    printf("%d\n",dfs(1,0));
    Print(1,0);
    return 0;
}

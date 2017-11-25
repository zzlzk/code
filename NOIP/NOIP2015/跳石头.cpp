#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 50010

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

int n,m,L;
int pos[MAXN];

bool judge(int x) {
    int cnt=0,now=0;
    for(int i=1;i<=n+1;i++)
        if(pos[i]-pos[now]<x) cnt++;
        else now=i;
    return cnt<=m;
}

int main() {
    input(L),input(n),input(m);
    for(int i=1;i<=n;i++)
        input(pos[i]);
    pos[n+1]=L;
    int l=1,r=L,ans;
    while(l<=r) {
        int mid=l+r>>1;
        if(judge(mid)) {
            l=mid+1;
            ans=mid;
        } else r=mid-1;
    }
    printf("%d",ans);
    return 0;
}
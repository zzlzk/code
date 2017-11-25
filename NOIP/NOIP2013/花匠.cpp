#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
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

int a[MAXN],cnt=0;

int main() {
    int n;
    input(n);
    for(int i=1;i<=n;i++) {
        int x;
        input(x);
        if(a[cnt]!=x) a[++cnt]=x;
    }
    if(cnt<=2) {
        printf("%d",cnt);
        return 0;
    }
    int ans=2;
    for(int i=2;i<cnt;i++)
        if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1]))
            ans++;
    printf("%d",ans);
    return 0;
}

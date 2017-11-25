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

int main() {
    int n;
    input(n);
    int last,now,ans=0;
    input(now);
    ans+=now;
    last=now;
    for(int i=2;i<=n;i++) {
        input(now);
        if(now>last) ans+=now-last;
        last=now;
    }
    printf("%d",ans);
    return 0;
}
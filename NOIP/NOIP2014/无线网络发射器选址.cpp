#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'&&c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

int a[150][150];

bool judge(int x,int y) {
    return 0<=x&&x<=128&&0<=y&&y<=128;
}

int main() {
    int d,n;
    input(d);
    input(n);
    for(int i=1;i<=n;i++) {
        int x,y,k;
        input(x),input(y),input(k);
        a[x][y]=k;
    }
    int ans=0,cnt=1;
    for(int i=0;i<=128;i++)
        for(int j=0;j<=128;j++) {
            int sum=0;
            for(int x=i-d;x<=i+d;x++)
                for(int y=j-d;y<=j+d;y++)
                    if(judge(x,y)) sum+=a[x][y];
            if(sum==ans) cnt++;
            if(sum>ans) ans=sum,cnt=1;
        }
    printf("%d %d",cnt,ans);
    return 0;
}
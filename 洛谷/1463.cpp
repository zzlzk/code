#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

const int prime[]={1,2,3,5,7,11,13,17,19,23,29,31};
int n,ans=1,num=1;

void dfs(int k,ll now,int cnt,int last) {
    if(k==12) {
        if(now>ans&&cnt>num) {
            ans=now;
            num=cnt;
        }
        if(now<=ans&&cnt>=num) {
            ans=now;
            num=cnt;
        }
        return;
    }
    int t=1;
    for(int i=0;i<=last;i++) {
        dfs(k+1,now*t,cnt*(i+1),i);
        t*=prime[k];
        if(now*t>n) break;
    }
}

int main() {
    scanf("%d",&n);
    dfs(1,1,1,20);
    printf("%d",ans);
    return 0;
}

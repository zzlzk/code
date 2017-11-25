#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 30

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

int ans;
int Poker[MAXN];
int cnt[MAXN];

void dfs(int x) {
    if(x>ans) return;
    memset(cnt,0,sizeof(cnt));
    int nowans=x;
    for(int i=1;i<=15;++i)
        ++cnt[Poker[i]];
    while(cnt[4]) {
        cnt[4]--;
        nowans++;
        if(cnt[2]>=2) cnt[2]-=2;
        else if(cnt[1]>=2) cnt[1]-=2;
    }
    while(cnt[3]) {
        cnt[3]--;
        nowans++;
        if(cnt[2]) cnt[2]--;
        else if(cnt[1]) cnt[1]--;
    }
    nowans+=cnt[1]+cnt[2];
    if(Poker[14]&&Poker[15]&&cnt[1]>=2) nowans--;
    ans=min(ans,nowans);
    for(int i=1,j;i<=8;i++) {
        for(j=i;Poker[j]&&j<=12;j++) {
            Poker[j]--;
            if(j-i+1>=5) dfs(x+1);
        }
        while(j>i) Poker[--j]++;
    }
    for(int i=1,j;i<=10;i++) {
        for(j=i;Poker[j]>=2&&j<=12;j++) {
            Poker[j]-=2;
            if(j-i+1>=3) dfs(x+1);
        }
        while(j>i) Poker[--j]+=2;
    }
    for(int i=1,j;i<=11;i++) {
        for(j=i;Poker[j]>=3&&j<=12;j++) {
            Poker[j]-=3;
            if(j-i+1>=2) dfs(x+1);
        }
        while(j>i) Poker[--j]+=3;
    }
    return;
}

int main() {
    int T,n;
    input(T),input(n);
    while(T--) {
        memset(Poker,0,sizeof(Poker));
        for(int i=1;i<=n;i++) {
            int number,color;
            input(number),input(color);
            if(number==0) Poker[13+color]++;
            else if(number<3) Poker[11+number]++;
            else Poker[number-2]++;
        }
        ans=n;
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}

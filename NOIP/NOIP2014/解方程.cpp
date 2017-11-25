#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXM 1000010
#define MAXN 110
const int prime[]={9973,9931,9941,9949,9967};

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

int n,m;
int ans[MAXM];
int a[5][MAXN],pre[5][MAXN],res[5][30010];

char ch[10010];

int f(int id,int x) {
    int sum=0;
    for(int i=0;i<=n;i++)
        sum=(sum+a[id][i]*pre[id][i])%prime[id];
    if(sum<0) sum+=prime[id];
    return sum;
}

bool judge(int x) {
    for(int i=0;i<5;i++)
        if(res[i][x%prime[i]]!=0)
            return false;
    return true;
}

int main() {
    input(n),input(m);
    for(int i=0;i<=n;i++) {
        scanf("%s",ch+1);
        int len=strlen(ch+1);
        bool flag=false;
        for(int j=0;j<5;j++)
            if(ch[1]!='-') a[j][i]=ch[1]-'0';
            else a[j][i]=0,flag=true;
        for(int j=0;j<5;j++) {
            for(int k=2;k<=len;k++)
                a[j][i]=(a[j][i]*10+ch[k]-'0')%prime[j];
            if(flag==true) a[j][i]=-a[j][i];
        }
    }
    for(int i=0;i<5;i++)
        for(int x=1;x<prime[i];x++) {
            pre[i][0]=1;
            for(int j=1;j<=n;j++)
                pre[i][j]=(pre[i][j-1]*x)%prime[i];
            res[i][x]=f(i,x);
        }
    for(int i=1;i<=m;i++)
        if(judge(i)) ans[++ans[0]]=i;
    printf("%d\n",ans[0]);
    for(int i=1;i<=ans[0];i++)
        printf("%d\n",ans[i]);
    return 0;
}

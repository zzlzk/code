#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;

#define MAXN 50010
#define MAXchar 1510

ull Hash[MAXN];
char s[MAXchar];

int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",s);
        for(int j=0;j<strlen(s);j++)
            Hash[i]=Hash[i]*13131+s[j];
    }
    sort(Hash+1,Hash+n+1);
    int ans=1;
    for(int i=2;i<=n;i++)
        if(Hash[i]!=Hash[i-1]) ans++;
    printf("%d\n",ans);
    return 0;
}

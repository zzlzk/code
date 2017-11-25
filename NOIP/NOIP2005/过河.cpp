#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 100005
#define inf 0x3f3f
int f[maxn],pos[maxn];
bool stone[maxn];
int main() {
    memset(f,inf,sizeof(f));
    int l,s,t,m;
    scanf("%d%d%d%d",&l,&s,&t,&m);
    for(int i=1;i<=m;i++) scanf("%d",&pos[i]);
    if(s==t) {
        int ans=0;
        for(int i=1;i<=m;i++)
            if(pos[i]%s==0) ans++;
        printf("%d",ans);
        return 0;
    }
    sort(pos+1,pos+m+1);
    pos[m+1]=l;
    for(int i=0;i<=m;i++)
        if(pos[i+1]-pos[i]>90)
            pos[i+1]=pos[i]+(pos[i+1]-pos[i])%90;
    for(int i=1;i<=m;i++) stone[pos[i]]=true;
    for(int i=s;i<=t;i++)
        if(stone[i]) f[i]=1;
        else f[i]=0;
    for(int i=2*s;i<=pos[m+1];i++) {
        for(int j=s;j<=t;j++){
            if(j>i) break;
            f[i]=min(f[i],f[i-j]);
        }
        if(stone[i]) f[i]++;
    }
    printf("%d",f[pos[m+1]]);
    return 0;
}

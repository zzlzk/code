#include<cstdio>
#include<cstring>
using namespace std;
int a[1010],cnt;
int main() {
	memset(a,-1,sizeof(a));
    int m,n,ans=0;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) {
        int word;
        bool flag=false;
        scanf("%d",&word);
        if(word<0) word=-word;
        for(int i=0;i<m;i++)
        	if(a[i]==word) {
				flag=true;
        		break;
        	}
        if(!flag) {
        	a[cnt%m]=word;
        	cnt++;
        	ans++;
		}
	}
    printf("%d",ans);
    return 0;
}

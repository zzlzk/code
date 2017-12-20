#include<cstdio>
using namespace std;
const int maxn = 40010;
int phi[maxn],prime[maxn],tot,n,ans=0;
bool vis[maxn];
void GetPhi() {
	phi[1]=1;
	for(int i=2;i<=n;i++) {
		if(vis[i]==false) prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=n;j++) {
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			} else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
	return;
}
int main() {
	scanf("%d",&n);
	GetPhi();
	for(int i=1;i<n;i++) ans+=phi[i];
	printf("%d\n",(ans<<1)+1);
	return 0;
}

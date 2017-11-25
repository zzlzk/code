#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 310
#define inf 999999
int G[maxn][maxn];
int main() {
	int n,s,ans=inf;
	scanf("%d%d",&n,&s);
	memset(G,inf,sizeof(G));
	for(int i=1;i<n;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u][v]=G[v][u]=w;
	}
	for(int k=1;k<=n;k++) {
		G[k][k]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]<=s) {
				int x=0;
				for(int k=1;k<=n;k++)
					x=max(x,(G[i][k]+G[j][k]-G[i][j])>>1);
				ans=min(ans,x);
			}
	printf("%d",ans);
	return 0;
}

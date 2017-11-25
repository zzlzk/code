#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
#define maxm 500
#define maxn 25
struct W {
	int a[maxm];
}work[maxn];
int way[maxm],step[20],z[20];
int machine[maxn][maxn],tim[maxn][maxn];
int n,m,ans;
void plan(int x) {
	int t=tim[x][step[x]],w=machine[x][step[x]];
	int s=0,start;
	for(int i=z[x];i<=maxm;i++) {
		if(work[w].a[i]==0) s++;
		else s=0;
		if(s==t) {
			start=i-t+1;
			break;
		}
	}
	for(int i=start;i<=start+t-1;i++)
		work[w].a[i]=x;
	step[x]++;
	z[x]=start+t;
	ans=max(start+t,ans);
}
int main () {
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++) step[i]=1;
	for(int i=1;i<=n*m;i++)
		scanf("%d",&way[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&machine[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&tim[i][j]);
	for(int i=1;i<=n*m;i++)
		plan(way[i]);
	printf("%d",ans);
	return 0;
}

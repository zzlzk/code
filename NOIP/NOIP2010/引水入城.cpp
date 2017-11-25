#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 510
#define inf 0x7fffffff
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
struct Node {
	int x,y;
	Node(int x=0,int y=0):
		x(x),y(y) {}
};
struct Segment {
	int l,r;
	Segment(int l=0,int r=0):
		l(l),r(r) {}
	bool operator < (const Segment &o)const {
		if(l==o.l) return r<o.r;
		return l<o.l;
	}
}a[maxn];
queue<Node>Q;
int G[maxn][maxn],vis[maxn][maxn],n,m;
void bfs(Node x,int flag) {
	Q.push(x);
	vis[1][flag]=flag;
	int l=inf,r=0;
	while(!Q.empty()) {
		Node u=Q.front();
		Q.pop();
		for(int i=0;i<4;i++) {
			Node v=Node(u.x+dx[i],u.y+dy[i]);
			if(vis[v.x][v.y]==flag) continue;
			if(v.x<1||v.x>n||v.y<1||v.y>m) continue;
			if(G[u.x][u.y]<=G[v.x][v.y]) continue;
			vis[v.x][v.y]=flag;
			Q.push(v);
			if(v.x==n) {
				l=min(l,v.y);
				r=max(r,v.y);
			}
		}
	}
	a[flag]=Segment(l,r);
	return;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&G[i][j]);
	for(int i=1;i<=m;i++)
		if(G[1][i]>=G[1][i-1]&&G[1][i]>=G[1][i+1])
			bfs(Node(1,i),i);
		else a[i]=Segment(inf,0);
	int cnt=0;
	for(int i=1;i<=m;i++)
		if(vis[n][i]==0) cnt++;
	if(cnt!=0) {
		printf("0\n%d",cnt);
		return 0;
	}
	printf("1\n");
	sort(a+1,a+m+1);
	a[1].l=1;
	int u=0,v=0,ans=0;
	for(int i=1;i<=m;i++) {
		if(a[i].l==inf) continue;
		if(u+1>=a[i].l) v=max(a[i].r,v);
		else {
			ans++;
			u=v;
			v=max(v,a[i].r);
		}
	}
	if(u!=m) ans++;
	printf("%d",ans);
	return 0;
}

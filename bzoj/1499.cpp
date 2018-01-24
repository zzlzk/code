#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
	x=0; T a=1;
	register char c=getchar();
	for(;c<48||c>57;c=getchar())
		if(c==45) a=-1;
	for(;c>=48&&c<=57;c=getchar())
		x=x*10+c-48;
	x*=a;
	return;
}

#define MAXN 210
#define inf 2147483647

char G[MAXN][MAXN];
int f[MAXN][MAXN][MAXN];
int dx[]={0,-1,1,0,0},dy[]={0,0,0,-1,1};
int q[MAXN],pos[MAXN],head,tail;
int n,m,sx,sy,K,ans;

void push(int now,int val,int x,int y) {
	if(val==-inf)return;
	for(;val-now>q[tail]&&head<=tail;tail--);
	q[++tail]=val-now,pos[tail]=now;
	return;
}

void dp(int p,int x,int y,int d,int T) {
	head=1,tail=0;
	for(int now=1;x<=n&&y<=m&&x>=1&&y>=1;now++) {
		if(G[x][y]=='x') head=1,tail=0;
		else push(now,f[p-1][x][y],x,y);
		for(;now-pos[head]>T&&head<=tail;head++);
		f[p][x][y]=(head<=tail?(q[head]+now):-inf);
		ans=max(ans,f[p][x][y]),
		x+=dx[d],y+=dy[d];
	}
	return;
}

int main() {
	input(n),input(m),input(sx),input(sy),input(K);
	for(int i=1;i<=n;i++)
		scanf("%s",G[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[0][i][j]=-inf;
	f[0][sx][sy]=0;
	for(int i=1,x,y,d;i<=K;i++) {
		input(x),input(y),input(d);
		if(d==1) for(int j=1;j<=m;j++) dp(i,n,j,d,y-x+1);
		if(d==2) for(int j=1;j<=m;j++) dp(i,1,j,d,y-x+1);
		if(d==3) for(int j=1;j<=n;j++) dp(i,j,m,d,y-x+1);
		if(d==4) for(int j=1;j<=n;j++) dp(i,j,1,d,y-x+1);				
	}
	printf("%d\n",ans);
	return 0;
}

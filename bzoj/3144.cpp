#include<queue>
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

#define MAXN 64010
#define MAXM 350010

struct Edge {
	int u,v,cap,next;
	Edge(int u=0,int v=0,int cap=0,int next=0):
		u(u),v(v),cap(cap),next(next) {}
};

Edge edge[MAXM<<1];
int head[MAXN],cnt=1;

void addedge(int u,int v,int cap) {
	edge[++cnt]=Edge(u,v,cap,head[u]),head[u]=cnt,
	edge[++cnt]=Edge(v,u,0,head[v]),head[v]=cnt;
	return;
}

queue<int> q;
int lev[MAXN],cur[MAXN];
int src,decc;

bool bfs() {
	for(int i=src;i<=decc;i++)
		lev[i]=-1;
	while(!q.empty()) q.pop();
	q.push(src),lev[src]=0;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			if(lev[v]==-1&&edge[i].cap) {
				lev[v]=lev[u]+1;
				if(v==decc) return true;
				q.push(v);
			}
		}
	}
	return false;
}

int dfs(int u,int flow) {
	if(u==decc) return flow;
	int used=0,x;
	for(int &i=cur[u],v;i;i=edge[i].next) {
		v=edge[i].v;
		if(lev[v]==lev[u]+1&&edge[i].cap) {
			x=dfs(v,min(flow-used,edge[i].cap)),
			used+=x,edge[i].cap-=x,edge[i^1].cap+=x;
			if(flow==used) break;
		}
	}
	if(flow!=used) lev[u]=-1;
	return used;
}

#define inf 2147483647

int dinic() {
	int ans=0;
	while(bfs()) {
		for(int i=src;i<=decc;i++)
			cur[i]=head[i];
		ans+=dfs(src,inf);
	}
	return ans;
}

#define id(x,y,z) (((z)==0)?0:((((z)-1)*P*Q)+(((x)-1)*Q)+(y)))

const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};

int v[45][45][45];

int main() {
	int P,Q,R,D;
	input(P),input(Q),input(R),input(D);
	src=0,decc=P*Q*R+1;
	for(int k=1;k<=R;k++)
		for(int i=1;i<=P;i++)
			for(int j=1;j<=Q;j++)
				input(v[i][j][k]);
	for(int i=1;i<=P;i++)
		for(int j=1;j<=Q;j++) {
			for(int k=1;k<=R;k++) {
				addedge(id(i,j,k-1),id(i,j,k),v[i][j][k]);
				for(int l=(k>D?0:5),x,y;l<4;l++) {
					x=i+dx[l],y=j+dy[l];
					if(x<1||y<1||x>P||y>Q) continue;
					addedge(id(i,j,k),id(x,y,k-D),inf);
				}
			}
			addedge(id(i,j,R),decc,inf);
		}
	printf("%d\n",dinic());
	return 0;
}

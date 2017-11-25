#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1010
#define inf 0x7fffffff
struct Stack {
	int s[maxn],top;
	Stack(): top(0) {}
	void push(int x) {
		s[++top]=x;
		return;
	}
	int front() {
		return s[top];
	}
	void pop() {
		top--;
		return;
	}
}st[3];
int a[maxn],dp[maxn],col[maxn],n;
bool G[maxn][maxn];
void UnSolvable() {
	printf("0");
	exit(0);
}
void dye(int i,int c) {
	col[i]=c;
	for(int j=1;j<=n;j++)
		if(G[i][j]) {
			if(col[j]==c) UnSolvable();
			if(!col[j]) dye(j,3-c); 
		}
	return;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dp[n+1]=inf;
	for(int i=n;i>=1;i--) {
		dp[i]=a[i];
		if(dp[i+1]<dp[i])
			dp[i]=dp[i+1];
	}
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(a[i]<a[j]&&dp[j+1]<a[i])
				G[i][j]=G[j][i]=true;
	for(int i=1;i<=n;i++)
		if(!col[i]) dye(i,1);
	int cnt=1;
	for(int i=1;i<=n;i++) {
		int COLOR=col[i];
		if(COLOR==1) {
			st[1].push(a[i]);
			printf("a ");
		} else {
			st[2].push(a[i]);
			printf("c ");
		}
		while(st[1].front()==cnt||st[2].front()==cnt) 
			if(st[1].front()==cnt) {
				st[1].pop();
				printf("b");
				if(cnt!=n) printf(" ");
				cnt++;
			} else {
				st[2].pop();
				printf("d");
				if(cnt!=n) printf(" ");
				cnt++;
			}
	}
	return 0;
}

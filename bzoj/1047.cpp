#include<deque>
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

#define MAXN 1010

deque<int> Q_Max,Q_Min;

void push(int x) {
	for(;!Q_Max.empty()&&Q_Max.back()<x;Q_Max.pop_back());
	Q_Max.push_back(x);
	for(;!Q_Min.empty()&&Q_Min.back()>x;Q_Min.pop_back());
	Q_Min.push_back(x);
	return;
}

void pop(int x) {
	if(x==Q_Max.front()) Q_Max.pop_front();
	if(x==Q_Min.front()) Q_Min.pop_front();
	return;
}

int G[MAXN][MAXN];
int Max[MAXN][MAXN],Min[MAXN][MAXN];

int main() {
	int a,b,n;
	input(a),input(b),input(n);
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			input(G[i][j]);
	for(int i=1;i<=b;i++) {
		Q_Max.clear(),Q_Min.clear();
		for(int j=1;j<=n;j++) push(G[j][i]);
		Max[1][i]=Q_Max.front(),
		Min[1][i]=Q_Min.front();
		for(int j=2;j+n-1<=a;j++) {
			push(G[j+n-1][i]),pop(G[j-1][i]),
			Max[j][i]=Q_Max.front(),
			Min[j][i]=Q_Min.front();
		}
	}
	int ans=2147483647;
	for(int i=1;i+n-1<=a;i++) {
		Q_Max.clear(),Q_Min.clear();
		for(int j=1;j<=n;j++)
			push(Max[i][j]),push(Min[i][j]);
		ans=min(ans,Q_Max.front()-Q_Min.front());
		for(int j=2;j+n-1<=b;j++) {
			push(Max[i][j+n-1]),push(Min[i][j+n-1]),
			pop(Max[i][j-1]),pop(Min[i][j-1]),
			ans=min(ans,Q_Max.front()-Q_Min.front());
		}
	}
	printf("%d\n",ans);
	return 0;
}

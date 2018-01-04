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

int f[MAXN][MAXN],s[MAXN][MAXN];

struct Point {
	int x,y;
	Point(int x=0,int y=0):
		x(x),y(y) {}
	void Input() {
		input(x),input(y);
		return;
	}
};

Point p[MAXN];

int main() {
	for(int n;~scanf("%d",&n);) {
		for(int i=1;i<=n;i++)
			p[i].Input();
		for(int i=1;i<=n;i++)
			f[s[i][i]=i][i]=0;
		for(int i=n;i;i--)
			for(int j=i+1;j<=n;j++) {
				f[i][j]=2147483647;
				for(int k=s[i][j-1];k+1<=j&&k<=s[i+1][j];k++)
					if(f[i][j]>f[i][k]+f[k+1][j]+p[k+1].x-p[i].x+p[k].y-p[j].y)
						f[i][j]=f[i][s[i][j]=k]+f[k+1][j]+p[k+1].x-p[i].x+p[k].y-p[j].y;
			}
		printf("%d\n",f[1][n]);
	}
	return 0;
}

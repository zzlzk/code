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

#define MAXN 5010

struct Point {
	
	int x,y;

	Point(int x=0,int y=0):
		x(x),y(y) {}
	
	void Input() {
		input(x),input(y);
		return;
	}

	Point operator - (const Point &q) const {
		return Point(x-q.x,y-q.y);
	}

	int operator * (const Point &q) const {
		return x*q.x+y*q.y;
	}

	int operator & (const Point &q) const {
		return x*q.y-y*q.x;
	}

};

int cross(Point a,Point b,Point c) {
	return (b-a)&(c-a);
} 

struct Line {
	Point s,t;
	Line() {}
	Line(Point s,Point t):
		s(s),t(t) {}
};

Point p[3];
Line line[MAXN];
int ans[MAXN];

int main() {
	for(int n,m;~scanf("%d",&n)&&n;memset(ans,0,sizeof(ans)),puts("")) {
		input(m),p[1].Input(),p[2].Input();
		for(int i=1,Ui,Li;i<=n;i++) {
			input(Ui),input(Li);
			line[i]=Line(Point(Ui,p[1].y),Point(Li,p[2].y));
		}
		line[n+1]=Line(Point(p[2].x,p[1].y),Point(p[2].x,p[2].y));
		for(int l,r,mid,pos;m;m--) {
			p[0].Input();
			for(l=1,r=n+1,mid=l+r>>1;l<=r;mid=l+r>>1)
				if(cross(p[0],line[mid].s,line[mid].t)<0)
					r=mid-1,pos=mid;
				else l=mid+1;
			ans[pos]++;
		}
		for(int i=1;i<=n+1;i++)
			printf("%d: %d\n",i-1,ans[i]);
	}
	return 0;
}
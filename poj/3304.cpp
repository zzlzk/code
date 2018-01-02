#include<cmath>
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

const double eps=1e-10;

int sgn(double x) {
	return fabs(x)<eps?0:(x<0?-1:1);
}

struct Point {
	
	double x,y;
	
	Point(double x=0.0,double y=0.0):
		x(x),y(y) {}
	
	Point operator - (const Point &q) const {
		return Point(x-q.x,y-q.y);
	}

	double operator *(const Point &q) const {
		return x*q.x+y*q.y;
	}

	double operator & (const Point &q) const {
		return x*q.y-y*q.x;
	}

};

struct Line {
	Point s,t;
	Line() {}
	Line(Point s,Point t):
		s(s),t(t) {}
};

double cross(Point a,Point b,Point c) {
	return (b-a)&(c-a);
}

double dis(Point a,Point b) {
	return sqrt((b-a)*(b-a));
}

bool intersect(Line l1,Line l2) {
	return sgn(cross(l2.s,l1.s,l1.t))*sgn(cross(l2.t,l1.s,l1.t))<=0;
}

#define MAXN 110

int n;
Line line[MAXN];

bool Judge(Line l) {
	if(sgn(dis(l.s,l.t))==0) return false;
	for(int i=1;i<=n;i++)
		if(intersect(l,line[i])==false)
			return false;
	return true;
}

int main() {
	int T;
	for(input(T);T;T--) {
		input(n);
		for(int i=1;i<=n;i++) {
			double a,b,c,d;
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			line[i]=Line(Point(a,b),Point(c,d));
		}
		bool flag=false;
		for(int i=1;i<=n&&!flag;i++)
			for(int j=1;j<=n&&!flag;j++)
				if(Judge(Line(line[i].s,line[j].s)))
					flag=true;
				else if(Judge(Line(line[i].s,line[j].t)))
					flag=true;
				else if(Judge(Line(line[i].t,line[j].s)))
					flag=true;
				else if(Judge(Line(line[i].t,line[j].t)))
					flag=true;
		puts(flag?"Yes!":"No!");
	}
	return 0;
}

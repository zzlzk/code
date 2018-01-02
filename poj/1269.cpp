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

const double eps=1e-8;

struct Point {
	
	double x,y;
	
	void Input() {
		scanf("%lf%lf",&x,&y);
		return;
	}

	Point(double x=0.00,double y=0.00):
		x(x),y(y) {}

	Point operator - (const Point &q) const {
		return Point(x-q.x,y-q.y);
	}

	double operator * (const Point &q) const {
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

int sgn(double x) {
	return fabs(x)<eps?0:(x<0?-1:1);
}

Point ans;
int intersect(Line a,Line b) {
	if(sgn((a.s-a.t)&(b.s-b.t))==0) {
		if(sgn((b.s-a.s)&(b.t-a.s))==0)
			return 6666;
		else return 1234;
	}
	double tmp=((a.s-b.s)&(b.s-b.t))/((a.s-a.t)&(b.s-b.t));
	ans=Point(a.s.x+(a.t.x-a.s.x)*tmp,a.s.y+(a.t.y-a.s.y)*tmp);
	return 2333;
}

int main() {
	int T;
	puts("INTERSECTING LINES OUTPUT");
	for(input(T);T;T--) {
		Point p1,p2,p3,p4;
		p1.Input(),p2.Input(),p3.Input(),p4.Input();
		int Case=intersect(Line(p1,p2),Line(p3,p4));
		if(Case==2333) printf("POINT %.2f %.2f\n",ans.x,ans.y);
		else puts(Case==6666?"LINE":"NONE");
	}
	puts("END OF OUTPUT");
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 5010
struct Apple {
	int h,s;
	Apple(int h=0,int s=0):
		h(h),s(s) {}
	bool operator < (const Apple&a)const {
		return s<a.s;
	}
}apple[maxn];
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
int main() {
	int n=input(),s=input();
	int a=input(),b=input();
	a+=b,b=0;
	for(int i=1,x,y;i<=n;i++) {
		x=input(),y=input();
		if(x>a) continue;
		apple[++b]=Apple(x,y);
	}
	sort(apple+1,apple+b+1);
	for(int i=1;i<=b;i++)
		if((s-=apple[i].s)<0) {
			printf("%d",i-1);
			return 0;
		}
	printf("0");
	return 0;
}

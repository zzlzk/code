#include<cstdio>
using namespace std;
int main() {
	int sum=0,last=0,deposit=0;
	for(int i=1;i<=12;i++) {
		sum=300+last;
		int expect;
		scanf("%d",&expect);
		sum-=expect;
		if(sum<0) {
			printf("-%d",i);
			return 0;
		} else if(sum>=100) {
			int hundred=sum/100;
			deposit+=hundred;
			sum%=100;
		}
		last=sum;
	}
	printf("%d",deposit*120+last);
	return 0;
}

#include<cstdio>
using namespace std;
int Need[10010]={6,2,5,5,4,5,6,3,7,6,8};
int main() {
	int n,ans=0;
	scanf("%d",&n);
	n-=4;
	for(int i=11;i<=10000;i++)
		for(int j=i;j>0;j/=10)
			Need[i]+=Need[j%10];
	for(int i=0;i<=1000;i++)
		for(int j=0;j<=1000;j++)
			if(Need[i]+Need[j]+Need[i+j]==n)ans++;
	printf("%d",ans);
	return 0;
}

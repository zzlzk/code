#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 200010
struct num {
	int Old,New;
	bool operator < (const num &q)const {
		return Old<q.Old;
	}
}a[maxn];
int Count[maxn];
int main() {
	int n,cnt=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].Old);
	sort(a+1,a+n+1);
	a[1].New=1;
	Count[1]++;
	for(int i=2;i<=n;i++) {
		if(a[i].Old==a[i-1].Old) a[i].New=a[i-1].New;
		else a[i].New=++cnt;
		Count[a[i].New]++;
	}
	printf("%d %d\n",a[1].Old,Count[1]);
	for(int i=2;i<=n;i++)
		if(a[i].Old==a[i-1].Old) continue;
		else printf("%d %d\n",a[i].Old,Count[a[i].New]);
	return 0;
}

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 85
struct Bign {
	static const int BASE=10000;
	int a[100],len;
	Bign() {
		len=1;
		a[0]=0;
	}
	Bign(int x) {
		len=1;
		a[0]=x;
	}
	Bign(const Bign &GG) {
		*this=GG;
	}
	Bign operator * (const int &p) const {
		int x=0;
		Bign A=*this;
		for(int i=0;i<len;i++) {
			A.a[i]*=p;
			A.a[i]+=x;
			x=A.a[i]/BASE;
			A.a[i]%=BASE;
		}
		if(x) {
			A.a[len]=x;
			A.len++;
		}
		return A;
	}
	Bign operator + (const Bign &GG)const {
		Bign A;
		int x=0,i;
		for(i=0;i<min(len,GG.len);i++) {
			A.a[i]=a[i]+GG.a[i]+x;
			x=A.a[i]/BASE;
			A.a[i]%=BASE;
		}
		for(;i<len;i++) {
			A.a[i]=a[i]+x;
			x=A.a[i]/BASE;
			A.a[i]%=BASE;
		}
		for(;i<GG.len;i++) {
			A.a[i]=GG.a[i]+x;
			x=A.a[i]/BASE;
			A.a[i]%=BASE;
		}
		A.len=max(len,GG.len);
		if(x==1) {
			A.a[len]=1;
			A.len++;
		}
		return A;
	}
	bool operator > (const Bign &GG)const {
		if(len>GG.len) return true;
		if(len<GG.len) return false;
		for(int i=len-1;i>=0;i--)
			if(a[i]>GG.a[i]) return true;
			else if(a[i]<GG.a[i]) return false;
		return false;
	}
	void Print() {
		printf("%d",a[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%04d",a[i]);
		printf("\n");
		return;
	}
}two[maxn],dp[maxn][maxn],ans;
int a[maxn][maxn],n,m;
void GetPower() {
	two[1]=2;
	for(int i=2;i<=m;i++)
		two[i]=two[i-1]*2;
	return;
}
Bign dpline(int line) {
	for(int i=0;i<m+1;i++)
		for(int j=m+1;j>i;j--) {
			dp[i][j]=0;
			Bign POW=two[m+i-j+1];
			Bign left=POW*a[line][i];
			Bign right=POW*a[line][j];
			if(i!=0) dp[i][j]=dp[i-1][j]+left;
			if(j!=m+1) {
				right=right+dp[i][j+1];
				if(right>dp[i][j]) dp[i][j]=right;
			}
		}
	Bign ret=0;
	for(int i=0;i<=m;i++)
		if(dp[i][i+1]>ret) ret=dp[i][i+1];
	return ret;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	GetPower();
	for(int i=1;i<=n;i++)
		ans=ans+dpline(i);
	ans.Print();
	return 0;
}

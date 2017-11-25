#include<map>
#include<cmath>
#include<cstdio>
using namespace std;
typedef long long ll;
map<int,int>mp;
inline int input() {
	char c=getchar();int x=0,a=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*a;
}
inline ll poowmod(ll a,int k,int p) {
	ll ret=1;
	for(;k;k>>=1,a=(a*a)%p)
		if(k&1) ret=(ret*a)%p;
	return ret;
}
int gcd(int a,int b) {
	return b==0?a:gcd(b,a%b);
}
void exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-(a/b)*y;
	return ;
}
inline void linemod(int y,int z,int p) {
	int g=gcd(y,p),a,b;
	if(z%g){
		printf("Orz, I cannot find x!\n");
		return;
	}
	y/=g;
	z/=g;
	p/=g;
	exgcd(y,p,a,b);
	a=(ll)a*z%p;
	while(a<0) a+=p;
	printf("%d\n",a);
	return;
}
inline void bsgs(int y,int z,int p) {
	mp.clear();
	if((y%=p)==0&&z==0) {
		printf("1\n");
		return;
	}
	if(y==0) {
		printf("Orz, I cannot find x!\n");
		return;
	}
	ll m=ceil(sqrt(p+0.5));
	mp[1]=m+1;
	for(ll i=1,t=1;i<m;i++) {
		t=(t*y)%p;
		if(!mp[t]) mp[t]=i;
	}
	ll inv=1,tmp=poowmod(y,p-m-1,p);
	for(ll k=0;k<m;k++,inv=(inv*tmp)%p) {
		int i=mp[(z*inv)%p];
		if(i) {
			printf("%lld\n",k*m+(i==m+1?0:i));
			return;
		}
	}
	printf("Orz, I cannot find x!\n");
	return;
}
void solve(int T,int L) {
	if(L==1) {
		while(T--) {
			int y=input(),z=input(),p=input();
			printf("%lld\n",poowmod(y,z,p));
		}
	} else if(L==2) {
		while(T--) {
			int y=input(),z=input(),p=input();
			linemod(y,z,p);
		}
	} else {
		while(T--) {
			int y=input(),z=input(),p=input();
			bsgs(y,z,p);
		}
	}
	return;
}
int main() {
	int T=input(),L=input();
	solve(T,L);
	return 0;
}

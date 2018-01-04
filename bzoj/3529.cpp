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

#define MAXQ 20010
#define MAXN 100010
#define N 100000

struct FenWick_Tree {
	int t[MAXN];
	FenWick_Tree() {
		memset(t,0,sizeof(t));
	}
	int lowbit(int x) {
		return x&(-x);
	}
	void modify(int k,int x) {
		for(;k<=N;k+=lowbit(k))
			t[k]+=x;
		return;
	}
	int query(int k) {
		int ans=0;
		for(;k;k-=lowbit(k))
			ans+=t[k];
		return ans;
	}
	int query(int l,int r) {
		return query(r)-query(l-1);
	}
};

FenWick_Tree bit;

struct Query {
	int n,m,a,id;
	Query(int n=0,int m=0,int a=0,int id=0):
		n(n),m(m),a(a),id(id) {}
	bool operator < (const Query &w) const {
		return a<w.a;
	}
};

Query q[MAXQ];

bool not_prime[MAXN];
int prime[MAXN],tot;
int mu[MAXN];

void LineShaker() {
	mu[1]=1;
	for(int i=2;i<=N;i++) {
		if(!not_prime[i]) mu[prime[++tot]=i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++) {
			not_prime[i*prime[j]]=true;
			if(i%prime[j]==0) {
				mu[i*prime[j]]=0;
				break;
			} else mu[i*prime[j]]=-mu[i];
		}
	}
	return;
}

struct Data {
	int x,id;
	Data(int x=0,int id=0):
		x(x),id(id) {}
	bool operator < (const Data &w) const {
		if(x!=w.x) return x<w.x;
		return id<w.id;
	}
	Data operator + (const int &w) const {
		return Data(x+w,id);
	}
	Data operator += (const int &w) {
		*this=*this+w;
		return *this;
	}
};

Data f[MAXN];

void prepare() {
	for(int i=1;i<=N;i++) {
		f[i].id=i;
		for(int j=i;j<=N;j+=i)
			f[j]+=i;
	}
	sort(f+1,f+100001);
	return LineShaker();
}

int ans[MAXQ];
void calc(int i,int n,int m) {
	if(n>m) swap(n,m);
	ans[i]=0;
	for(int l=1,r;l<=n;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans[i]+=bit.query(l,r)*(n/l)*(m/l);
	}
	ans[i]&=2147483647;
	return;
}

int main() {
	prepare();
	int Q,n,m,a;
	input(Q);
	for(int i=1;i<=Q;i++) {
		input(n),input(m),input(a),
		q[i]=Query(n,m,a,i);
	}
	sort(q+1,q+Q+1);
	for(register int i=1,j=1;i<=Q;i++) {
		for(;f[j].x<=q[i].a;j++)
			for(register int k=f[j].id,l=1;k<=N;k+=f[j].id,l++)
				bit.modify(k,mu[l]*f[j].x);
		calc(q[i].id,q[i].n,q[i].m);
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
	return 0;
}

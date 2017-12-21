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

#define MAXN 400010

int s[MAXN],n;
int c[MAXN<<1],X[MAXN<<1],Y[MAXN<<1];
int rank[MAXN],sa[MAXN],height[MAXN];

void Get_Height() {
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++) {
		for(k=max(k-1,0);s[i+k]==s[sa[rank[i]-1]+k];k++);
		height[rank[i]]=k;
	}
	return;
}

void Build_SuffixArray(int m) {
	int *x=X,*y=Y;
	for(int i=1;i<=m;i++) c[i]=0;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<n;k<<=1) {
		int p=0;
		for(int i=n;i>n-k;i--) y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
		swap(x,y),m=1;
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i+1]]&&y[sa[i]+k]==y[sa[i+1]+k]?m:m++;
		if(m>n) return Get_Height();
	}
	return Get_Height();
}

char ch[MAXN];

int pos,top;

int getid(int i) {
	return sa[i]==pos?0:(sa[i]>pos?2:1);
}

ll st[MAXN],sum[MAXN],tot[MAXN];

int main() {
	scanf("%s",ch);
	n=strlen(ch);
	for(int i=1;i<=n;i++)
		s[i]=ch[i-1];
	s[++n]='#',pos=n;
	scanf("%s",ch);
	int n_=strlen(ch);
	for(int i=1;i<=n_;i++)
		s[++n]=ch[i-1];
	Build_SuffixArray(138);
	ll ans=0;
    for(int i=1,id;i<=n;i++) {
        id=getid(i);
		if(!id) continue;
        if(id==2) ans+=tot[top];
        if(i!=n){
            st[++top]=height[i+1];
			sum[top]=2-id;
            tot[top]=st[top]*sum[top]+tot[top-1];
            while(st[top]<=st[top-1]&&top!=0) {
                sum[top-1]+=sum[top];
                st[top-1]=st[top--];
                tot[top]=st[top]*sum[top]+tot[top-1];
            }
        }
    }
    top=0;
    for(int i=1,id;i<=n;i++) {
        id=getid(i);
		if(!id) continue;
        if(id==1) ans+=tot[top];
        if(i!=n) {
            st[++top]=height[i+1];
			sum[top]=id-1;
            tot[top]=st[top]*sum[top]+tot[top-1];
            while(st[top]<=st[top-1]&&top!=0) {
                sum[top-1]+=sum[top];
                st[top-1]=st[top--];
                tot[top]=st[top]*sum[top]+tot[top-1];
            }
        }
    }
    printf("%lld\n",ans);
	return 0;
}

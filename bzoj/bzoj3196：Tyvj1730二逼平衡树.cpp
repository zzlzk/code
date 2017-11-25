#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 50010
#define maxm 3000010
struct Segment_tree {
	int l,r,root,Max,Min;
}t[maxn<<2];
int data[maxn],size[maxm],ch[maxm][2];
int fa[maxm],cnt[maxm],num[maxm];
int n,m,sz=0;
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void updata(int now) {
	int l=ch[now][0],r=ch[now][1];
	size[now]=size[l]+size[r]+cnt[now];
	return;
}
inline void updataseg(int now) {
	int lc=now<<1,rc=now<<1|1;
	t[now].Max=max(t[lc].Max,t[rc].Max);
	t[now].Min=min(t[lc].Min,t[rc].Min);
	return;
}
inline int son(int x) {
	return ch[fa[x]][1]==x;
}
void rotate(int &root,int x) {
	int y=fa[x],z=fa[y];
	int b=son(x),c=son(y),a=ch[x][!b];
	if(z) ch[z][c]=x;
	else root=x;
	fa[x]=z;
	if(a) fa[a]=y;
	ch[y][b]=a;
	ch[x][!b]=y;
	fa[y]=x;
	updata(y);
	updata(x);
	return;
}
void splay(int &root,int x,int i) {
	while(fa[x]!=i) {
		int y=fa[x],z=fa[y];
		if(z==i) rotate(root,x);
		else {
			if(son(x)==son(y)) {
				rotate(root,y);
				rotate(root,x);
			} else {
				rotate(root,x);
				rotate(root,x);
			}
		}
	}
	return;
}
void insert(int &k,int c) {
	if(k==0) {
		k=++sz;
		size[k]=cnt[k]=1;
		num[k]=c;
		return;
	}
	if(num[k]==c) cnt[k]++;
	else if(num[k]<c) {
		insert(ch[k][1],c);
		fa[ch[k][1]]=k;
	} else {
		insert(ch[k][0],c);
		fa[ch[k][0]]=k;
	}
	updata(k);
	return;
}
void buildseg(int now,int l,int r) {
	t[now].l=l,t[now].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	buildseg(now<<1,l,mid);
	buildseg(now<<1|1,mid+1,r);
	return;
}
int getpre(int rt,int k) {
	int pos=rt,ret;
	while(pos) {
		if(num[pos]>=k) pos=ch[pos][0];
		else ret=pos,pos=ch[pos][1];
	}
	return ret;
}
int getsuf(int rt,int k) {
	int pos=rt,ret;
	while(pos) {
		if(num[pos]<=k) pos=ch[pos][1];
		else ret=pos,pos=ch[pos][0];		
	}
	return ret;
}
int getk(int rt,int k) {
	if(num[rt]==k) return rt;
	if(num[rt]<k) return getk(ch[rt][1],k);
	if(num[rt]>k) return getk(ch[rt][0],k);
}
void build(int rt,int pos,int x) {
	insert(t[rt].root,x);
	if(t[rt].l==t[rt].r) {
		t[rt].Max=t[rt].Min=x;
		return;
	}
	int mid=t[rt].l+t[rt].r>>1;
	if(pos<=mid) build(rt<<1,pos,x);
	else build(rt<<1|1,pos,x);
	updataseg(rt);
	return;
}
void dfsseg(int rt) {
	int x=getsuf(t[rt].root,-1);
	int y=getpre(t[rt].root,1e8+1);
	splay(t[rt].root,x,0);
	size[x]++;
	ch[x][0]=++sz;
	fa[sz]=x;
	size[sz]=cnt[sz]=1;
	num[sz]=-1;
	splay(t[rt].root,y,0);
	size[y]++;
	ch[y][1]=++sz;
	fa[sz]=y;
	size[sz]=cnt[sz]=1;
	num[sz]=1e8+1;
	if(t[rt].l==t[rt].r) return;
	dfsseg(rt<<1);
	dfsseg(rt<<1|1);
	return;
}
int getmax(int rt,int l,int r) {
	if(l<=t[rt].l&&t[rt].r<=r) return t[rt].Max;
	int mid=t[rt].l+t[rt].r>>1,ret=-1;
	if(l<=mid) ret=max(ret,getmax(rt<<1,l,r));
	if(mid<r) ret=max(ret,getmax(rt<<1|1,l,r));
	return ret;	
}
int getmin(int rt,int l,int r) {
	if(l<=t[rt].l&&t[rt].r<=r) return t[rt].Min;
	int mid=t[rt].l+t[rt].r>>1,ret=1e8+1;
	if(l<=mid) ret=min(ret,getmin(rt<<1,l,r));
	if(mid<r) ret=min(ret,getmin(rt<<1|1,l,r));
	return ret;
}
int query_order(int rt,int l,int r,int k) {
	if(l<=t[rt].l&&t[rt].r<=r) {
		int p=getpre(t[rt].root,k);
		splay(t[rt].root,p,0);
		return size[p]-size[ch[p][1]]-1;
	}
	int mid=t[rt].l+t[rt].r>>1,ret=0;
	if(l<=mid) ret+=query_order(rt<<1,l,r,k);
	if(mid<r) ret+=query_order(rt<<1|1,l,r,k);
	return ret;
}
void del(int &rt,int k) {
	int x=getk(rt,k);
	if(cnt[x]>1) {
		splay(rt,x,0);
		cnt[x]--;
		size[x]--;
	} else {
		int p=getpre(rt,k),s=getsuf(rt,k);
		splay(rt,p,0);
		splay(rt,s,p);
		ch[s][0]=0;
	}
	return;
}
void modify(int rt,int pos,int pre,int now) {
	del(t[rt].root,pre);
	insert(t[rt].root,now);
	if(t[rt].l==t[rt].r) {
		t[rt].Max=t[rt].Min=now;
		return;
	}
	int mid=t[rt].l+t[rt].r>>1;
	if(pos<=mid) modify(rt<<1,pos,pre,now);
	else modify(rt<<1|1,pos,pre,now);
	updataseg(rt);
	return;
}
int query_pre(int rt,int l,int r,int k) {
	if(l<=t[rt].l&&t[rt].r<=r)
		return num[getpre(t[rt].root,k)];
	int mid=t[rt].l+t[rt].r>>1,ret=-1;
	if(l<=mid) ret=max(ret,query_pre(rt<<1,l,r,k));
	if(mid<r) ret=max(ret,query_pre(rt<<1|1,l,r,k));
	return ret;
}
int query_suf(int rt,int l,int r,int k) {
	if(l<=t[rt].l&&t[rt].r<=r)
		return num[getsuf(t[rt].root,k)];
	int mid=t[rt].l+t[rt].r>>1,ret=1e8+1;
	if(l<=mid) ret=min(ret,query_suf(rt<<1,l,r,k));
	if(mid<r) ret=min(ret,query_suf(rt<<1|1,l,r,k));
	return ret;
}
int query_number(int L,int R,int k) {
	int l=1,r=getmax(1,L,R),mid,ret,tmp;
	while(l<=r) {
		mid=l+r>>1;
		tmp=query_order(1,L,R,mid);
		if(tmp<k) ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret;
}
int main() {
	n=input(),m=input();
	buildseg(1,1,n);
	for(int i=1;i<=n;i++) data[i]=input();
	for(int i=1;i<=n;i++) build(1,i,data[i]);
	dfsseg(1);
	while(m--) {
		int l,r,k,pos,op=input();
		if(op==1) {
			l=input(),r=input(),k=input();
			printf("%d\n",query_order(1,l,r,k)+1);
		} else if(op==2) {
			l=input(),r=input(),k=input();
			printf("%d\n",query_number(l,r,k));
		} else if(op==3) {
			pos=input(),k=input();
			modify(1,pos,data[pos],k);
			data[pos]=k;
		} else if(op==4) {
			l=input(),r=input(),k=input();
			int ans=query_pre(1,l,r,k);
			if(ans!=1e8+1) printf("%d\n",ans);
			else printf("%d\n",getmax(1,l,r));
		} else if(op==5) {
			l=input(),r=input(),k=input();
			int ans=query_suf(1,l,r,k);
			if(ans!=-1) printf("%d\n",ans);
			else printf("%d\n",getmin(1,l,r));
		}
	}
	return 0;
}

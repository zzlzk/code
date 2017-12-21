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

#define blocksize 1500

int tot,size[blocksize],list[blocksize],next[blocksize];
char s[2000010],data[blocksize][blocksize];

int _new() {
	return list[tot++];
}

void _delete(int t) {
	list[--tot]=t;
	return;
}

void Find(int &p,int &b) {
	for(b=0;b!=-1&&p>size[b];b=next[b])
		p-=size[b];
	return;
}

void fillblock(int b,int n,char *s,int _next) {
	if(b==-1) return;
	next[b]=_next,size[b]=n;
	memcpy(data[b],s,n);
	return;
}

void split(int b,int p) {
	if(b==-1||p==size[b]) return;
	int t=_new();
	fillblock(t,size[b]-p,data[b]+p,next[b]);
	next[b]=t,size[b]=p;
	return;
}

void maintain(int b) {
	for(;b!=-1;b=next[b])
		for(int t=next[b];t!=-1&&size[t]+size[b]<=blocksize;t=next[t]) {
			memcpy(data[b]+size[b],data[t],size[t]);
			size[b]+=size[t],next[b]=next[t];
			_delete(t);
		}
	return;
}

void insert(int p,int n,char *s) {
	int b,t,i;
	Find(p,b),split(b,p);
	for(i=0;i+blocksize<=n;i+=blocksize) {
		t=_new();
		fillblock(t,blocksize,s+i,next[b]);
		next[b]=t,b=t;
	}
	if(n-i) {
		t=_new();
		fillblock(t,n-i,s+i,next[b]);
		next[b]=t;
	}
	return maintain(b);
}

void erase(int p,int n) {
	int b,_next;
	Find(p,b),split(b,p);
	for(_next=next[b];_next!=-1&&n>size[_next];_next=next[_next])
		n-=size[_next];
	split(_next,n);
	_next=next[_next];
	for(int t=next[b];t!=_next;t=next[t]) {
		next[b]=next[t];
		_delete(t);
	}
	return maintain(b);
}

void copy(int p,int n,char *s) {
	int b,t,i;
	Find(p,b);
	i=min(n,size[b]-p);
	memcpy(s,data[b]+p,i);
	for(t=next[b];t!=-1&&i+size[t]<=n;i+=size[t],t=next[t])
		memcpy(s+i,data[t],size[t]);
	if(n-i&&t!=-1) memcpy(s+i, data[t], n-i);
	return;
}

int main() {
	for(int i=1;i<blocksize;list[i]=i++);
	tot=1,next[0]=-1;
	int cursor=0,T;
	input(T);
	char op[10];
	for(int n;T;T--) {
		scanf("%s",op);
		if(op[0]=='M') input(cursor);
		else if(op[0]=='I') {
			input(n);
			for(int i=0;i<n;) {
				char c=getchar();
				if(32<=c&&c<=126) s[i++]=c;
			}
			s[n]='\0';
			insert(cursor,n,s);
		} else if(op[0]=='D') {
			input(n);
			erase(cursor,n);
		} else if(op[0]=='G') {
			input(n);
			copy(cursor,n,s);
			s[n]='\0';
			printf("%s\n",s);
		} else cursor+=(op[0]=='P'?-1:1);
	}
	return 0;
}

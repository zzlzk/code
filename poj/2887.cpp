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

#define MAXN 1000010
#define L 2000
#define N 2000

struct Data {
	char s[L];
	int next,size;
	void init() {
		memset(s,0,sizeof(s));
		next=-1,size=0;
		return;
	}
};

struct Massive_chain_list {
	Data list[N];
    int head,tot;
	void split(int x) {
		list[tot].init();
		for(int i=L/2;i<L;i++){
			list[tot].s[i-L/2]=list[x].s[i],
			list[tot].size++,
			list[x].size--,
			list[x].s[i]=0;
		}
		list[tot].next=list[x].next;
		list[x].next=tot++;
		return;
	}
	void init(char s[]) {
		head=tot=0;
		list[tot++].init();
		for(int i=0,k=head;s[i];k=list[k].next) {
			for(int j=0;j<L&&s[i];j++,i++) {
				list[k].s[j]=s[i];
				list[k].size++;
			}
			if(s[i]) {
				list[tot].init();
				list[k].next=tot++;
			}
		}
		for(int i=head;i!=-1;i=list[i].next)
			if(list[i].size==L) split(i);
		return;
	}
	void insert(int pos, char ch) {
		int k=head;
		while(pos>list[k].size&&list[k].next!=-1)
			pos-=list[k].size,k=list[k].next;
		if(pos>=list[k].size)
			list[k].s[list[k].size]=ch;
		else {
			for(int i=list[k].size;i>pos;i--)
				list[k].s[i]=list[k].s[i-1];
			list[k].s[pos]=ch;
		}
		if(++list[k].size==L) split(k);
		return;
	}
	char query(int pos) {
		int k=head;
		while(pos>list[k].size)
			pos-=list[k].size,k=list[k].next;
		return list[k].s[pos-1];
	}
};

Massive_chain_list block;

char s[MAXN];

int main() {
	scanf("%s",s);
	block.init(s);
	int n;
	input(n);
	for(int k;n;n--) {
		scanf("%s",s);
		if(s[0]=='I') {
			scanf("%s",s),input(k);
			block.insert(k-1,s[0]);
		} else {
			scanf("%d",&k);
			printf("%c\n",block.query(k));
		}
	}
	return 0;
}

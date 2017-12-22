#include<queue>
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

struct Trie {
	Trie *ch[26];
	Trie *fail;
	int cnt;
	Trie() {
		for(int i=0;i<26;i++)
			this->ch[i]=NULL;
		fail=NULL;
		cnt=0;
	}
};

char s[160][80],ss[1000010];

struct AC_automaton {

	Trie *root;
	queue<Trie*> q;
	int ans[MAXN],pos[MAXN],timee;

	void Clear() {
		root=new Trie;
		timee=0;
		memset(ans,0,sizeof(ans));
		memset(pos,0,sizeof(pos));
		return;
	}

	AC_automaton() {
		this->Clear();
	}

	void insert(char *s) {
		timee++;
		Trie *now=root;
		int id,L=strlen(s);
		for(int i=0;i<L;i++) {
			id=s[i]-'a';
			if(now->ch[id]==NULL)
				now->ch[id]= new Trie;
			now=now->ch[id];
		}
		if(!now->cnt) now->cnt=timee;
		pos[timee]=now->cnt;
		return;
	}
	
	void get_fail() {
		q.push(root);
		Trie *now,*pos;
		while(!q.empty()) {
			pos=NULL,now=q.front();
			q.pop();
			for(int i=0;i<26;i++) {
				if(now->ch[i]==NULL) continue;
				if(now==root)
					now->ch[i]->fail=root;
				else {
					for(pos=now->fail;pos;pos=pos->fail)
						if(pos->ch[i]!=NULL) {
							now->ch[i]->fail=pos->ch[i];
							break;
						}
					if(pos==NULL)
						now->ch[i]->fail=root;
				}
				q.push(now->ch[i]);
			}
		}
		return;
	}
	
	void query(char *s) {
		int L=strlen(s),id;
		Trie *now=root;
		for(int i=0;i<L;i++) {
			id=s[i]-'a';
			while(now->ch[id]==NULL&&now!=root)
				now=now->fail;
			now=now->ch[id];
			if(now==NULL) now=root;
			for(Trie *pos=now;pos!=root;pos=pos->fail)
				ans[pos->cnt]++;
		}
		return;
	}

	void print(int n) {
		int Max=-1;
		for(int i=1;i<=n;i++)
			Max=max(Max,ans[i]);
		printf("%d\n",Max);
		for(int i=1;i<=n;i++)
			if(ans[pos[i]]==Max)
				printf("%s\n",s[i]);
		return;
	}
};

AC_automaton ac;

int main() {
	for(int n;scanf("%d",&n)!=EOF&&n!=0;ac.Clear()) {
		for(int i=1;i<=n;i++) {
			scanf("%s",s[i]),
			ac.insert(s[i]);
		}
		ac.get_fail(),
		scanf("%s",ss),
		ac.query(ss),ac.print(n);
	}
	return 0;
}

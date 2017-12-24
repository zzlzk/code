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

#define MAXN 1048580

struct Trie {
    Trie *ch[26];
    bool flag;
    Trie() {
        for(int i=0;i<26;i++)
            ch[i]=NULL;
        flag=false;
    }
};

Trie *root;

Trie ooo[6010];
Trie *gg=ooo;

int Max;

void insert(char *s) {
    Trie *now=root;
    int L=strlen(s);
    Max=max(L,Max);
    for(int i=0,id;i<L;i++) {
        id=s[i]-'a';
        if(now->ch[id]==NULL)
            now->ch[id]=gg++;
        now=now->ch[id];
    }
    now->flag=true;
    return;
}

char s[MAXN];

bool query(int l,int r) {
    Trie *now=root;
    for(int i=l,id;i<=r;i++) {
        id=s[i]-'a';
        if(now->ch[id]==NULL) return false;
        now=now->ch[id];
    }
    return now->flag;
}

bool f[MAXN];

int main() {
    int n,m;
    input(n),input(m);
    root=gg++;
    for(int i=1;i<=n;i++) {
        scanf("%s",s);
        insert(s);
    }
    for(int i=1;i<=m;i++) {
        scanf("%s",s);
        memset(f,0,sizeof(f));
        int L=strlen(s),ans=0;
        for(int j=0;j<L;j++)
            for(int k=max(j-Max,-1);k<=j;k++)
                if((k==-1||f[k])&&query(k+1,j)) {
                    f[j]=true,ans=j+1;
                    break;
                }
        printf("%d\n",ans);
    }
    return 0;
}

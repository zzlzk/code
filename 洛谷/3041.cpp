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

#define inf 2147483647
#define MAXK 1010

struct Trie {
    Trie *ch[3];
    Trie *fail;
    int f[MAXK];
    int cnt;
    Trie(): cnt(0) {
        for(int i=0;i<3;i++)
            ch[i]=NULL;
        fail=NULL;
    }
};

int n,k;

struct AC_automaton {
    
    Trie memory_pool[410],*gg;
    Trie *root;
    queue<Trie*> q;

    AC_automaton() {
        root=gg=memory_pool;
        for(int i=0;i<MAXK;i++)
            root->f[i]=0;
    }

    void insert(char *s) {
        int L=strlen(s);
        Trie *now=root;
        for(int i=0,id;i<L;i++) {
            id=s[i]-'A';
            if(now->ch[id]==NULL) {
                now->ch[id]=++gg;
                for(int o=0;o<MAXK;o++)
                    now->ch[id]->f[o]=-inf;
            }
            now=now->ch[id];
        }
        now->cnt++;
        return;
    }

    void get_fail() {
        for(int i=0;i<3;i++)
            if(root->ch[i]!=NULL) {
                root->ch[i]->fail=root;
                q.push(root->ch[i]);
            }
        while(!q.empty()) {
            Trie *now=q.front();
            q.pop();
            for(int i=0;i<3;i++) {
                if(now->ch[i]==NULL) continue;
                Trie *pos;
                for(pos=now->fail;pos;pos=pos->fail)
                    if(pos->ch[i]!=NULL) {
                        now->ch[i]->fail=pos->ch[i];
                        break;
                    }
                if(pos==NULL) now->ch[i]->fail=root;
                now->ch[i]->cnt+=now->ch[i]->fail->cnt;
                q.push(now->ch[i]);
            }
        }
        return;
    }


    void dp() {
        for(int i=1;i<=k;i++) {
            q.push(root);
            while(!q.empty()) {
                Trie *now=q.front();
                q.pop();
                now->f[i]+=now->cnt;
                for(int j=0;j<3;j++)
                    if(now->ch[j]!=NULL) {
                        now->ch[j]->f[i]=max(now->f[i-1],now->ch[j]->f[i]);
                        q.push(now->ch[j]);
                    }
                for(Trie *pos=now->fail;pos;pos=pos->fail)
                    pos->f[i]=max(now->f[i],pos->f[i]);
            }
        }
        return;
    }

};

AC_automaton ac;

int main() {
    input(n),input(k);
    char s[20];
    for(int i=1;i<=n;i++) {
        scanf("%s",s);
        ac.insert(s);
    }
    ac.get_fail();
    ac.dp();
    printf("%d\n",ac.root->f[k]);
    return 0;
}

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

struct AC_automaton {
    
    Trie *root;
    queue<Trie*> q;
    
    AC_automaton() {
        root=new Trie;
    }

    void insert(char *s) {
        Trie *now=root;
        int id,L=strlen(s);
        for(int i=0;i<L;i++) {
            id=s[i]-'a';
            if(now->ch[id]==NULL)
                now->ch[id]= new Trie;
            now=now->ch[id];
        }
        now->cnt++;
        return;
    }
    
    void get_fail() {
        q.push(root);
        Trie *now,*pos;
        while(!q.empty()) {
            pos=NULL,now=*&q.front();
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
    
    int query(char *s) {
        int ans=0,L=strlen(s),id;
        Trie *now=root;
        for(int i=0;i<L;i++) {
            id=s[i]-'a';
            while(now->ch[id]==NULL&&now!=root)
                now=now->fail;
            now=now->ch[id];
            if(now==NULL) now=root;
            for(Trie *pos=now;pos!=root&&pos->cnt>=0;pos=pos->fail)
                ans+=pos->cnt,pos->cnt=-1;
        }
        return ans;
    }

};

AC_automaton ac;

char s[MAXN];

int main() {
    int T,n;
    for(input(n);n;n--) {
        scanf("%s",s);
        ac.insert(s);
    }
    ac.get_fail();
    scanf("%s",s);
    printf("%d\n",ac.query(s));
    return 0;
}

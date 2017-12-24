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

#define MAXN 100100

struct Trie {
    Trie *ch[26];
    Trie *fail;
    int maxL;
    Trie(): maxL(0) {
        for(int i=0;i<26;i++)
            ch[i]=NULL;
        fail=NULL;
    }
    void *operator new(size_t) {
        static Trie memory_pool[MAXN],*gg=memory_pool;
        return gg++;
    }
};

struct AC_automaton {
    
    Trie *root;
    queue<Trie*> q;

    AC_automaton() {
        root=new Trie;
    }

    void insert(char *s) {
        int L=strlen(s);
        Trie *now=root;
        for(int i=0,id;i<L;i++) {
            id=s[i]-'a';
            if(now->ch[id]==NULL)
                now->ch[id]=new Trie;
            now=now->ch[id];
        }
        now->maxL=max(now->maxL,L);
        return;
    }

    void get_fail() {
        for(int i=0;i<26;i++)
            if(root->ch[i]!=NULL) {
                root->ch[i]->fail=root;
                q.push(root->ch[i]);
            } else root->ch[i]=root;
        while(!q.empty()) {
            Trie *now=q.front();
            q.pop();
            for(int i=0;i<26;i++)
                if(now->ch[i]!=NULL) {
                    now->ch[i]->fail=now->fail->ch[i];
                    now->ch[i]->maxL=max(now->ch[i]->maxL,now->ch[i]->fail->maxL);
                    q.push(now->ch[i]);
                } else now->ch[i]=now->fail->ch[i];
        }
        return;
    }
};

AC_automaton ac;

char s[MAXN],ss[MAXN];

template<typename T>
struct Stack {
    T a[MAXN];
    int top;
    Stack(): top(0) {}
    void push(T x) {
        a[++top]=x;
        return;
    }
};

Stack<char> st;

Trie *a[MAXN];

int main() {
    int n,L;
    scanf("%s",s);
    input(n);
    for(int i=1;i<=n;i++) {
        scanf("%s",ss),
        ac.insert(ss);
    }
    ac.get_fail(),a[0]=ac.root;
    L=strlen(s);
    for(int i=0;i<L;i++) {
        st.push(s[i]);
        a[st.top]=a[st.top-1]->ch[s[i]-'a'];
        if(a[st.top]->maxL) st.top-=a[st.top]->maxL;
    }
    for(int i=1;i<=st.top;i++)
        printf("%c",st.a[i]);
    puts("");
    return 0;
}

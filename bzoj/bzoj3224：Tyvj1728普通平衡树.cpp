#include<cstdio>
using namespace std;
#define maxn 100010
int fa[maxn],ch[maxn][2],size[maxn],cnt[maxn],data[maxn];
int root,nn,n,tot;
inline int input() {
    int x=0,a=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    return x*a;
}
int son(int x) {
    return x==ch[fa[x]][1];
}
void updata(int rt) {
    int l=ch[rt][0],r=ch[rt][1];
    size[rt]=size[l]+size[r]+cnt[rt];
    return;
}
void rotate(int x) {
    int y=fa[x],z=fa[y],b=son(x),c=son(y),a=ch[x][!b];
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
void splay(int x,int i) {
    while(fa[x]!=i) {
        int y=fa[x],z=fa[y];
        if(z==i) rotate(x);
        else {
            if(son(x)==son(y)) {
                rotate(y);
                rotate(x);
            } else {
                rotate(x);
                rotate(x);
            }
        }
    }
    return;
}
void ins(int &rt,int x) {
    if(rt==0) {
        rt=++nn;
        data[nn]=x;
        size[nn]=cnt[nn]=1;
        return;
    }
    if(x==data[rt]) {
        cnt[rt]++;size[rt]++;
        return;
    }
    if(x<data[rt]) {
        ins(ch[rt][0],x);
        fa[ch[rt][0]]=rt;
        updata(rt);
    } else {
        ins(ch[rt][1],x);
        fa[ch[rt][1]]=rt;
        updata(rt);
    }
    return;
}
int getpre(int rt,int x) {
    int p=rt,ans;
    while(p) {
        if(x<=data[p]) p=ch[p][0];
        else ans=p,p=ch[p][1];
    }
    return ans;
}
int getsuf(int rt,int x) {
    int p=rt,ans;
    while(p) {
        if(x>=data[p]) p=ch[p][1];
        else ans=p,p=ch[p][0];
    }
    return ans;
}
int getmin(int rt) {
    int p=rt,ans=-1;
    while(p) ans=p,p=ch[p][0];
    return ans;
}
void del(int rt,int x) {
    if(data[rt]==x) {
        if(cnt[rt]>1) cnt[rt]--,size[rt]--;
        else {
            splay(rt,0);
            int p=getmin(ch[rt][1]);
            if(p!=-1) {
                splay(p,rt);
                root=p;
                fa[p]=0;
                ch[p][0]=ch[rt][0];
                fa[ch[rt][0]]=p;
                updata(p);
            } else root=ch[rt][0],fa[ch[rt][0]]=0;
        }
        return;
    }
    if(x<data[rt]) {
        del(ch[rt][0],x);
        updata(rt);
    } else {
        del(ch[rt][1],x);
        updata(rt);
    }
    return;
}
int getk(int rt,int k) {
    if(data[rt]==k) {
        splay(rt,0);
        if(ch[rt][0]==0) return 1;
        else return size[ch[rt][0]]+1;
    }
    if(k<data[rt]) return getk(ch[rt][0],k);
    else return getk(ch[rt][1],k);
}
int getkth(int rt,int k) {
    int l=ch[rt][0];
    if(size[l]+1<=k&&k<=size[l]+cnt[rt]) return data[rt];
    if(k<size[l]+1) return getkth(ch[rt][0],k);
    if(size[l]+cnt[rt]<k) return getkth(ch[rt][1],k-(size[l]+cnt[rt]));
}
int main() {
    for(int i=input(),op,x;i>=1;i--) {
        op=input(),x=input();
        if(op==1) tot++,ins(root,x);
        if(op==2) tot--,del(root,x);
        if(op==3) printf("%d\n",getk(root,x));
        if(op==4) printf("%d\n",getkth(root,x));
        if(op==5) printf("%d\n",data[getpre(root,x)]);
        if(op==6) printf("%d\n",data[getsuf(root,x)]);
    }
    return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1010

template<typename T>
void input(T &x) {
    x=0; int a=1;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    if(a==-1) x=-x;
    return;
}

struct Minister {
    
    int l,r,product;
    
    Minister(int l=0,int r=0,int product=0):
        l(l),r(r),product(product) {}
    
    bool operator < (const Minister &a)const {
        return product<a.product;
    }
    
}Game[maxn];

struct Bign {
    
    static const int BASE=10000;
    static const int MAXN=1010;
    int a[MAXN],len;
    
    Bign() {
        len=1;
        for(int i=0;i<MAXN;i++)
            a[i]=0;
    }
    
    Bign(int x) {
        len=0;
        do {
            a[len]=x%BASE;
            x/=BASE;
            len++;
        }while(x!=0);
    }
    
    Bign(const Bign &GG) {
        *this=GG;
    }
    
    void Clear() {
        while(a[len-1]==0&&len!=1) len--;
        return;
    }
    
    Bign operator * (const int &p) const {
        int x=0;
        Bign A=*this;
        for(int i=0;i<len;i++) {
            A.a[i]*=p;
            A.a[i]+=x;
            x=A.a[i]/BASE;
            A.a[i]%=BASE;
        }
        if(x) {
            A.a[len]=x;
            A.len++;
        }
        A.Clear();
        return A;
    }
    
    Bign operator *= (const int &p) {
        *this=*this*p;
        return *this;
    }
    
    Bign operator / (const int &p) const {
        Bign ret,A=*this;
        ret.len=len+1;
        for(int i=len-1;i>=0;i--) {
            ret.a[i]=A.a[i]/p;
            if(i!=0) A.a[i-1]+=(A.a[i]%p*BASE);
            A.a[i]/=p;
        }
        ret.Clear();
        return ret;
    }
    
    Bign operator /= (const int &p) {
        *this=*this/p;
        return *this;
    }
    
    bool operator < (const Bign &GG) const {
        if(len<GG.len) return true;
        if(len>GG.len) return false;
        for(int i=len-1;i>=0;i--)
            if(a[i]<GG.a[i]) return true;
            else if(a[i]>GG.a[i]) return false;
        return false;
    }
    
    void Print() {
        Clear();
        printf("%d",a[len-1]);
        for(int i=len-2;i>=0;i--)
            printf("%04d",a[i]);
        printf("\n");
        return;
    }
    
};

int main() {
    int n;
    input(n);
    for(int i=0;i<=n;i++) {
        int l,r;
        input(l),input(r);
        Game[i]=Minister(l,r,l*r);
    }
    sort(Game+1,Game+n+1);
    Bign now=Game[0].l,Ans;
    for(int i=1;i<=n;i++) {
        Bign GG=now/Game[i].r;
        if(Ans<GG) Ans=GG;
        now*=Game[i].l;
    }
    Ans.Print();
    return 0;
}
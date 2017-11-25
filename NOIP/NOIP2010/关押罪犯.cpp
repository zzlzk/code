#include<algorithm>
#include<cstdio>
using namespace std;
#define maxn 100050
struct node{
    int a , b , c;
}man[maxn];
int father[maxn];
bool cmp(node a,node b) {
    return a.c>b.c;
}
int find(int x) {
    return x==father[x]?x:x=find(father[x]);
}
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        scanf("%d%d%d",&man[i].a,&man[i].b,&man[i].c);
    for(int i=1;i<=2*n;i++) father[i]=i;
    sort(man,man+m,cmp);
    for (int i=0;i<m;++i) {
        int x=find(man[i].a);
        int y=find(man[i].b);
        if(x==y) {
            printf("%d",man[i].c);
            return 0;
        }
        father[x]=find(man[i].b+n);
        father[y]=find(man[i].a+n);
    }
    printf("0");
    return 0;
}
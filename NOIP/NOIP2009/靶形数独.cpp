#include<cstdio>
#include<algorithm>
using namespace std;
const int mark[10][10]={{0,0,0,0,0, 0,0,0,0,0},
                        {0,6,6,6,6, 6,6,6,6,6},
                        {0,6,7,7,7, 7,7,7,7,6},
                        {0,6,7,8,8, 8,8,8,7,6},
                        {0,6,7,8,9, 9,9,8,7,6},
                        {0,6,7,8,9,10,9,8,7,6},
                        {0,6,7,8,9, 9,9,8,7,6},
                        {0,6,7,8,8, 8,8,8,7,6},
                        {0,6,7,7,7, 7,7,7,7,6},
                        {0,6,6,6,6, 6,6,6,6,6}};
const int pos[10][10]={{0,0,0,0,0,0,0,0,0,0},
                       {0,1,1,1,2,2,2,3,3,3},
                       {0,1,1,1,2,2,2,3,3,3},
                       {0,1,1,1,2,2,2,3,3,3},
                       {0,4,4,4,5,5,5,6,6,6},
                       {0,4,4,4,5,5,5,6,6,6},
                       {0,4,4,4,5,5,5,6,6,6},
                       {0,7,7,7,8,8,8,9,9,9},
                       {0,7,7,7,8,8,8,9,9,9},
                       {0,7,7,7,8,8,8,9,9,9}};
struct lattice {
    int R,C;
	bool vis;
    lattice(int R=0,int C=0):
        R(R),C(C) {}
    bool operator < (const lattice &a) const {
        if(R!=a.R) return R>a.R;
        return C>a.C;
    }
}lat[90];
bool row[10][10],column[10][10],square[10][10];
int ans=-1,Score,need;
void Astar(int cnt,int Score) {
    if(cnt==need+1) {
        ans=Score>ans?Score:ans;
        return;
    }
    int Pos,mincan=10;
    for(int i=1;i<=need;i++) 
        if(!lat[i].vis) {
            int R=lat[i].R,C=lat[i].C,Possible=0;
            for(int j=1;j<=9;j++) {
                if(row[R][j]||column[C][j]||square[pos[R][C]][j]) continue;
                Possible++;
            }
            if(Possible<mincan) mincan=Possible,Pos=i;
            if(Possible<=1) break;
        }
    if(!mincan) return;
	lat[Pos].vis=true;
    for(int i=1;i<=9;i++) {
        int R=lat[Pos].R,C=lat[Pos].C;
        if(row[R][i]||column[C][i]||square[pos[R][C]][i]) continue;
        row[R][i]=column[C][i]=square[pos[R][C]][i]=true;
        Astar(cnt+1,Score+i*mark[R][C]);
        row[R][i]=column[C][i]=square[pos[R][C]][i]=false;
    }
    lat[Pos].vis=false;
	return;
}
int main() {
    for(int i=1;i<=9;i++)
        for(int j=1,k;j<=9;j++) {
            scanf("%d",&k);
            if(k) {
                row[i][k]=column[j][k]=square[pos[i][j]][k]=true;
                Score+=k*mark[i][j];
            } else lat[++need]=lattice(i,j);
        }
    sort(lat+1,lat+need+1);
    Astar(1,Score);
    printf("%d",ans);
    return 0;
}

#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 103
int SumPrize=0;
struct Student {
    string name;
    int test,grade,num,sum;
    bool west,cadre;
    bool operator < (const Student &a) const {
        return sum<a.sum;
    }
}stu[maxn];
void calcPrize(Student &a) {
    if(a.num>=1&&a.test>80) a.sum+=8000;
    if(a.test>85&&a.grade>80) a.sum+=4000;
    if(a.test>90) a.sum+=2000;
    if(a.test>85&&a.west==true) a.sum+=1000;
    if(a.grade>80&&a.cadre==true) a.sum+=850;
    SumPrize+=a.sum;
}
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>stu[i].name>>stu[i].test>>stu[i].grade;
        char c,cc;
        cin>>c>>cc;
        stu[i].cadre=c=='Y'?true:false;
        stu[i].west=cc=='Y'?true:false;
        cin>>stu[i].num;
        calcPrize(stu[i]);
    }
    sort(stu+1,stu+n+1);
    cout<<stu[n].name<<endl<<stu[n].sum<<endl<<SumPrize;
    return 0;
}

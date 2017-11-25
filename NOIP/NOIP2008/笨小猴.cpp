#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 110
char word[maxn];
int Count[30];
int id(char ch) {
	return ch-'a'+1;
}
bool is_prime(int x) {
	if(x==1||x==0) return false;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}
int main() {
	scanf("%s",word);
	int len=strlen(word);
	int Max=-maxn,Min=maxn;
	for(int i=0;i<len;i++)
		Count[id(word[i])]++;
	for(int i=1;i<=26;i++)
		if(Count[i]!=0) {
			Max=max(Max,Count[i]);
			Min=min(Min,Count[i]);
		}
	int x=Max-Min;
	bool flag=is_prime(x);
	if(flag) printf("Lucky Word\n%d",x);
	else printf("No Answer\n0");
	return 0;
}

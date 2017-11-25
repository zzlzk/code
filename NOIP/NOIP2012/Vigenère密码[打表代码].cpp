#include<cstdio>
using namespace std;
char a[100][100];
int main() {
	freopen("ovo.txt","w",stdout);
	for(int i='A',x=1;i<='Z';i++,x++) {
		for(int j=0,y=1;j<26;j++,y++)
			a[x][y]=(char)i+j;
	}
	printf("const char a[30][30]={\n{");
	for(int i=1;i<26;i++)
			printf("'%c',",a[1][i]);
	printf("'%c'},\n",a[1][26]);
	for(int i=2;i<=26;i++) {
		printf("{");
		int j,k;
		for(j=1;a[i][j]!='Z';j++)
			printf("'%c',",a[i][j]);
		printf("'%c',",a[i][j]);
		for(k=1;k<26-j;k++)
			printf("'%c',",a[1][k]);
		printf("'%c'}",a[1][26-j]);
		if(i!=26) printf(",");
		printf("\n");
	}
	printf("};\n");
	return 0;
} 

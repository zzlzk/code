#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Heap {
	static const int maxn=10010;
	int a[maxn],size;
	void clear() {
		memset(a,0,sizeof(a));
		size=0;
		return;
	}
	Heap() {
		this->clear();
	}
	void push(int x) {
		a[++size]=x;
		int son=size,dad;
		while(son!=1) {
			dad=son>>1;
			if(a[dad]>a[son])
				swap(a[dad],a[son]);
			son=dad;
		}
		return;
	}
	int pop() {
		int ret=a[1],dad=1,son;
		a[1]=a[size--];
		while(dad<<1<=size) {
			son=dad<<1;
			if(son<size&&a[son]>a[son+1]) son++;
			if(a[dad]>a[son])
				swap(a[dad],a[son]);
			dad=son;
		}
		return ret;
	}
	int get() {
		return pop()+pop();
	}
}heap;
int main() {
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		int weight;
		scanf("%d",&weight);
		heap.push(weight);
	}
	for(int i=1;i<n;i++) {
		int sum=heap.get();
		ans+=sum;
		heap.push(sum);
	}
	printf("%d",ans);
	return 0;
}

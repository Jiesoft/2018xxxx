#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cctype>
#define INF 2000000000
using namespace std;
typedef long long ll;
int read(){
	int f=1,x=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return f*x; 
}
//����2�������Ҫ����Ӱ��
//1.����  2.���� 
//�����Լ�֦��ͬ��ɫ<=2���˳�
//����һ��������к�һ���¼�����
//�¼����м���Ƿ��п��������ķ��飬�еĻ��Ͱ�������һ�����һ������������ 
//�ڵ�����������Ϸ��Ƿ��з��飬�еĻ����Ϸ��ķ����½���ȫ�������¼����� 
//������Ҫ������С�
int pz[10][5][7];
int n,ans[10][3],movement[10][3],cnt[11],flag=0;
int dque[10005][2],dr,df;//������� 
int eque[10005][2],er,ef;//�¼����� 
int visx[10],visy[10],vis[5][7];
void solve_clear(int cur){
	int dx,dy,col,len;
	for(int i=0;i<5;i++)visx[i]=0;
	for(int i=0;i<7;i++)visy[i]=0;
	memset(vis,0,sizeof(vis));
	while(er>ef){
		dx=eque[ef][0],dy=eque[ef++][1];
		if(!visx[dx]){//ͬһ��x 
			visx[dx]=1;
			col=pz[cur][dx][0],len=1;
			for(int i=1;i<7;i++){
				if(pz[cur][dx][i]==col)
					len++;
				else{
					if(len>=3&&col){
						for(int j=i-1;i-j<=len;j--)vis[dx][j]=1;
					}
					col=pz[cur][dx][i],len=1;
				}
			}
			if(len>=3&&col){
				for(int j=6;7-j<=len;j--)vis[dx][j]=1;
			}
		}
		if(!visy[dy]){
			visy[dy]=1;
			col=pz[cur][0][dy],len=1;
			for(int i=1;i<5;i++){
				if(pz[cur][i][dy]==col)
					len++;
				else{
					if(len>=3&&col){
						for(int j=i-1;i-j<=len;j--)vis[j][dy]=1;
					}
					col=pz[cur][i][dy],len=1;
				}
			}
			if(len>=3&&col){
				for(int j=4;5-j<=len;j--)vis[j][dy]=1;
			}
		}
	}
	for(int i=0;i<5;i++)
		for(int j=0;j<7;j++)
			if(vis[i][j]){
				pz[cur][i][j]=0;
				if(j!=6)
					dque[dr][0]=i,dque[dr++][1]=j+1;
			}	
}
void solve_drop(int cur){
	int dx,dy,des;
	while(dr>df){
		dx=dque[df][0],dy=dque[df++][1];
		for(des=dy-1;des>=0&&!pz[cur][dx][des];des--);
		des++;
		for(int i=dy;i<7;i++)
			if(pz[cur][dx][i])
				pz[cur][dx][des++]=pz[cur][dx][i],
				eque[er][0]=dx,eque[er++][1]=des-1;
		for(int i=des;i<7;i++)
			pz[cur][dx][i]=0;
	}
}
void dfs(int cur){
	if(flag)return ;
	if(cur==n){
		for(int i=0;i<5;i++)
			if(pz[cur][i][0])return ;
		memcpy(ans,movement,sizeof(ans));
		flag=1;
		return ;
	}
	for(int i=1;i<=10;i++)cnt[i]=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<7;j++)
			cnt[pz[cur][i][j]]++;
	for(int i=1;i<=10;i++)
		if(cnt[i]&&cnt[i]<3)return ;
	for(int i=0;i<5;i++){
		for(int j=0;j<7;j++){
			if(!pz[cur][i][j])continue;
			if(i!=4&&pz[cur][i+1][j]!=pz[cur][i][j]){
				//�����ƶ�
				memcpy(pz[cur+1],pz[cur],sizeof(pz[0]));
				swap(pz[cur+1][i+1][j],pz[cur+1][i][j]);
				dr=df=0,ef=er=0;
				dque[dr][0]=i,dque[dr++][1]=j,
				dque[dr][0]=i+1,dque[dr++][1]=j;
				while(dr>df)
					solve_drop(cur+1),solve_clear(cur+1);
				movement[cur][0]=i,movement[cur][1]=j,movement[cur][2]=1;
				dfs(cur+1);
			}
			if(i&&!pz[cur][i-1][j]&&pz[cur][i-1][j]!=pz[cur][i][j]){//����� 
				memcpy(pz[cur+1],pz[cur],sizeof(pz[0]));
				swap(pz[cur+1][i-1][j],pz[cur+1][i][j]);
				dr=df=0,ef=er=0;
				dque[dr][0]=i,dque[dr++][1]=j,
				dque[dr][0]=i-1,dque[dr++][1]=j;
				while(dr>df){
					solve_drop(cur+1),solve_clear(cur+1);
				}
				movement[cur][0]=i,movement[cur][1]=j,movement[cur][2]=-1;
				dfs(cur+1);
			}
		}
	}
}
void init(){
	n=read();
	int t;
	for(int i=0;i<5;i++)
		for(int j=0;j<8;j++){
			t=read();
			if(!t)break;
			pz[0][i][j]=t;
		}
}
void solve(){
	dfs(0);
	if(!flag)printf("-1\n");
	else {
		for(int i=0;i<n;i++)
			printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
	}
}
int main(){
	freopen("a.in","r",stdin);
	init();
	solve();
	return 0;
}

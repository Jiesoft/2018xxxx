#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
int n,to[30],plus[30]={0},com=0,used[30]={0},ans[30];
char a[30],b[30],c[30];//a �� b �� c ��
bool build(int d){
    if(com)return true;
    if(!d){if(plus[d])return false;
    com=1;memcpy(ans,to,sizeof(to));return true;}
    int _a,_b,_c,i,j,k;
    for(_a=1;_a<d;_a++){
        i=to[a[_a]-'A'],j=to[b[_a]-'A'],k=to[c[_a]-'A'];
        if(i>=0&&j>=0&&k>=0&&(i+j)%n!=k&&(i+j+1)%n!=k)return false;
    }
    _a=a[d]-'A',_b=b[d]-'A',_c=c[d]-'A';
    i=to[_a],j=to[_b],k=to[_c];
    if(i<0&&j>=0)swap(i,j),swap(a[d],b[d]),swap(_a,_b);
    //k jinwei
    //used to plus
    if(i>=0){
        if(j>=0){
            if(k>=0){
                if((i+j+plus[d])%n==k){
                    if(i+j+plus[d]>=n)plus[d-1]++;
                    build(d-1);
                    if(plus[d-1])plus[d-1]--;
                }else return false;
            }else{
                k=(i+j+plus[d])%n;
                if(used[k])return false;
                if(i+j+plus[d]>=n)plus[d-1]++;
                used[k]=1,to[_c]=k;
                build(d-1);
                to[_c]=-1,used[k]=0;
                if(plus[d-1])plus[d-1]--;
            }
        }else{
            if(k>=0){
                j=k-plus[d]-i;
                if(j<0)j+=n;
                if(used[j])return false;
                if(i+j+plus[d]>=n)plus[d-1]++;
                used[j]=1,to[_b]=j;
                build(d-1);
                to[_b]=-1,used[j]=0;
                if(plus[d-1])plus[d-1]--;
            }else{
                for(j=0;j<n;j++)
                    if(!used[j]){
                        k=(i+j+plus[d])%n;
                        if(!used[k]&&((_c==_b&&k==j)||(_c!=_b&&k!=j))){
                            if(i+j+plus[d]>=n)plus[d-1]++;
                            used[j]=used[k]=1,to[_c]=k,to[_b]=j;
                            build(d-1);
                            used[k]=used[j]=0,to[_c]=to[_b]=-1;
                            if(plus[d-1])plus[d-1]--;
                        }
                    }
            }
        }
    }else if(k>=0){
        for(i=0;i<n;i++)
            if(!used[i]){
                j=(k-plus[d]-i);
                if(j<0)j+=n;
                if(!used[j]&&((_a==_b&&i==j)||(_a!=_b&&i!=j))){
                    if(i+j+plus[d]>=n)plus[d-1]++;
                    used[i]=used[j]=1,to[_a]=i,to[_b]=j;
                    build(d-1);
                    used[i]=used[j]=0,to[_a]=to[_b]=-1;
                    if(plus[d-1])plus[d-1]--;
                }
            }
    }else{
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                if((!used[i])&&(!used[j])&&((_a==_b&&i==j)||(_a!=_b&&i!=j))){
                    k=(i+j+plus[d])%n;
                    if(!used[k]&&((_c==_b&&k==j)||(_c!=_b&&k!=j))&&((_c==_a&&k==i)||(_c!=_a&&k!=i))){
                        if(i+j+plus[d]>=n)plus[d-1]++;
                        used[i]=used[j]=used[k]=1;
                        to[_a]=i,to[_b]=j,to[_c]=k;

                        build(d-1);
                        used[i]=used[j]=used[k]=0;
                        to[_a]=to[_b]=to[_c]=-1;
                        if(plus[d-1])plus[d-1]--;
                    }
                }
            }
    }
}
int main(){
    scanf("%d%s%s%s",&n,&a[1],&b[1],&c[1]);
    memset(to,-1,sizeof(to));
    build(n);
    for(int i=0;i<n;i++)
        printf("%d ",ans[i]);
    return 0;
}
/*
���ѣ�DFS��
    ���ȶ�����ôһ���ӷ���ʽ������Ҫ���ǽ�λ��
    �������λ���ý�λ�����Դ����λ��ʼ��

    �赽��dλʱ�������ĸΪa���м��Ϊb�������Ϊc��
    ��f��n����ʾn����������֣���ʼΪ-1����
    plus[d]��ʾdλ��Ҫ��Ҫ��λ��
    ��used��ʾһ�������Ƿ�ʹ�ù���
    �����й�ʽ(f(a)+f(b)+plus[d]) %n��nΪ��������=f(c)��
    Ȼ��������ۣ�

        1.f(a)=-1,f(b)=-1,f(c)=-1.
            ö��f(a)��f(b)�����������f(c)��
            ö��ʱҪע��f(a)��f(b)��f(c)�Ƿ��ù���
        2.f(a)>=0,f(b)>=0,f(c)>=0.
            �ж�(f(a)+f(b)+plus[d])%n�Ƿ�Ϊf(c)�����ǵĻ����ݡ�
            �ж������ȷ���Ƿ��λ��
        3.f(a)>=0,f(b)>=0,f(c)=-1
            ���f(c)��֮��ͬ1.
        4.f(a)>=0,f(b)=-1,f(c)>=0
            ���f(b)��С��f(b)����С���㣬Ҫ��n��
            ֮���1��ࡣ
        5.f(a)>=0,f(b)=-1,f(c)=-1
            ö��f(b)��Ȼ��ͬ�ϡ�
        6.f(a)=-1,f(b)>=0,f(c)>=0
            ͬ4.
        7.ֻ��f(c)>=0
            ö��f(a)��Ȼ��ͬ�ϡ�

    ȷ�����˵�dλ����ô��d-1λ�Ľ�λҲȷ���ˣ�ֱ�ӵݹ���ȥ��
    d=0ʱ�ж�f(a)+f(b)+plus[d]�Ƿ���ڵ���n����������ݡ�
        ��Ϊ���λ�������ٽ�λ��

    ����ʱ������ˣ���ô�п��ܵ�������ôһ���ӣ�
        ��i=jʱ,f(i)������f(j)��ȣ���֮���ܡ�
    ���������д���ˣ�����90.

    �����Լ�֦�����ѵ���dλʱ������1��d-1λ��
    ���ڵ�i��1<=i<d��λʱ�������¾���֪��i��������ּ��м������
    �����Ƿ������λ�����������������
        ����(f(a_i)+f(b_i))%n != f(c_i) && (f(a_i)+f(b_i)+1)%n != f(c_i) ��
    ��ôֱ�ӻ��ݡ�
    �����͹��ˡ�
    ϸ�ڸ�����
*/

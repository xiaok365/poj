#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int N=10;
int n,dp[N][N][N][N][2*N],a[N][N],x,sumall,sum[N][N];
inline int s(int x1,int y1,int x2,int y2){ //预处理
    int now=sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
    return now;
}
int main(){
    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    while(~scanf("%d",&n)){
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++)
                scanf("%d",&a[i][j]),sumall+=a[i][j];
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++)
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        for(int i=1;i<=8;i++)
            for(int j=1;j<=8;j++)
                for(int x=i;x<=8;x++)
                    for(int y=j;y<=8;y++)
                        dp[i][j][x][y][0]+=s(i,j,x,y),
                                dp[i][j][x][y][0]*=dp[i][j][x][y][0];
        for(int k=1;k<n;k++)
            for(int i=1;i<=8;i++)
                for(int j=1;j<=8;j++)
                    for(int xx=i;xx<=8;xx++)
                        for(int yy=j;yy<=8;yy++){
                            dp[i][j][xx][yy][k]=1e9;
                            for(int aa=i;aa<xx;aa++){
                                dp[i][j][xx][yy][k]=min(dp[i][j][xx][yy][k],
                                                        dp[i][j][aa][yy][k-1]+dp[aa+1][j][xx][yy][0]);
                                dp[i][j][xx][yy][k]=min(dp[i][j][xx][yy][k],
                                                        dp[aa+1][j][xx][yy][k-1]+dp[i][j][aa][yy][0]);
                            }
                            for(int aa=j;aa<yy;aa++){
                                dp[i][j][xx][yy][k]=min(dp[i][j][xx][yy][k],
                                                        dp[i][aa+1][xx][yy][k-1]+dp[i][j][xx][aa][0]);
                                dp[i][j][xx][yy][k]=min(dp[i][j][xx][yy][k],
                                                        dp[i][j][xx][aa][k-1]+dp[i][aa+1][xx][yy][0]);
                            }

                            cout<<dp[i][j][xx][yy][k]<<endl;

                        }
        double ans=dp[1][1][8][8][n-1]*1.0/n-(sumall*1.0/n)*(sumall*1.0/n);
        ans=sqrt(ans);
        printf("%.3f\n",ans);
    }
}
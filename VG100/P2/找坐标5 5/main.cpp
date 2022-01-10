#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*1代表前进FD
2代表左转ZT
3代表右转RT
0表示有墙壁 */ 
volatile int O;//命令序列数组编号 
volatile int A[20];// 命令序列数组 
volatile int L[26];//模块左，前，右通断情况 ，数据为通向的模块号 
volatile int F[26];//-1代表未知，0代表墙 
volatile int R[26];
volatile int l[26];//模块左，前，右优先级，优先走大的 
volatile int f[26];
volatile int r[26];
volatile int D[26];//机器人到模块时的方向，返回时用 
volatile int i=1;//当前探索总模块数 
volatile int E=1;//当前机器人模块位置 
volatile int X[26]={0},Y[26]={0};//机器人当前位置及模块坐标 
volatile int x,y,d,x1,y1;//机器人初始位置,方向及目标位置 
FILE*fp;
FILE*fp1;
void FD(void)//往前探索一格 
{ 
	F[E]=i+1;
	E=i+1;
	A[O]=1;
	O++;
	switch (d)
	{	
		case 1:Y[0]++;break;
		case 2:X[0]++;break;
		case 3:Y[0]--;break;
		case 4:X[0]--;break;
	}
	X[E]=X[0];Y[E]=Y[0];	
	D[E]=d;
	i=E;
}
void LT(void)//往左探索一格 
{ 
	L[E]=i+1;
	E=i+1;
	A[O]=2;
	O++; 
	d--;
	A[O]=1;
	O++;
	if(d>4)d=d-4;
	if(d<1)d=d+4;//左转前进一个模块
	switch (d)
	{	
		case 1:Y[0]++;break;
		case 2:X[0]++;break;
		case 3:Y[0]--;break;
		case 4:X[0]--;break;
	}
	X[E]=X[0];Y[E]=Y[0];
	D[E]=d;
	i=E;
}
void RT(void)//往右探索一格 
{
	R[E]=i+1;
	E=i+1;
	A[O]=3;
	O++; 
	d++;	
	A[O]=1;
	O++;
	if(d>4)d=d-4;
	if(d<1)d=d+4;//右转前进一个模块
	switch (d)
	{	
		case 1:Y[0]++;break;
		case 2:X[0]++;break;
		case 3:Y[0]--;break;
		case 4:X[0]--;break;
	}
	X[E]=X[0];Y[E]=Y[0];
	D[E]=d;
	i=E;	
}
int Fin(volatile int M)//找终点 
{
	if(X[0]==x1&&Y[0]==y1) 
	{
		for(i=1;i<=25;i++)
		{
			if(L[i]==-1)L[i]=0;
			if(F[i]==-1)F[i]=0;
			if(R[i]==-1)R[i]=0;
		}
		return 1;//如果到达指定坐标，则未去过的地方全部视为有墙 
	}
	switch (d)//先判断左中右优先级
	{
		case 1:
			if(Y[0]<y1)
			{
				f[M]=3;
				if(X[0]>x1)l[M]=2;	
				else r[M]=2;	
			}
			else if(X[0]>x1)
			{
				l[M]=3;
				if(Y[0]==y1)f[M]=2;
				else r[M]=2;
			}
			else
			{
				if(Y[0]==y1)f[M]=2;
				else l[M]=2;
				r[M]=3;				
			}
			break;
		case 2:
			if(X[0]<x1)
			{
				f[M]=3;
				if(Y[0]<y1)l[M]=2;	
				else r[M]=2;	
			}
			else if(Y[0]<y1)
			{
				l[M]=3;
				if(X[0]==x1)f[M]=2;
				else r[M]=2;
			}
			else
			{
				if(X[0]==x1)f[M]=2;
				else l[M]=2;
				r[M]=3;				
			}
			break;
		case 3:
			if(Y[0]>y1)
			{
				f[M]=3;
				if(X[0]<x1)l[M]=2;	
				else r[M]=2;	
			}
			else if(X[0]<x1)
			{
				l[M]=3;
				if(Y[0]==y1)f[M]=2;
				else r[M]=2;
			}
			else
			{
				if(Y[0]==y1)f[M]=2;
				else l[M]=2;
				r[M]=3;				
			}
			break;
		case 4:	
			if(X[0]>x1)
			{
				f[M]=3;
				if(Y[0]>y1)l[M]=2;	
				else r[M]=2;	
			}
			else if(Y[0]>y1)
			{
				l[M]=3;
				if(X[0]==x1)f[M]=2;
				else r[M]=2;
			}
			else
			{
				if(X[0]==x1)f[M]=2;
				else l[M]=2;
				r[M]=3;				
			}
			break;
	} 
	volatile int X1,Y1,X2,Y2,X3,Y3,C=0,Z;
	//若返回值为1则到达终点,准备返回	
	X1=X[0];X2=X[0];X3=X[0];	
	Y1=Y[0];Y2=Y[0];Y3=Y[0];	
	switch (d)
	{
		case 1:
			X1--;
			Y2++;
			X3++;
			break;	
		case 2:
			Y1++;
			X2++;
			Y3--;
			break; 
		case 3:
			X1++;
			Y2--;
			X3--;
			break;			
		case 4:
			Y1--;
			X2--;
			Y3++;
			break; 			
	}
	if(L[M]!=0)	//先根据当前位置和方向确定周围模块坐标
	{
		for(Z=1;Z<=25;Z++)
		{
			if(X1==X[Z]&&Y1==Y[Z])
			{	
				L[M]=Z; 
				l[M]=0; 
				C++;
			}
		}
	}
	else 
	{
		l[M]=0;
		C++;	
	}
	if(F[M]!=0)
	{
		for(Z=1;Z<=25;Z++)
		{
			if(X2==X[Z]&&Y2==Y[Z])
			{
				F[M]=Z;
				f[M]=0;
				if(C==1)C++;
			}	
		}
	}
	else 
	{	
		if(C==1)C++;
		f[M]=0;
	}		
	if(R[M]!=0)
	{
		for(Z=1;Z<=25;Z++)
		{
			if(X3==X[Z]&&Y3==Y[Z])
			{
				R[M]=Z;
				r[M]=0;
				if(C==2)C++;
			}
		}
	}
	else 
	{
		if(C==2)C++; 
		r[M]=0;	
	}	
	if(X[0]==x1&&Y[0]==y1)C=3;
	if(C==3)return 1;//如果三边都有墙或都去过则说明到达终点 
	return 2;
} 
void FH(void)//从一点返回一点 
{
	volatile int FX;//返回方向 
	volatile int I,T;
	A[O]=2;
	O++;
	A[O]=2;
	O++;//掉头
	while(1)
	{
		for(I=1;I<=E;I++)
		{
			if(L[I]==E)
			{
				FX=-1;//前进一个模块右转 
				break;
			}
			if(F[I]==E)
			{
				FX=0;//前进一个模块 
				break;
			}
			if(R[I]==E)
			{
				FX=1;//前进一个模块左转 
				break;
			}
		}
		A[O]=1;
		O++;//前进一个模块 
		E=I;
		Fin(E);//分析已去过模块周围相连模块 
		if(L[E]==-1||F[E]==-1||R[E]==-1||(E==1&&i>=25))
		{
			if(FX==1)
			{
				A[O]=3;O++;//右转 
			} 
			if(FX==-1)
			{
				A[O]=2;O++;//左转 
			}
			else
			{
				A[O]=2;O++;A[O]=2;O++;//掉头 
			}
			break;//到达还有未去过的岔路的模块处结束返回 
		}
		if(FX==-1)
		{
			A[O]=3;
			O++;
			//右转 
		} 
		if(FX==1)
		{
			A[O]=2;
			O++;
			//左转 
		}
	}	 
	X[0]=X[I];Y[0]=Y[I];
	d=D[I];
} 
void work(void)
{
	for(O=1;O<=20;O++)A[O]=0;
	O=1;
	if(Fin(E)!=1)
	{
		if(L[E]==-1&&(l[E]>r[E]||R[E]!=-1)&&(l[E]>f[E]||F[E]!=-1))LT();
		else
		{
			if(R[E]==-1&&(r[E]>l[E]||L[E]!=-1)&&(r[E]>f[E]||F[E]!=-1))RT();
			else if(F[E]==-1)FD();
		}
	}
	else
	{
		FH();
		if(L[E]==-1&&(l[E]>r[E]||R[E]!=-1)&&(l[E]>f[E]||F[E]!=-1))LT();
		else
		{
			if(R[E]==-1&&(r[E]>l[E]||L[E]!=-1)&&(r[E]>f[E]||F[E]!=-1))RT();	
			else if(F[E]==-1)FD();	
		}		
	}
	for(O=1;O<=20;O++)
	{
		if(A[O]==0)break;
		fprintf(fp,"%d ",A[O]);
	} 
	fprintf(fp,"\n");//生成命令序列 
} 
int main(int argc, char** argv) 
{
	x=4;y=5;x1=5;y1=5;d=3; 
	fp1=fopen("墙壁情况.txt","r");
	fp=fopen("命令序列.txt","w");
	for(i=1;i<=25;i++)
	{
		X[i]=-5;Y[i]=-5;
		L[i]=-1;F[i]=-1;R[i]=-1;
		l[i]=1;f[i]=1;r[i]=1;
	} 
	X[0]=x;Y[0]=y;X[1]=X[0];Y[1]=Y[0];
	i=1;
	while(i<=25)
	{
		fscanf(fp1,"%d%d%d",&L[E],&F[E],&R[E]);//读取墙壁情况
		work();//产生命令序列 
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*1����ǰ��FD
2������תZT
3������תRT
0��ʾ��ǽ�� */ 
volatile int O;//�������������� 
volatile int A[20];// ������������ 
volatile int L[26];//ģ����ǰ����ͨ����� ������Ϊͨ���ģ��� 
volatile int F[26];//-1����δ֪��0����ǽ 
volatile int R[26];
volatile int l[26];//ģ����ǰ�������ȼ��������ߴ�� 
volatile int f[26];
volatile int r[26];
volatile int D[26];//�����˵�ģ��ʱ�ķ��򣬷���ʱ�� 
volatile int i=1;//��ǰ̽����ģ���� 
volatile int E=1;//��ǰ������ģ��λ�� 
volatile int X[26]={0},Y[26]={0};//�����˵�ǰλ�ü�ģ������ 
volatile int x,y,d,x1,y1;//�����˳�ʼλ��,����Ŀ��λ�� 
FILE*fp;
FILE*fp1;
void FD(void)//��ǰ̽��һ�� 
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
void LT(void)//����̽��һ�� 
{ 
	L[E]=i+1;
	E=i+1;
	A[O]=2;
	O++; 
	d--;
	A[O]=1;
	O++;
	if(d>4)d=d-4;
	if(d<1)d=d+4;//��תǰ��һ��ģ��
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
void RT(void)//����̽��һ�� 
{
	R[E]=i+1;
	E=i+1;
	A[O]=3;
	O++; 
	d++;	
	A[O]=1;
	O++;
	if(d>4)d=d-4;
	if(d<1)d=d+4;//��תǰ��һ��ģ��
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
int Fin(volatile int M)//���յ� 
{
	if(X[0]==x1&&Y[0]==y1) 
	{
		for(i=1;i<=25;i++)
		{
			if(L[i]==-1)L[i]=0;
			if(F[i]==-1)F[i]=0;
			if(R[i]==-1)R[i]=0;
		}
		return 1;//�������ָ�����꣬��δȥ���ĵط�ȫ����Ϊ��ǽ 
	}
	switch (d)//���ж����������ȼ�
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
	//������ֵΪ1�򵽴��յ�,׼������	
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
	if(L[M]!=0)	//�ȸ��ݵ�ǰλ�úͷ���ȷ����Χģ������
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
	if(C==3)return 1;//������߶���ǽ��ȥ����˵�������յ� 
	return 2;
} 
void FH(void)//��һ�㷵��һ�� 
{
	volatile int FX;//���ط��� 
	volatile int I,T;
	A[O]=2;
	O++;
	A[O]=2;
	O++;//��ͷ
	while(1)
	{
		for(I=1;I<=E;I++)
		{
			if(L[I]==E)
			{
				FX=-1;//ǰ��һ��ģ����ת 
				break;
			}
			if(F[I]==E)
			{
				FX=0;//ǰ��һ��ģ�� 
				break;
			}
			if(R[I]==E)
			{
				FX=1;//ǰ��һ��ģ����ת 
				break;
			}
		}
		A[O]=1;
		O++;//ǰ��һ��ģ�� 
		E=I;
		Fin(E);//������ȥ��ģ����Χ����ģ�� 
		if(L[E]==-1||F[E]==-1||R[E]==-1||(E==1&&i>=25))
		{
			if(FX==1)
			{
				A[O]=3;O++;//��ת 
			} 
			if(FX==-1)
			{
				A[O]=2;O++;//��ת 
			}
			else
			{
				A[O]=2;O++;A[O]=2;O++;//��ͷ 
			}
			break;//���ﻹ��δȥ���Ĳ�·��ģ�鴦�������� 
		}
		if(FX==-1)
		{
			A[O]=3;
			O++;
			//��ת 
		} 
		if(FX==1)
		{
			A[O]=2;
			O++;
			//��ת 
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
	fprintf(fp,"\n");//������������ 
} 
int main(int argc, char** argv) 
{
	x=4;y=5;x1=5;y1=5;d=3; 
	fp1=fopen("ǽ�����.txt","r");
	fp=fopen("��������.txt","w");
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
		fscanf(fp1,"%d%d%d",&L[E],&F[E],&R[E]);//��ȡǽ�����
		work();//������������ 
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}

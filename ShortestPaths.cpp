//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShortestPaths.h"
#include<algorithm>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
int n ,impossible;

int **square = new int *[n];


__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//stack用來tracing路徑
int top=-1;
int stack[10000];
void push(int element)
{
	stack[++top]=element;
}
int pop()
{   if(top==-1) return -1;
	return stack[top--];
}

//print 亂數產生的表
void PrintG(int **square,int n,int grid_size)
{
   Form1->StringGrid1-> RowCount = n+1;
   Form1->StringGrid1-> ColCount = n+1;

   Form1->StringGrid1->FixedCols =1;
   Form1->StringGrid1->FixedRows =1;
   for (int i=0; i<n+1; i++)
		Form1->StringGrid1->RowHeights[i] = grid_size;
   for (int i=0; i<n+1; i++)
		Form1->StringGrid1->ColWidths[i] = grid_size;
   for(int i=0;i<n;i++)
		Form1->StringGrid1->Cells[i+1][0]=i;
   for(int i=0;i<n;i++)
        Form1->StringGrid1->Cells[0][i+1] = i;
   for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			Form1->StringGrid1->Cells[j+1][i+1] = square[i][j];
}

void sssp(int **W, int s, int n)
{
	int *D = new int[n];       //用來存single source到其他每點的最小距離
	bool *founded = new bool[n];      //跟D一樣的array 用來存他是否已找到最小 找到:true
	Form1->StringGrid2-> RowCount = n+1;
	Form1->StringGrid2-> ColCount = n+1;
	int count=-1,x,c;
	int *A=new int[n];         //用來記predecessor



	for(int i=0; i<n; i++)
	{
		founded[i] = false;         //一開始found內先全部設為false 都還沒找到
		D[i] = impossible;
    }

    int v, minD;
    D[s] = 0; v = s;
	do
	{
		count++;              //count是用來控制print時要印在第幾行
		founded[v] = true;    //founded array 裡source那格已找到 設成true
		for(int i=0; i<n; i++)
		{
			if(W[v][i] != impossible && D[i] > D[v]+W[v][i])  //透過v走過去比較小
			{    D[i] = D[v]+W[v][i];
				 A[i]=v;
			}
        }

		minD = impossible; v = n;
		for(int i=0; i<n; i++)
		{
			if(!founded[i] && D[i]<minD)     //找現在還沒被找到且是D裡最小
			{
                v = i; minD = D[i];
            }
		}
		if(v!=n)
		{
			Form1->Memo1->Lines->Add("min = "+IntToStr(v));

			for(int i=0;i<n;i++)
			{
				Form1->StringGrid2->Cells[count+1][i+1] = D[i] ;
			}
		}

	}while(v != n);
	//print tracing
	for(int j=0;j<n;j++)
	{   String lines=s;
		int sum=0;
		c=j;
		while(c!=s)
		{
			x=A[c];         //ex:A[3]=5->找A[5]=? push進stack
			push(c);
			c=x;
		}
		while(top!=-1)
		{
			int y=pop();      //通通pop出來 因為是FILO 所以可以形成路徑

			lines=lines+"--"+"["+(D[y]-sum)+"]"+"-->"+y;

			sum+=D[y]-sum;
		}
		if(D[j]!=impossible)
			Form1->Memo1->Lines->Add("The shortest distance from "+IntToStr(s)+" to "+IntToStr(j)+" is "+IntToStr(D[j])+" with path "+lines);
		else
			Form1->Memo1->Lines->Add("It's impossible to have a path from "+IntToStr(s)+" to "+IntToStr(j));

	}
    Form1->Memo1->Lines->Add("- - - - - - - - - - - - - - - - - - - - - - - - - - - -");
	for(int i=0;i<count;i++)
		Form1->StringGrid2->Cells[i+1][0]=i;
	Form1->StringGrid2->Cells[count+1][0]="from";
    for(int i=0;i<n;i++)
        Form1->StringGrid2->Cells[0][i+1] = i;
	Form1->StringGrid2->Cells[count+1][s+1] = 0 ;
	for(int i=0;i<n;i++)
	{   if(i!=s)
			Form1->StringGrid2->Cells[count+1][i+1] = A[i] ;      //最後一行印該點是從哪點來的所以最小
	}


}
void apsp(int **W, int n)
{
	int **D = new int*[n];
	int **A=new int*[n];      //用來存predecessor
	for(int i=0;i<n;i++)
		A[i]=new int [n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
            A[i][j]=0;
	Form1->StringGrid3-> RowCount = n+1;
	Form1->StringGrid3-> ColCount = n+1;
	Form1->StringGrid4-> RowCount = n+1;
	Form1->StringGrid4-> ColCount = n+1;
	for(int i=0; i<n; i++)
	{
		D[i] = new int[n];
		for(int j=0; j<n; j++)
		{
			D[i][j] = W[i][j];          //先存原始兩點間距離
		}
	}

	for(int k=0; k<n; k++)       //dynamic programming
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(D[i][k]!=impossible && D[k][j]!=impossible&& D[i][j]> D[i][k]+D[k][j]) //若透過k去 距離會比較小
				{
					D[i][j]=D[i][k]+D[k][j] ;
					A[i][j]=k;
				}
				if(i==j)
				{
					D[i][j]=0;
					A[i][j]=i;
				}
			}
		}
	}
    for(int i=0;i<n;i++)
		Form1->StringGrid3->Cells[i+1][0]=i;
	for(int i=0;i<n;i++)
		Form1->StringGrid3->Cells[0][i+1] = i;
	for(int i=0;i<n;i++)
		Form1->StringGrid4->Cells[i+1][0]=i;
	for(int i=0;i<n;i++)
		Form1->StringGrid4->Cells[0][i+1] = i;
	for(int i=0;i<n;i++)
	{   for(int j=0;j<n;j++)
			Form1->StringGrid3->Cells[j+1][i+1] = D[i][j] ;
	}
	for(int i=0;i<n;i++)
	{   for(int j=0;j<n;j++)
			Form1->StringGrid4->Cells[j+1][i+1] = A[i][j] ;
	}

}
void TransClos(int **W,int n,int impossible)
{
    int **D = new int*[n];
	Form1->StringGrid5-> RowCount = n+1;
	Form1->StringGrid5-> ColCount = n+1;
	for(int i=0; i<n; i++)
	{
		D[i] = new int[n];
		for(int j=0; j<n; j++)
		{
			D[i][j] = W[i][j];
			if(D[i][j]==impossible)  //無路可走
				D[i][j]=0;
			else
				D[i][j]=1;         //有路可走
		}
	}

	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(D[i][k]!=0 && D[k][j]!=0)
				{
					D[i][j]=1;        //用dynamic programming後找到有路走
				}

			}
		}
	}
    for(int i=0;i<n;i++)
		Form1->StringGrid5->Cells[i+1][0]=i;
	for(int i=0;i<n;i++)
		Form1->StringGrid5->Cells[0][i+1] = i;
	for(int i=0;i<n;i++)
	{   for(int j=0;j<n;j++)
			Form1->StringGrid5->Cells[j+1][i+1] = D[i][j] ;
	}
}

//---------------------------------------------------------------------------
//Generate G
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	n = StrToInt(Edit1->Text);       //亂數產生n個點
	int range = StrToInt(Edit2->Text);    //產生亂數的範圍
	int boundary = StrToInt(Edit3->Text);
	impossible = StrToInt(Edit4->Text);
	int grid_size = StrToInt(Edit6->Text);  //控制stringrid格子大小
	for (int i=0; i<n; i++)
		square[i] = new int [n];

	for(int i=0;i<n;i++)
	{  for(int j=0;j<n;j++)
	   {
		 square[i][j]=rand()%range+1;      //亂數產生每兩點間的直接距離
		 if(i==j)
		 {
			 square[i][j]=impossible;       //0->0 1->1 2->2...設為不可能
		 }
		 if(square[i][j]>boundary)          //若亂數產生的距離大於使用者輸入的上界 也設為不可能
			square[i][j]=impossible;
	   }

	}
	if(CheckBox2->Checked)
		PrintG(square,n,grid_size);


}
//---------------------------------------------------------------------------

//single source all destination
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int source = StrToInt(Edit5->Text);
	sssp(square,source,n);
}
//all pairs
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	 apsp(square,n);
}
//---------------------------------------------------------------------------

//transitive closure
void __fastcall TForm1::Button4Click(TObject *Sender)
{
      TransClos(square,n,impossible);
}
//---------------------------------------------------------------------------


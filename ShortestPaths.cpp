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
//stack�Ψ�tracing���|
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

//print �üƲ��ͪ���
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
	int *D = new int[n];       //�ΨӦssingle source���L�C�I���̤p�Z��
	bool *founded = new bool[n];      //��D�@�˪�array �ΨӦs�L�O�_�w���̤p ���:true
	Form1->StringGrid2-> RowCount = n+1;
	Form1->StringGrid2-> ColCount = n+1;
	int count=-1,x,c;
	int *A=new int[n];         //�ΨӰOpredecessor



	for(int i=0; i<n; i++)
	{
		founded[i] = false;         //�@�}�lfound���������]��false ���٨S���
		D[i] = impossible;
    }

    int v, minD;
    D[s] = 0; v = s;
	do
	{
		count++;              //count�O�Ψӱ���print�ɭn�L�b�ĴX��
		founded[v] = true;    //founded array ��source����w��� �]��true
		for(int i=0; i<n; i++)
		{
			if(W[v][i] != impossible && D[i] > D[v]+W[v][i])  //�z�Lv���L�h����p
			{    D[i] = D[v]+W[v][i];
				 A[i]=v;
			}
        }

		minD = impossible; v = n;
		for(int i=0; i<n; i++)
		{
			if(!founded[i] && D[i]<minD)     //��{�b�٨S�Q���B�OD�̳̤p
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
			x=A[c];         //ex:A[3]=5->��A[5]=? push�istack
			push(c);
			c=x;
		}
		while(top!=-1)
		{
			int y=pop();      //�q�qpop�X�� �]���OFILO �ҥH�i�H�Φ����|

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
			Form1->StringGrid2->Cells[count+1][i+1] = A[i] ;      //�̫�@��L���I�O�q���I�Ӫ��ҥH�̤p
	}


}
void apsp(int **W, int n)
{
	int **D = new int*[n];
	int **A=new int*[n];      //�ΨӦspredecessor
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
			D[i][j] = W[i][j];          //���s��l���I���Z��
		}
	}

	for(int k=0; k<n; k++)       //dynamic programming
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(D[i][k]!=impossible && D[k][j]!=impossible&& D[i][j]> D[i][k]+D[k][j]) //�Y�z�Lk�h �Z���|����p
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
			if(D[i][j]==impossible)  //�L���i��
				D[i][j]=0;
			else
				D[i][j]=1;         //�����i��
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
					D[i][j]=1;        //��dynamic programming���즳����
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
	n = StrToInt(Edit1->Text);       //�üƲ���n���I
	int range = StrToInt(Edit2->Text);    //���Ͷüƪ��d��
	int boundary = StrToInt(Edit3->Text);
	impossible = StrToInt(Edit4->Text);
	int grid_size = StrToInt(Edit6->Text);  //����stringrid��l�j�p
	for (int i=0; i<n; i++)
		square[i] = new int [n];

	for(int i=0;i<n;i++)
	{  for(int j=0;j<n;j++)
	   {
		 square[i][j]=rand()%range+1;      //�üƲ��ͨC���I���������Z��
		 if(i==j)
		 {
			 square[i][j]=impossible;       //0->0 1->1 2->2...�]�����i��
		 }
		 if(square[i][j]>boundary)          //�Y�üƲ��ͪ��Z���j��ϥΪ̿�J���W�� �]�]�����i��
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


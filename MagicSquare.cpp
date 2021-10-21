//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MagicSquare.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#include <cstdlib>

#define SWAP(x,y,t) (t = x, x = y, y = t)
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    DWord fstyle;
	fstyle = GetWindowLong(Edit1->Handle, GWL_STYLE); // 宣告Edit1輸入僅為數字
	SetWindowLong(Edit1->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT);
}
//---------------------------------------------------------------------------
void MagicSquareOdd(int **square, int n)
{
	int i, j, k, l, data;
	for (i=0; i<n; i++)
	{	for (j=0; j<n; j++)
		{
			square[i][j]=0;
		}                 //每個位置都先填0
	}
	if (Form1->RadioButton1->Checked)
	{   i = 0;                   //up checked 1擺上面
		j = n/2;

	}
	else if(Form1->RadioButton2->Checked)
	{   i = n-1;                 //down checked 1擺下面
		j = n/2;
	}
	else if(Form1->RadioButton3->Checked)
	{   i = n/2;
		j=0;                      //left checked 1擺左邊

	}
	else if(Form1->RadioButton4->Checked)
	{   i=n/2;
		j=n-1;                    //right checked 1擺右邊

    }
	square[i][j] = 1;            //擺1的位置
	data = 2;                    //填2
	while (data <= n*n)          //有n*n個數字要填
	{   if (Form1->RadioButton1->Checked&&Form1->RadioButton5->Checked)         //1擺上面 產生方向:左上
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				i = (i+1) % n;
			else
			{i = k; j = l; }
		}
        else if (Form1->RadioButton1->Checked&&Form1->RadioButton6->Checked)    //1擺上面 產生方向:右上
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				i = (i+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton2->Checked&&Form1->RadioButton7->Checked)    //1擺下面 產生方向:左下
		{   k = (i+1==n) ? 0 : i+1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				i = (i-1 < 0) ? n-1 : i-1;
			else
			 { i = k; j = l; }
		}

		else if (Form1->RadioButton2->Checked&&Form1->RadioButton8->Checked)    //1擺下面 產生方向:右下
		{   k = (i+1==n) ? 0 : i+1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				i = (i-1 < 0) ? n-1 : i-1;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton3->Checked&&Form1->RadioButton5->Checked)    //1擺左邊 產生方向:左上
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				j = (j+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton3->Checked&&Form1->RadioButton7->Checked)    //1擺左邊 產生方向:左下
		{   k = (i+1==n) ? 0 : i+1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				j = (j+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton4->Checked&&Form1->RadioButton6->Checked)    //1擺右邊 產生方向:右上
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				j = (j-1 < 0) ? n-1 : j-1;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton4->Checked&&Form1->RadioButton8->Checked)    //1擺右邊 產生方向:右下
		{   k = (i+1==n) ? 0 : i+1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				j = (j-1 < 0) ? n-1 : j-1;
			else
			 { i = k; j = l; }
		}

		square[i][j]=data++;   // 填1 ->2 ->3 ...
	}
}





void MagicSquare4n(int **square, int n)
{   int miniSqrNum = n/4; //size of boxes
	int count = 1; 	      //counter 1 to n*n
	int inv_count = n*n;     //counter n*n to 1
	for(int i=0;i<n;i++){

		for(int j=0;j<n;j++)
		{

		   if(j>=miniSqrNum && j<n-miniSqrNum)
		   {
			if(i>=miniSqrNum && i<n-miniSqrNum)
				square[i][j] = count;    //central box
			else
				square[i][j] = inv_count; // up & down boxes

		   }
		   else if(i<miniSqrNum || i>=n-miniSqrNum)
		   {
			 square[i][j]=count;	         // 4 corners
		   }
		   else
		      square[i][j] = inv_count;  	// left & right boxes


		   count++;
		   inv_count--;
		}

	}
}

void MagicSquareEven(int **square, int n)
{
	int row = 0;
	int col= n / 2;  //size of ABCD boxes
	int count;

	int a = n / 2,b = a - 1;
	int i, j, k;

	//creating 4 magic boxes
	for(count = 1; count <= n*n; count++)
	{
		square[row][col] = count;              //A box
		square[row+n][col+n] = count + n*n;    //B box
		square[row][col+n] = count + 2*n*n;    //C box
		square[row+n][col] = count + 3*n*n;    //D box
		if(count % n == 0)
			row++;

		else
		{
			if(row==0)
				row=n-1;
			else
				row=row-1;

			if(col==n-1)
				col=0;
			else
				col=col+1;

		}
	}


    //swap
	for(i = 0; i < n; i++)
	{
		if(i != a)
		{
			for(j = 0; j < a; j++)
				SWAP(square[i][j], square[n+i][j], k);

			for(j = 0; j < b; j++)
				SWAP(square[i][2*n-1-j], square[n+i][2*n-1-j], k);
		}

		else
		{
			for(j = 1; j <= a; j++)
				SWAP(square[a][j], square[n+a][j], k);
			for(j = 0; j < b; j++)
				SWAP(square[a][2*n-1-j], square[n+a][2*n-1-j], k);
		}
	}
}


void PrintSquare(int **square, int n)
{
	int len=IntToStr(n*n).Length();
	int block = len+5;       //固定每格的寬度
	int blank_len, sum_len,i, j, k, sum, tmp;
	String row1,str_sum;
	if(Form1->CheckBox1->Checked)
	{
		Form1 ->Memo2 ->Lines ->Add("- - - - - - - Magic Square "+IntToStr(n)+" x "+IntToStr(n)+" - - - - - - -"); //印出方陣size
	}
	else
		Form1 ->Memo1 ->Lines ->Add("- - - - - - - Magic Square "+IntToStr(n)+" x "+IntToStr(n)+" - - - - - - -"); //印出方陣size


	if(Form1->CheckBox1->Checked )
	{
		Form1->StringGrid1-> RowCount = n+1;
		Form1->StringGrid1-> ColCount = n+1;   //StringGrid產生(n+1)x(n+1)個格子 可以寫出check的結果
	}
	else
	{
		Form1->StringGrid1-> RowCount = n;
		Form1->StringGrid1-> ColCount = n;     //StringGrid產生n*n個格子
	}
	//排row
	for (i = 0; i < n; i++)
	{   row1 = " ";          //用來排版
		int sum = 0;
		Form1->StringGrid1->ColWidths[i]= (block+1) * 5;  //格子寬度

		for (j = 0; j < n; j++)
		{
			str_sum = IntToStr(square[i][j]);
			blank_len = block - str_sum.Length();           //固定方陣寬度
			for (k = 0; k < blank_len; k++)
			   row1 += " ";

			row1 += square[i][j];
			Form1->StringGrid1->Cells[j][i] = square[i][j];
			sum += square[i][j];                           //每列總和
		}
        //自動驗算每列總和
		if(Form1 ->CheckBox1 -> Checked)
		{
			str_sum = IntToStr(sum);
			blank_len = block - str_sum.Length();
			//固定方陣寬度
			for (k = 0; k < blank_len; k++)
				row1 += " ";

			Form1 ->Memo2 ->Lines ->Add(row1+"—"+IntToStr(sum));
			Form1->StringGrid1->ColWidths[i]= (block+5) * 5;
			Form1->StringGrid1->Cells[n][i] = "—"+IntToStr(sum);
		}
		else
			Form1 ->Memo1 ->Lines ->Add(row1);                   //print row

	}

    //最後一列 填行 對角總和
	//自動驗算行&對角線總和
	if(Form1 ->CheckBox1 -> Checked)
	{
		row1 = " ";
        //計算行總和
		for (j = 0; j < n; j++)
		{
			sum = 0;
			for (i = 0; i < n; i++)
			   sum += square[i][j];

			str_sum = IntToStr(sum);
			blank_len = block - str_sum.Length();              //固定方陣寬度
			for (k = 1; k < blank_len; k++)
				row1 += " ";
			row1 = row1+"|"+sum;
			Form1->StringGrid1->Cells[j][n] = "|"+IntToStr(sum);
		}

		//計算左下到右上總和
		sum = 0;
		for (i = 0; i < n; i++)
		{
			j = n - 1 -i;
			sum += square[i][j];
		}
		str_sum = IntToStr(sum);
		blank_len = block - str_sum.Length();  //固定方陣寬度
		for (k = -1; k < blank_len; k++)
			row1 += " ";
		row1 = row1+"/" + sum;
		tmp=sum;

		//計算左上到右下總和
        sum = 0;
		for (i = 0; i < n; i++)
		{
			j = i;
			sum += square[i][j];
		}
		str_sum = IntToStr(sum);
		blank_len = block - str_sum.Length();             //固定方陣寬度
		for (k = -1; k < blank_len; k++)
			row1 += " ";
		row1 = row1+"\\" + sum;


		Form1->StringGrid1->ColWidths[n]= (block+5) * 10;
		Form1->StringGrid1->Cells[n][n] = "\\"+IntToStr(tmp)+" /"+IntToStr(sum);
		Form1 ->Memo2 ->Lines ->Add(row1);           //print行&斜線總和
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{   int n = StrToInt(Edit1->Text);         //nxn方陣
	int **square = new int *[n];           //依照n大小 動態產生n+1列


	for (int i=0; i<n; i++)
		square[i] = new int [n];           //每一列再產生n+1行

	if(n == 0)          //方陣大小不可=0
	{   Form1 ->Memo1 ->Lines ->Add("* * * * * Square size should NOT be 0. * * * * *");
		Form1 ->Memo2 ->Lines ->Add("* * * * * Square size should NOT be 0. * * * * *");
		Form1->StringGrid1-> RowCount = 0;
		Form1->StringGrid1-> ColCount = 0;
		Form1->StringGrid1->ColWidths[0]= 600;
		Form1->StringGrid1->Cells[0][0] = "Square size should NOT be 0.";
	}
	else if(n == 2)    //方陣大小不可=2
	{   Form1 ->Memo1 ->Lines ->Add("* * * * * Square size should NOT be 2. * * * * *");
		Form1 ->Memo2 ->Lines ->Add("* * * * * Square size should NOT be 2. * * * * *");
        Form1->StringGrid1-> RowCount = 0;
		Form1->StringGrid1-> ColCount = 0;
		Form1->StringGrid1->ColWidths[0]= 600;
		Form1->StringGrid1->Cells[0][0] = "Square size should NOT be 2.";
	}
	else if(n%4 == 0)  //n=4的倍數
	{   MagicSquare4n(square, n);
		PrintSquare(square, n);
	}
	else if(n%2 == 0) //n=2的倍數(偶數)
	{   MagicSquareEven(square, n/2);
		PrintSquare(square, n);
	}
	else              //所有奇數
	{   //選擇的組合可以產生magic square
		if((Form1->RadioButton1->Checked&&Form1->RadioButton5->Checked)||(Form1->RadioButton1->Checked&&Form1->RadioButton6->Checked)||(Form1->RadioButton2->Checked&&Form1->RadioButton7->Checked)||(Form1->RadioButton2->Checked&&Form1->RadioButton8->Checked)||(Form1->RadioButton3->Checked&&Form1->RadioButton5->Checked)||(Form1->RadioButton3->Checked&&Form1->RadioButton7->Checked)||(Form1->RadioButton4->Checked&&Form1->RadioButton6->Checked)||(Form1->RadioButton4->Checked&&Form1->RadioButton8->Checked))
		{	MagicSquareOdd(square, n);
			PrintSquare(square, n);
		}
		//選擇的組合無法產生magic square
		else
		{
			Form1 ->Memo1 ->Lines ->Add("* * * * * This combination can NOT form a magic square. * * * * *");
            Form1 ->Memo2 ->Lines ->Add("* * * * * This combination can NOT form a magic square. * * * * *");
			Form1->StringGrid1-> RowCount = 0;
			Form1->StringGrid1-> ColCount = 0;
			Form1->StringGrid1->ColWidths[0]= 600;
			Form1->StringGrid1->Cells[0][0] = "This combination can NOT form a magic square.";
		}
	}



	//記憶體還給電腦
	for (int i=0; i<n; i++)
		delete[]square[i];

	delete[] square;
}
//---------------------------------------------------------------------------


//畫面clear
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form1->Memo1->Lines->Clear();
    Form1->Memo2->Lines->Clear();
	Form1->StringGrid1-> RowCount = 0;
	Form1->StringGrid1-> ColCount = 0;
	Form1->StringGrid1->ColWidths[0]= 0;
}
//---------------------------------------------------------------------------



















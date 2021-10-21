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
	fstyle = GetWindowLong(Edit1->Handle, GWL_STYLE); // �ŧiEdit1��J�Ȭ��Ʀr
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
		}                 //�C�Ӧ�m������0
	}
	if (Form1->RadioButton1->Checked)
	{   i = 0;                   //up checked 1�\�W��
		j = n/2;

	}
	else if(Form1->RadioButton2->Checked)
	{   i = n-1;                 //down checked 1�\�U��
		j = n/2;
	}
	else if(Form1->RadioButton3->Checked)
	{   i = n/2;
		j=0;                      //left checked 1�\����

	}
	else if(Form1->RadioButton4->Checked)
	{   i=n/2;
		j=n-1;                    //right checked 1�\�k��

    }
	square[i][j] = 1;            //�\1����m
	data = 2;                    //��2
	while (data <= n*n)          //��n*n�ӼƦr�n��
	{   if (Form1->RadioButton1->Checked&&Form1->RadioButton5->Checked)         //1�\�W�� ���ͤ�V:���W
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				i = (i+1) % n;
			else
			{i = k; j = l; }
		}
        else if (Form1->RadioButton1->Checked&&Form1->RadioButton6->Checked)    //1�\�W�� ���ͤ�V:�k�W
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				i = (i+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton2->Checked&&Form1->RadioButton7->Checked)    //1�\�U�� ���ͤ�V:���U
		{   k = (i+1==n) ? 0 : i+1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				i = (i-1 < 0) ? n-1 : i-1;
			else
			 { i = k; j = l; }
		}

		else if (Form1->RadioButton2->Checked&&Form1->RadioButton8->Checked)    //1�\�U�� ���ͤ�V:�k�U
		{   k = (i+1==n) ? 0 : i+1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				i = (i-1 < 0) ? n-1 : i-1;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton3->Checked&&Form1->RadioButton5->Checked)    //1�\���� ���ͤ�V:���W
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				j = (j+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton3->Checked&&Form1->RadioButton7->Checked)    //1�\���� ���ͤ�V:���U
		{   k = (i+1==n) ? 0 : i+1;
			l = (j-1<0) ? n-1 : j-1;
			if (square[k][l]>0)
				j = (j+1) % n;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton4->Checked&&Form1->RadioButton6->Checked)    //1�\�k�� ���ͤ�V:�k�W
		{   k = (i-1<0) ? n-1 : i-1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				j = (j-1 < 0) ? n-1 : j-1;
			else
			 { i = k; j = l; }
		}
		else if (Form1->RadioButton4->Checked&&Form1->RadioButton8->Checked)    //1�\�k�� ���ͤ�V:�k�U
		{   k = (i+1==n) ? 0 : i+1;
			l = (j+1==n) ? 0 : j+1;
			if (square[k][l]>0)
				j = (j-1 < 0) ? n-1 : j-1;
			else
			 { i = k; j = l; }
		}

		square[i][j]=data++;   // ��1 ->2 ->3 ...
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
	int block = len+5;       //�T�w�C�檺�e��
	int blank_len, sum_len,i, j, k, sum, tmp;
	String row1,str_sum;
	if(Form1->CheckBox1->Checked)
	{
		Form1 ->Memo2 ->Lines ->Add("- - - - - - - Magic Square "+IntToStr(n)+" x "+IntToStr(n)+" - - - - - - -"); //�L�X��}size
	}
	else
		Form1 ->Memo1 ->Lines ->Add("- - - - - - - Magic Square "+IntToStr(n)+" x "+IntToStr(n)+" - - - - - - -"); //�L�X��}size


	if(Form1->CheckBox1->Checked )
	{
		Form1->StringGrid1-> RowCount = n+1;
		Form1->StringGrid1-> ColCount = n+1;   //StringGrid����(n+1)x(n+1)�Ӯ�l �i�H�g�Xcheck�����G
	}
	else
	{
		Form1->StringGrid1-> RowCount = n;
		Form1->StringGrid1-> ColCount = n;     //StringGrid����n*n�Ӯ�l
	}
	//��row
	for (i = 0; i < n; i++)
	{   row1 = " ";          //�Ψӱƪ�
		int sum = 0;
		Form1->StringGrid1->ColWidths[i]= (block+1) * 5;  //��l�e��

		for (j = 0; j < n; j++)
		{
			str_sum = IntToStr(square[i][j]);
			blank_len = block - str_sum.Length();           //�T�w��}�e��
			for (k = 0; k < blank_len; k++)
			   row1 += " ";

			row1 += square[i][j];
			Form1->StringGrid1->Cells[j][i] = square[i][j];
			sum += square[i][j];                           //�C�C�`�M
		}
        //�۰����C�C�`�M
		if(Form1 ->CheckBox1 -> Checked)
		{
			str_sum = IntToStr(sum);
			blank_len = block - str_sum.Length();
			//�T�w��}�e��
			for (k = 0; k < blank_len; k++)
				row1 += " ";

			Form1 ->Memo2 ->Lines ->Add(row1+"�X"+IntToStr(sum));
			Form1->StringGrid1->ColWidths[i]= (block+5) * 5;
			Form1->StringGrid1->Cells[n][i] = "�X"+IntToStr(sum);
		}
		else
			Form1 ->Memo1 ->Lines ->Add(row1);                   //print row

	}

    //�̫�@�C ��� �﨤�`�M
	//�۰�����&�﨤�u�`�M
	if(Form1 ->CheckBox1 -> Checked)
	{
		row1 = " ";
        //�p����`�M
		for (j = 0; j < n; j++)
		{
			sum = 0;
			for (i = 0; i < n; i++)
			   sum += square[i][j];

			str_sum = IntToStr(sum);
			blank_len = block - str_sum.Length();              //�T�w��}�e��
			for (k = 1; k < blank_len; k++)
				row1 += " ";
			row1 = row1+"|"+sum;
			Form1->StringGrid1->Cells[j][n] = "|"+IntToStr(sum);
		}

		//�p�⥪�U��k�W�`�M
		sum = 0;
		for (i = 0; i < n; i++)
		{
			j = n - 1 -i;
			sum += square[i][j];
		}
		str_sum = IntToStr(sum);
		blank_len = block - str_sum.Length();  //�T�w��}�e��
		for (k = -1; k < blank_len; k++)
			row1 += " ";
		row1 = row1+"/" + sum;
		tmp=sum;

		//�p�⥪�W��k�U�`�M
        sum = 0;
		for (i = 0; i < n; i++)
		{
			j = i;
			sum += square[i][j];
		}
		str_sum = IntToStr(sum);
		blank_len = block - str_sum.Length();             //�T�w��}�e��
		for (k = -1; k < blank_len; k++)
			row1 += " ";
		row1 = row1+"\\" + sum;


		Form1->StringGrid1->ColWidths[n]= (block+5) * 10;
		Form1->StringGrid1->Cells[n][n] = "\\"+IntToStr(tmp)+" /"+IntToStr(sum);
		Form1 ->Memo2 ->Lines ->Add(row1);           //print��&�׽u�`�M
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{   int n = StrToInt(Edit1->Text);         //nxn��}
	int **square = new int *[n];           //�̷�n�j�p �ʺA����n+1�C


	for (int i=0; i<n; i++)
		square[i] = new int [n];           //�C�@�C�A����n+1��

	if(n == 0)          //��}�j�p���i=0
	{   Form1 ->Memo1 ->Lines ->Add("* * * * * Square size should NOT be 0. * * * * *");
		Form1 ->Memo2 ->Lines ->Add("* * * * * Square size should NOT be 0. * * * * *");
		Form1->StringGrid1-> RowCount = 0;
		Form1->StringGrid1-> ColCount = 0;
		Form1->StringGrid1->ColWidths[0]= 600;
		Form1->StringGrid1->Cells[0][0] = "Square size should NOT be 0.";
	}
	else if(n == 2)    //��}�j�p���i=2
	{   Form1 ->Memo1 ->Lines ->Add("* * * * * Square size should NOT be 2. * * * * *");
		Form1 ->Memo2 ->Lines ->Add("* * * * * Square size should NOT be 2. * * * * *");
        Form1->StringGrid1-> RowCount = 0;
		Form1->StringGrid1-> ColCount = 0;
		Form1->StringGrid1->ColWidths[0]= 600;
		Form1->StringGrid1->Cells[0][0] = "Square size should NOT be 2.";
	}
	else if(n%4 == 0)  //n=4������
	{   MagicSquare4n(square, n);
		PrintSquare(square, n);
	}
	else if(n%2 == 0) //n=2������(����)
	{   MagicSquareEven(square, n/2);
		PrintSquare(square, n);
	}
	else              //�Ҧ��_��
	{   //��ܪ��զX�i�H����magic square
		if((Form1->RadioButton1->Checked&&Form1->RadioButton5->Checked)||(Form1->RadioButton1->Checked&&Form1->RadioButton6->Checked)||(Form1->RadioButton2->Checked&&Form1->RadioButton7->Checked)||(Form1->RadioButton2->Checked&&Form1->RadioButton8->Checked)||(Form1->RadioButton3->Checked&&Form1->RadioButton5->Checked)||(Form1->RadioButton3->Checked&&Form1->RadioButton7->Checked)||(Form1->RadioButton4->Checked&&Form1->RadioButton6->Checked)||(Form1->RadioButton4->Checked&&Form1->RadioButton8->Checked))
		{	MagicSquareOdd(square, n);
			PrintSquare(square, n);
		}
		//��ܪ��զX�L�k����magic square
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



	//�O�����ٵ��q��
	for (int i=0; i<n; i++)
		delete[]square[i];

	delete[] square;
}
//---------------------------------------------------------------------------


//�e��clear
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form1->Memo1->Lines->Clear();
    Form1->Memo2->Lines->Clear();
	Form1->StringGrid1-> RowCount = 0;
	Form1->StringGrid1-> ColCount = 0;
	Form1->StringGrid1->ColWidths[0]= 0;
}
//---------------------------------------------------------------------------



















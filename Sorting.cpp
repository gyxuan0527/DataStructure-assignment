//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Sorting.h"
#include <time.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int data[1000000];
int original_data [1000000];    //未排序的原始資料
int n,y=0,z=0;
double SelSortTime [10];    // declare Time arrays, which would keep real CPU times
double BubSortTime [10];
double RandGenTime [10];
double BT[100],ST[100];
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    //input合理性檢測
	DWord fstyle;
	fstyle = GetWindowLong(Edit1->Handle, GWL_STYLE); // 宣告Edit1輸入僅為數字
	SetWindowLong(Edit1->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit2->Handle, GWL_STYLE); // 宣告Edit2輸入僅為數字
	SetWindowLong(Edit2->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit3->Handle, GWL_STYLE); // 宣告Edit3輸入僅為數字
	SetWindowLong(Edit3->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
}


void SelectionSort(int data[],int n)
{
	int i,j,tmp,min;
		for(i=0;i<n;i++)
		{
			min=i;
			for(j=i+1;j<n;j++)
			{
				if(data[j]<data[min])
				{
					min=j;
                }
			}
			tmp=data[i];
			data[i]=data[min];
            data[min]=tmp;
		} //0跟第1 2 3 ...比 如果比較小就交換index  最後才換值
}

void BubbleSort(int data[],int n)
{
	int i,j,tmp;
	for (int i = n - 1; i > 0; --i)
	{    for (int j = 0; j < i; ++j)
		 {	if (data[j] > data[j + 1])
			{
				tmp=data[j];
				data[j]=data[j+1];
				data[j+1]=tmp;
			}
		 }
	}//0跟1比 1跟2比 大的值往下沉
}

void getData(int data[], int original_data[], int n)
{   int i;
	for (i = 0; i < n; i++)
	{
		data[i] = original_data[i];
	}

}//取未整理資料來排序 以免bubblesort排到已經用selectionsort排過的

//selection sort print data
void printData2(int data[],int n)
{
	int i;
		for(i=0;i<n;i++)
		{
		  Form1->Memo2->Lines->Add("data["+IntToStr(i)+"]="+IntToStr(data[i]));
		}
}
//bubble sort print data
void printData3(int data[],int n)
{
	int i;
		for(i=0;i<n;i++)
		{
		  Form1->Memo3->Lines->Add("data["+IntToStr(i)+"]="+IntToStr(data[i]));
		}
}

//檢查資料是否整理成功
void checkData (int data[], int n , int flag)
{   int i;
	for (i = 0; i < n-1; i++)       //若後者為大於前者 i不增加至n
	{
		if(data[i]>data[i+1])break;
	}
	if (i == n-1)
	{
		if (flag == 2) Form1->Memo2->Lines->Add("Correctly Sorted.");
		else if (flag == 3) Form1->Memo3->Lines->Add("Correctly Sorted.");
	}
	else       //i不等於n 代表資料沒整理成功
	{
		if (flag == 2) Form1->Memo2->Lines->Add("Incorrectly Sorted.");
		else if (flag == 3) Form1->Memo3->Lines->Add("Incorrectly Sorted.");
    }
}

int BinarySearch (int data[], int n, int target)
{	int left=0, right=n,middle;
		while(left<=right)
		{   middle = (left+right)/2;       //找中間的資料
			if(data[middle]==target)
				return middle;                //找到就輸出
			else if(data[middle]>target)          //搜尋中間到最小值間
				right = middle -1;
			else                                 //搜尋中間到最大值間
				left = middle +1;
		}
		return -1;
}






//---------------------------------------------------------------------------
//generate random numbers click
void __fastcall TForm1::Button1Click(TObject *Sender)
{   n=StrToInt(Edit1->Text);  //注意n要設成global variable
	int range=StrToInt(Edit2->Text);
	int i;

	clock_t t_begin,t_end;  //用來計cpu時間
		t_begin=clock();
        for(i=0;i<n;i++)
		{
			original_data[i]=rand()%range+1;

		}
		t_end=clock();
		Form1->Memo1->Lines->Add("CPU time (sec.)="+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC));
		if(CheckBox1->Checked)   //echo print打勾
		{
			for(i=0;i<n;i++)
			{
				Form1->Memo1->Lines->Add("data["+IntToStr(i)+"]="+IntToStr(original_data[i]));
			}
		}

}
//---------------------------------------------------------------------------
//selection sort click
void __fastcall TForm1::Button2Click(TObject *Sender)
{   clock_t t_begin,t_end;
	 t_begin=clock();
	 getData(data,original_data,n);
	 SelectionSort(data,n);
	 t_end=clock();
	 Form1->Memo2->Lines->Add("CPU time (sec.)="+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC));
	 ST[y]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
	 y++;
	 if(CheckBox1->Checked)
	 {
		printData2(data,n);
	 }
	 if(CheckBox2->Checked)checkData(data,n, 2);   //self check打勾

}
//---------------------------------------------------------------------------

//bubble sort click
void __fastcall TForm1::Button3Click(TObject *Sender)
{   clock_t t_begin,t_end;
	 t_begin=clock();
	 getData(data,original_data,n);
	 BubbleSort(data,n);
	 t_end=clock();
	 Form1->Memo3->Lines->Add("CPU time (sec.)="+FloatToStr((float)(t_end-t_begin)/CLOCKS_PER_SEC));
	 BT[z]=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
	 z++;
	 if(CheckBox1->Checked)
	 {
		printData3(data,n);
	 }
	 if(CheckBox2->Checked)checkData(data,n, 3);

}
//---------------------------------------------------------------------------
//binary search click
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int target = StrToInt(Edit3->Text);          //取得搜尋目標數
	int success = -1;
	success = BinarySearch(data, n , target);
	if(success >= 0 && success<n)           //若在data內找到目標 輸出資料位置
		Memo4 ->Lines ->Add(IntToStr(target)+" has been found in data["+IntToStr(success)+"]. ");
	else                                    //若success仍計為-1 代表沒找到資料
		Memo4 ->Lines ->Add(IntToStr(target)+" has NOT been found, Sorry.");
}
//---------------------------------------------------------------------------
//load chart click
void __fastcall TForm1::Button5Click(TObject *Sender)
{
 int i;
        Chart1->RemoveAllSeries();             // Remove all previous series
        Chart1->Title->Text->Clear();         // Clear chart chart title
        Chart1->Title->Text->Add("SelectionSort v.s BubbleSort");
        Chart1->BottomAxis->Title->Caption = "data size";    // x-axis' title
        Chart1->LeftAxis->Title->Caption = "CPU time (sec.)";    // y-axis' title
		for (int i=0; i<6; i++) // acquire CPU time information for the three serieses
		{      SelSortTime[i] = ST[i];    // Just use random values here
				BubSortTime[i] = BT[i];

		}
        Chart1->AddSeries( new TBarSeries (this) );      // create a new BAR series
        Chart1->Series[0]->Title = "Selection Sort";
		Chart1->Series[0]->AddArray( SelSortTime, 5 );
                // assign the values in SelSortTime onto the series one by one from 0 to 4
        Chart1->AddSeries( new TBarSeries (this) );
        Chart1->Series[1]->Title = "Bubble Sort";
                for (i=0; i<6; i++) Chart1->Series[1]->Add( BubSortTime[i], 10000*(i+1), clGreen );
                // assign the values in BubSortTime onto the series one by one from 0 to 4


		for (int i=0; i<2; i++)     // Set marks visible
        {      Chart1->Series[i]->Marks->Visible = true;
                Chart1->Series[i]->Marks->Style = smsValue;
        }
        /* ---- Another ways to create serieses
        // new series one by one
        TLineSeries * Series = new TLineSeries(Chart1);
        Chart1->AddSeries(Series);

        TBarSeries * Series2 = new TBarSeries(Chart1);
        Chart1->AddSeries(Series2);
        // new series by loop
        for (i=1; i<=3; i++)
        {      TLineSeries * Series = new TLineSeries(Chart1);
                Series->ParentChart = Chart1;
                Chart1->AddSeries(Series);
        }
		---- */
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Permutations.h"
#define SWAP(x,y,t)(t=x,x=y,y=t)
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int count;  //計index或step的變數
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void PermStr(String keyin_string, int k, int n)

	{   int i, tmp;
		if (k == n)       //終止條件 n個字元從第k+1個開始排 即第n個
		   Form1->Memo1->Lines->Add(keyin_string+"  ["+IntToStr(count++)+"]");
		else
		{   for (i=k; i<=n; i++) //從字串第k的位置排列到第n-1個
		   {  SWAP(keyin_string[k], keyin_string[i], tmp); //將第k個位置跟第i個位置字元交換
			  PermStr(keyin_string, k+1, n); //從第k+1的位置繼續排列
			  SWAP(keyin_string[k], keyin_string[i], tmp); //換回原本的位置 以免出錯
		   }
		}
	}

void PermStrTra(String keyin_string, int k, int n)

	{
		int i, tmp;
		if (k == n)
		{
			String tab_1 = "\t";
			for (int x = 0; x < k; x++)
			{ 							   //做到第幾個位置 就輸出幾個空格
				tab_1 +="\t";
			}
			Form1->Memo2->Lines->Add(tab_1+"==> (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+")! k==n-1 print!");
			//已排完n-1個位置 輸出排列
			Form1->Memo2->Lines->Add(keyin_string+"  ["+IntToStr(count++)+"]");
            //排列結果[第幾筆資料]
		}
		else
		{	for (i=k; i<=n; i++)
			{   String tab_2 = "\t";
				for (int x = 0; x < k; x++)  //做到第幾個位置 就輸出幾個空格
				{
					tab_2 +="\t";
				}
				SWAP(keyin_string[k], keyin_string[i], tmp);
				Form1->Memo2->Lines->Add(tab_2+">i="+IntToStr(i-1)+"  (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+"),  swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"],  list[ ]="+keyin_string);
				//輸出交換第k個位置與第n個位置的排列
				PermStrTra(keyin_string, k+1, n);
				SWAP(keyin_string[k], keyin_string[i], tmp); //換回來 以免出錯
				Form1->Memo2->Lines->Add(tab_2+"<i="+IntToStr(i-1)+"  (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+"),  swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"],  list[ ]="+keyin_string);
				//輸出如何回復原本排列
			}
		}
	}


//---------------------------------------------------------------------------

void MoveTower(int disk, String start, String end, String vacant)
{
	if(disk >= 1) //還沒做完所有的move
	{
		MoveTower(disk-1,start,vacant,end);
		Form1->Memo3->Lines->Add("Step "+IntToStr(count++)+": Move the top disk from tower "+start+" to tower "+end);
		//輸出步驟 及將柱子?的Top disk移動到柱子? 步驟數+1
		MoveTower(disk-1,vacant,end,start);
	}
 }



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//Permute click & tracing check
void __fastcall TForm1::Button1Click(TObject *Sender)
{  	int k, n;
	String keyin_string;
	keyin_string = Edit1->Text;    //取得字串
	k = StrToInt(Edit2->Text);    //從取得字串的第k+1個字元開始排列
	n = keyin_string.Length();    //取得字串長度
	count = 0;                    //[index]歸0
	PermStr(keyin_string, k+1, n);  //長度n的字串從第k+1個位置開始排列
	Form1->Memo1->Lines->Add("-----------------------------------------------------------------------------------------------------------------");

	if(CheckBox1 ->Checked)       //Tracing打勾 輸出完整排列過程
	{
		Form1->Memo2->Lines->Add("\tGo==>(k,n)=("+IntToStr(k)+","+IntToStr(n)+")");//輸出要從第k個字元開始排列n個字元 (k,n)
		count = 0;
		PermStrTra(keyin_string, k+1, n);
		Form1->Memo2->Lines->Add("-----------------------------------------------------------------------------------------------------------------");
	}

}
//---------------------------------------------------------------------------
//Move Tower click
void __fastcall TForm1::Button2Click(TObject *Sender)
{  int disk_num = StrToInt(Edit3 ->Text); //disk數
	count = 1;         //從step1開始
	MoveTower(disk_num,"A","C","B"); //將disk_num數的disk從A移到C
	Form1->Memo3->Lines->Add("\t----- "+IntToStr(count-1)+" steps in total for "+IntToStr(disk_num)+" disks -----");
	// 輸出總共做了多少步驟

}
//---------------------------------------------------------------------------
//Permute /tracing clear
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Form1->Memo1->Lines->Clear();
	Form1->Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------
//Tower of Hanoi /tracing clear
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Form1->Memo3->Lines->Clear();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

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
int count;  //�pindex��step���ܼ�
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void PermStr(String keyin_string, int k, int n)

	{   int i, tmp;
		if (k == n)       //�פ���� n�Ӧr���q��k+1�Ӷ}�l�� �Y��n��
		   Form1->Memo1->Lines->Add(keyin_string+"  ["+IntToStr(count++)+"]");
		else
		{   for (i=k; i<=n; i++) //�q�r���k����m�ƦC���n-1��
		   {  SWAP(keyin_string[k], keyin_string[i], tmp); //�N��k�Ӧ�m���i�Ӧ�m�r���洫
			  PermStr(keyin_string, k+1, n); //�q��k+1����m�~��ƦC
			  SWAP(keyin_string[k], keyin_string[i], tmp); //���^�쥻����m �H�K�X��
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
			{ 							   //����ĴX�Ӧ�m �N��X�X�ӪŮ�
				tab_1 +="\t";
			}
			Form1->Memo2->Lines->Add(tab_1+"==> (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+")! k==n-1 print!");
			//�w�Ƨ�n-1�Ӧ�m ��X�ƦC
			Form1->Memo2->Lines->Add(keyin_string+"  ["+IntToStr(count++)+"]");
            //�ƦC���G[�ĴX�����]
		}
		else
		{	for (i=k; i<=n; i++)
			{   String tab_2 = "\t";
				for (int x = 0; x < k; x++)  //����ĴX�Ӧ�m �N��X�X�ӪŮ�
				{
					tab_2 +="\t";
				}
				SWAP(keyin_string[k], keyin_string[i], tmp);
				Form1->Memo2->Lines->Add(tab_2+">i="+IntToStr(i-1)+"  (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+"),  swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"],  list[ ]="+keyin_string);
				//��X�洫��k�Ӧ�m�P��n�Ӧ�m���ƦC
				PermStrTra(keyin_string, k+1, n);
				SWAP(keyin_string[k], keyin_string[i], tmp); //���^�� �H�K�X��
				Form1->Memo2->Lines->Add(tab_2+"<i="+IntToStr(i-1)+"  (k,n)=("+IntToStr(k-1)+","+IntToStr(n)+"),  swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"],  list[ ]="+keyin_string);
				//��X�p��^�_�쥻�ƦC
			}
		}
	}


//---------------------------------------------------------------------------

void MoveTower(int disk, String start, String end, String vacant)
{
	if(disk >= 1) //�٨S�����Ҧ���move
	{
		MoveTower(disk-1,start,vacant,end);
		Form1->Memo3->Lines->Add("Step "+IntToStr(count++)+": Move the top disk from tower "+start+" to tower "+end);
		//��X�B�J �αN�W�l?��Top disk���ʨ�W�l? �B�J��+1
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
	keyin_string = Edit1->Text;    //���o�r��
	k = StrToInt(Edit2->Text);    //�q���o�r�ꪺ��k+1�Ӧr���}�l�ƦC
	n = keyin_string.Length();    //���o�r�����
	count = 0;                    //[index]�k0
	PermStr(keyin_string, k+1, n);  //����n���r��q��k+1�Ӧ�m�}�l�ƦC
	Form1->Memo1->Lines->Add("-----------------------------------------------------------------------------------------------------------------");

	if(CheckBox1 ->Checked)       //Tracing���� ��X����ƦC�L�{
	{
		Form1->Memo2->Lines->Add("\tGo==>(k,n)=("+IntToStr(k)+","+IntToStr(n)+")");//��X�n�q��k�Ӧr���}�l�ƦCn�Ӧr�� (k,n)
		count = 0;
		PermStrTra(keyin_string, k+1, n);
		Form1->Memo2->Lines->Add("-----------------------------------------------------------------------------------------------------------------");
	}

}
//---------------------------------------------------------------------------
//Move Tower click
void __fastcall TForm1::Button2Click(TObject *Sender)
{  int disk_num = StrToInt(Edit3 ->Text); //disk��
	count = 1;         //�qstep1�}�l
	MoveTower(disk_num,"A","C","B"); //�Ndisk_num�ƪ�disk�qA����C
	Form1->Memo3->Lines->Add("\t----- "+IntToStr(count-1)+" steps in total for "+IntToStr(disk_num)+" disks -----");
	// ��X�`�@���F�h�֨B�J

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

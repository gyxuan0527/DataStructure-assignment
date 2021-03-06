#include <vcl.h>
#pragma hdrstop

#include "SinglyLinkedList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include <stdlib.h>
TForm1 *Form1;
//---------------------------------------------------------------------------

struct node
{   int data;
	struct node * next;
};

struct node * first;
struct node* last;
struct node * top;
struct node* front ;
struct node* rear  ;

struct node * NewNode(int element)
{
	struct node * p;
	p = (struct node *) malloc (sizeof (struct node));
	p ->data = element ;
	p ->next = NULL ;
	return p;
}
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{   first = NewNode(0);
	first ->next = first;
	last = first;
	top = NewNode(0);
	top ->next = top;

	rear=NewNode(0);
	rear->next=rear;
	front=rear;

    //input瞶┦浪代
	DWord fstyle;
	fstyle = GetWindowLong(Edit1->Handle, GWL_STYLE); // Edit1块度计
	SetWindowLong(Edit1->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit2->Handle, GWL_STYLE); // Edit2块度计
	SetWindowLong(Edit2->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit3->Handle, GWL_STYLE); // Edit3块度计
	SetWindowLong(Edit3->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit4->Handle, GWL_STYLE); // Edit4块度计
	SetWindowLong(Edit4->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit5->Handle, GWL_STYLE); // Edit5块度计
	SetWindowLong(Edit5->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER
	fstyle = GetWindowLong(Edit6->Handle, GWL_STYLE); // Edit6块度计
	SetWindowLong(Edit6->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_RIGHT); // fstyle or ES_NUMBER

}


void printList(struct node * first)
{   struct node * p;
	String str = "";
	for(p=first->next; p!=first;p=p->next)
		str += IntToStr(p->data)+"==>";
	Form1 ->Memo1 ->Lines ->Add(str + "<");
}

void insertFirst(int element)
{
	struct node * p = NewNode(element);
	p ->next = first ->next;
	first->next = p;
	if (last == first)    //セ琌﹃
		last = p;
}

void insertLast(int element)
{
	struct node * p = NewNode(element);
	p ->next = last ->next;
	last->next = p;
	last = p;
}


struct node * searchTarget(int target)
{
	struct node * p;
	for(p = first->next; (p!=first && p->data!=target) ;p = p->next);    //眖circular list材0﹃材1秨﹍ 程(ぃ穦露ㄓ)临⊿тtarget ぃ耞穓碝
	if(p ==first)
		return NULL;
	return p;
}


struct node * searchTargetBefore(int target)       //┮тtarget玡ê兜
{
	struct node * p, * q;
	for(q = first, p= first ->next; (p!=first && p->data!=target) ; q = p,p = p->next);
	if(p ==first)
		return NULL;
	return q;
}


void insertAfter(int element, struct node * x)
{
	struct node * p = NewNode(element);
	p ->next = x ->next;
	x ->next = p;
}

void deleteAfter(struct node * x)
{
	struct node * p = x ->next;
	x->next = p->next;
	if(p == last)
        last = x;
	free (p);
}


void clearList(struct node * first)
{
	struct node * p;
	for(p = first->next; p!= first; p = first ->next)
	{   first->next = p->next;
		free(p);                  //材1材2材3材4....
	}
    last = first;
}


void push(int element)
{
	struct node * p = NewNode(element);
	p ->next = top ->next;           //top材0﹃夹
	top->next = p;
}


int pop()
{   struct node * p = top->next;        //程ê
	if(p == top)                        //stack is empty
		return -1;

	top ->next = p->next;
	free(p);
	return p->data;
}


void printStack(struct node * first)
{   struct node * p;
	String str = "";
	for(p=first->next; p!=first;p=p->next)
		str += IntToStr(p->data)+"==>";
	Form1 ->Memo2 ->Lines ->Add(str + "<");
}



void AddQueue(int element)
{
	struct node* p =NewNode(element);

	rear->next=p;
    p->next=front;
    rear=p;
}


int DeleteQueue()
{
	struct node* p = front->next;
	if(front ==p)
		return -1;

	Form1 ->Label8 ->Caption = "Pop result : " + IntToStr(p->data) + "";
	front->next=p->next;
	free(p);
	return p->data;
}

void printQueue(struct node * front)
{
	struct node* p;
	String str = "";
	for(p=front->next; p!=front;p=p->next)
		str += IntToStr(p->data)+"==>";
	Form1 ->Memo3 ->Lines ->Add(str + "<");
}


//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
	Form1->PageControl2->TabIndex = Form1->PageControl1->TabIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl2Change(TObject *Sender)
{
	Form1->PageControl1->TabIndex = Form1->PageControl2->TabIndex;
}
//---------------------------------------------------------------------------
//Insert first
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    int element = StrToInt(Form1 ->Edit1 ->Text);
	insertFirst(element);
	printList(first);
}
//---------------------------------------------------------------------------

//Insert last
void __fastcall TForm1::Button2Click(TObject *Sender)
{   int element = StrToInt(Form1 ->Edit1 ->Text);
	insertLast(element);
	printList(first);

}
//---------------------------------------------------------------------------
//Search target
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int target = StrToInt(Form1 ->Edit2->Text);
	struct node *x;
	x =searchTarget(target);
	if (x!=NULL)          //Τтtarget
		Form1 ->Memo1 ->Lines ->Add(IntToStr(x->data)+" has been found.");
	else                  //⊿тtarget
		Form1 ->Memo1 ->Lines ->Add(IntToStr(target)+" has NOT been found.");
    printList(first);
}
//---------------------------------------------------------------------------
//Search_insert after
void __fastcall TForm1::Button4Click(TObject *Sender)
{   int target = StrToInt(Form1 ->Edit2->Text);
	int element = StrToInt(Form1 ->Edit1 ->Text);
	struct node *x;
	x =searchTarget(target);            //穓碝琌target
	if(x!=NULL)                         //тtarget
		insertAfter(element, x);
	else                                //тぃtarget
		Form1 ->Memo1 ->Lines ->Add(IntToStr(target)+" has NOT been found.");
	printList(first);
}
//---------------------------------------------------------------------------
//Search_insert before
void __fastcall TForm1::Button5Click(TObject *Sender)
{   int target = StrToInt(Form1 ->Edit2->Text);
	int element = StrToInt(Form1 ->Edit1 ->Text);
	struct node *x;
	x =searchTargetBefore(target);     //穓碝琌target
	if(x!=NULL)                        //тtarget
		insertAfter(element, x);
	else                               //тぃtarget
	   Form1 ->Memo1 ->Lines ->Add(IntToStr(target)+" has NOT been found.");
	printList(first);

}
//---------------------------------------------------------------------------
//search delete
void __fastcall TForm1::Button6Click(TObject *Sender)
{   int target = StrToInt(Form1 ->Edit2->Text);
	int element = StrToInt(Form1 ->Edit1 ->Text);
	struct node *x;
	x =searchTargetBefore(target);       //穓碝琌target
	if(x!=NULL)                          //тtarget
		deleteAfter(x);
	else                                 //тぃtarget
	   Form1 ->Memo1 ->Lines ->Add(IntToStr(target)+" has NOT been found.");
	printList(first);
}
//---------------------------------------------------------------------------
//Insert n random numbers
void __fastcall TForm1::Button7Click(TObject *Sender)
{   int n = StrToInt(Form1 ->Edit3 ->Text);       //﹍玻ネn睹计
	int range = StrToInt(Form1 ->Edit4 ->Text);   //睹计玻ネ絛瞅
	int *data = new int [n];
	String str = "";
	for (int i = 0; i < n; i++)
	{   data[i] = rand() % range + 1 ;   //+1:ㄏ睹计ぃ穦瞷0
		str += IntToStr(data[i])+"_";
		insertLast(data[i]);
	}
	Form1 ->Memo1 ->Lines ->Add(IntToStr(n)+" random numbers: "+str);
	printList(first);
}
//---------------------------------------------------------------------------

//clear
void __fastcall TForm1::Button8Click(TObject *Sender)
{   clearList(first);
	printList(first);
}
//---------------------------------------------------------------------------
//Stack push
void __fastcall TForm1::Button9Click(TObject *Sender)
{   int element = StrToInt(Form1 ->Edit5 ->Text);
	push(element);
	printStack(top);
}
//---------------------------------------------------------------------------
//Stack pop
void __fastcall TForm1::Button10Click(TObject *Sender)
{   int result = pop();
	if(result != -1)     //stack临⊿
		printStack(top);
	else                  //top=NULL
		Form1 ->Memo2 ->Lines ->Add("Stack is empty.");
	Form1 ->Label6 ->Caption = "Pop result : " + IntToStr(result) + "";
}
//---------------------------------------------------------------------------
//Queue push
void __fastcall TForm1::Button11Click(TObject *Sender)
{   int element = StrToInt(Form1 ->Edit6 ->Text);
	AddQueue(element);
	printQueue(front);
}
//---------------------------------------------------------------------------
//Queue pop
void __fastcall TForm1::Button12Click(TObject *Sender)
{   int result = DeleteQueue();
	if(result != -1)     //stack临⊿
		printQueue(front);
    else                  //top=NULL
		Form1 ->Memo3 ->Lines ->Add("Queue is empty.");
	Form1 ->Label8 ->Caption = "Pop result : " + IntToStr(result) + "";

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet1Show(TObject *Sender)
{
    TabSheet4->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet2Show(TObject *Sender)
{
    TabSheet5->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet3Show(TObject *Sender)
{
    TabSheet6->Show();
}
//---------------------------------------------------------------------------




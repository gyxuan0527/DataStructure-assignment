//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "BinarySearchTree.h"
#include "stdlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

struct BSTreeNode
{   struct BSTreeNode *leftchild;
	int data;
	struct BSTreeNode *rightchild;
};

struct StackNode
{   struct BSTreeNode *treenode;
	struct StackNode *next;
};

struct QNode
{   struct BSTreeNode *treenode;
	struct QNode *next;
};

struct BSTreeCNode
{   struct BSTreeCNode *leftchild;
	char * data;
	struct BSTreeCNode *rightchild;
};

struct DrawTreeNode
{   struct DrawTreeNode* leftchild;
	int data;
	int index;
	struct DrawTreeNode* rightchild;
};

struct BSTreeCNode *Croot;
struct BSTreeNode *root;
struct StackNode *top;
struct DrawTreeNode* DrawRoot;
int* X;
int* Y;
String tree;
int count_node;
int** treenode;

void push_node(struct BSTreeNode *node )
{ struct StackNode *old_top;
  old_top = top;
  top = (struct StackNode *) malloc (sizeof(struct StackNode));
  top->treenode = node;
  top->next = old_top;
}

struct BSTreeNode *pop_node()
{ struct BSTreeNode *Tnode;
  struct StackNode *old_top;
  if (top == NULL);       // StackEmpty();
  else
  {  Tnode = top->treenode;
	 old_top = top;
	 top = top->next;
	 free(old_top);
	 return Tnode;
  }
}

struct QNode *front, *rear;

void AddQueue(struct BSTreeNode *Tnode)
{   struct QNode *node;
	node = (struct QNode *) malloc(sizeof(struct QNode));
	node->treenode = Tnode;
	node->next = NULL;
	if (front == NULL)
		front = node;
	else
		rear->next = node;
	rear = node;
}

struct BSTreeNode *DeleteQueue()
{ struct BSTreeNode *Tnode;
 struct QNode *old_front;
 if (front == NULL);  //QueueEmpty();
 else
 {   Tnode = front->treenode;
	 old_front = front;
	 front = front->next;
	 free(old_front);
	 return Tnode;
 }
}

void LevelOrder (struct BSTreeNode *node)
{ AddQueue(node);
  while (front != NULL)
  {  node = DeleteQueue();
	 tree += IntToStr(node->data)+"_";
	 if (node->leftchild != NULL)
		AddQueue(node->leftchild);
	 if (node->rightchild != NULL)
		AddQueue(node->rightchild);
  }
}

int InsertBST(int x)
{  struct BSTreeNode *p, *q;
	p = root; q = NULL;
	while (p != NULL)
	{ q = p;
	  if (x < p->data)           //向左找
		  p = p->leftchild;
	  else                       //向右找
		  p = p->rightchild;
	}
	// p = (struct BSTreeNode *) malloc (sizeof(BSTreeNode));
	p = new struct BSTreeNode;      //建一個新的格子
	p->data = x;                    //data那格填值
	p->leftchild = p->rightchild = NULL;          //左兒子 右兒子都接地
	if (root == NULL)
	{   root = p;                             //原是空的 創了之後只有一格
		count_node++;
	}
	else if (x < q->data)                     //更新新增那格的爸爸的leftchild
	{   q->leftchild = p;
		count_node++;
	}
	else
	{   q->rightchild = p;                    //更新新增那格的爸爸的rightchild
		count_node++;
	}
	return 1;
}

int DeleteBSTree(int x)
{   struct BSTreeNode *p , *father, *k, *f;
	 p = root;
	 father = NULL;
	 while (p != NULL)
	 {  if (x == p->data) // 找到 x 所在的節點 p 了
		{  if ((p->leftchild == NULL) && (p->rightchild == NULL))
			   k = NULL; // p 為樹葉節點
		   else if (p->leftchild != NULL ) // p 含有左子樹
		   {  f = p; // 找出 p 左子樹的最右樹葉
			  k = p->leftchild;
			  while (k->rightchild !=NULL)
			  {  f = k;
				 k = k->rightchild;
			  }  // k 即為 p 左子樹的最右樹葉
			  if (p == f)     // k 即為 p 的左兒子
					f->leftchild = k->leftchild;
			  else
					f->rightchild = k->leftchild;
		   }
		   else    // p 無左子樹, 檢查右子樹
		   {   f = p; //找出 p 右子樹的最左樹葉
			   k = p->rightchild;
			   while (k->leftchild != NULL)
			   {  f = k;
				  k = k ->leftchild;
			   }  // k 即為 p 右子樹的最左樹葉
			   if (p == f)    // k 即為 p 的右兒子
					f->rightchild = k->rightchild;
			   else
					f->leftchild = k->rightchild;
		   }
		   if (k != NULL)   // k 挪至原 p 處, 繼承 p 的左右指標
		   {   k->leftchild = p->leftchild;
			   k->rightchild = p->rightchild;
		   }
		   if (father == NULL)
				root = k;
		   else
		   {  if (x < father->data)  //決定k是father的左或右兒子
					father->leftchild = k;
			  else
					father->rightchild = k;
		   }
		   free(p);
		   count_node--;
		   return 1; //成功地刪除 x，於此傳回1返回呼叫處
		}
		else //尚未找到x，繼續往下一階層找
		{  father = p;
			if (x < p->data)
				p = p->leftchild;
			else
				p = p->rightchild;
		}
	 }
	 return 0; //未找到x，傳回0
}
//inorder LVR
void print_BSTree(struct BSTreeNode * node)
{  if (node != NULL)
   {  print_BSTree(node->leftchild);
	  tree += IntToStr(node->data)+"_";
	  print_BSTree(node->rightchild);
   }
}
//VLR
void print_BSTree_preorder(struct BSTreeNode * node)
{  if (node != NULL)
   {  tree += node->data +"+";
	  print_BSTree_preorder(node->leftchild);
	  print_BSTree_preorder(node->rightchild);
   }
}

void Inorder_Stack(struct BSTreeNode * node)
{   // node = root;
  do
  {  while (node != NULL)
	 {  push_node(node);
		node = node->leftchild;
	 }  // phsh all left children
	 if (top != NULL)
	 {  node = pop_node();
		tree += IntToStr(node->data)+"_";
		node = node->rightchild;
	 } // inorder printing and check right child
  } while ((top!=NULL)||(node!=NULL));
}

void Postorder_Stack(struct BSTreeNode * node)
{  do
   {  while (node != NULL)
	  {   tree = IntToStr(node->data)+"_"+tree;
		  push_node(node);
		  node = node->rightchild;
	  }   // push all left children
	  if (top != NULL)
	  {   node = pop_node();
		  node = node->leftchild;
	  }
  } while ((top!=NULL)||(node!=NULL));
}

void Preorder_Stack(struct BSTreeNode * node)
{  do
   { while (node != NULL)
	 {   tree += IntToStr(node->data)+"_";
		 push_node(node);
		 node = node->leftchild;
	 }   // push all left children
	 if (top != NULL)
	 {   node = pop_node();
		 node = node->rightchild;
	 }
   } while ((top!=NULL)||(node!=NULL));
}

int tempcount;

int Depth_BTree(struct BSTreeNode* node, int level)
{   int depth, l_depth, r_depth;
	if (node!=NULL)
	{
	   l_depth = Depth_BTree(node->leftchild, (level+1));
	   r_depth = Depth_BTree(node->rightchild, (level+1));
	   depth = l_depth>r_depth? l_depth : r_depth;
	   return depth;
	}
	else
		return (level-1);
}


void determine_X(struct DrawTreeNode* node, int left, int right)
{   if (node != NULL)
	{  int m = (left+right)/2;
	   X[node->index] = (m == 0) ? left : m;
	   determine_X(node->leftchild, left, (m-1<left)?left:m-1);
	   determine_X(node->rightchild, (m+1<right)?m+1:right, right);
	}
}

void determine_Y(struct DrawTreeNode* node, int top, int bottom, int depth)
{  int detH = (top+bottom)/(depth+1);
   for (int i=0; i<depth+1; i++)
   {  Y[i] = (detH < 10) ? 10*i : detH*i;
   }
}

struct DrawTreeNode* CopyBSTtoDT(struct BSTreeNode* TreeRoot, int index, int depth)
{   if (TreeRoot==NULL)
	{   return NULL;
	}
	struct DrawTreeNode* copyRoot = (struct DrawTreeNode*)malloc(sizeof(DrawTreeNode));
	copyRoot->data = TreeRoot->data;
	copyRoot->index = index;
	copyRoot->leftchild = CopyBSTtoDT(TreeRoot->leftchild, 2*index, depth);
	copyRoot->rightchild = CopyBSTtoDT(TreeRoot->rightchild, 2*index+1, depth);
	return copyRoot;
}

// void Draw_BST(struct DrawTreeNode* DrawRoot, int detW, int detH, int node_radius)
void Draw_BST(struct DrawTreeNode* DrawRoot, int node_radius)
{   if (DrawRoot!=NULL)
	{  int level = ceil(log(DrawRoot->index+1.0)/log(2.0));
	   if (DrawRoot->leftchild!=NULL)
	   {   Form1->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);
		   Form1->Image1->Canvas->LineTo(X[DrawRoot->leftchild->index], Y[level+1]);

	   }
	   if (DrawRoot->rightchild)
	   {   Form1->Image1->Canvas->MoveTo(X[DrawRoot->index], Y[level]);
		   Form1->Image1->Canvas->LineTo(X[DrawRoot->rightchild->index], Y[level+1]);

	   }
	   Form1->Image1->Canvas->Ellipse(X[DrawRoot->index]- node_radius,
		   Y[level] - node_radius,
		   X[DrawRoot->index]+ node_radius,
		   Y[level] + node_radius);
	   Form1->Image1->Canvas->TextOut(X[DrawRoot->index]-5, Y[level]-7, IntToStr(DrawRoot->data));

	   Draw_BST(DrawRoot->leftchild, node_radius);
	   Draw_BST(DrawRoot->rightchild, node_radius);
	}
}

void Clear_BST(struct BSTreeNode* BSTnode)
{   if (BSTnode != NULL)
	{   Clear_BST(BSTnode->leftchild);
		Clear_BST(BSTnode->rightchild);
		delete(BSTnode);
	}
}

void Clear_DBST(struct DrawTreeNode* DBSTnode)
{   if (DBSTnode != NULL)
	{   Clear_DBST(DBSTnode->leftchild);
		Clear_DBST(DBSTnode->rightchild);
		delete(DBSTnode);
	}
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    count_node=0;
}
//---------------------------------------------------------------------------

//insert into BST
void __fastcall TForm1::Button1Click(TObject *Sender)
{   int data = Edit1->Text.ToInt();
	int success = InsertBST(data);
	if (!success)
	{
		Memo1->Lines->Add("Fail to insert:"+IntToStr(data));
	}
	else
	{   tree = "";
		print_BSTree(root);
		Memo1->Lines->Add("Inorder (recursively):      "+tree);
		if (CheckBox1->Checked) Button4->Click();

	}
}
//---------------------------------------------------------------------------
//delete from BST
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int target = Edit5->Text.ToInt();
	int success = DeleteBSTree(target);
	if (success)
	{  	 Memo1->Lines->Add(IntToStr(target) +" has been deleted.");

	}
	else Memo1->Lines->Add(IntToStr(target) +" has not been found.");
	tree = "";
	print_BSTree(root);
	Memo1->Lines->Add(tree);
	if (CheckBox1->Checked) Button4->Click();
}
//---------------------------------------------------------------------------
//random integers
void __fastcall TForm1::Button3Click(TObject *Sender)
{   int n = Edit2->Text.ToInt();
	int * data = new int [n];
	 String inp = "";
	 srand(time(NULL));
	 int range_min = Edit3->Text.ToInt();
	 int range_max = Edit4->Text.ToInt();
	 for (int i=0; i<n; i++)
	 {   data[i] = rand()%(range_max-range_min+1)+range_min;
		 int success = InsertBST(data[i]);
		 inp += IntToStr(data[i]) +"-";
	 }
	 Memo1->Lines->Add(inp);
	 tree = "";
	 print_BSTree(root);
	 Memo1->Lines->Add("Inorder (recursively):      "+tree);
	 if (CheckBox1->Checked) Button4->Click();
}
//---------------------------------------------------------------------------
//draw BST
void __fastcall TForm1::Button4Click(TObject *Sender)
{
 //Clear Image
	Image1->Picture->Assign(NULL);
	Image1->Canvas->Pen->Color = (TColor)RGB(0, 0, 255);
 /*
 //Reset Node Record
	treenode = new int* [count_node];
	for (int i=0; i < count_node; i++)
	{	treenode[i] = new int [4]; }
 */
 //Tree Depth & Data Record
	tempcount=0;
	int depth = Depth_BTree(root, 1);
	Memo1->Lines->Add("depth:"+IntToStr(depth));
//Tree Height & Width
	int tree_Height = ScrollBox1->Height;
	int tree_Width = ScrollBox1->Width;
//Node Distance
	int total_node = pow(2.0, depth)-1;
	int detW = tree_Width/(total_node+1);
	int detH = tree_Height/(depth+1);
//Node Size
	int node_radius = (detW*5/6 > detH/2) ? detH/2 : detW*5/6;
//Find Node Coordinate
// treenode = Find_Coordinate(treenode, count_node, total_node);
//int temp_space, uponlevel_space;
//int depth_node, upon_node;
	Image1->Top = 0;
	Image1->Left = 0;
	Image1->Height = tree_Height;
	Image1->Width = tree_Width;
	DrawRoot = CopyBSTtoDT(root, 1, depth);
	X = new int [total_node+2];
	Y = new int [depth+1];
	determine_X(DrawRoot, 0+node_radius, tree_Width-node_radius);
	determine_Y(DrawRoot, 0, tree_Height, depth);
/*
	tree = "";
	for (int i=0; i<total_node+1; i++) tree += IntToStr(X[i])+" ";
	Form1->Memo1->Lines->Add(tree);
	tree = "";
	for (int j=0; j<depth+1; j++) tree += IntToStr(Y[j])+" ";
	Form1->Memo1->Lines->Add(tree);
*/
//  Draw_BST(DrawRoot, detW, detH, node_radius);
	Draw_BST(DrawRoot, node_radius);
	delete(X);
	delete(Y);
/*
//print level 2~depth
	int data, x, y, parent_x, parent_y, site;
	for (int i=depth; i >= 1; i--) {
	for (int j=0; j < count_node; j++) {
	if (treenode[j][2]==i) {
		data = treenode[j][0];
		x = treenode[j][1];
		y = treenode[j][2];
		for (int data_index=0; data_index < count_node; data_index++) {
			 site = treenode[j][3];
		if (floor(site/2.0) == treenode[data_index][3]) {
			 parent_x = treenode[data_index][1];
			 parent_y = treenode[data_index][2];
		break;
			}
		}
    //Draw Line
	if (i!=1) {
		Image1->Canvas->MoveTo (x*detW, y*detH);
		Image1->Canvas->LineTo(parent_x*detW, parent_y*detH);
	}
	//Draw Node
	Image1->Canvas->Ellipse(x*detW-(node_radius),
		  y*detH-(node_radius),
		  x*detW+(node_radius),
		  y*detH+(node_radius));
	//Node->data output
	Image1->Canvas->TextOutA(x*detW-(node_radius/2), y*detH-(node_radius/2), IntToStr(data));
   }
  }
 }
 */
 /*
 //Tree Grid
	for (int i=0; i < total_node+1; i++) {
		 Image1->Canvas->MoveTo(i*detW, 0);
	Image1->Canvas->LineTo(i*detW, tree_Height);
	}
	for (int i=0; i < depth+1; i++) {
		 Image1->Canvas->MoveTo(0, i*detH);
		 Image1->Canvas->LineTo(tree_Width, i*detH);
	}
 */
}
//---------------------------------------------------------------------------
//clear BST
void __fastcall TForm1::Button5Click(TObject *Sender)
{   Image1->Picture->Assign(NULL);
	Memo1->Text = "";
	Clear_BST(root);
	Clear_DBST(DrawRoot);
}
//---------------------------------------------------------------------------
//infix
void __fastcall TForm1::Button6Click(TObject *Sender)
{   tree = "";
	Inorder_Stack(root);
    Memo1->Lines->Add("Inorder (nonrecursively): "+tree);
}
//---------------------------------------------------------------------------
//postfix
void __fastcall TForm1::Button7Click(TObject *Sender)
{   tree = "";
	Postorder_Stack(root);
    Memo1->Lines->Add("Postorder(nonrecursively):"+tree);
}
//---------------------------------------------------------------------------
//prefix
void __fastcall TForm1::Button8Click(TObject *Sender)
{   tree = "";
	Preorder_Stack(root);
	Memo1->Lines->Add("Preorder (nonrecursively):"+tree);
}
//---------------------------------------------------------------------------
//level order
void __fastcall TForm1::Button9Click(TObject *Sender)
{   tree = "";
	LevelOrder(root);
	Memo1->Lines->Add("Level-order :    "+tree);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Edit2->Text = IntToStr(((TTrackBar*)Sender)->Position);
}
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
	Edit3->Text = IntToStr(((TTrackBar*)Sender)->Position);
}
void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
	Edit4->Text = IntToStr(((TTrackBar*)Sender)->Position);
}

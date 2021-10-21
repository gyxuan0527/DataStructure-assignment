#include <vcl.h>
#pragma hdrstop
#include "Maze.h"
#define Max_StackSize 100000
#define possible_direction 8
int maze[1000][1000];
int h,w;                                     //存長寬
int top;                                     //stack最上面那項的index

struct offset
{
	int dx, dy;
};
enum direction {N,NE,E,SE,S,SW,W,NW};    //考慮 8 個方向
struct position
{
	 int x, y;
	 direction dir;
};
position step;                            //現在(座標,方向)
position stack [Max_StackSize];          //走過(座標,方向)
offset move[possible_direction];		// 可能移動的八個方向


void push(position step)
{   if (top == h*w)
		Form1->Memo1->Lines->Add("Full Stack");
	else
		stack[++top] = step;                //把現在(座標,方向)存入堆疊
}
position pop()
{   if (top == -1)                              //空堆疊
		Form1->Memo1->Lines->Add("Empty Stack");
	else
		return stack[top--];                    //pop出走過的格子
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void MouseInMaze(int maze[][1000], int Height, int Width)
{   int i, j, u, v;         //(i,j)->(u,v)
	bool found = false;      //還沒找到預設為false

    //可移動方向的 i j變化量
	move[N].dx = -1; move[N].dy = 0;
	move[NE].dx =-1; move[NE].dy = 1;
	move[E].dx = 0; move[E].dy = 1;
	move[SE].dx = 1; move[SE].dy = 1;
	move[S].dx = 1; move[S].dy = 0;
	move[SW].dx = 1; move[SW].dy = -1;
	move[W].dx = 0; move[W].dy = -1;
	move[NW].dx = -1; move[NW].dy = -1;

	//把(1,0) (1,1) 著色
	maze[1][0] = 2;
	maze[1][1] = 2;

	Form1->StringGrid1->Cells[0][1] = 2;
	Form1->StringGrid2->Cells[0][1] = 2;
	Form1->StringGrid3->Cells[0][1] = 2;
	Form1->StringGrid4->Cells[0][1] = 2;
	  Sleep(Form1 ->TrackBar1 ->Position);
	Form1->StringGrid1->Refresh();
	Form1->StringGrid4->Refresh();
	Form1->StringGrid1->Cells[1][1] = 2;
	Form1->StringGrid2->Cells[1][1] = 2;
	Form1->StringGrid3->Cells[1][1] = 2;
	Form1->StringGrid4->Cells[1][1] = 2;
	  Sleep(Form1 ->TrackBar1 ->Position);
	Form1->StringGrid1->Refresh();
	Form1->StringGrid4->Refresh();


	step.x = 2;   //預設第一步
	step.y = 1;
	step.dir = N;
	push(step);   //第一步放堆疊
	while (top != -1 && found==false)     //不是空堆疊或還沒找到就繼續找
	{   step = pop();

		i= step.x;
		j = step.y;
		step.dir = step.dir;  //現在位置
		while (step.dir <= NW && found==false)       //還沒找到且還有可嘗試方向
		{   u = i + move[step.dir].dx;              //自(i,j)欲嘗試的下一步座標(u,v)
			v = j + move[step.dir].dy;

			//周圍找到可以走的格子
			if (maze[u][v] == 0)
			{
				maze[u][v] = 2;        //該位置設成2
				Form1->StringGrid1->Cells[v][u] = 2;
				Form1->StringGrid2->Cells[v][u] = 2;
				Form1->StringGrid3->Cells[v][u] = 2;
				Form1->StringGrid4->Cells[v][u] = 2;
				Sleep(Form1 ->TrackBar1 ->Position);
				Form1->StringGrid1->Refresh();
				Form1->StringGrid4->Refresh();

				step.x = i;
				step.y = j;
				step.dir = direction(step.dir + 1);

				push(step);
				//成功走到出口
                if ((u == Height - 3) && (v == Width - 2))
				{   found = true;

					step.x = i;
					step.y = j;

					push(step);          //存入現在位置

					maze[u][v] = 2;        //該位置填2
					Form1->StringGrid1->Cells[v][u] = 2;
					Form1->StringGrid2->Cells[v][u] = 2;
					Form1->StringGrid3->Cells[v][u] = 2;
					Form1->StringGrid4->Cells[v][u] = 2;
					Sleep(Form1 ->TrackBar1 ->Position);
					Form1->StringGrid1->Refresh();
					Form1->StringGrid4->Refresh();
					while (top != -1)
					{
						position rout = pop(); //pop出從入口至出口的完整路徑
					}

				}

				i = u;
				j = v;
				step.dir = N;
			}
			else
				step.dir = direction(step.dir + 1);
		}
		//SE
		if(maze[u+1][v+1]!=1&&maze[u+1][v+1]!=4)
		{
			maze[u+1][v+1] = 3;
			Form1->StringGrid1->Cells[v+1][u+1] = 3;
			Form1->StringGrid2->Cells[v+1][u+1] = 3;  //不可能走
			Form1->StringGrid3->Cells[v+1][u+1] = 3;
			Form1->StringGrid4->Cells[v+1][u+1] = 3;
			Sleep(Form1 ->TrackBar1 ->Position);
			Form1->StringGrid1->Refresh();
			Form1->StringGrid4->Refresh();
		}
	}
	//把出口 (h-2,w-1) (h-2,w-2) 著色
	maze[h-2][w-2] = 2;
	Form1->StringGrid1->Cells[w-2][h-2] = 2;
	Form1->StringGrid2->Cells[w-2][h-2] = 2;
	Form1->StringGrid3->Cells[w-2][h-2] = 2;
	Form1->StringGrid4->Cells[w-2][h-2] = 2;
	  Sleep(Form1 ->TrackBar1 ->Position);
	Form1->StringGrid1->Refresh();
	Form1->StringGrid4->Refresh();
	maze[h-2][w-1] = 2 ;
	Form1->StringGrid1->Cells[w-1][h-2] = 2;
	Form1->StringGrid2->Cells[w-1][h-2] = 2;
	Form1->StringGrid3->Cells[w-1][h-2] = 2;
	Form1->StringGrid4->Cells[w-1][h-2] = 2;
	  Sleep(Form1 ->TrackBar1 ->Position);
	Form1->StringGrid1->Refresh();
    Form1->StringGrid4->Refresh();
}


//---------------------------------------------------------------------------
//load maze 讀檔
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FILE*fp;           // Define fp as a pointer pointing to some file (with data type FILE) in HD
	String out;
	int  m, n, i, j;
	AnsiString infile; // Use builder's string (AnsiString) to ease the conversion (into const char *)
	if(OpenDialog1->Execute())
	{
	   infile = OpenDialog1->FileName;
		fp = fopen(infile.c_str(),"r+"); //c_str函数的傳回值是 const char *, 即把AnsiString轉成const char *給fopen使用
		fscanf(fp,"%d%d", &m, &n);       // Read in two integers m & n
		Memo1->Lines->Add("(m , n) = ("+IntToStr(m)+" ,"+IntToStr(n)+" )");

		h= m;
		w= n;

		for(i=0; i<m; i++)      // Reda in m*n 0/1/2's into maze[][]
		{	for (j=0; j<n; j++)
				fscanf(fp, "%d", &maze[i][j]);
		}
		fclose(fp);              // 寫完檔後請關檔
		for(i=0; i<m; i++)     // Print out maze[][] in Memo1
		{   out = "";
			for (j=0; j<n; j++)
				out += "  "+IntToStr(maze[i][j]);
			Memo1->Lines->Add(out);
		}

		int grid_size =StrToInt(Edit1->Text);

		//colored
		Form1 ->StringGrid1 ->RowCount = m;
		Form1 ->StringGrid1 ->ColCount = n;
		for (i=0; i<m; i++)
			StringGrid1 -> RowHeights[i] = grid_size;
		for (i=0; i<n; i++)
			StringGrid1 -> ColWidths[i] = grid_size;
		for (i=0; i<m; i++)
		{   for (j=0; j<n; j++)
				Form1 -> StringGrid1 -> Cells[j][i] = maze[i][j];
		}

		// 只填數字進string grid
		StringGrid2->RowCount = m;
		StringGrid2->ColCount = n;
		for (i=0; i<m; i++)
		{
			for (j=0; j<n; j++)
				StringGrid2->Cells[j][i] = maze[i][j];
		}

		//fixed
		StringGrid3->RowCount = m;
		StringGrid3->ColCount = n;
		StringGrid3->FixedCols =0;
		StringGrid3->FixedRows =0;
		for (i=0; i<m; i++)
			StringGrid3->RowHeights[i] = grid_size;
		for (i=0; i<n; i++)
			StringGrid3->ColWidths[i] = grid_size;
		for (i=0; i<m; i++)
		   for (j=0; j<n; j++)
				 StringGrid3->Cells[j][i] = StringGrid2->Cells[j][i];

		//colored without line
		StringGrid4->RowCount = m;
		StringGrid4->ColCount = n;
		StringGrid4->FixedCols=0;
		StringGrid4->FixedRows=0;
		StringGrid4->GridLineWidth = 0;
		for (i=0; i<m; i++)
			StringGrid4->RowHeights[i] = grid_size;
		for (i=0; i<n; i++)
			StringGrid4->ColWidths[i] = grid_size;
		for (i=0; i<m; i++)
		{   for (j=0; j<n; j++)
					Form1 -> StringGrid4 -> Cells[j][i] = maze[i][j];
		}
	}
	else
		Memo1->Lines->Add("Nothing happens.");
}




//用 StringGrid 呈現迷宮
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,TGridDrawState State)
{
	AnsiString text = StringGrid1->Cells[ACol][ARow];
	if (text == "0")        //可能可走
		Form1->StringGrid1->Canvas->Brush->Color =(TColor) RGB(235, 214, 214) ;
	else if(text=="1")     //迷宮內牆壁
		Form1->StringGrid1->Canvas->Brush->Color = (TColor)RGB(129, 129, 65) ;
	else if (text == "2")   //最終路徑
		Form1->StringGrid1->Canvas->Brush->Color = (TColor)RGB(255, 226, 82) ;
	else if (text == "3")   //走過知道不能走
		Form1->StringGrid1->Canvas->Brush->Color =(TColor)RGB(255, 129, 66);
	else if(text=="4")      //外圍牆壁
		Form1->StringGrid1->Canvas->Brush->Color = (TColor)RGB(29, 35, 35);

	StringGrid1->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------
//用StringGrid呈現迷宮(without lines)
 void __fastcall TForm1::StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,TGridDrawState State)
 {   AnsiString text = StringGrid4->Cells[ACol][ARow];
	if (text == "0")        //可能可走
		Form1->StringGrid4->Canvas->Brush->Color =(TColor) RGB(235, 214, 214) ;
	else if(text=="1")     //迷宮內牆壁
		Form1->StringGrid4->Canvas->Brush->Color = (TColor)RGB(129, 129, 65) ;
	else if (text == "2")   //最終路徑
		Form1->StringGrid4->Canvas->Brush->Color = (TColor)RGB(255, 226, 82) ;
	else if (text == "3")   //走過知道不能走
		Form1->StringGrid4->Canvas->Brush->Color =(TColor)RGB(255, 129, 66) ;
	else if(text=="4")      //外圍牆壁
		Form1->StringGrid4->Canvas->Brush->Color = (TColor)RGB(29, 35, 35);

	StringGrid4->Canvas->FillRect(Rect);

 }

//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
//find tour
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	MouseInMaze(maze,h,w);
	String tab;
	Memo1->Lines->Add("Touring Maze ("+IntToStr(h)+" * "+IntToStr(w)+")");
	for(int i=0; i<h; i++)
	{   tab = "";
		for (int j=0; j<w; j++)
			tab=tab+ "  "+IntToStr(maze[i][j]);
		Memo1->Lines->Add(tab);
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


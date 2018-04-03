//作者：张长宇 
//功能：实现控制台贪吃蛇小游戏 
//日期：2018.04.03   
//
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<iostream>

#define left 0					// 离控制台最左边的距离 
#define top 0					// 离控制台最上边的距离 
#define high 20					// 游戏界面高 
#define width 20				// 游戏界面宽 
#define LENGTH (high*width)		// 蛇最长长度 
#define speed 300				// 游戏速度 
#define toup 72					// 蛇向上移动  72为方向键上的码值 
#define todown 80				// 蛇向下移动  80为方向键上的码值 
#define toleft 75				// 蛇向左移动  75为方向键上的码值  
#define toright 77				// 蛇向右移动  77为方向键上的码值 
using namespace std;

typedef struct {
	int snk_x[LENGTH];			// 存放蛇每一个点的x坐标 
	int snk_y[LENGTH];			// 存放蛇每一个点的y坐标
	int length;					// 蛇现在长度 
	int direction;				// 蛇现在移动方向 
}snake;//蛇结构体 

snake snk={{0},{0},3,toright};	// 初始化蛇 
int tail_x=0,tail_y=0;			// 记录蛇尾巴的上一个值，用来清屏 
int food_x,food_y;				// 记录食物位置 

//设置输出内容颜色 
void SetColor(int ForeColor=5,int BackColor=8){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BackColor*16+ForeColor);
}

/*void SetColor_light(unsigned short BackColor=0,unsigned short ForeColor=5,unsigned short LightColor=8){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BackColor|ForeColor|LightColor);
}*/ //设置输出亮度 

//移动坐标 
void gotoxy(int x,int y){
	COORD point;
	point.X=x;
	point.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);
}

//初始化游戏界面 
void init_wall(){
	SetColor(0x9,0x3);
	for(int i=0;i<width;i++){
		gotoxy(0,i);
		for(int j=0;j<20;j++){
			gotoxy(2*i,j);
			cout << "■";
		}
	}
}

//产生一个食物 
void init_food(){
	SetColor/*_light*/(0xc,0x3);
	food_x=2*(rand()%width)+left;
	food_y=rand()%high+top;
	if(food_x<left||food_x>=left+2*width||food_y<top||food_y>=top+high)	init_food();//食物不能在游戏界面外 
	for(int i=snk.length - 1; i >= 0; --i){											//食物不能在蛇身上 
        if (snk.snk_x[i]==food_x&&snk.snk_y[i]==food_y){
            init_food();
        }
    }
	gotoxy(food_x,food_y);cout<<"★";
}

//判断是否吃到食物，吃到产生新的事物 
void eat_food(){
	if(snk.snk_x[snk.length-1]==food_x&&snk.snk_y[snk.length-1]==food_y){
		gotoxy(food_x,food_y);cout<<"■";
		snk.length++;
		init_food();	
		for (int i = snk.length-1; i > 0 ; i--) {
			snk.snk_x[i] = snk.snk_x[i - 1];
			snk.snk_y[i] = snk.snk_y[i - 1];
		}
		snk.snk_x[0] = tail_x;
		snk.snk_y[0] = tail_y;
	}	
}

//初始化蛇 
void init_snake(){
	snk.snk_x[0]=left+width;
	snk.snk_y[0]=top+high/2;
	for (int i = 1; i < snk.length; ++i) {
		snk.snk_x[i] = snk.snk_x[i - 1] + 2;
		snk.snk_y[i] = snk.snk_y[i - 1];
	}
	snk.snk_x[0]=tail_x,snk.snk_y[0]=tail_y;
}

//输出蛇 
void out_snake(){
	//"○", "●"■
	SetColor(0x9,0x3);
	gotoxy(tail_x,tail_y);cout<<"■";
	SetColor/*_light*/(0xe,0x3);
	gotoxy(left+5*width/2,top+high/2);cout<<"score: "<<snk.length-3; 
	gotoxy(snk.snk_x[snk.length-1],snk.snk_y[snk.length-1]);cout<<"○";
	for(int i=0;i<snk.length-1;i++){
		gotoxy(snk.snk_x[i],snk.snk_y[i]);cout<<"●";
	}
	
}

//移动蛇 
void move_snake(){
	//gotoxy(snk.snk_x[0],snk.snk_y[0]);cout <<"   ";
	tail_x=snk.snk_x[0],tail_y=snk.snk_y[0];
	if(snk.direction==toright){
		for (int i = 0;i<snk.length-1;  i++) {
			snk.snk_x[i] = snk.snk_x[i + 1];
			snk.snk_y[i] = snk.snk_y[i + 1];
		}
		snk.snk_x[snk.length-1]=snk.snk_x[snk.length-1]+2;
	}
	if(snk.direction==toup){
		for (int i = 0;i<snk.length-1;  i++) {
			snk.snk_x[i] = snk.snk_x[i + 1];
			snk.snk_y[i] = snk.snk_y[i + 1];
		}
		snk.snk_y[snk.length-1]=snk.snk_y[snk.length-1]-1;
	}
	if(snk.direction==toleft){
		for (int i = 0;i<snk.length-1;  i++) {
			snk.snk_x[i] = snk.snk_x[i + 1];
			snk.snk_y[i] = snk.snk_y[i + 1];
		}
		snk.snk_x[snk.length-1]=snk.snk_x[snk.length-1]-2;
	}	
	if(snk.direction==todown){
		for (int i = 0;i<snk.length-1;  i++) {
			snk.snk_x[i] = snk.snk_x[i + 1];
			snk.snk_y[i] = snk.snk_y[i + 1];
		}
		snk.snk_y[snk.length-1]=snk.snk_y[snk.length-1]+1;
	}
	
}

//响应键盘操作 
int keyPush() {
	char ch = getch();
	if (ch == 27) {//esc退出 
		return 1;
	}
	if (ch == 's') {//暂停 
		getch();
	}
	if (ch == -32) {
		ch = getch();
		if ((ch == toup || ch == todown || ch == toleft || ch == toright)) {
			if (ch == toup && snk.direction == todown) {
				return 0;
			}
			else if (ch == todown && snk.direction == toup) {
				return 0;
			}
			else if (ch == toleft && snk.direction == toright) {
				return 0;
			}
			else if (ch == toright && snk.direction == toleft) {
				return 0;
			}
			snk.direction = ch;
		}
	}
	return 0;
}

//判断蛇是否死了 
int died(){
	if(snk.snk_x[snk.length-1]<left||snk.snk_x[snk.length-1]>=left+2*width||snk.snk_y[snk.length-1]<top||snk.snk_y[snk.length-1]>=top+high){
		return 1;
	}
	for(int i=snk.length - 2; i >= 0; --i){
        if ((snk.snk_x[i]==snk.snk_x[snk.length - 1])
            && (snk.snk_y[i]==snk.snk_y[snk.length - 1])){
            return 1;
        }
    }
	return 0;
}

//选择是否再来一遍 
int play_again(){
	system("cls");
	gotoxy(width,high/2);cout <<"gameover";Sleep(1000);
	cout<<"play again? y/n?";
	char ch;
	cin>>ch;
	if(ch=='Y'||ch=='y')	return 1;
	else return 0;	
}

int main()
{
	do{
		srand(time(0));	
		init_wall();
		init_food();
		init_snake();
		out_snake();
		Sleep(200);
		do{
			if(_kbhit()) {
				if(keyPush()) {
					break;
				}
			}
			move_snake();
			eat_food();
			out_snake();
			Sleep(speed);
		}while(!died());
	}while(play_again());
	system("pause");
	return 0;
}

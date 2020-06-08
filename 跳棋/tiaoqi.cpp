#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<vector>
#include <iomanip>
#include <stdio.h>
#include<iomanip>

using namespace std;
const int maxn = 100 + 5;

int Num;//棋子编号
int playmap[maxn][maxn];//玩家棋谱
int G[maxn][maxn];   //AI棋谱
int g[maxn][maxn];   //存编号id
int path[maxn];      //存每个节点的父节点，即路径
int n, m;             //n行   m列
int vx[4] = { -1,1,0,0 };   //一个节点周围上下左右4个节点
int vy[4] = { 0,0,-1,1 };
bool vis[maxn][maxn];     //标记某节点是否已经被访问过

int max1 = 0; int max2 = 0; int max3 = 0; int max4 = 0; int max5 = 0;
int i2, j2;
int lastx, lasty, lastnum;
int Sx, Sy, Fx, Fy;
bool allow;//标记玩家操作是否合法
double playloss;
int s;
int Time = 0;//回合数

struct node//定义bfs节点
{
	int x;
	int y;
	int id;
	int parent = 0;
	node(int a, int b, int c)
	{
		x = a;
		y = b;
		id = c;
	}
};


struct chess//棋子结构体
{
	int x;
	int y;
	int num;
	int xx;
	int yy;
	
	chess(int a, int b, int c, int d, int e)
	{
		x = a;
		y = b;
		xx= c;
		yy = d;
		num= e;
		
	}
};


void readmap() //读取txt文件
{
	FILE* file;
	freopen_s(&file, "tiaoqi.txt", "r", stdin);
	memset(G, 0, sizeof(G));
	memset(playmap, 0, sizeof(playmap));

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> G[i][j];
		}
}

int max(int a,int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

double countcost(int a,int b,int c,int d)//计算单步平均行程
{

	int sx, sy;
	int fx, fy;
	sx = a;
	sy = b;
	fx = c;
	fy = d;
	if (sx == fx && sy == fy)//判断棋子是否抵达目标位置
		return 0;
	else
	{
		i2 = 0;
		j2 = 0;
		int k = 1;//记录编号
		memset(vis, 0, sizeof(vis));
		memset(path, 0, sizeof(path));
		memset(g, 0, sizeof(g));
		queue<node> q;
		queue<node> q1;
		node v = node(sx, sy, 1);
		q.push(v);
		vis[sx][sy] = 1;
		while (!q.empty())
		{
			node u = q.front();
			q.pop();
			path[u.id] = u.parent;//记录每个点的父节点
			g[u.x][u.y] = u.id;//记录每个坐标的编号
			for (int i = 0; i < 4; i++)
			{
				int tx = u.x + vx[i];
				int ty = u.y + vy[i];
				if (G[tx][ty] && !vis[tx][ty])//有路可走且未访问
				{
					vis[tx][ty] = 1;
					//cout<<tx<<ty<<endl;
					node v = node(tx, ty, ++k);

					v.parent = u.id;
					q.push(v);
				}
				else if (!G[tx][ty])//有墙可跳
					for (int num2 = 1; num2 <= max(m,n); num2++)//间隔若干个墙
					{
						int nx = u.x + num2 * vx[i];
						int ny = u.y + num2 * vy[i];
						if (G[nx][ny] == 1 && !vis[nx][ny])//墙对面有空地且未访问
						{

							node vv = node(nx, ny, ++k);//跳跃点入队
							vv.parent = u.id;
							q.push(vv);

							node v1 = node(nx, ny, k);
							v1.parent = u.id;
							q1.push(v1);

							vis[nx][ny] = 1;
							while (!q1.empty())//跳跃点判断能否连跳
							{
								node u1 = q1.front();
								q1.pop();
								for (int i = 0; i < 4; i++)
								{
									int tx = u1.x + vx[i];
									int ty = u1.y + vy[i];
									if (!G[tx][ty])
									{
										for (int num3 = 1; num3 <= max(m, n); num3++)
										{
											int mx = u1.x + num3 * vx[i];
											int my = u1.y + num3 * vy[i];
											if (G[mx][my] == 1 && !vis[mx][my])//连跳点未被标记
											{
												node v2 = node(mx, my, k);//连跳点入队
												v2.parent = u.id;
												q1.push(v2);
												q.push(v2);
												vis[mx][my] = 1;
												break;
											}
											else if (vis[mx][my])//连跳点已被标记
												break;
										}
									}
								}
							}
							break;
						}
						else if (vis[nx][ny])//墙对面已标记
							break;
					}
			}
		}
		vector<int> ans;

		int fnum = 0;
		fnum = g[fx][fy];

		while (fnum)//从后面开始找父亲节点
		{
			ans.push_back(fnum);
			fnum = path[fnum];
		}
		s = 0;
		int idd = 0;
		while (!ans.empty())
		{
			s++;
			cout << *(ans.end() - 1) << ' ';//ans最后一个元素是0
			ans.pop_back();
			if (s == 1)
				idd = *(ans.end() - 1);//第一步移动所至位置id
		}
		if (s == 2)//判断玩家输入是否为单次移动
			allow = 1;
		else
			allow = 0;
			

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (g[i][j] == idd)//第一步移动所至位置x，y
				{
					i2 = i;
					j2 = j;
				}
		cout << "步数为" << s - 1 << endl;
		cout << "距离为" << abs(sx - fx) + abs(sy - fy) << endl;
		return (abs(static_cast<double>(sx) - static_cast<double>(fx)) + abs(static_cast<double>(sy) - static_cast<double>(fy))) / (abs(static_cast<double>(i2) - static_cast<double>(fx)) + abs(static_cast<double>(j2) - static_cast<double>(fy)));
	}
}

void playmove() {
	allow = 0;
	while (!allow)//判断玩家输入合法性
	{
		cout << "第" << Time << "回合" << endl;
		cout << "选择移动棋子的初始位置" << endl;
		scanf_s("%d", &Sx);
		scanf_s("%d", &Sy);
		cout << "选择移动棋子的中止位置" << endl;
		scanf_s("%d", &Fx);
		scanf_s("%d", &Fy);
		
		if (Sx <= n && Sy <= m && Fx <= n && Fy <= m)
		{
			countcost(Sx, Sy, Fx, Fy);
			if (allow == 0)
				cout << "该位置不可移动，请重新输入" << endl;
			else
			{
				G[Sx][Sy] = 1;
				G[Fx][Fy] = 0;
				playmap[Sx][Sy] = 0;
				playmap[Fx][Fy] = 1;
			}
		}
		else
			cout << "该位置不存在，请重新输入" << endl;
	}
	
}
queue<chess> Chess;
void AImove() {

	double lossmax =0;
	max1 = 0;
	for (int i = 0; i <= static_cast<int>(Chess.size()); i++)//判断能够移动的所有棋子当前最优决策
	{
		chess u = Chess.front();
		Chess.pop();
		double loss = countcost(u.x, u.y, u.xx, u.yy);
		if (lossmax >= loss || s == 0)
		{
			chess num7 = chess(u.x, u.y, u.xx, u.yy, u.num);
			Chess.push(num7);
		}

		else if (loss == 0)//棋子已抵达目标
			continue;
		else if (lossmax < loss)//最优棋子
		{
			lossmax = loss;
			if (max1)
			{
				chess num6 = chess(max1, max2, max3, max4, max5);
				Chess.push(num6);
			}
			max1 = u.x;
			max2 = u.y;
			max3 = u.xx;
			max4 = u.yy;
			max5 = u.num;
		}

	}
	cout << lossmax << endl;

}




int main()
{
	readmap();//读取txt文件
	Num = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (G[i][j] == 0)
			{	
				playmap[n + 1 - i][m + 1 - j] = 1;//生成玩家棋子
				chess num5 = chess(i, j, n-i/2+1, m+1-j, Num);//将AI棋子入队
				Chess.push(num5);
				Num++;
			}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (playmap[i][j] == 1)//将玩家棋子加入棋盘
				G[i][j] = 0;


	FILE* file;
	freopen_s(&file, "CON", "r", stdin);
	

	while (!Chess.empty())//开始循环队列
	{

		for (int i = 1; i <= n; i++)//显示棋盘
			for (int j = 1; j <= m; j++)
			{
				if(j==1)
					cout << setw(3) << i<<" ";
				if (!G[i][j]&& !playmap[i][j])
					cout << " * ";
				else if (G[i][j] == 1 && !playmap[i][j])
					cout << " _ ";
				if (playmap[i][j] == 1)
					cout << " # ";
				if (j == m)
					cout << "\n";
			}
		cout << "\n";
		playmove();//玩家移动
		AImove();//AI移动
		if (lastx == max1 && lasty == max2 && lastnum == max5)//检测AI最后的棋子是否到位，或跳出循环
			break;

		lastx = max1; lasty = max2; lastnum = max5;
		double haha = countcost(max1, max2, max3, max4);
		chess num8 = chess(i2, j2, max3, max4, max5);
		Chess.push(num8);
		cout << max1 << " " << max2 << endl;
		G[max1][max2] = 1;
		G[i2][j2] = 0;
		Time++;
		system("cls");
	
	}
	cout<<endl << "电脑获得了胜利";//并没有玩家获得了胜利。。。
}

	

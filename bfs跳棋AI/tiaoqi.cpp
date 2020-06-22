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

int Num;//���ӱ��
int playmap[maxn][maxn];//�������
int G[maxn][maxn];   //AI����
int g[maxn][maxn];   //����id
int path[maxn];      //��ÿ���ڵ�ĸ��ڵ㣬��·��
int n, m;             //n��   m��
int vx[4] = { -1,1,0,0 };   //һ���ڵ���Χ��������4���ڵ�
int vy[4] = { 0,0,-1,1 };
bool vis[maxn][maxn];     //���ĳ�ڵ��Ƿ��Ѿ������ʹ�

int max1 = 0; int max2 = 0; int max3 = 0; int max4 = 0; int max5 = 0;
int i2, j2;
int lastx, lasty, lastnum;
int Sx, Sy, Fx, Fy;
bool allow;//�����Ҳ����Ƿ�Ϸ�
double playloss;
int s;
int Time = 0;//�غ���

struct node//����bfs�ڵ�
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


struct chess//���ӽṹ��
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


void readmap() //��ȡtxt�ļ�
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

double countcost(int a,int b,int c,int d)//���㵥��ƽ���г�
{

	int sx, sy;
	int fx, fy;
	sx = a;
	sy = b;
	fx = c;
	fy = d;
	if (sx == fx && sy == fy)//�ж������Ƿ�ִ�Ŀ��λ��
		return 0;
	else
	{
		i2 = 0;
		j2 = 0;
		int k = 1;//��¼���
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
			path[u.id] = u.parent;//��¼ÿ����ĸ��ڵ�
			g[u.x][u.y] = u.id;//��¼ÿ������ı��
			for (int i = 0; i < 4; i++)
			{
				int tx = u.x + vx[i];
				int ty = u.y + vy[i];
				if (G[tx][ty] && !vis[tx][ty])//��·������δ����
				{
					vis[tx][ty] = 1;
					//cout<<tx<<ty<<endl;
					node v = node(tx, ty, ++k);

					v.parent = u.id;
					q.push(v);
				}
				else if (!G[tx][ty])//��ǽ����
					for (int num2 = 1; num2 <= max(m,n); num2++)//������ɸ�ǽ
					{
						int nx = u.x + num2 * vx[i];
						int ny = u.y + num2 * vy[i];
						if (G[nx][ny] == 1 && !vis[nx][ny])//ǽ�����пյ���δ����
						{

							node vv = node(nx, ny, ++k);//��Ծ�����
							vv.parent = u.id;
							q.push(vv);

							node v1 = node(nx, ny, k);
							v1.parent = u.id;
							q1.push(v1);

							vis[nx][ny] = 1;
							while (!q1.empty())//��Ծ���ж��ܷ�����
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
											if (G[mx][my] == 1 && !vis[mx][my])//������δ�����
											{
												node v2 = node(mx, my, k);//���������
												v2.parent = u.id;
												q1.push(v2);
												q.push(v2);
												vis[mx][my] = 1;
												break;
											}
											else if (vis[mx][my])//�������ѱ����
												break;
										}
									}
								}
							}
							break;
						}
						else if (vis[nx][ny])//ǽ�����ѱ��
							break;
					}
			}
		}
		vector<int> ans;

		int fnum = 0;
		fnum = g[fx][fy];

		while (fnum)//�Ӻ��濪ʼ�Ҹ��׽ڵ�
		{
			ans.push_back(fnum);
			fnum = path[fnum];
		}
		s = 0;
		int idd = 0;
		while (!ans.empty())
		{
			s++;
			cout << *(ans.end() - 1) << ' ';//ans���һ��Ԫ����0
			ans.pop_back();
			if (s == 1)
				idd = *(ans.end() - 1);//��һ���ƶ�����λ��id
		}
		if (s == 2)//�ж���������Ƿ�Ϊ�����ƶ�
			allow = 1;
		else
			allow = 0;
			

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (g[i][j] == idd)//��һ���ƶ�����λ��x��y
				{
					i2 = i;
					j2 = j;
				}
		cout << "����Ϊ" << s - 1 << endl;
		cout << "����Ϊ" << abs(sx - fx) + abs(sy - fy) << endl;
		return (abs(static_cast<double>(sx) - static_cast<double>(fx)) + abs(static_cast<double>(sy) - static_cast<double>(fy))) / (abs(static_cast<double>(i2) - static_cast<double>(fx)) + abs(static_cast<double>(j2) - static_cast<double>(fy)));
	}
}

void playmove() {
	allow = 0;
	while (!allow)//�ж��������Ϸ���
	{
		cout << "��" << Time << "�غ�" << endl;
		cout << "ѡ���ƶ����ӵĳ�ʼλ��" << endl;
		scanf_s("%d", &Sx);
		scanf_s("%d", &Sy);
		cout << "ѡ���ƶ����ӵ���ֹλ��" << endl;
		scanf_s("%d", &Fx);
		scanf_s("%d", &Fy);
		
		if (Sx <= n && Sy <= m && Fx <= n && Fy <= m)
		{
			countcost(Sx, Sy, Fx, Fy);
			if (allow == 0)
				cout << "��λ�ò����ƶ�������������" << endl;
			else
			{
				G[Sx][Sy] = 1;
				G[Fx][Fy] = 0;
				playmap[Sx][Sy] = 0;
				playmap[Fx][Fy] = 1;
			}
		}
		else
			cout << "��λ�ò����ڣ�����������" << endl;
	}
	
}
queue<chess> Chess;
void AImove() {

	double lossmax =0;
	max1 = 0;
	for (int i = 0; i <= static_cast<int>(Chess.size()); i++)//�ж��ܹ��ƶ����������ӵ�ǰ���ž���
	{
		chess u = Chess.front();
		Chess.pop();
		double loss = countcost(u.x, u.y, u.xx, u.yy);
		if (lossmax >= loss || s == 0)
		{
			chess num7 = chess(u.x, u.y, u.xx, u.yy, u.num);
			Chess.push(num7);
		}

		else if (loss == 0)//�����ѵִ�Ŀ��
			continue;
		else if (lossmax < loss)//��������
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
	readmap();//��ȡtxt�ļ�
	Num = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (G[i][j] == 0)
			{	
				playmap[n + 1 - i][m + 1 - j] = 1;//�����������
				chess num5 = chess(i, j, n-i/2+1, m+1-j, Num);//��AI�������
				Chess.push(num5);
				Num++;
			}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (playmap[i][j] == 1)//��������Ӽ�������
				G[i][j] = 0;


	FILE* file;
	freopen_s(&file, "CON", "r", stdin);
	

	while (!Chess.empty())//��ʼѭ������
	{

		for (int i = 1; i <= n; i++)//��ʾ����
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
		playmove();//����ƶ�
		AImove();//AI�ƶ�
		if (lastx == max1 && lasty == max2 && lastnum == max5)//���AI���������Ƿ�λ��������ѭ��
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
	cout<<endl << "���Ի����ʤ��";//��û����һ����ʤ��������
}

	

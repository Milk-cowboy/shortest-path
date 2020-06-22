#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<vector>
#include <iomanip>
#include <stdio.h>
#include<iomanip>

using namespace std;
const int maxn = 20;

int Num;//���ӱ��
int G[maxn][maxn];   //AI����
int g[maxn][maxn];   //����id
int gk[maxn][maxn];  
int path[100];      //��bfs�ڵ�·��
int n, m;             //n��   m��
int k = 1,kk = 1,kkk = 1;//��¼���
int vx[4] = { -1,1,0,0 };   //һ���ڵ���Χ��������4���ڵ�
int vy[4] = { 0,0,-1,1 };
bool vis[maxn][maxn];     //���ĳ�ڵ��Ƿ��Ѿ������ʹ�
int Sx, Sy, Fx, Fy;
bool allow;//�����Ҳ����Ƿ�Ϸ�
int Time = 1;//�غ���
int depth,depth1;//���������
int bestqipu[maxn][maxn];
int sx, sy��fx, fy, fnum, s;
int lastx, lasty;
int bestqipan[maxn][maxn];
int Gg[maxn][maxn];
int path3[10000]; //��¼���ײ�����·��
int ID;
int win = 0;
int num1, num2;
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




struct qipu //�������ײ������ڵ�
{
	int qipan[maxn][maxn];
	int parent;
	double score;
	int flag;
	int id;
	qipu(int a, int b, int c, int a1, int b1, int d, double e, int f, int g)
	{
		qipan[a][b] = c;
		qipan[a1][b1] = 1;
		parent = d;
		score = e;
		flag = f;
		id = g;
	}
};


queue<qipu> q2;//������ֶ���

void readmap() //��ȡtxt�ļ�
{
	FILE* file;
	freopen_s(&file, "in.txt", "r", stdin);
	memset(G, 0, sizeof(G));
	cin >> depth;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> G[i][j];
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (G[i][j] == 0)
			{
				if (!q2.empty())
				{
					qipu u = q2.front();
					q2.pop();
					u.qipan[i][j] = 1;
					u.qipan[n + 1 - i][j] = 2;
					q2.push(u);
				}
				else
				{
					qipu u = qipu(i, j, 1, 0, 0, 0, 0, 0, 1);
					memset(u.qipan, 0, sizeof(u.qipan));
					u.qipan[i][j] = 1;
					u.qipan[n + 1 - i][j] = 2;
					q2.push(u);
				}

			}
		}
	qipu u = q2.front();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (u.qipan[i][j] != 0)
			{
				G[i][j] = 0;
			}
		}
	memset(Gg, 0, sizeof(Gg));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (u.qipan[i][j] == 0)
				Gg[i][j] = 1;
			else
				Gg[i][j] = 0;
		}
}

double max(double a, double b) {
	if (a >= b)
		return a;
	else
		return b;
}

double min(double a, double b) {
	if (a <= b)
		return a;
	else
		return b;
}

int sum(int a, int b) {

	return a + b;
}

int shortpath(int Gb[maxn][maxn],int a, int b, int c, int d)//�������·��
{

	int sx, sy;
	int fx, fy;
	sx = a;
	sy = b;
	fx = c;
	fy = d;
	int g1[maxn][maxn];
	bool vis1[maxn][maxn];
	int path1[2000];
	memset(vis1, 0, sizeof(vis1));
	memset(path1, 0, sizeof(path1));
	memset(g1, 0, sizeof(g1));
	queue<node> q5;
	q5 = queue<node>();
	queue<node> q6;
	q6 = queue<node>();
	node v = node(sx, sy, 1);
	q5.push(v);
	vis1[sx][sy] = 1;
	kkk = 1;
	while (!q5.empty())
	{

		node u = q5.front();
		q5.pop();
		path1[u.id] = u.parent;//��¼ÿ����ĸ��ڵ�
		g1[u.x][u.y] = u.id;//��¼ÿ������ı��
		for (int i = 0; i < 4; i++)
		{
			int tx = u.x + vx[i];
			int ty = u.y + vy[i];
			if (Gb[tx][ty] && !vis1[tx][ty])//��·������δ����
			{
				vis1[tx][ty] = 1;
				//cout<<tx<<ty<<endl;
				node v = node(tx, ty, ++kkk);
				v.parent = u.id;
				q5.push(v);
			}
			else if (!Gb[tx][ty])//��ǽ������δ����
				for (int num2 = 1; num2 <= max(m, n); num2++)
				{
					int nx = u.x + num2 * vx[i];
					int ny = u.y + num2 * vy[i];
					if (Gb[nx][ny] == 1 && !vis1[nx][ny])
					{

						node vv = node(nx, ny, ++kkk);
						vv.parent = u.id;
						q5.push(vv);

						node v1 = node(nx, ny, kkk);
						v1.parent = u.id;
						q6.push(v1);

						vis1[nx][ny] = 1;
						while (!q6.empty())
						{
							node u1 = q6.front();
							q6.pop();
							for (int i = 0; i < 4; i++)
							{
								int tx = u1.x + vx[i];
								int ty = u1.y + vy[i];
								if (!Gb[tx][ty])
								{
									for (int num3 = 1; num3 <= max(m, n); num3++)
									{
										int mx = u1.x + num3 * vx[i];
										int my = u1.y + num3 * vy[i];
										if (Gb[mx][my] == 1 && !vis1[mx][my])
										{
											node v2 = node(mx, my, kkk);
											v2.parent = u.id;
											q6.push(v2);
											q5.push(v2);
											vis1[mx][my] = 1;
											break;
										}
										else if (vis1[mx][my])
											break;
									}
								}
							}
						}
						break;
					}//Ѱ���ĸ�����ǽ����ƥ���
					else if (vis1[nx][ny])
						break;

				}
		}
	}

	vector<int> ans;
	ans.clear();
	fnum = g1[fx][fy];
	while (fnum)//�Ӻ��濪ʼ�Ҹ��׽ڵ�
	{
		ans.push_back(fnum);
		fnum = path1[fnum];
	}
	s = 0;

	while (!ans.empty())
	{
		s++;
		ans.pop_back();

	}
	
	return s - 1;
}


double countscore(int Gc[maxn][maxn], int a, int b, int c)//������������
{
	
	int minlosspath=1000;//��̵����յ�·��
	int gather = 0;//�ۼ��̶�
	int alllosspath = 0;//������̵����յ�·��
	int line = 0;//����λ��
	int arrive = 0;//���ӵִ��յ���
	int losspath = 0;//�����յ�·��
	memset(gk, 0, sizeof(gk));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			
			if (Gc[i][j] != 0)
				gk[i][j] = 0;
			else
				gk[i][j] = 1;
		}
	if (a == 1)
	{
		for (int ii = 1; ii <= n - 1; ii++)
			for (int jj = 1; jj <= m; jj++)
				if (Gc[ii][jj] == a)
				{
					for (int j = 1; j <= m; j++)
						if (Gc[n][j] == 0)
						{
							losspath = shortpath(gk,ii, jj, n, j);
							minlosspath = 1000;
							minlosspath = min(minlosspath, losspath);
						}
					alllosspath = sum(minlosspath, alllosspath);
				}
		for (int jj = 1; jj <= m; jj++)
		{
			int i = n;
			if (Gc[i][jj] == a)
				arrive++;
		}
		for (int ii = 1; ii <= n; ii++)
			for (int jj = 1; jj <= m; jj++)
				if (Gc[ii][jj] == a)
					line = sum(line, n-ii);
	}
	else if (a == 2)
	{
		for (int ii = 2; ii <= n; ii++)
			for (int jj = 1; jj <= m; jj++)
				if (Gc[ii][jj] == a)
				{
					for (int j = 1; j <= m; j++)
						if (Gc[1][j] == 0)
						{
							losspath = shortpath(gk,ii, jj, 1, j);
							minlosspath = 1000;
							minlosspath = min(minlosspath, losspath);
						}
					alllosspath = sum(minlosspath, alllosspath);
					
				}
		for (int jj = 1; jj <= m; jj++)
		{
			int i = 1;
			if (Gc[i][jj] == a)
				arrive++;
		}
		for (int ii = 1; ii <= n; ii++)
			for (int jj = 1; jj <= m; jj++)
				if (Gc[ii][jj] == a)
					line = sum(line, n-1);
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (Gc[i][j] == a)
			{
				gather = sum(gather, abs(b - i) + abs(c - j));
			}
	if (minlosspath == 1000)
		minlosspath = 0;

	double Score =( 8 * minlosspath + gather + 10 * line )/ (arrive*arrive+1);
	return 1 / Score;

}



void gettree()//�������ײ�����
{
	qipu u = q2.front();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (u.qipan[i][j] != 0)
			{
				G[i][j] = 0;
			}
		}
	int num = 1;
	u.score = 0;
	ID = 1;
	queue<qipu> q3;
	while (q2.front().flag < depth)
	{

		int Wtree = q2.size();
		for (int i = 1; i <= Wtree; i++)
		{
			qipu ub = q2.front();
			ub.flag++;
			q2.pop();
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
				{
					if (ub.qipan[i][j] != 0)
						G[i][j] = 0;
					else
						G[i][j] = 1;
				}


			for (int ixx = 1; ixx <= n; ixx++)
				for (int jyy = 1; jyy <= m; jyy++)
				{
					if (ub.qipan[ixx][jyy] == 1)
					{
						memset(vis, 0, sizeof(vis));
						memset(path, 0, sizeof(path));
						memset(g, 0, sizeof(g));
						queue<node> q;
						queue<node> q1;
						node v = node(ixx, jyy, 1);

						q.push(v);

						vis[ixx][jyy] = 1;
						k = 1;

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
								else if (!G[tx][ty])//��ǽ������δ����
									for (int num2 = 1; num2 <= max(m, n); num2++)
									{
										int nx = u.x + num2 * vx[i];
										int ny = u.y + num2 * vy[i];
										if (G[nx][ny] == 1 && !vis[nx][ny])
										{

											node vv = node(nx, ny, ++k);
											vv.parent = u.id;
											q.push(vv);

											node v1 = node(nx, ny, k);
											v1.parent = u.id;
											q1.push(v1);

											vis[nx][ny] = 1;
											while (!q1.empty())
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
															if (G[mx][my] == 1 && !vis[mx][my])
															{
																node v2 = node(mx, my, k);
																v2.parent = u.id;
																q1.push(v2);
																q.push(v2);
																vis[mx][my] = 1;
																break;
															}
															else if (vis[mx][my])
																break;
														}
													}
												}
											}
											break;
										}//Ѱ���ĸ�����ǽ����ƥ���
										else if (vis[nx][ny])
											break;

									}
							}
						}

						for (int ix = 1; ix <= n; ix++)
							for (int jy = 1; jy <= m; jy++)
								if (ub.qipan[ix][jy] != 1)
								{
									vector<int> ans;
									fnum = g[ix][jy];

									while (fnum)//�Ӻ��濪ʼ�Ҹ��׽ڵ�
									{
										ans.push_back(fnum);
										fnum = path[fnum];
									}
									s = 0;

									while (!ans.empty())
									{
										s++;
										ans.pop_back();

									}
									ans.clear();
									if (s == 2)
									{
										/*cout << "���ӿ��Ե���" << ix << " " << jy << endl;*/
										qipu us = ub;
										lastx = ix;
										lasty = jy;
										us.qipan[ix][jy] = 1;
										us.qipan[ixx][jyy] = 0;
										path3[ub.id] = ub.parent;
										us.id = ID;
										ID++;
										us.parent = ub.id;
										us.score += countscore(us.qipan, 1, lastx, lasty);
										q2.push(us);
										q3.push(us);

									}
								}
					}
				}
		}


		cout << endl;
		Wtree = q2.size();

		for (int i = 1; i <= Wtree; i++)
		{
			qipu ub = q2.front();
			ub.flag++;
			q2.pop();
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
				{
					if (ub.qipan[i][j] != 0)
						G[i][j] = 0;
					else
						G[i][j] = 1;
				}


			for (int ixx = 1; ixx <= n; ixx++)
				for (int jyy = 1; jyy <= m; jyy++)
				{
					if (ub.qipan[ixx][jyy] == 2)
					{
						memset(vis, 0, sizeof(vis));
						memset(path, 0, sizeof(path));
						memset(g, 0, sizeof(g));
						queue<node> q;
						queue<node> q1;
						node v = node(ixx, jyy, 1);

						q.push(v);

						vis[ixx][jyy] = 1;
						k = 1;

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
								else if (!G[tx][ty])//��ǽ������δ����
									for (int num2 = 1; num2 <= max(m, n); num2++)
									{
										int nx = u.x + num2 * vx[i];
										int ny = u.y + num2 * vy[i];
										if (G[nx][ny] == 1 && !vis[nx][ny])
										{

											node vv = node(nx, ny, ++k);
											vv.parent = u.id;
											q.push(vv);

											node v1 = node(nx, ny, k);
											v1.parent = u.id;
											q1.push(v1);

											vis[nx][ny] = 1;
											while (!q1.empty())
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
															if (G[mx][my] == 1 && !vis[mx][my])
															{
																node v2 = node(mx, my, k);
																v2.parent = u.id;
																q1.push(v2);
																q.push(v2);
																vis[mx][my] = 1;
																break;
															}
															else if (vis[mx][my])
																break;
														}
													}
												}
											}
											break;
										}//Ѱ���ĸ�����ǽ����ƥ���
										else if (vis[nx][ny])
											break;

									}
							}
						}

						for (int ix = 1; ix <= n; ix++)
							for (int jy = 1; jy <= m; jy++)
								if (ub.qipan[ix][jy] != 1)
								{
									vector<int> ans;
									fnum = g[ix][jy];

									while (fnum)//�Ӻ��濪ʼ�Ҹ��׽ڵ�
									{
										ans.push_back(fnum);
										fnum = path[fnum];
									}
									s = 0;

									while (!ans.empty())
									{
										s++;
										ans.pop_back();

									}
									ans.clear();
									if (s == 2)
									{
										/*cout << "����" << num << "���Ե���" << ix << " " << jy << endl;*/

										qipu us = ub;
										lastx = ix;
										lasty = jy;
										us.qipan[ix][jy] = 2;
										us.qipan[ixx][jyy] = 0;
										path3[ub.id] = ub.parent;
										us.id = ID;
										ID++;
										us.parent = ub.id;
										us.score -= countscore(us.qipan, 2, lastx, lasty);
										q2.push(us);
										q3.push(us);
									}
								}

						num++;

					}
				}
		}
	}


	queue<qipu> q4;
	queue<qipu> q9;
	while (depth > 1)
	{

		int lastparent = 0;

		while (!q3.empty())
		{
			qipu u = q3.front();
			q3.pop();
			if (u.flag == depth)
				q4.push(u);
			else
				q9.push(u);
		}

		vector<double> aans;
		if (depth % 2 == 0)
		{
			double maxscore1 = 100;
			double maxscore2 = 100;
			while (!q4.empty())
			{
				qipu u5 = q4.front();
				q4.pop();
				int newid = u5.parent;
				if (newid == lastparent || lastparent == 0)
				{
					maxscore1 = min(u5.score, maxscore1);
					lastparent = newid;
				}
				else if (newid > lastparent && lastparent != 0)
				{
					aans.push_back(maxscore1);
					maxscore1 = min(u5.score, maxscore2);
					lastparent = newid;

				}
			}
			aans.push_back(maxscore1);
		}
		else
		{
			double maxscore1 = -100;
			double maxscore2 = -100;
			while (!q4.empty())
			{
				qipu u5 = q4.front();
				q4.pop();
				int newid = u5.parent;
				if (newid == lastparent || lastparent == 0)
				{
					maxscore1 = max(u5.score, maxscore1);
					lastparent = newid;
				}
				else if (newid > lastparent && lastparent != 0)
				{
					aans.push_back(maxscore1);
					maxscore1 = max(u5.score, maxscore2);
					lastparent = newid;

				}
			}
			aans.push_back(maxscore1);
		}

		depth--;
		for (int i = 0; i < aans.size();)
		{
			qipu u8 = q9.front();
			q9.pop();

			if (u8.flag == depth)
			{
				u8.score = aans[i];
				i++;
			}
			q9.push(u8);
		}
		aans.clear();
		while (!q9.empty())
		{
			qipu u7 = q9.front();
			q9.pop();
			q3.push(u7);
		}

	}

	double	maxscore3 = -100;
	while (!q3.empty())
	{
		qipu u5 = q3.front();
		q3.pop();
		/*cout << "���Ե�" << endl;
		int abc = 0;
		if (abc < 1)
		{
			abc++;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)


				{
					cout << u5.qipan[i][j] << " ";
					if (j == m)
						cout << endl;
				}
		}
		cout << "���Ե�" << endl;
		cout << "�����Ϊ" << u5.score << endl;*/
		if (u5.score > maxscore3)
		{

			maxscore3 = max(u5.score, maxscore3);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
					bestqipu[i][j] = u5.qipan[i][j];

		}
	}
	qipu ug = q2.front();
	q2 = queue<qipu>();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			ug.qipan[i][j] = bestqipu[i][j];
		}
	ug.parent = 0;
	ug.score = 0;
	ug.flag = 0;
	ug.id = 1;
	q2.push(ug);
}

void AImove()//�����ƶ�
{
	depth = depth1;
	gettree();
	qipu u = q2.front();
	q2.pop();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			u.qipan[i][j] = bestqipu[i][j];

			if (bestqipu[i][j] != 0)
				G[i][j] = 0;
			else
				G[i][j] = 1;
		}
	q2.push(u);
	num2 = 0;
	for (int j = 1; j <= m; j++)
	{
		int i = 9;	
		if (u.qipan[i][j] == 1)
			num2++;
	}
	if (num2 == 6)
	{
		cout << "AI�����ʤ��" << endl;
		win = 1;
		system("pause");
	}

}



void playmove() //����ƶ�
{
	allow = 0;
	qipu u = q2.front();

	while (!allow)//�ж��������Ϸ���
	{
		cout << "��" << Time << "�غ�" << endl;
		cout << "ѡ���ƶ����ӵĳ�ʼλ��" << endl;
		scanf_s("%d", &Sx);
		scanf_s("%d", &Sy);
		cout << "ѡ���ƶ����ӵ���ֹλ��" << endl;
		scanf_s("%d", &Fx);
		scanf_s("%d", &Fy);
		if (Sx <= n && Sy <= m && Fx <= n && Fy <= m&& u.qipan[Sx][Sy] == 2)
		{
			int Allow;
			int gkk[maxn][maxn];
			memset(gkk, 0, sizeof(gkk));
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++)
				{

					if (u.qipan[i][j] != 0)
						gkk[i][j] = 0;
					else
						gkk[i][j] = 1;
				}
			Allow = shortpath(gkk,Sx, Sy, Fx, Fy);
			if (Allow == 1)
				allow = 1;
			if (allow == 0)
				cout << "��λ�ò����ƶ�������������" << endl;
			else
			{
				G[Sx][Sy] = 1;
				G[Fx][Fy] = 0;
				Gg[Sx][Sy] = 1;
				Gg[Fx][Fy] = 0;
				q2.pop();			
				u.qipan[Sx][Sy] = 0;
				u.qipan[Fx][Fy] = 2;
				q2.push(u);
			}
		}
		else
			cout << "��λ�ò����ڣ�����������" << endl;
	}


	num1 = 0;
	for (int j = 1; j <= m; j++)
	{
		int i = 1;		
		if (u.qipan[i][j] == 2)
			num1++;
	}
	if (num1 == 6)
	{
		cout << "��һ����ʤ��" << endl;
		win = 1;
		system("pause");
	}
}

int main()
{
	readmap();//��ȡtxt�ļ�
	Num = 1;
	depth1 = depth;
	
	FILE * file;
	freopen_s(&file, "CON", "r", stdin);



	while (!win)//��ʼѭ������
	{
		qipu u = q2.front();
	
		for (int i = 1; i <= n; i++)//��ʾ����
			for (int j = 1; j <= m; j++)
			{
				if (j == 1)
					cout << setw(3) << i << " ";
				if (u.qipan[i][j]==1)
					cout << " * ";
				else if (u.qipan[i][j] == 0)
					cout << " _ ";
				else if (u.qipan[i][j] == 2)
					cout << " # ";
				if (j == m)
					cout << "\n";
			}
		cout << "\n";
		
		//playmove();//����ƶ�
		AImove();//AI�ƶ�
		Time++;
		system("cls");
	}

}

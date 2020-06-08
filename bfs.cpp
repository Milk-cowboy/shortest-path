#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn = 100 + 5;

int G[maxn][maxn];   //存图的d=id
int g[maxn][maxn];   //存编号
int path[maxn];      //存每个节点的父节点，即路径
int n, m;             //n行   m列
int k = 1;//记录编号
int end_num;
int vx[5] = { -1,1,0,0 };   //vx  vy用来计算一个节点周围上下左右4个节点
int vy[5] = { 0,0,-1,1 };
bool vis[maxn][maxn];     //判断某节点是否已经被访问过
int sx, sy;
int fx, fy, fnum;
struct node
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


<<<<<<< HEAD
=======
void readmap() {
	FILE* file;
	freopen_s(&file,"in.txt","r",stdin);
	memset(G, 0, sizeof(G));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> G[i][j];
		}
}


>>>>>>> 6cf01d6... first commit

int main()
{	
	cout << "输入起点坐标" << endl;
	cin >> sx >> sy;
	cout << "起点坐标为" <<sx<<sy<< endl;
	cout << "输入终点坐标" << endl;
	cin >> fx >> fy;
	cout << "终点坐标为" << fx << fy << endl;
<<<<<<< HEAD
	freopen("in.txt","r",stdin);
	memset(G, 0, sizeof(G));
=======
	
	
>>>>>>> 6cf01d6... first commit
	memset(vis, 0, sizeof(vis));
	memset(path, 0, sizeof(path));
	memset(g, 0, sizeof(g));
	
<<<<<<< HEAD
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			cin >> G[i][j];
		}
=======
	readmap();
>>>>>>> 6cf01d6... first commit

	
	queue<node> q;
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
		}
	}
	vector<int> ans;

	
	fnum = g[fx][fy];
	for (int i=1;i<=n;i++ )
		for (int j = 1; j <= m; j++)
		{
			cout << g[i][j]<<" ";
			if (j == m)
				cout << "\n";
		}

	while (fnum)//从后面开始找父亲节点
	{
		ans.push_back(fnum);
		fnum = path[fnum];
	}
	int s = 0;
	while (!ans.empty())
	{
		s++;
		cout << *(ans.end() - 1) << ' ';//ans最后一个元素是0
		ans.pop_back();
	}
	cout << endl << s - 1;
	return 0;
}


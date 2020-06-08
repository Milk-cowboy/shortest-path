#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn = 100 + 5;

int G[maxn][maxn];   //��ͼ��d=id
int g[maxn][maxn];   //����
int path[maxn];      //��ÿ���ڵ�ĸ��ڵ㣬��·��
int n, m;             //n��   m��
int k = 1;//��¼���
int end_num;
int vx[5] = { -1,1,0,0 };   //vx  vy��������һ���ڵ���Χ��������4���ڵ�
int vy[5] = { 0,0,-1,1 };
bool vis[maxn][maxn];     //�ж�ĳ�ڵ��Ƿ��Ѿ������ʹ�
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
	cout << "�����������" << endl;
	cin >> sx >> sy;
	cout << "�������Ϊ" <<sx<<sy<< endl;
	cout << "�����յ�����" << endl;
	cin >> fx >> fy;
	cout << "�յ�����Ϊ" << fx << fy << endl;
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

	while (fnum)//�Ӻ��濪ʼ�Ҹ��׽ڵ�
	{
		ans.push_back(fnum);
		fnum = path[fnum];
	}
	int s = 0;
	while (!ans.empty())
	{
		s++;
		cout << *(ans.end() - 1) << ' ';//ans���һ��Ԫ����0
		ans.pop_back();
	}
	cout << endl << s - 1;
	return 0;
}


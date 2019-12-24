/* **************************************************
 *                  数据结构课程设计
 *    题    目  交通换乘规划
 *    姓    名  黄远鹏      学    号  183401050225
 *    班    级  软件1802
 *    指导教师  滕一平
 * ************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

#define MAXSIZE 100   // 最大顶点数
#define INF 0x3f3f3f3f   // 无穷大
enum vehicle_type { subway, normal_bus, air_bus, none = INF };

struct edge
{
	string name;
	vehicle_type type;
	edge():type(none) {}
	edge(char _name[], vehicle_type _type):name(_name), type(_type) {}
};

class graph
{
private:
	int vertexNum;   // 总顶点数
	string vertices[MAXSIZE];   // 顶点信息
	unordered_map<string, size_t> index;   // 根据顶点信息找到对应下标
	edge adjM[MAXSIZE][MAXSIZE];   // 邻接矩阵
	bool insertVertex(string station_name);   // 增加顶点
	int findMin(int dist[], bool collected[]);   // lessTime()的辅助函数
public:
	graph():vertexNum(0) {};
	bool isVertexInGraph(string vertex_name);   // 判断某点是否在图内
	bool insertEdge(string vertex1_name, string vertex2_name, edge new_edge);   // 插入边
	void lessTime(string src_name, string dst_name);   // 输出"时间短"换乘方案
	void subwayOnly(string src_name, string dst_name);   // 输出"只坐地铁"换乘方案
};

bool graph::isVertexInGraph(string vertex_name)
{
	return (index.find(vertex_name) != index.end());
}
bool graph::insertVertex(string vertex_name)
{
	if(isVertexInGraph(vertex_name))   // 已有该顶点，无需插入
		return false;
	vertices[vertexNum] = vertex_name;   // 增加一个顶点并初始化相关信息
	index[vertex_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string vertex1_name, string vertex2_name, edge new_edge)
{
	insertVertex(vertex1_name);
	insertVertex(vertex2_name);
	size_t vertex1_index = index[vertex1_name], vertex2_index = index[vertex2_name];
	if(adjM[vertex1_index][vertex2_index].type != none)   // 已有这条边，无需插入
		return false;
	adjM[vertex1_index][vertex2_index] = new_edge;   // 插入新边
	adjM[vertex2_index][vertex1_index] = new_edge;
	return true;
}
int graph::findMin(int time[], bool collected[])
{
	int min_index, min_time = INF;
	for(int i = 0; i < vertexNum; i++)
	{
		if(collected[i] == false && time[i] < min_time)
		{
			min_time = time[i];
			min_index = i;
		}
	}
	return min_time == INF ? -1 : min_index;   // 未找到返回-1
}
void graph::lessTime(string src_name, string dst_name)
{
	system("title 交通换乘规划 - 时间最短的乘车方案");
	size_t src = index[src_name], dst = index[dst_name];
	int time[MAXSIZE], path[MAXSIZE];
	bool collected[MAXSIZE];
	for(int i = 0; i < vertexNum; i++)
	{
		switch(adjM[src][i].type)
		{
			case subway:     time[i] = 3; break;   // 地铁3min走一站
			case normal_bus: time[i] = 7; break;   // 公交7min走一站
			case air_bus:    time[i] = 7; break;
			case none:       time[i] = none; break;   // 没有直达路径，初始化为none(用无穷大表示)
		}
		if(time[i] != none)   // 与起点直接相连的点
			path[i] = src;
		else
			path[i] = -1;
		collected[i] = false;
	}
	time[src] = 0;
	collected[src] = true;
	while(true)
	{
		int min = findMin(time, collected);
		if(min == -1)
			break;
		collected[min] = true;
		for(int i = 0; i < vertexNum; i++)
		{
			if(collected[i] == false && adjM[min][i].type != none)
			{
				int new_time;
				switch(adjM[min][i].type)
				{
					case subway:     new_time = 3; break;
					case normal_bus: new_time = 7; break;
					case air_bus:    new_time = 7; break;
				}
				if(time[min] + new_time < time[i])
				{
					time[i] = time[min] + new_time;
					path[i] = min;
				}
			}
		}
	}
	if(time[dst] == INF)
	{
		printf("从 %s 到 %s 暂无换乘路径，建议您采用其它出行方式。\n\n",
			src_name.c_str(), dst_name.c_str());
		system("pause");
		return;
	}
	size_t temp = dst;
	stack<size_t> st;   // 用于暂存最短路径
	st.push(dst);
	while(path[temp] != -1)
	{
		st.push(path[temp]);
		temp = path[temp];
	}
	printf("从 %s 到 %s 时间最短的乘车方案：\n\n", src_name.c_str(), dst_name.c_str());
	temp = st.top();
	st.pop();
	string line;
	vehicle_type type = none;
	int cost = 0, subwayStation_cnt = 0;   // 所需费用，乘坐地铁站数
	while(true)
	{
		cout << vertices[temp];
		if(st.empty() || adjM[temp][st.top()].name != line)
		{
			if(st.empty() || adjM[temp][st.top()].type != type)
			{   // 在终点处或改换交通方式时计算费用
				if(type == subway)   // 地铁按乘坐站数收费
				{
					if(subwayStation_cnt <= 7)   // 0-7站，3元
						cost += 3;
					else if(subwayStation_cnt <= 14)   // 8-14站，5元
						cost += 5;
					else   // 大于14站，8元
						cost += 8;
					subwayStation_cnt = 0;
				}
				else if(type == normal_bus)   // 普通公交1元
					cost += 1;
				else if(type == air_bus)   // 空调公交2元
					cost += 2;
			}

			if(st.empty())   // 在终点处退出循环
				break;
			line = adjM[temp][st.top()].name;   // 在换乘站更新换乘信息
			type = adjM[temp][st.top()].type;
			cout << "（" << line << "）";
		}
		if(adjM[temp][st.top()].type == subway)   // 乘坐地铁要累计站数
			subwayStation_cnt++;
		temp = st.top();
		st.pop();
		cout << " -> ";
	}
	cout << endl << "总用时：" << time[dst] << "分钟，";
	cout << "费用：" << cost << "元" << endl << endl;
	system("pause");
}
void graph::subwayOnly(string src_name, string dst_name)
{
	system("title 交通换乘规划 - 只坐地铁的乘车方案");
	size_t src = index[src_name], dst = index[dst_name];
	int dist[MAXSIZE], path[MAXSIZE];
	memset(dist, -1, sizeof(dist));
	memset(path, -1, sizeof(path));
	dist[src] = 0;
	queue<size_t> qu;
	qu.push(src);
	while(!qu.empty())
	{
		size_t t = qu.front();
		qu.pop();
		for(int i = 0; i < vertexNum; i++)
		{
			if(adjM[t][i].type == subway && dist[i] == -1)
			{
				dist[i] = dist[t] + 1;
				path[i] = t;
				qu.push(i);
			}
		}
	}
	if(dist[dst] == -1)
	{
		printf("从 %s 仅乘坐地铁无法到达 %s，建议您更换乘车方案或采用其它出行方式。\n\n",
			src_name.c_str(), dst_name.c_str());
		system("pause");
		return;
	}
	size_t temp = dst;
	stack<size_t> st;
	st.push(dst);
	while(path[temp] != -1)
	{
		st.push(path[temp]);
		temp = path[temp];
	}
	printf("从 %s 到 %s 只坐地铁的乘车方案：\n\n", src_name.c_str(), dst_name.c_str());
	temp = st.top();
	st.pop();
	string line;
	while(true)
	{
		cout << vertices[temp];
		if(st.empty())   // 到达终点，退出循环
			break;
		if(adjM[temp][st.top()].name != line)
		{
			line = adjM[temp][st.top()].name;   // 在换乘站更新换乘信息
			cout << "（" << line << "）";
		}
		temp = st.top();
		st.pop();
		cout << " -> ";
	}
	cout << endl << "总用时：" << dist[dst] * 3 << "分钟，";
	int cost;
	if(dist[dst] <= 7)   // 0-7站，3元
		cost = 3;
	else if(dist[dst] <= 14)   // 8-14站，5元
		cost = 5;
	else   // 大于14站，8元
		cost = 8;
	cout << "费用：" << cost << "元" << endl << endl;
	system("pause");
}

graph map;
void loadMap()   // 加载地图
{
	system("title 交通换乘规划 - 加载地图");
	printf("     交通换乘规划：加载地图\n\n");
	printf("请输入地图文件名，以回车结束：");
	char mapFileName[256];
	cin.getline(mapFileName, 256);
	FILE *fp = fopen(mapFileName, "r");
	while(fp == NULL)   // 若文件打开失败，则重新输入文件名直至打开成功
	{
		printf("\n文件打开失败，请检查文件名是否输入正确以及文件是否存在。\n\n");
		printf("请重新输入：");
		cin.getline(mapFileName, 256);
		fp = fopen(mapFileName, "r");
	}
	printf("\n请稍候. . . \n\n");
	int n;
	fscanf(fp, "%d", &n);
	char name[256];   // 线路名称
	int num, type, isCycle;   // 线路站点数  地铁0/普通公交1/空调公交2  是否环线
	for(int i = 0; i < n; i++)
	{
		fscanf(fp, "%s%d%d%d\n", name, &num, &type, &isCycle);
		char v1[256], v2[256];
		for(int j = 0; j < num - 1 + isCycle; j++)
		{
			fscanf(fp, "%s%s\n", v1, v2);
			map.insertEdge(v1, v2, edge(name, (vehicle_type)type));
		}
	}
	fclose(fp);
	printf("地图加载成功。");
	system("pause");
}
void inputSrc(string &src)   // 输入起点
{
	printf("\n请输入起点：");
	getline(cin, src);
	while(!map.isVertexInGraph(src))   // 未找到这个起点
	{
		if(src.size() > 2   // 长度大于2
			&& src.substr(src.size() - 2, src.size()) == "站"   // 最后一个字是"站"
			&& map.isVertexInGraph(src.substr(0, src.size() - 2)))   // 去掉"站"字后该点存在
		{
			src = src.substr(0, src.size() - 2);   // 用户输入多了一个"站"字，去掉即可
			break;
		}
		printf("\n未查找到您输入的地址，请重新输入起点：");
		getline(cin, src);
	}
}
void inputDst(string &dst, const string &src)   // 输入终点
{
	printf("\n请输入终点：");
	getline(cin, dst);
	while(!map.isVertexInGraph(dst) || dst == src)   // 未找到这个终点或起点与终点相同
	{
		if(dst.size() > 2 && dst.substr(dst.size() - 2, dst.size()) == "站"
			&& map.isVertexInGraph(dst.substr(0, dst.size() - 2))
			&& dst.substr(0, dst.size() - 2) != src)   // 去掉"站"字后不与起点相同
		{
			dst = dst.substr(0, dst.size() - 2);   // 用户输入多了一个"站"字，去掉即可
			break;
		}
		printf("\n未查找到您输入的地址或终点与起点相同，请重新输入终点：");
		getline(cin, dst);
	}
}
int main()
{
	system("color fc");
	loadMap();
	string src, dst, choice;
	while(true)
	{
		system("cls");
		system("title 交通换乘规划");
		printf("     交通换乘规划\n");
		fflush(stdin);
		inputSrc(src);
		inputDst(dst, src);
		printf("\n请选择乘车方案：\n");
		printf("     1 - 时间短\n");
		printf("     2 - 只坐地铁\n");
		printf("\n请输入：");
		getline(cin, choice);
		switch(choice[0])
		{
			case '1':system("cls"); map.lessTime(src, dst);     break;
			case '2':system("cls"); map.subwayOnly(src, dst);   break;

			default:printf("输入错误，请重新输入。"); system("pause"); break;
		}
	}
	return 0;
}
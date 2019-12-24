/* **************************************************
 *                  ���ݽṹ�γ����
 *    ��    Ŀ  ��ͨ���˹滮
 *    ��    ��  ��Զ��      ѧ    ��  183401050225
 *    ��    ��  ���1802
 *    ָ����ʦ  ��һƽ
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

#define MAXSIZE 100   // ��󶥵���
#define INF 0x3f3f3f3f   // �����
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
	int vertexNum;   // �ܶ�����
	string vertices[MAXSIZE];   // ������Ϣ
	unordered_map<string, size_t> index;   // ���ݶ�����Ϣ�ҵ���Ӧ�±�
	edge adjM[MAXSIZE][MAXSIZE];   // �ڽӾ���
	bool insertVertex(string station_name);   // ���Ӷ���
	int findMin(int dist[], bool collected[]);   // lessTime()�ĸ�������
public:
	graph():vertexNum(0) {};
	bool isVertexInGraph(string vertex_name);   // �ж�ĳ���Ƿ���ͼ��
	bool insertEdge(string vertex1_name, string vertex2_name, edge new_edge);   // �����
	void lessTime(string src_name, string dst_name);   // ���"ʱ���"���˷���
	void subwayOnly(string src_name, string dst_name);   // ���"ֻ������"���˷���
};

bool graph::isVertexInGraph(string vertex_name)
{
	return (index.find(vertex_name) != index.end());
}
bool graph::insertVertex(string vertex_name)
{
	if(isVertexInGraph(vertex_name))   // ���иö��㣬�������
		return false;
	vertices[vertexNum] = vertex_name;   // ����һ�����㲢��ʼ�������Ϣ
	index[vertex_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string vertex1_name, string vertex2_name, edge new_edge)
{
	insertVertex(vertex1_name);
	insertVertex(vertex2_name);
	size_t vertex1_index = index[vertex1_name], vertex2_index = index[vertex2_name];
	if(adjM[vertex1_index][vertex2_index].type != none)   // ���������ߣ��������
		return false;
	adjM[vertex1_index][vertex2_index] = new_edge;   // �����±�
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
	return min_time == INF ? -1 : min_index;   // δ�ҵ�����-1
}
void graph::lessTime(string src_name, string dst_name)
{
	system("title ��ͨ���˹滮 - ʱ����̵ĳ˳�����");
	size_t src = index[src_name], dst = index[dst_name];
	int time[MAXSIZE], path[MAXSIZE];
	bool collected[MAXSIZE];
	for(int i = 0; i < vertexNum; i++)
	{
		switch(adjM[src][i].type)
		{
			case subway:     time[i] = 3; break;   // ����3min��һվ
			case normal_bus: time[i] = 7; break;   // ����7min��һվ
			case air_bus:    time[i] = 7; break;
			case none:       time[i] = none; break;   // û��ֱ��·������ʼ��Ϊnone(��������ʾ)
		}
		if(time[i] != none)   // �����ֱ�������ĵ�
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
		printf("�� %s �� %s ���޻���·���������������������з�ʽ��\n\n",
			src_name.c_str(), dst_name.c_str());
		system("pause");
		return;
	}
	size_t temp = dst;
	stack<size_t> st;   // �����ݴ����·��
	st.push(dst);
	while(path[temp] != -1)
	{
		st.push(path[temp]);
		temp = path[temp];
	}
	printf("�� %s �� %s ʱ����̵ĳ˳�������\n\n", src_name.c_str(), dst_name.c_str());
	temp = st.top();
	st.pop();
	string line;
	vehicle_type type = none;
	int cost = 0, subwayStation_cnt = 0;   // ������ã���������վ��
	while(true)
	{
		cout << vertices[temp];
		if(st.empty() || adjM[temp][st.top()].name != line)
		{
			if(st.empty() || adjM[temp][st.top()].type != type)
			{   // ���յ㴦��Ļ���ͨ��ʽʱ�������
				if(type == subway)   // ����������վ���շ�
				{
					if(subwayStation_cnt <= 7)   // 0-7վ��3Ԫ
						cost += 3;
					else if(subwayStation_cnt <= 14)   // 8-14վ��5Ԫ
						cost += 5;
					else   // ����14վ��8Ԫ
						cost += 8;
					subwayStation_cnt = 0;
				}
				else if(type == normal_bus)   // ��ͨ����1Ԫ
					cost += 1;
				else if(type == air_bus)   // �յ�����2Ԫ
					cost += 2;
			}

			if(st.empty())   // ���յ㴦�˳�ѭ��
				break;
			line = adjM[temp][st.top()].name;   // �ڻ���վ���»�����Ϣ
			type = adjM[temp][st.top()].type;
			cout << "��" << line << "��";
		}
		if(adjM[temp][st.top()].type == subway)   // ��������Ҫ�ۼ�վ��
			subwayStation_cnt++;
		temp = st.top();
		st.pop();
		cout << " -> ";
	}
	cout << endl << "����ʱ��" << time[dst] << "���ӣ�";
	cout << "���ã�" << cost << "Ԫ" << endl << endl;
	system("pause");
}
void graph::subwayOnly(string src_name, string dst_name)
{
	system("title ��ͨ���˹滮 - ֻ�������ĳ˳�����");
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
		printf("�� %s �����������޷����� %s�������������˳�����������������з�ʽ��\n\n",
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
	printf("�� %s �� %s ֻ�������ĳ˳�������\n\n", src_name.c_str(), dst_name.c_str());
	temp = st.top();
	st.pop();
	string line;
	while(true)
	{
		cout << vertices[temp];
		if(st.empty())   // �����յ㣬�˳�ѭ��
			break;
		if(adjM[temp][st.top()].name != line)
		{
			line = adjM[temp][st.top()].name;   // �ڻ���վ���»�����Ϣ
			cout << "��" << line << "��";
		}
		temp = st.top();
		st.pop();
		cout << " -> ";
	}
	cout << endl << "����ʱ��" << dist[dst] * 3 << "���ӣ�";
	int cost;
	if(dist[dst] <= 7)   // 0-7վ��3Ԫ
		cost = 3;
	else if(dist[dst] <= 14)   // 8-14վ��5Ԫ
		cost = 5;
	else   // ����14վ��8Ԫ
		cost = 8;
	cout << "���ã�" << cost << "Ԫ" << endl << endl;
	system("pause");
}

graph map;
void loadMap()   // ���ص�ͼ
{
	system("title ��ͨ���˹滮 - ���ص�ͼ");
	printf("     ��ͨ���˹滮�����ص�ͼ\n\n");
	printf("�������ͼ�ļ������Իس�������");
	char mapFileName[256];
	cin.getline(mapFileName, 256);
	FILE *fp = fopen(mapFileName, "r");
	while(fp == NULL)   // ���ļ���ʧ�ܣ������������ļ���ֱ���򿪳ɹ�
	{
		printf("\n�ļ���ʧ�ܣ������ļ����Ƿ�������ȷ�Լ��ļ��Ƿ���ڡ�\n\n");
		printf("���������룺");
		cin.getline(mapFileName, 256);
		fp = fopen(mapFileName, "r");
	}
	printf("\n���Ժ�. . . \n\n");
	int n;
	fscanf(fp, "%d", &n);
	char name[256];   // ��·����
	int num, type, isCycle;   // ��·վ����  ����0/��ͨ����1/�յ�����2  �Ƿ���
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
	printf("��ͼ���سɹ���");
	system("pause");
}
void inputSrc(string &src)   // �������
{
	printf("\n��������㣺");
	getline(cin, src);
	while(!map.isVertexInGraph(src))   // δ�ҵ�������
	{
		if(src.size() > 2   // ���ȴ���2
			&& src.substr(src.size() - 2, src.size()) == "վ"   // ���һ������"վ"
			&& map.isVertexInGraph(src.substr(0, src.size() - 2)))   // ȥ��"վ"�ֺ�õ����
		{
			src = src.substr(0, src.size() - 2);   // �û��������һ��"վ"�֣�ȥ������
			break;
		}
		printf("\nδ���ҵ�������ĵ�ַ��������������㣺");
		getline(cin, src);
	}
}
void inputDst(string &dst, const string &src)   // �����յ�
{
	printf("\n�������յ㣺");
	getline(cin, dst);
	while(!map.isVertexInGraph(dst) || dst == src)   // δ�ҵ�����յ��������յ���ͬ
	{
		if(dst.size() > 2 && dst.substr(dst.size() - 2, dst.size()) == "վ"
			&& map.isVertexInGraph(dst.substr(0, dst.size() - 2))
			&& dst.substr(0, dst.size() - 2) != src)   // ȥ��"վ"�ֺ��������ͬ
		{
			dst = dst.substr(0, dst.size() - 2);   // �û��������һ��"վ"�֣�ȥ������
			break;
		}
		printf("\nδ���ҵ�������ĵ�ַ���յ��������ͬ�������������յ㣺");
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
		system("title ��ͨ���˹滮");
		printf("     ��ͨ���˹滮\n");
		fflush(stdin);
		inputSrc(src);
		inputDst(dst, src);
		printf("\n��ѡ��˳�������\n");
		printf("     1 - ʱ���\n");
		printf("     2 - ֻ������\n");
		printf("\n�����룺");
		getline(cin, choice);
		switch(choice[0])
		{
			case '1':system("cls"); map.lessTime(src, dst);     break;
			case '2':system("cls"); map.subwayOnly(src, dst);   break;

			default:printf("����������������롣"); system("pause"); break;
		}
	}
	return 0;
}
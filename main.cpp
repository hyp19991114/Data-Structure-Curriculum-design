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
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

#define MAXSIZE 200   // ��󶥵���
#define INF 0x3f3f3f3f   // �����
enum vehicle_type { subway, normal_bus, air_bus, none = INF };

struct vertex
{
	string name;
	vector<string> line;   // ��һ�㾭����������·
};

class graph
{
private:
	int vertexNum;   // �ܶ�����
	vertex vertices[MAXSIZE];   // ������Ϣ
	unordered_map<string, size_t> index;   // ���ݶ�����Ϣ�ҵ���Ӧ�±�
	vehicle_type adjM[MAXSIZE][MAXSIZE];   // �ڽӾ���
	int timeLT[MAXSIZE][MAXSIZE], pathLT[MAXSIZE][MAXSIZE];   // ����"ʱ���"���˷������
	bool insertVertex(string station_name);   // ���Ӷ���
public:
	graph();
	bool insertEdge(string edge1_name, string edge2_name, vehicle_type weight);   // �����
	void lessTime_calculate();   // Ԥ�ȼ���"ʱ���"���˷�������ѯʱ��ֱ�����
	void lessTime(string src_name, string dst_name);   // "ʱ���"���˷���
	void lessCost(string src_name, string dst_name);   // "�۸��"���˷���
	void lessTransfer(string src_name, string dst_name);   // "�۸��"���˷���
};

bool graph::insertVertex(string station_name)
{
	if(index.find(station_name) != index.end())   // ���иö��㣬�������
		return false;
	vertices[vertexNum].name = station_name;   // ����һ�����㲢��ʼ�������Ϣ
	index[station_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string vertex1_name, string vertex2_name, vehicle_type weight)
{
	insertVertex(vertex1_name);
	insertVertex(vertex2_name);
	size_t vertex1_index = index[vertex1_name], vertex2_index = index[vertex2_name];
	if(adjM[vertex1_index][vertex2_index] != INF)   // ���������ߣ��������
		return false;
	adjM[vertex1_index][vertex2_index] = weight;   // �����±�
	adjM[vertex2_index][vertex1_index] = weight;
	return true;
}
graph::graph()
{
	vertexNum = 0;
	for(int i = 0; i < MAXSIZE; i++)
		for(int j = 0; j < MAXSIZE; j++)
			adjM[i][j] = none;
}
void graph::lessTime_calculate()
{
	for(int i = 0; i < vertexNum; i++)
		for(int j = 0; j < vertexNum; j++)
			switch(adjM[i][j])
			{
				case subway:     timeLT[i][j] = 3; break;   // ����3min��һվ
				case normal_bus: timeLT[i][j] = 7; break;   // ����7min��һվ
				case air_bus:    timeLT[i][j] = 7; break;
				case none:       timeLT[i][j] = INF; break;   // û��ֱ��·������ʼ��ΪINF
			}
	memset(pathLT, -1, sizeof(pathLT));
	for(int k = 0; k < vertexNum; k++)
		for(int i = 0; i < vertexNum; i++)
			for(int j = 0; j < vertexNum; j++)
				if(timeLT[i][k] + timeLT[k][j] < timeLT[i][j])
				{
					timeLT[i][j] = timeLT[i][k] + timeLT[k][j];
					pathLT[i][j] = k;
				}
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
	while(fp == NULL)
	{
		printf("\n�ļ���ʧ�ܣ������ļ����Ƿ�������ȷ�Լ��ļ��Ƿ���ڡ�\n\n");
		printf("���������룺");
		cin.getline(mapFileName, 256);
		FILE *fp = fopen(mapFileName, "r");
	}
	printf("\n���Ժ�...\n\n");
	int n;
	fscanf(fp, "%d", &n);
	string name;   // ��·����
	int num, type, isCycle;   // ��·վ����  ����0/��ͨ����1/�յ�����2  �Ƿ���
	for(int i = 0; i < n; i++)
	{
		cin >> name >> num >> type >> isCycle;
		string v1, v2;
		for(int j = 0; j < num - 1 + isCycle; j++)
		{
			cin >> v1 >> v2;
			map.insertEdge(v1, v2, (vehicle_type)type);
		}
	}
	fclose(fp);
	map.lessTime_calculate();
	printf("��ͼ���سɹ���");
	system("pause");
}

int main1()
{
	system("color fc");
	loadMap();

	char choice[256];
	while(true)
	{
		system("cls");
		system("title ��ͨ���˹滮");
		fflush(stdin);

	}

	return 0;
}

int main()
{
	main1();



	return 0;
}
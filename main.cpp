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
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
using namespace std;

#define MAXSIZE 200   // ��󶥵���
#define INF 0x3f3f3f3f   // �����

struct vertex
{
	string name;
	bool isTransferStation;


};

class graph
{
private:
	int vertexNum;   // �ܶ�����
	vertex vertices[MAXSIZE];   // ������Ϣ
	unordered_map<string, size_t> index;   // ���ݶ�����Ϣ�ҵ���Ӧ�±�
	int adjM[MAXSIZE][MAXSIZE];   // �ڽӾ���
	int distanceLT[MAXSIZE][MAXSIZE], pathLT[MAXSIZE][MAXSIZE];   // ����"ʱ���"���˷������
	bool insertVertex(string station_name);   // ���Ӷ���
public:
	graph();
	bool insertEdge(string edge1_name, string edge2_name, int weight);   // �����
	void floyd();   // floyd�㷨��⻻�˷���
	void lessTime(string src, string dst);   // "ʱ���"���˷���
	void lessCost();   // "�۸��"���˷���
};

bool graph::insertVertex(string station_name)
{
	if(index.find(station_name) != index.end())   // ���иö��㣬�������
		return false;
	vertices[vertexNum].name = station_name;   // ����һ�����㲢��ʼ�������Ϣ
	vertices[vertexNum].isTransferStation = false;
	index[station_name] = vertexNum;
	vertexNum++;
	return true;
}
bool graph::insertEdge(string edge1_name, string edge2_name, int weight)
{
	insertVertex(edge1_name);
	insertVertex(edge2_name);
	size_t edge1_index = index[edge1_name], edge2_index = index[edge2_name];
	if(adjM[edge1_index][edge2_index] != INF)   // ���������ߣ��������
		return false;
	adjM[edge1_index][edge2_index] = weight;   // �����±�
	adjM[edge2_index][edge1_index] = weight;
	return true;
}
graph::graph()
{
	vertexNum = 0;
	for(int i = 0; i < MAXSIZE; i++)
		for(int j = 0; j < MAXSIZE; j++)
			adjM[i][j] = INF;
}
void graph::floyd()
{
	// "ʱ���"���˷���
	memcpy(distanceLT, adjM, sizeof(adjM));
	memset(pathLT, -1, sizeof(pathLT));
	for(int k = 0; k < vertexNum; k++)
		for(int i = 0; i < vertexNum; i++)
			for(int j = 0; j < vertexNum; j++)
				if(distanceLT[i][k] + distanceLT[k][j] < distanceLT[i][j])
				{
					distanceLT[i][j] = distanceLT[i][k] + distanceLT[k][j];
					pathLT[i][j] = k;
				}

	// "�۸��"���˷���

}
void graph::lessTime(string src, string dst)
{

}
void graph::lessCost()
{

}

graph map;
void loadMap()   // ���ص�ͼ
{
	system("title ��ͨ���˹滮 - ���ص�ͼ");
	printf("   ��ͨ���˹滮�����ص�ͼ\n\n");
	printf("   �������ͼ�ļ������Իس�������");
	char mapFileName[256];
	scanf("%[^\n]", mapFileName);
	FILE *fp = fopen(mapFileName, "r");
	int n;
	fscanf(fp, "%d", &n);
	char lineName[256];
	for(int i = 0; i < n; i++)
	{

	}




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


	return 0;
}
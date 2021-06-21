#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define MVNum 100

typedef char VerTexType;
typedef int ArcType;

typedef struct ArcNode {
	ArcType vertex_tail, vertex_head;
	struct ArcNode* nextarc_tail, * nextarc_head;
}ArcNode;

typedef struct VNode {
	VerTexType data;
	ArcNode* first_in_arc, * first_out_arc;
}VNode;

typedef struct {
	VNode vertex[MVNum];
	int vertex_num, arc_num;
}ALGraph;

Status CreateDG(ALGraph* G);
int LocateVertex(ALGraph G, VerTexType v);
void PrintGraph(ALGraph G);

void main() {
	ALGraph G;
	CreateDG(&G);
	PrintGraph(G);
}

Status CreateDG(ALGraph* G) {
	int i, j, k;
	VerTexType v1, v2;
	printf("请输入顶点数：");
	scanf("%d", &(G->vertex_num));
	printf("请输入边数：");
	scanf("%d", &(G->arc_num));
	for (i = 0; i < G->vertex_num; i++)
	{
		printf("请输入第%d顶点内容：", i + 1);
		getchar();
		scanf("%c", &(G->vertex[i].data));
		G->vertex[i].first_in_arc = G->vertex[i].first_out_arc = NULL;
	}
	for (k = 0; k < G->arc_num; k++)
	{
		printf("请输入要连接的两个顶点的信息：");
		getchar();
		scanf("%c %c", &v1, &v2);
		i = LocateVertex(*G, v1);
		j = LocateVertex(*G, v2);
		ArcNode* arcnode_p = (ArcNode*)malloc(sizeof(ArcNode));
		arcnode_p->vertex_tail = i;
		arcnode_p->vertex_head = j;
		arcnode_p->nextarc_tail = G->vertex[i].first_out_arc;
		arcnode_p->nextarc_head = G->vertex[j].first_in_arc;
		G->vertex[i].first_out_arc = G->vertex[j].first_in_arc = arcnode_p;
	}
	return OK;
}

int LocateVertex(ALGraph G, VerTexType v) {
	int i;
	for (i = 0; i < G.vertex_num; i++)
	{
		if (v == G.vertex[i].data)
		{
			return i;
		}
	}
	return -1;
}

void PrintGraph(ALGraph G) {
	int i;
	ArcNode* arc_node_out, * arc_node_in;
	printf("位置  顶点  邻接顶点位置\n");
	for (i = 0; i < G.vertex_num; i++)
	{
		arc_node_out = G.vertex[i].first_out_arc;
		arc_node_in = G.vertex[i].first_in_arc;
		printf("%-4d  %-4c  ", i, G.vertex[i].data);
		printf("出度：");
		while (arc_node_out != NULL)
		{
			printf("%-2d ", arc_node_out->vertex_head);
			arc_node_out = arc_node_out->nextarc_tail;
		}
		printf("\n%12c入度：", ' ');
		while (arc_node_in != NULL)
		{
			printf("%-2d ", arc_node_in->vertex_tail);
			arc_node_in = arc_node_in->nextarc_head;
		}
		printf("\n");
	}
}
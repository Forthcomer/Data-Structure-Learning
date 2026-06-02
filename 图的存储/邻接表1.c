/*
邻接表1

试在邻接表存储结构上实现图的基本操作 insert_vertex 和 insert_arc，
相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode;

typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph* G, VertexType v);
 //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v);
bool insert_arc(ListGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、
插入边时顶点v或w不存在）返回false。
*/
#include <stdio.h>
#include "graph.h" //请勿删除，否则检查不通过
bool insert_vertex(ListGraph *G, VertexType v){
    if (locate_vertex(G, v) == -1 && G->vexnum < MAX_VERTEX_NUM){
        G->vertex[G->vexnum].data = v;
        G->vertex[G->vexnum].firstarc = NULL;
        G->vexnum++;
    }else {
        return false;
    }
    return true;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w){
    int v_index = locate_vertex(G, v);
    int w_index = locate_vertex(G, w);
    if (v_index == -1 || w_index == -1) return false;
    //1、检查v->w是否已经存在（这里DG和UDG都需要）
    ArcNode *p = G->vertex[v_index].firstarc;
    while (p != NULL){
        if (p->adjvex == w_index) return false;
        p = p->nextarc;
    }
    if (G->type == UDG){
        //2、无向图还要检查反向边是否已存在
        ArcNode *p = G->vertex[w_index].firstarc;
        while (p != NULL){
            if (p->adjvex == v_index) return false;
            p = p->nextarc;
        }
        ArcNode *q1 = (ArcNode*)malloc(sizeof(ArcNode));
        q1->adjvex = w_index;
        q1->nextarc = G->vertex[v_index].firstarc;
        G->vertex[v_index].firstarc = q1;
        ArcNode *q2 = (ArcNode*)malloc(sizeof(ArcNode));
        q2->adjvex = v_index;
        q2->nextarc = G->vertex[w_index].firstarc;
        G->vertex[w_index].firstarc = q2;
    }else {
        ArcNode *q1 = (ArcNode*)malloc(sizeof(ArcNode));
        q1->adjvex = w_index;
        q1->nextarc = G->vertex[v_index].firstarc;
        G->vertex[v_index].firstarc = q1;
    }
    G->arcnum++;//统一加一
    return true;
}

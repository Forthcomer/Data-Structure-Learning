/*
邻接表2

试在邻接表存储结构上实现图的基本操作 del_vertex，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph *G, VertexType v); 
//返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v); //删除顶点 v
当成功删除顶点或边时，函数返回true，否则（如顶点或边不存在、删除边时顶点v或w不存在）返回false。
*/
#include <stdio.h>
#include "graph.h" //请勿删除，否则检查不通过

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v){
    int v_index = locate_vertex(G, v);
    if (v_index == -1) return false;
    //1、删掉v的所有出边
    ArcNode *p = G->vertex[v_index].firstarc;
    while(p != NULL){
        ArcNode *temp = p;
        p = p->nextarc;
        free(temp);
        G->arcnum--;
    }
    G->vertex[v_index].firstarc = NULL;
    //2、遍历所有其他顶点的邻接表，删除指向v_index的入边
    for (int i = 0; i < G->vexnum; i++){
        if (i == v_index) continue;
        ArcNode *cur = G->vertex[i].firstarc;
        ArcNode *prev = NULL;
        while (cur != NULL){
            if (cur->adjvex == v_index){
                ArcNode *temp = cur;
                cur = cur->nextarc;
                if (prev == NULL)
                    G->vertex[i].firstarc = cur;
                else
                    prev->nextarc = cur;
                free(temp);
                G->arcnum--;
            }else{
                prev = cur;
                cur = cur->nextarc;
            }
        }
    }
    //3、将vertex数组中v_index后面的元素都前移一位
    for (int i = v_index; i < G->vexnum - 1; i++){
        G->vertex[i] = G->vertex[i + 1];
    }
    G->vexnum--;
    //4、更新所有边的adjvex；大于v_index的减1（因为索引变了）
    for (int i = 0; i < G->vexnum; i++){
        ArcNode *cur = G->vertex[i].firstarc;
        while (cur != NULL){
            if (cur->adjvex > v_index){
                cur->adjvex--;
            }
            cur = cur->nextarc;
        }
    }
    return true;
}

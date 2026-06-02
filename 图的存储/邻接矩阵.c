/*
邻接矩阵

试在邻接矩阵存储结构上实现图的基本操作 matrix_insert_vertex 和matrix_insert_arc，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct{
    VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); 
//返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、插入边时顶点v或w不存在）返回false。
*/
#include <stdio.h>
#include "graph.h" // 请不要删除，否则检查不通过

bool matrix_insert_vertex(MatrixGraph *G, VertexType v){
    if (G->vexnum >= MAX_VERTEX_NUM) return false;
    if (matrix_locate_vertex(G, v) == -1){//没有顶点才需要加顶点
        int new_idx = G->vexnum;
        G->vertex[G->vexnum] = v;
        //初始化邻接矩阵中的新行和新列
        for (int i = 0; i <= new_idx; i++){
            G->arcs[new_idx][i] = 0;
            G->arcs[i][new_idx] = 0;
        }
        G->vexnum++;
    }else {
        return false;
    }
    return true;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w){
    if(matrix_locate_vertex(G, v) != -1 && matrix_locate_vertex(G, w) != -1){
        int v_index = matrix_locate_vertex(G, v);
        int w_index = matrix_locate_vertex(G, w);
        if (G->arcs[v_index][w_index] != 1){
            if (G->type == DG){
                G->arcs[v_index][w_index] = 1;
            }else{
                G->arcs[v_index][w_index] = 1;
                G->arcs[w_index][v_index] = 1;
            }
        G->arcnum++;
        }else {
            return false;
        }
    }else {
        return false;
    }
    return true;
}
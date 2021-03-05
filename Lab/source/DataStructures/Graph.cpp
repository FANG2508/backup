#include <DataStructures/Graph.h>

//#define DEBUG

#ifdef DEBUG
#include <cstdio>
void Graph::info () {
    printf("pts: size:%d\n", pts.size());
    for (auto A:pts)printf("%d ", A);
    printf("\nedges:\n");
    for (auto VEC:edges) {
        for (bool A:VEC)
            printf("%d ", A);
        puts("");
    }
}
#else
void Graph::info () {return;}
#endif




int Graph::GetPointIdx(int point) const{
    for (int i = 0; i < pts.size(); ++i) {
        if(pts[i]==point)return i;
    }
    return -1;
}

int Graph::GetIdDegree(int idx) const {
    if(idx==-1)return 0;
    int sum=0;
    for (auto i:edges[idx]) {
        if(i)sum+=1;
    }
    return sum;
}

Graph::Graph() {
    pts.clear();
    edges.clear();
}

Graph::~Graph() {
    pts.clear();
    edges.clear();
}

bool Graph::AddVertex(int vertex) {
    if (GetPointIdx(vertex)==-1){
        pts.push_back(vertex);
        for (int i=0;i<edges.size();i++) {
            edges[i].push_back(false);
        }
        edges.emplace_back(std::vector<bool>(pts.size(),false));
        return true;
    }
    return false;
}

bool Graph::RemoveVertex(int vertex) {
    const int idx = GetPointIdx(vertex);
    if (idx==-1){
        return false;
    }
    pts.erase(pts.begin()+idx);
    edges.erase(edges.begin()+idx);
    for (int i=0;i<edges.size();i++) {
        edges[i].erase(edges[i].begin()+idx);
    }
    return true;
}

bool Graph::AddEdge(int vertex1, int vertex2) {
    const int src_idx=GetPointIdx(vertex1);
    const int dst_idx=GetPointIdx(vertex2);
    if(src_idx==-1||dst_idx==-1||edges[src_idx][dst_idx])return false;
    else {
        edges[src_idx][dst_idx]=true;
        return true;
    }
}

bool Graph::RemoveEdge(int vertex1, int vertex2) {
    const int src_idx=GetPointIdx(vertex1);
    const int dst_idx=GetPointIdx(vertex2);
    if(src_idx==-1||dst_idx==-1||!edges[src_idx][dst_idx])return false;
    else {
        edges[src_idx][dst_idx]=false;
        return true;
    }
}

int Graph::CountVertices() const {
    return pts.size();
}

int Graph::CountEdges() const {
    int sum=0;
    for (int i=0;i<pts.size();i++) {
        sum+=GetIdDegree(i);
    }
    return sum;
}

bool Graph::ContainsVertex(int vertex) const {
    return GetPointIdx(vertex)!=-1;
}

bool Graph::ContainsEdge(int vertex1, int vertex2) const {
    const int src_idx=GetPointIdx(vertex1);
    const int dst_idx=GetPointIdx(vertex2);
    if(src_idx==-1||dst_idx==-1||!edges[src_idx][dst_idx])return false;
    else return true;
}

std::vector<int> Graph::GetVertices() const {
    return std::vector<int> (pts);
}

std::vector<Edge> Graph::GetEdges() const {
    std::vector<Edge> ret={};
    for (int src=0;src<edges.size();src++) {
        for (int dst=0;dst<edges[src].size();dst++) {
            if(edges[src][dst])ret.emplace_back(pts[src],pts[dst]);
        }
    }
    return ret;
}

std::vector<Edge> Graph::GetIncomingEdges(int vertex) const {
    std::vector<Edge> ret={};
    const int idx=GetPointIdx(vertex);
    if(idx==-1)return ret;
    for (int src=0;src<edges.size();src++) {
        if(edges[src][idx])ret.emplace_back(pts[src],pts[idx]);
    }
    return ret;
}

std::vector<Edge> Graph::GetOutgoingEdges(int vertex) const {
    std::vector<Edge> ret={};
    const int idx=GetPointIdx(vertex);
    if(idx==-1)return ret;
    for (int dst=0;dst<edges.size();dst++) {
        if(edges[idx][dst])ret.emplace_back(pts[idx],pts[dst]);
    }
    return ret;
}

int Graph::GetDegree(int vertex) const {

    return GetIdDegree(GetPointIdx(vertex));
}

std::vector<int> Graph::GetNeighbors(int vertex) const {
    const int idx=GetPointIdx(vertex);
    std::vector<int> ret={};
    if(idx==-1)return ret;
    for (int i=0;i<edges[idx].size();i++) {
        if(edges[idx][i])ret.push_back(pts[i]);
    }
    return ret;
}
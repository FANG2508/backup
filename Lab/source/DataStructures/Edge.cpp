#include <DataStructures/Edge.h>

Edge::Edge(int source, int destination) {
    src=source;
    dst=destination;
}

Edge::~Edge() {

}

int Edge::GetSource() const {
    return src;
}

int Edge::GetDestination() const {
    return dst;
}
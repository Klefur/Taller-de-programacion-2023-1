#include "Node.h"

using namespace std;

Node::Node(Simplex *s) {
    this->s = s;
}

Node::Node(vector<float> upperBound) {
    this->upperBound = upperBound;
    this->s = nullptr;
}

Node::~Node() {}


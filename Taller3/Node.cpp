#include "Node.h"

using namespace std;

/**
 * @brief Constructor de la clase Node
 * @param s puntero al simplex
 */
Node::Node(Simplex *s) {
    this->s = s;
}

/**
 * @brief Constructor de la clase Node
 * @param upperBound vector con los upper bound
 */
Node::Node(vector<float> upperBound) {
    this->upperBound = upperBound;
    this->s = nullptr;
}


/**
 * @brief Destructor de la clase Node
 */
Node::~Node() {}


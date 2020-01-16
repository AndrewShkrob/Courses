#include <algorithm>
#include <iostream>
#include <vector>

#if defined(__unix__) || defined(__APPLE__)

#include <sys/resource.h>

#endif

class Node;

class Node {
public:
    int key{};
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = nullptr;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int get_height(Node *node) {
    if (node == nullptr)
        return 0;
    std::vector<int> heights;
    for (auto &child : node->children)
        heights.push_back(get_height(child));
    if (heights.empty())
        return 1;
    return 1 + *std::max_element(std::begin(heights), std::end(heights));
}

int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<Node> nodes;
    size_t root_node_index = 0;
    nodes.resize(n);
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        else
            root_node_index = child_index;
        nodes[child_index].key = child_index;
    }

    std::cout << get_height(&nodes[root_node_index]) << std::endl;
    return 0;
}

int main(int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}

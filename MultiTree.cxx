// 将多叉树的节点结构改为模板
template <typename T>
struct Node {
    T data; // 节点存储的数据
    vector<Node<T>*> children; // 节点的子节点列表
};

// 将多叉树容器的类定义改为模板
template <typename T>
class MultiTree {
private:
    Node<T>* root; // 多叉树的根节点
public:
    // 构造函数，初始化一个空的多叉树
    MultiTree() {
        root = nullptr;
    }

    // 析构函数，释放多叉树占用的内存
    ~MultiTree() {
        clear();
    }

    // 清空多叉树的函数，采用递归的方式
    void clear(Node<T>* node) {
        if (node == nullptr) return; // 如果节点为空，直接返回
        for (Node<T>* child : node->children) { // 遍历节点的每个子节点
            clear(child); // 递归地清空子节点
        }
        delete node; // 删除节点
    }

    // 清空多叉树的函数，调用私有函数
    void clear() {
        clear(root); // 清空根节点
        root = nullptr; // 将根节点置为空
    }

    // 判断多叉树是否为空的函数
    bool empty() {
        return root == nullptr; // 如果根节点为空，返回真，否则返回假
    }

    // 获取多叉树的根节点的函数
    Node<T>* getRoot() {
        return root; // 返回根节点
    }

    // 设置多叉树的根节点的函数
    void setRoot(Node<T>* node) {
        root = node; // 将根节点设置为给定的节点
    }

    // 插入一个子节点到给定的父节点的函数
    void insert(Node<T>* parent, Node<T>* child) {
        if (parent == nullptr) return; // 如果父节点为空，直接返回
        parent->children.push_back(child); // 将子节点添加到父节点的子节点列表中
    }

    // 删除一个子节点从给定的父节点的函数
    void erase(Node<T>* parent, Node<T>* child) {
        if (parent == nullptr || child == nullptr) return; // 如果父节点或子节点为空，直接返回
        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) { // 遍历父节点的子节点列表
            if (*it == child) { // 如果找到了要删除的子节点
                parent->children.erase(it); // 从列表中删除该子节点
                break; // 跳出循环
            }
        }
        clear(child); // 清空该子节点及其后代节点占用的内存
    }

};

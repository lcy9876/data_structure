/**
 * @file BST.h
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 *
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     *
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     *
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     *
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     *
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     *
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root {
        rhs.root
    } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     *
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     *
     * 这是一个公有接口，它调用了私有的递归函数。
     *
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     *
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     *
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     *
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     *
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     *
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     *
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     *
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     *
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }


    /**
     * @brief 移动赋值运算符
     *
     * 将一个树的资源移动到当前树中。
     *
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

private:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针

        /**
         * @brief 构造函数，接受常量引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt } {}

        /**
         * @brief 构造函数，接受右值引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } {}
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     *
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     *
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        }
        else if (x > t->element) {
            return contains(x, t->right);
        }
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     *
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     *
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode * &t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr,
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
            /// 如果元素已存在，则不进行插入
            /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
    }

    /**
     * @brief 递归从树中移除指定的元素
     *
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    void removeold(const Comparable &x, BinaryNode * &t) {
        /// 这个逻辑其实是 find and remove, 从 t 开始
        if (t == nullptr) {
            return;  /// 元素不存在
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        }
        /// 进入以下这两个分支，都是说明找到了要删除的元素
        else if (t->left != nullptr && t->right != nullptr) {  /// 有两个子节点
            /// 将右子树中的最小元素替换当前节点，这里实际上只是替换值，不是替换节点
            t->element = findMin(t->right)->element;
            /// 然后递归删除右子树中的最小元素
            remove(t->element, t->right);
            /// 这是一种效率较低的做法，更好的做法是做节点的替换和移动
            /// 但会更加复杂，我们在后面再讨论
        } else {
            /// 有一个或没有子节点的情形是简单的
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * @brief 递归克隆树的结构
     *
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
   
	// 非递归实现AVL树的删除操作
	/*
	再从一棵二叉搜索树中删除一个节点之前必须先找到该节点所在的位置
	删除操作往往会引起很多后果 , 主要来自两个方面 : 
	一方面删除树中的一个节点必然会导致原本连通的树结构发生阻隔
	其次 , 当二叉搜索树中的某个节点被删除之后 , 树中的有序关系可能遭到破坏

	具体而言分为三种情况 : 
	1.删除的节点没有孩子
	2.删除的节点只有一个孩子
	3.删除的节点有两个孩子
	注 : 1和2可以看成是一种类型 , 只有一个孩子 , 这个孩子是空(nullptr)
	情况三的处理方法 , 使用前驱结点或者后继节点代替该节点 , 删除前驱即可
	前驱结点 : 当前节点的左子树中 , 元素的最大值
	后继节点 : 当前节点的右子树中 , 元素的最小值

	流程: 
	1. 从root开始寻找值为val的节点，cur指向它
	2. 先判断是否满足情况3，如果满足，需要找cur的前驱节点，用前驱把cur节点的值给覆盖掉，直接删前驱
	3. 删除情况1和情况2   直接删除cur指针指向的节点就可以了
	*/




void remove(const Comparable &val, BinaryNode * &xx)
	{
		// 1. 从root开始寻找值为val的节点，cur指向它
		BinaryNode *pre = nullptr;  //记录父节点
		BinaryNode *cur = xx;
		while(cur != nullptr)
		{
			if(val < cur->element)
			{
				pre = cur;
				cur = cur->left;
			}
			else if(val > cur->element)
			{
				pre = cur;
				cur = cur->right;
			}
			else
			{
				break;
			}
		}
		//判断找没找到
		if(cur == nullptr)
			return;

		// 2. 先判断是否满足情况3，如果满足，需要找cur的前驱节点，用前驱把cur节点的值给覆盖掉，直接删前驱
		if(cur->left != nullptr && cur->right != nullptr)
		{
			BinaryNode *old = cur;
			pre = cur;
			//找前驱
			cur = cur->left;
			while(cur->right != nullptr)
			{
				pre = cur;
				cur = cur->right;
			}
			//用前驱覆盖被删除节点
			old->element = cur->element;
		}
		// 3. 删除情况1和情况2   直接删除cur指针指向的节点就可以了
		BinaryNode *child = cur->left;
		if(child == nullptr)
		{
			child = cur->right;
		}

		if(pre == nullptr) // cur指向的根节点
		{
			xx = child;
		}
		else
		{
			// 要把删除节点的孩子赋给cur父节点相应的地址域里面
			if(cur == pre->left)
			{
				pre->left = child;
			}
			else
			{
				pre->right = child;
			}
		}
		delete cur;
	}


};
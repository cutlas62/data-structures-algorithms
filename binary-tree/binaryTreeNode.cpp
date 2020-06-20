#include <cstdio>
#include <stdexcept>
#include <stack>
#include <deque>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

class BinaryTreeNode
{
public:
    char _value;
    BinaryTreeNode *_left;
    BinaryTreeNode *_right;

    BinaryTreeNode (char value)
    {
        _value = value;
        _left = nullptr;
        _right = nullptr;
    }

    ~BinaryTreeNode (void)
    {
        delete(_left);
        delete(_right);
    }

    BinaryTreeNode *addLeftChild (char value)
    {
        _left = new BinaryTreeNode(value);
        return this->_left;
    }

    BinaryTreeNode *addRightChild (char value)
    {
        _right = new BinaryTreeNode(value);
        return this->_right;
    }
};


void printDFS (BinaryTreeNode *head)
{
    printf("\nDFS:\n");

    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }

    stack<BinaryTreeNode *> nodesToVisit;
    nodesToVisit.push(head);

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.top();
        nodesToVisit.pop();

        if (curNode->_right != nullptr)
        {
            nodesToVisit.push(curNode->_right);
        }
        if (curNode->_left != nullptr)
        {
            nodesToVisit.push(curNode->_left);
        }

        printf("%c ", curNode->_value);
    }
    printf("\n");
}

void printBFS (BinaryTreeNode *head)
{
    printf("\nBFS:\n");

    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }

    deque<BinaryTreeNode *> nodesToVisit;
    nodesToVisit.push_back(head);

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.front();
        nodesToVisit.pop_front();

        if (curNode->_left != nullptr)
        {
            nodesToVisit.push_back(curNode->_left);
        }
        if (curNode->_right != nullptr)
        {
            nodesToVisit.push_back(curNode->_right);
        }
        printf("%c ", curNode->_value);
    }
    printf("\n");
}

void findNodeDFS (BinaryTreeNode *head, char target)
{
    printf("\nFind '%c' using DFS:\n", target);

    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }

    stack<BinaryTreeNode *> nodesToVisit;
    nodesToVisit.push(head);
    unordered_map<BinaryTreeNode *, BinaryTreeNode *> traces;	// key = child, value = parent
    traces.insert(make_pair(head, nullptr));

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.top();
        nodesToVisit.pop();

        if (curNode->_value == target)
        {
            vector<BinaryTreeNode *> reversedPath;
            BinaryTreeNode *curTrace = curNode;
            while (curTrace != nullptr)
            {
                reversedPath.push_back(curTrace);
                curTrace = traces.find(curTrace)->second;

            }

            reverse(reversedPath.begin(), reversedPath.end());

            for (BinaryTreeNode *curNodeInPath : reversedPath)
            {
                printf("%c ", curNodeInPath->_value);
            }
            printf("\n");
            return;
        }

        if (curNode->_right != nullptr)
        {
            nodesToVisit.push(curNode->_right);
            traces.insert(make_pair(curNode->_right, curNode));

        }
        if (curNode->_left != nullptr)
        {
            nodesToVisit.push(curNode->_left);
            traces.insert(make_pair(curNode->_left, curNode));
        }
    }
}

void findNodeBFS (BinaryTreeNode *head, char target)
{
    printf("\nFind '%c' using BFS:\n", target);

    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }


    deque<BinaryTreeNode *> nodesToVisit;
    nodesToVisit.push_back(head);

    unordered_map<char, char> traces;	// key = child, value = parent
    traces.insert(make_pair(head->_value, 0));

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.front();
        nodesToVisit.pop_front();

        if (curNode->_value == target)
        {
            vector<char> reversedPath;

            char curTrace = curNode->_value;
            while (curTrace != 0)
            {
                reversedPath.push_back(curTrace);
                curTrace = traces.find(curTrace)->second;
            }

            reverse(reversedPath.begin(), reversedPath.end());

            for (char curChar : reversedPath)
            {
                printf("%c ", curChar);
            }
            printf("\n");

            return;
        }

        if (curNode->_left != nullptr)
        {
            nodesToVisit.push_back(curNode->_left);
            traces.insert(make_pair(curNode->_left->_value, curNode->_value));
        }
        if (curNode->_right != nullptr)
        {
            nodesToVisit.push_back(curNode->_right);
            traces.insert(make_pair(curNode->_right->_value, curNode->_value));
        }
    }
}

int countLeaves (BinaryTreeNode *head)
{
    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }

    int nLeaves = 0;

    stack<BinaryTreeNode *> nodesToVisit;
    nodesToVisit.push(head);

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.top();
        nodesToVisit.pop();

        if (curNode->_left == nullptr && curNode->_right == nullptr)
        {
            nLeaves++;
        }
        else
        {
            if (curNode->_right != nullptr)
            {
                nodesToVisit.push(curNode->_right);
            }
            if (curNode->_left != nullptr)
            {
                nodesToVisit.push(curNode->_left);
            }
        }

    }
    return nLeaves;
}

bool isPerfect (BinaryTreeNode *head)
{
    if (head == nullptr)
    {
        throw invalid_argument ("head was nullptr");
    }

    stack<pair<BinaryTreeNode *, int>> nodesToVisit;
    nodesToVisit.push(make_pair(head, 1));

    int nNodes = 0;
    int maxDepth = 0;

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.top().first;
        int curDepth = nodesToVisit.top().second;
        nodesToVisit.pop();

        nNodes++;

        if (curNode->_right == nullptr && curNode->_left == nullptr)
        {
            maxDepth = max(maxDepth, curDepth);
        }
        else
        {
            if (curNode->_left != nullptr)
            {
                nodesToVisit.push(make_pair(curNode->_left, curDepth + 1));
            }
            if (curNode->_right != nullptr)
            {
                nodesToVisit.push(make_pair(curNode->_right, curDepth + 1));
            }
        }
    }

    return (pow(2, maxDepth) - 1 == nNodes);
}

bool isBalanced (BinaryTreeNode *head)
{
    if (head == nullptr)
    {
        throw invalid_argument("head was nullptr");
    }

    stack<pair<BinaryTreeNode *, int>> nodesToVisit;
    nodesToVisit.push(make_pair(head, 1));

    int maxDepth = 1;
    int minDepth = INT_MAX;

    while (!nodesToVisit.empty())
    {
        BinaryTreeNode *curNode = nodesToVisit.top().first;
        int curDepth = nodesToVisit.top().second;
        nodesToVisit.pop();

        if (curNode->_left == nullptr && curNode->_right == nullptr)
        {
            maxDepth = max(maxDepth, curDepth);
            minDepth = min(minDepth, curDepth);
        }
        else
        {
            if (curNode->_left != nullptr)
            {
                nodesToVisit.push(make_pair(curNode->_left, curDepth + 1));
            }
            if (curNode->_right != nullptr)
            {
                nodesToVisit.push(make_pair(curNode->_right, curDepth + 1));
            }
        }

        if (maxDepth - minDepth > 1)
        {
            return false;
        }
    }

    return true;
}

int main (int argc, char *argv [])
{
    BinaryTreeNode *a = new BinaryTreeNode ('A');
    BinaryTreeNode *b = a->addLeftChild('B');
    BinaryTreeNode *c = a->addRightChild('C');
    BinaryTreeNode *d = b->addLeftChild('D');
    BinaryTreeNode *e = b->addRightChild('E');
    BinaryTreeNode *f = c->addLeftChild('F');
    BinaryTreeNode *g = c->addRightChild('G');
    BinaryTreeNode *h = d->addLeftChild('H');
    BinaryTreeNode *i = d->addRightChild('I');
    BinaryTreeNode *j = e->addLeftChild('J');
    BinaryTreeNode *k = e->addRightChild('K');
    BinaryTreeNode *l = f->addLeftChild('L');
    BinaryTreeNode *m = f->addRightChild('M');
    BinaryTreeNode *n = g->addLeftChild('N');
    BinaryTreeNode *o = g->addRightChild('O');
    BinaryTreeNode *p = j->addLeftChild('P');
    BinaryTreeNode *q = l->addLeftChild('Q');
    BinaryTreeNode *r = m->addRightChild('R');
    BinaryTreeNode *s = q->addLeftChild('S');
    BinaryTreeNode *t = q->addRightChild('T');
    BinaryTreeNode *u = r->addLeftChild('U');
    BinaryTreeNode *v = r->addRightChild('V');
    BinaryTreeNode *w = v->addRightChild('W');
    BinaryTreeNode *x = w->addLeftChild('X');
    BinaryTreeNode *y = x->addLeftChild('Y');
    BinaryTreeNode *z = x->addRightChild('Z');


    printDFS(a);

    printBFS(a);

    printf("\nThe tree has %d leaves\n\n", countLeaves(a));

    findNodeDFS(a, 'I');
    findNodeDFS(a, 'M');
    findNodeDFS(a, 'S');
    findNodeDFS(a, 'Y');

    findNodeBFS(a, 'I');
    findNodeBFS(a, 'M');
    findNodeBFS(a, 'S');
    findNodeBFS(a, 'Y');

    printf("\nIs it a perfect tree? %s\n\n", isPerfect(a) ? "Yes" : "No");
    printf("\nIs it a balanced tree? %s\n\n", isBalanced(a) ? "Yes" : "No");
}

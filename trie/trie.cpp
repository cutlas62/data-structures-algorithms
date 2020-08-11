#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class TrieNode
{
public:

    TrieNode (void):
        children (26, nullptr)
    {
    }

    bool containsKey (char c)
    {
        return (children[c - 'a'] != nullptr);
    }

    TrieNode *get (char c)
    {
        return children[c - 'a'];
    }

    void put (char c, TrieNode *node)
    {
        children[c - 'a'] = node;
    }

    void setEnd (void)
    {
        isEnd = true;
    }

    bool getEnd (void)
    {
        return isEnd;
    }


private:

    vector<TrieNode *> children;
    bool isEnd;

};


class Trie
{

public:
    Trie (void)
    {
        root = new TrieNode();
    }

    void insert (string str)
    {
        TrieNode *curNode = root;
        int strLength = str.length();
        for (int i = 0; i < strLength; i++)
        {
            if (!curNode->containsKey(str[i]))
            {
                curNode->put(str[i], new TrieNode ());
            }
            curNode = curNode->get(str[i]);
        }
        curNode->setEnd();

    }

private:

    TrieNode *root;
};




int main (int argc, char *argv[])
{

    Trie *root = new Trie();


}
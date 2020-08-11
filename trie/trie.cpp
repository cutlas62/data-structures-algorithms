#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class TrieNode
{
public:

    TrieNode (void):
        children (26, nullptr),
        isEnd(false)
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
        unsigned int strLength = str.length();
        for (unsigned int i = 0; i < strLength; i++)
        {
            if (!curNode->containsKey(str[i]))
            {
                curNode->put(str[i], new TrieNode ());
            }
            curNode = curNode->get(str[i]);
        }
        curNode->setEnd();

    }

    bool search (string str)
    {
        TrieNode *curNode = searchPrefix(str);
        return (curNode != nullptr && curNode->getEnd());
    }

    TrieNode *searchPrefix (string str)
    {
        TrieNode *curNode = root;
        unsigned int strLength = str.length();
        for (unsigned int i = 0; i < strLength; i++)
        {
            if (!curNode->containsKey(str[i]))
            {
                return nullptr;
            }
            curNode = curNode->get(str[i]);
        }
        return curNode;
    }


private:

    TrieNode *root;
};




int main (int argc, char *argv[])
{

    Trie *_trie = new Trie();

    _trie->insert("cacatua");
    _trie->insert("cacatuas");
    _trie->insert("caca");
    _trie->insert("cacaza");
    _trie->insert("cactus");
    _trie->insert("cacasara");
    _trie->insert("cacatri");


    printf("cacatua exists: %s\n", _trie->search("cacatua") ? "Yes" : "No");



}
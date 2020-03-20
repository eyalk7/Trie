//
// Created by eyalk on 20/03/2020.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <string>
#include <stack>

using std::string;

const int NUM_OF_LETTERS = 26;
const int NORMALIZE = 'a' - 1;
const int END_OF_WORD = 0;

class Trie {
public:
    enum TrieReturn {SUCCESS, WORD_ALREADY_EXISTS, WORD_NOT_EXISTS};

    Trie() : root (new TrieNode) {};
    ~Trie() {deleteAll(root);};

    TrieReturn insert(const string& word);
    TrieReturn remove(const string& word);
    bool contains(const string& word);
    string findByPrefix(const string& prefix);

private:
    class TrieNode {
    public:
        TrieNode* letters[NUM_OF_LETTERS+1];
        TrieNode() {
            for (int i = 0; i < NUM_OF_LETTERS+1; i++) letters[i] = nullptr;
        };
    };

    static void deleteAll(TrieNode* curr);

    TrieNode* root;
};


#endif //TRIE_TRIE_H

//
// Created by eyalk on 20/03/2020.
//

#include "Trie.h"

using std::stack;


void Trie::deleteAll(Trie::TrieNode *curr) {
    for (int i = 0; i < NUM_OF_LETTERS+1; i++) {
        if (curr->letters[i]) deleteAll(curr->letters[i]);
    }
    delete curr;
}

Trie::TrieReturn Trie::insert(const string& word) {
    TrieReturn res = WORD_ALREADY_EXISTS;
    auto iter = root;

    for (auto letter : word) {
        if (!iter->letters[letter-NORMALIZE]) {
            res = SUCCESS;
            iter->letters[letter-NORMALIZE] = new TrieNode;
        }
        iter = iter->letters[letter-NORMALIZE];
    }

    if (!iter->letters[END_OF_WORD]) {
        res = SUCCESS;
        iter->letters[END_OF_WORD] = new TrieNode;
    }

    return res;
}

Trie::TrieReturn Trie::remove(const string& word) {
    stack<TrieNode*> st;
    st.push(root);

    for (auto letter : word) {
        auto top = st.top();
        if (!top->letters[letter-NORMALIZE]) return WORD_NOT_EXISTS;
        st.push(top->letters[letter-NORMALIZE]);
    }
    if (!st.top()->letters[END_OF_WORD]) return WORD_NOT_EXISTS;

    auto prev = st.top()->letters[END_OF_WORD];
    while (!st.empty()) {
        auto top = st.top();
        bool to_return = false;

        for (int i = 0; i < NUM_OF_LETTERS+1; i++) {
            if (top->letters[i] == prev) {
                delete prev;
                top->letters[i] = nullptr;
            } else if (top->letters[i]) {
                to_return = true;
            }
        }

        if (to_return) return SUCCESS;

        prev = top;
        st.pop();
    }

    return SUCCESS;
}

bool Trie::contains(const string& word) {
    auto iter = root;
    for (auto letter : word) {
        if (!iter->letters[letter-NORMALIZE]) return false;
        iter = iter->letters[letter-NORMALIZE];
    }
    if (!iter->letters[END_OF_WORD]) return false;

    return true;
}

string Trie::findByPrefix(const string &prefix) {
    auto iter = root;
    for (auto letter : prefix) {
        if (!iter->letters[letter-NORMALIZE]) return "";
        iter = iter->letters[letter-NORMALIZE];
    }

    string res = prefix;
    while (!iter->letters[END_OF_WORD]) {
        for (int i = 1; i < NUM_OF_LETTERS+1; i++) {
            if (iter->letters[i]) {
                res.push_back(i + NORMALIZE);
                iter = iter->letters[i];
                break;
            }
        }
    }

    return res;
}

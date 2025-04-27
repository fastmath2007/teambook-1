struct Aho {
struct node {
    map <int, int> trie;
    int e = 0, suf = 0, bad = 0;
};
vector <node> mem;
int get_next_or_create(int nd, int c) {
    if (mem[nd].trie.find(c) == mem[nd].trie.end()) {
        mem[nd].trie[c] = mem.size();
        mem.emplace_back();

    }
    int v = mem[nd].trie[c];
    mem[v].e = c;
    return v;
}
Aho (vector <vector <int> > t) {
    int L = 0;
    for (auto &e : t) {
        L += e.size();
    }
    mem.reserve(L + 1);
    mem.emplace_back();
    for (int j = 0; j < t.size(); ++j) {
        int cur = 0;
        for (int c : t[j]) {
            cur = get_next_or_create(cur, c);
        }
        mem[cur].bad = 1;
    }
    queue <int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        mem[u].bad |= mem[mem[u].suf].bad;
        for (auto [c, v] : mem[u].trie) {
            if (u == 0) {
                mem[v].suf = 0;
            }
            else {
                int go = mem[u].suf;
                while (go>0 && mem[go].trie.find(c) == mem[go].trie.end()) {
                    go = mem[go].suf;
                }
                if (mem[go].trie.find(c) != mem[go].trie.end()) {
                    mem[v].suf = mem[go].trie[c];
                }
                else {
                    mem[v].suf = 0;
                }
            }
            q.push(v);
        }
    }
}
};

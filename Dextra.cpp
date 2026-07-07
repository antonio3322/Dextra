#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void Dekstra_student(vector<vector<pair<int, int>>>& G, vector<int>& Len,
    vector<int>& Parent, int start) {
    int n = G.size() - 1;

    vector<int> Mark(n + 1, 0);
    Len = vector<int>(n + 1, 1e9);
    Parent = vector<int>(n + 1, -1);
    Len[start] = 0;

    for (int i = 0; i < n; i++) {
        int uk = 0;
        int len = 1e9;

        for (int j = 1; j <= n; j++) {
            if (Mark[j] == 0) {
                if (Len[j] < len) {
                    uk = j;
                    len = Len[j];
                }
            }
        }

        if (uk == 0) break;

        Mark[uk] = 1;

        for (int i = 0; i < G[uk].size(); i++) {
            int neighbor = G[uk][i].first;
            int weight = G[uk][i].second;

            if (Mark[neighbor] == 0) {
                if (Len[uk] + weight < Len[neighbor]) {
                    Len[neighbor] = Len[uk] + weight;
                    Parent[neighbor] = uk;
                }
            }
        }
    }
}

void Dekstra_school(vector<vector<pair<int, int>>>& G, vector<int>& Len,
    vector<int>& Parent, int start) {
    int n = G.size() - 1;

    vector<int> Mark(n + 1, 0);
    Len = vector<int>(n + 1, 1e9);
    Parent = vector<int>(n + 1, -1);
    Len[start] = 0;

    for (int i = 0; i < n; i++) {
        int uk = 0;
        int len = 1e9;

        for (int j = 1; j <= n; j++) {
            if (Mark[j] == 0) {
                if (Len[j] < len) {
                    uk = j;
                    len = Len[j];
                }
            }
        }

        if (uk == 0) break;

        Mark[uk] = 1;

        for (int i = 0; i < G[uk].size(); i++) {
            int neighbor = G[uk][i].first;
            int weight = G[uk][i].second;

            if (Mark[neighbor] == 0) {
                if (Len[uk] + weight < Len[neighbor]) {
                    Len[neighbor] = Len[uk] + weight;
                    Parent[neighbor] = uk;
                }
            }
        }
    }
}

bool compareResults(const vector<int>& Len1, const vector<int>& Len2) {
    if (Len1.size() != Len2.size()) return false;

    for (int i = 1; i < Len1.size(); i++) {
        if (Len1[i] != Len2[i]) {
            return false;
        }
    }
    return true;
}

void printPath(const vector<int>& Parent, int start, int finish) {
    vector<int> temp;
    for (int v = finish; v != -1; v = Parent[v]) {
        temp.push_back(v);
        if (v == start) break;
    }

    if (temp.empty() || temp.back() != start) {
        cout << "Путь не существует!" << endl;
        return;
    }

    for (int i = temp.size() - 1; i >= 0; i--) {
        cout << temp[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

void printDistances(const vector<int>& Len, const string& name) {
    cout << name << ":\n";
    for (int i = 1; i < Len.size(); i++) {
        cout << "  dist[" << i << "] = ";
        if (Len[i] == 1e9) {
            cout << "∞" << endl;
        }
        else {
            cout << Len[i] << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> G(n + 1);

    cout << "Введите рёбра (a b вес):\n";
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        G[a].push_back({ b, w });
        G[b].push_back({ a, w });
    }

    int start, finish;
    cout << "Введите начальную и конечную вершины: ";
    cin >> start >> finish;

    vector<int> Len_opt, Parent_opt;
    vector<int> Len_naive, Parent_naive;

    Dekstra_student(G, Len_opt, Parent_opt, start);
    Dekstra_school(G, Len_naive, Parent_naive, start);

    if (compareResults(Len_opt, Len_naive)) {
        cout << "Ответы совпадают" << endl;
    }
    else {
        cout << "Ответы не совпадают" << endl;
    }

    cout << "Расстояние от вершины" << start << "\n";
    printDistances(Len_opt, "Оптимизированная");
    cout << endl;
    printDistances(Len_naive, "Наивная");

    cout << "\n Путь до вершины" << finish << "\n";

    cout << "Оптимизированная: ";
    printPath(Parent_opt, start, finish);

    cout << "Наивная:";
    printPath(Parent_naive, start, finish);

    return 0;
}

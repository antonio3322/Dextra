#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

bool Bad_rib(vector<vector<pair<int, int>>>& G, int n) {
    for (int u = 1; u <= n; u++) {
        for (auto rib : G[u]) {
            if (rib.second < 0) {
                return true;
            }
        }
    }
    return false;
}

void Dekstra_school(vector<vector<pair<int, int>>>& G, vector<int>& Len,
    vector<int>& Putty, int start) {
    int n = G.size() - 1;

    vector<int> Mark(n + 1, 0);
    Len = vector<int>(n + 1, 1e9);
    Putty = vector<int>(n + 1, -1);
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
                    Putty[neighbor] = uk;
                }
            }
        }
    }
}

void Dekstra_student(vector<vector<pair<int, int>>>& G, vector<int>& Len,
    vector<int>& Putty, int start) {
    int n = G.size() - 1;

    Len = vector<int>(n + 1, 1e9);
    Putty = vector<int>(n + 1, -1);
    Len[start] = 0;

    set<pair<int, int>> s;
    s.insert({ 0, start });

    while (!s.empty()) {
        int v = s.begin()->second;
        s.erase(s.begin());

        for (int i = 0; i < G[v].size(); i++) {
            int to = G[v][i].first;
            int weight = G[v][i].second;

            if (Len[v] + weight < Len[to]) {
                s.erase({ Len[to], to });
                Len[to] = Len[v] + weight;
                Putty[to] = v;
                s.insert({ Len[to], to });
            }
        }
    }
}

bool Compare(const vector<int>& Len1, const vector<int>& Len2) {
    if (Len1.size() != Len2.size()) return false;

    for (int i = 1; i < Len1.size(); i++) {
        if (Len1[i] != Len2[i]) {
            return false;
        }
    }
    return true;
}

void Print_Path(const vector<int>& Putty, int start, int finish) {
    vector<int> temp;
    for (int v = finish; v != -1; v = Putty[v]) {
        temp.push_back(v);
        if (v == start) break;
    }

    if (temp.empty() || temp.back() != start) {
        cout << "Путь не существует!" << endl;
        return;
    }

    for (int i = temp.size() - 1; i >= 0; i--) {
        cout << temp[i];
        if (i > 0) cout << " => ";
    }
    cout << endl;
}

void Print_Distances(const vector<int>& Len, const string& name) {
    cout << name << ":" << endl;
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
    cin >> n >> m;

    vector<vector<pair<int, int>>> G(n + 1);

    cout << "\nВведите рёбра (a b вес):\n";
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        G[a].push_back({ b, w });
        G[b].push_back({ a, w });  
    }

    if (Bad_rib(G, n)) {
        cout << "Обнаружены отрицательные рёбра" << endl;
        return 0;
    }

    int start, finish;
    cout << "\nВведите начальную и конечную вершины: ";
    cin >> start >> finish;

    if (start < 1 || start > n || finish < 1 || finish > n) {
        cout << "Неверные номера вершин" << endl;
        return 0;
    }

    if (start == finish) {
        cout << "\nРасстояние = 0" << endl;
        cout << "Путь: " << start << endl;
        return 0;
    }

    vector<int> Len_school, Parent_school;
    vector<int> Len_student, Parent_student;

    Dekstra_school(G, Len_school, Parent_school, start);
    Dekstra_student(G, Len_student, Parent_student, start);

    bool ok1 = Compare(Len_school, Len_student);

    if (ok1) {
        cout << "Результаты совпадают\n";
    }
    else {
        cout << "Результаты не совпадают\n";
    }

    Print_Distances(Len_school, "Школьная");
    cout << endl;
    Print_Distances(Len_student, "Студенческая ");
    cout << endl;

    cout << "\nПуть до вершины " << finish << endl;

    if (Len_school[finish] == 1e9) {
        cout << "Пути не существует\n";
    }
    else {
        cout << "Школьная:     ";
        Print_Path(Parent_school, start, finish);

        cout << "Студенческая: ";
        Print_Path(Parent_student, start, finish);
    }
    return 0;
}

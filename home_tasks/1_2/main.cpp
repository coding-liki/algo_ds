#include <iostream>
#include <unordered_map>

using namespace std;

void readMap(unordered_map<int, int> *map, const int length) {
    for (int i = 0; i < length; i++) {
        int input;
        cin >> input;
        map->find(input) != map->end() ? (*map)[input]++ : (*map)[input] = 1;
    }
}


int readMapAndCountExistedElements(unordered_map<int, int> *map, const int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        int input;
        cin >> input;
        map->find(input) != map->end() && (*map)[input] > 0 ? ++count && (*map)[input]-- : 0;
    }

    return count;
}

int main() {
    unordered_map<int, int> a;
    int n1, n2;
    cin >> n1 >> n2;
    readMap(&a, n1);

    cout << readMapAndCountExistedElements(&a, n2);

    return 0;
}

#include <iostream>
#include <set>

using namespace std;

void readSet(set<int_fast16_t> *set) {
    int_fast16_t inputInt;

    cin >> inputInt;

    while (inputInt != 0) {
        set->insert(inputInt);
        cin >> inputInt;
    }
}

void readAndCulculateSymetricSubSet(set<int_fast16_t> *alreadyReadSet) {
    int_fast16_t inputInt;

    cin >> inputInt;

    while (inputInt != 0) {
        if (alreadyReadSet->contains(inputInt)) {
            alreadyReadSet->erase(inputInt);
        } else {
            alreadyReadSet->insert(inputInt);
        }
        cin >> inputInt;
    }
}

void writeSet(set<int_fast16_t> *set) {
    if (set->empty()) {
        cout << 0;
        return;
    }

    for (auto iterator = set->begin(); iterator != set->end(); ++iterator) {
        cout << *iterator;
        if (iterator != set->end()) {
            cout << " ";
        }
    }
}

int main() {
    set<int_fast16_t> a, b, c;

    readSet(&a);
    readAndCulculateSymetricSubSet(&a);
    writeSet(&a);
}

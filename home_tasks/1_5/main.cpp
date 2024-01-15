#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;


int64_t findMinimumDifference(vector<int32_t> *packet, size_t packetIndex, int64_t currentDifference,
                              int64_t *minimumDifference) {
    if (packetIndex >= packet->size()) {
        *minimumDifference = min(abs(currentDifference), *minimumDifference);
        return *minimumDifference;
    }

    findMinimumDifference(
        packet,
        packetIndex + 1,
        abs(currentDifference - packet->at(packetIndex)),
        minimumDifference
    );

    findMinimumDifference(
        packet,
        packetIndex + 1,
        abs(currentDifference + packet->at(packetIndex)),
        minimumDifference
    );
    return *minimumDifference;
}

int main() {
    vector<int32_t> packet;

    packet.reserve(30);
    size_t packetSize;
    cin >> packetSize;

    for (size_t i = 0; i < packetSize; i++) {
        int32_t weight;
        cin >> weight;
        packet.push_back(weight);
    }

    int64_t minimumDifference = INT64_MAX;
    cout << findMinimumDifference(&packet, 1, packet[0], &minimumDifference);
    return 0;
}

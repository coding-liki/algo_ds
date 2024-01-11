#include <iostream>
#include <numeric>
#include <forward_list>
#include <sstream>

using namespace std;


uint32_t calculatePolynomial(forward_list<uint32_t> *coefficientValuesList, const uint32_t x, const uint32_t mod) {
    auto addPolynomialPart = [x, mod](pair<uint32_t, uint32_t> accumulator, const uint32_t coefficient) {
        accumulator.first = (accumulator.first + accumulator.second * coefficient) % mod;

        accumulator.second = (accumulator.second * x) % mod;

        return accumulator;
    };


    return accumulate(
               coefficientValuesList->begin(),
               coefficientValuesList->end(),
               pair<uint32_t, uint32_t>(0, 1),
               addPolynomialPart
           ).first % mod;
}

int main() {
    uint32_t degree;
    uint16_t calculatedValuesCount;
    uint32_t mod;
    forward_list<uint32_t> coefficientValuesList;

    cin >> degree >> calculatedValuesCount >> mod;

    for (uint32_t i = 0; i < degree + 1; i++) {
        uint32_t value;
        cin >> value;

        coefficientValuesList.push_front(value);
    }
    std::stringstream output;

    for (uint16_t i = 0; i < calculatedValuesCount; i++) {
        uint32_t x;
        cin >> x;
        output << calculatePolynomial(&coefficientValuesList, x, mod);
        if (i < calculatedValuesCount) {
            output << "\n";
        }
    }

    cout << output.str();

    return 0;
}

#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double>
input_numbers(istream& in,size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in) {
    Input data;
    cerr << "Enter number count: ";
    size_t number_count;
    cin >> number_count;
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    cerr << "Enter column count: ";
    cin >> data.bin_count;
    return data;
}

int
main() {
    Input data = read_input(cin);
    const auto bins = make_histogram(data);
    show_histogram_svg(bins);
    //show_histogram_text(bins);
    return 0;
}

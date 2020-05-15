#include <sstream>
#include <string>
#include <curl/curl.h>
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
read_input(istream& in,bool prompt) {
    Input data;
    size_t number_count;
    if(prompt)
    {
    cerr << "Enter number count: ";
    in >> number_count;
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    cerr << "Enter column count: ";
    in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }

    return data;
}

Input
download(const string& address) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        res = curl_easy_perform(curl);
        if (res)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
   curl_easy_cleanup(curl);
   return read_input(buffer, false);
}

int
main(int argc, char* argv[]) {
    Input input;
   if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    //show_histogram_text(bins);
    return 0;
}

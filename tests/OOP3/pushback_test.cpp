#include "lib/main_lib.h"
#include "Vector.hpp"

int main(int argc, char *argv[])
{
    ar_skaiciuoti_laika = true;
    timer_prad();

    unsigned int sz = atoi(argv[1]); // 100000, 1000000, 10000000, 100000000

    std::vector<int> v1;
    unsigned int mem_count = 0;

    for (unsigned int i = 1; i <= sz; ++i)
    {
        v1.push_back(i);
        if (v1.capacity() == v1.size())
            mem_count++;
    }

    timer_pab("std::vector push_back");
    cout << mem_count << endl;
    mem_count = 0;

    timer_prad();

    custm::vector<int> v2;

    for (unsigned int i = 1; i <= sz; ++i)
    {
        v2.push_back(i);
        if (v2.capacity() == v2.size())
            mem_count++;
    }

    timer_pab("Vector push_back");
    cout << mem_count << endl;
}

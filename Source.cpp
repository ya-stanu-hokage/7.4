#include <algorithm>
#include <execution>
#include <iostream>
#include <fstream>
#include <vector>

#include "Timer.hpp"

int main()
{
    std::fstream fout_1("For_each.csv", std::ios::out);
    fout_1 << "n, multy, singe" << std::endl;

    for (auto i = 10000000; i <= 100000000; i += 10000000)
    {
        std::vector<double> vector_1(i);
        std::vector<double> vector_2(i);
        std::iota(std::begin(vector_1), std::end(vector_1), 1.0);
        std::iota(std::begin(vector_2), std::end(vector_2), 1.0);

        Timer t1("Muly for_each");
        std::for_each(std::execution::par, std::begin(vector_1), std::end(vector_1), [](auto& x)
            {
                x += x;
            });
        t1.Pause();

        Timer t2("Single for_each");
        std::for_each(std::begin(vector_2), std::end(vector_2), [](auto& x)
            {
                x += x;
            });
        t2.Pause();

        fout_1 << i << ',' << t1.getMc() << ',' << t2.getMc() << std::endl;
    }


    std::fstream fout_2("P_S and I_S.csv", std::ios::out);
    fout_2 << "n, P_S, I_S" << std::endl;

    for (auto i = 10000000; i <= 100000000; i += 10000000)
    {
        std::vector<double> vector_1(i);
        std::vector<double> vector_2(i);
        std::iota(std::begin(vector_1), std::end(vector_1), 1.0);
        std::iota(std::begin(vector_2), std::end(vector_2), 1.0);

        Timer t1("partial_sum");
        std::partial_sum(std::begin(vector_1), std::end(vector_1), std::begin(vector_1));
        t1.Pause();

        Timer t2("inclusive_scan");
        std::inclusive_scan(std::execution::par, std::begin(vector_2), std::end(vector_2), std::begin(vector_2));
        t2.Pause();

        fout_2 << i << ',' << t1.getMc() << ',' << t2.getMc() << std::endl;
    }


    std::fstream fout_3("T_R and I_P.csv", std::ios::out);
    fout_3 << "n, T_R, I_P" << std::endl;
    for (auto i = 10000000; i <= 100000000; i += 10000000)
    {
        std::vector<double> vector_1(i);
        std::vector<double> vector_2(i);
        std::iota(std::begin(vector_1), std::end(vector_1), 1.0);
        std::iota(std::begin(vector_2), std::end(vector_2), 1.0);

        Timer t1("transform_reduce");
        std::transform_reduce(std::execution::par, std::begin(vector_1), std::end(vector_1), std::begin(vector_2), 0);
        t1.Pause();

        Timer t2("inner_product");
        std::inner_product(std::begin(vector_1), std::end(vector_1), std::begin(vector_2), 0);
        t2.Pause();
        fout_3 << i << ',' << t1.getMc() << ',' << t2.getMc() << std::endl;
    }


    return 0;
}
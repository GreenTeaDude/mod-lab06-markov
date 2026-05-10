#include "../include/textgen.h"

#include <iostream>
#include <fstream>

const int NPREF = 2;
const int MAXGEN = 1200;
const std::string NONWORD = "\n";

int main()
{
    std::ifstream input("input.txt");

    if (!input)
    {
        std::cout << "Ошибка: не удалось открыть input.txt" << std::endl;
        return 1;
    }

    std::ofstream output("result/gen.txt");

    if (!output)
    {
        std::cout << "Ошибка: не удалось открыть result/gen.txt" << std::endl;
        return 1;
    }

    StateTab statetab;
    Prefix prefix;

    for (int i = 0; i < NPREF; i++)
    {
        prefix.push_back(NONWORD);
    }

    build(statetab, prefix, input);
    generate(statetab, MAXGEN, output);

    input.close();
    output.close();

    std::cout << "Текст успешно сгенерирован в файл result/gen.txt" << std::endl;

    return 0;
}

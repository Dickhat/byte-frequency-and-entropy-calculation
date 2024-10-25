#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Второй параметр путь графического файла, третий параметр путь к отчету
int main(int argc, char* argv[])
{
    ifstream file;      // Исходный файл
    ofstream statistic; // Файл сводка
    
    file.open(argv[1], ios::binary);    // Дескриптор графического файла
    statistic.open(argv[2], ios::out);  // Дескриптор статистического файла

    int symbols[256];
    int countOfSymbols = 0;

    if (file.is_open() && statistic.is_open())
    {
        cout << "File is opened";

        // Зануление массива
        for (int i = 0; i < 256; ++i)
            symbols[i] = 0;

        char symbol;

        // Подсчитывание байтов
        while (file.read(&symbol, sizeof(byte)))
        {
            countOfSymbols++;
            int temp = static_cast<int>(symbol);
            symbols[int(symbol) + 128] += 1;
        }

        float entropy = 0;
        float probability;
        float partOfEntropy;

        // Вывод Частотного анализа и энтропии
        for (int i = 0; i < 256; ++i)
        {
            partOfEntropy = 0;
            probability = 0;

            probability = float(symbols[i]) / countOfSymbols;

            if(probability != 0)
                partOfEntropy = probability * log2(probability);

            statistic << left << setw(4) << i + 1 << " " << setw(5) << symbols[i] << " " 
                      << left << setw(11) << probability << " " << left << setw(11) << partOfEntropy << endl;

            entropy -= partOfEntropy;
        }

        statistic << setw(10) << countOfSymbols << " " << left << setw(11) << 1 << " " << left << setw(11) << entropy << endl;

    }
    else
    {
        cout << "File not opened";
        return -1;
    }

    return 0;
}

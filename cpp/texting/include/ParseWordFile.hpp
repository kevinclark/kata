#ifndef WORD_FILE_PARSER_HPP
#define WORD_FILE_PARSER_HPP

#include <fstream>
#include "Word.hpp"

template <typename OutIter>
void ParseWordFile(const std::string& filename, OutIter out)
{
    std::fstream file(filename.c_str(), std::ios_base::in);

    while (file)
    {
        std::string line;

        getline(file, line);
        std::string word, partOfSpeech;
        size_t termFreq, docFreq;

        file >> termFreq;
        file >> word;
        file >> partOfSpeech;
        file >> docFreq;

        *out++ = Word(word, termFreq);
    }

    file.close();
}

#endif // WORD_FILE_PARSER_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cctype>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#include "ParseWordFile.hpp"
#include "Trie.hpp"
#include "Word.hpp"

void PrintHelp(std::ostream& out)
{
    out << "Enter text messages." << std::endl
        << "Use space or 0 for spaces." << std::endl
        << "Use 843+, 843++ for alternatives." << std::endl
        << "Ctrl-D to quit." << std::endl
        << std::endl
        << "7:pqrs 8:tuv 9:wxyz" << std::endl
        << " 4:ghi 5:jkl 6:mno" << std::endl
        << "    2:abc 3:def" << std::endl << std::endl;
}

std::string NumbersFor(const std::string& str)
{
    std::stringstream stream;

    BOOST_FOREACH(char ch, str)
    {
        switch (ch)
        {
            case 'a':
            case 'b':
            case 'c':
                stream << "2";
                break;

            case 'd':
            case 'e':
            case 'f':
                stream << "3";
                break;

            case 'g':
            case 'h':
            case 'i':
                stream << "4";
                break;

            case 'j':
            case 'k':
            case 'l':
                stream << "5";
                break;

            case 'm':
            case 'n':
            case 'o':
                stream << "6";
                break;

            case 'p':
            case 'q':
            case 'r':
            case 's':
                stream << "7";
                break;

            case 't':
            case 'u':
            case 'v':
                stream << "8";
                break;

            case 'w':
            case 'x':
            case 'y':
            case 'z':
                stream << "9";
                break;

            // Put all the weird stuff somewhere else
            default:
                stream << "0";
                break;
        }
    }

    return stream.str();
}

typedef Trie<char, Word> trie_type;

std::string FindWord(const trie_type& trie, const std::string& keys, size_t alternative)
{
    typedef std::vector<Word>   Words;

    trie_type::result_type candidates = trie.find(keys);
    
    Words::const_iterator match;
    Words words(candidates.first, candidates.second);
    std::sort(words.begin(), words.end(), boost::mem_fn(&Word::MoreFrequent));

    for (Words::const_iterator word = words.begin(); word != words.end(); ++word)
    {
        match = word;

        if (alternative == 0)
        {
            break;
        }
        else
        {
            --alternative;
        }
    }

    if (match == words.end())
    {
        return "No alternative";
    }
    else
    {
        return match->str();
    }
}

int main(int argc, char* argv[])
{

    std::cout << "Loading..." << std::endl;

    std::vector<Word> words; 
    ParseWordFile("data/all.num.o5", std::back_inserter(words));

    trie_type trie;

    BOOST_FOREACH(const Word& word, words)
    {
        trie.insert(NumbersFor(word.str()), word);
    }

    PrintHelp(std::cout);

    while (std::cin)
    {
        std::string input;
        std::cin >> input;
        std::stringstream keys;
        size_t numAlternatives = 0;

        for (std::string::const_iterator ch = input.begin(); ch != input.end(); ++ch)
        {

            if (*ch == '+')
            {
                ++numAlternatives;
            }
            else if (*ch == ' ' || *ch == '0')
            {
                try
                {
                    std::cout << FindWord(trie, keys.str(), numAlternatives) << " ";
                }
                catch (const std::runtime_error& e)
                {
                    std::cout << e.what();
                }

                numAlternatives = 0;
                keys.str("");
            }
            else
            {
                keys << *ch;
            }
        }

        std::cout << FindWord(trie, keys.str(), numAlternatives) << std::endl;
    }

    return 0;
}

#ifndef WORD_HPP
#define WORD_HPP

#include <string>

class Word
{
  public:
    Word(const std::string& word, size_t termFreq)
      : m_word(word), m_termFreq(termFreq)
    {}

    bool operator<(const Word& other) const
    {
        return m_word < other.m_word;
    }

    bool MoreFrequent(const Word& other) const
    {
        return m_termFreq > other.m_termFreq;
    }

    const std::string& str() const { return m_word; }

    void print(std::ostream& out) const
    {
        out << m_word;
    }

  private:
    std::string m_word;
    size_t      m_termFreq;
};

std::ostream& operator<<(std::ostream& out, const Word& word)
{
    word.print(out);
    return out;
}

#endif // WORD_HPP

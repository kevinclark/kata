#ifndef TRIE_HPP
#define TRIE_HPP

#include <map>
#include <set>
#include <utility>
#include <iterator>
#include <boost/foreach.hpp>

template <typename Key, typename Value>
class TrieNode
{

  public:
    typedef     Key                         key_type;
    typedef     Value                       value_type;
    typedef     std::set<value_type>        storage_type;

  private:
    typedef     std::map<key_type, TrieNode*>   map_type;

  public:
    TrieNode* operator[](const key_type& key) const
    {
        typename map_type::const_iterator edge = m_edges.find(key);

        if (edge != m_edges.end())
        {
            return edge->second;
        }
        else
        {
            return NULL;
        }
    }

    void AddValue(const value_type& value)
    {
        m_values.insert(value);
    }

    const storage_type& Values() const
    {
        return m_values;
    }

    TrieNode* AddEdge(key_type key)
    {
        TrieNode* node(new TrieNode());

        m_edges.insert(std::make_pair(key, node));

        return node;
    }

    ~TrieNode()
    {
        BOOST_FOREACH(const typename map_type::value_type& edge, m_edges)
        {
            if (edge.second != NULL)
            {
                delete edge.second;
            }
        }
    }

  private:
    storage_type                m_values;
    map_type                    m_edges;
};


template <typename Key, typename Value>
class Trie
{
  public:
    typedef Key                                                     key_type;
    typedef Value                                                   value_type;
    typedef TrieNode<key_type, value_type>                          node_type;
    typedef typename node_type::storage_type::const_iterator        result_const_iterator;
    typedef std::pair<result_const_iterator, result_const_iterator> result_type;
    
    template <typename Container>
    void insert(const Container& keys, const value_type& value)
    {
        node_type* currentNode = &m_root;


        BOOST_FOREACH(const key_type& key, keys)
        {
            node_type* nextNode = (*currentNode)[key]; 

            // If this length isn't built, build it
            if (nextNode == NULL)
            {
                nextNode = currentNode->AddEdge(key);
            }

            currentNode = nextNode;
        }

        if (currentNode != NULL)
        {
            currentNode->AddValue(value);
        }
    }

    template <typename Container>
    result_type find(const Container keys) const
    {
        const node_type* currentNode = &m_root;
        const node_type* nextNode = NULL;

        BOOST_FOREACH(const key_type& key, keys)
        {
            nextNode = (*currentNode)[key];

            if (nextNode == NULL)
            {
                break;
            }

            currentNode = nextNode;
        }

        if (nextNode == NULL)
        {
            return std::make_pair(result_const_iterator(), result_const_iterator());
        }

        return std::make_pair(nextNode->Values().begin(), nextNode->Values().end());
    }

  private:

    node_type    m_root;
};

#endif

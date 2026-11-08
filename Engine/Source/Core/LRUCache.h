#pragma once

#include <list>
#include <unordered_map>
#include <optional>
#include <functional>
#include <stdexcept>
#include <utility>

namespace DarrJorge
{
template<typename Key, typename Value>
class LRUCache
{
public:
    using value_type = std::pair<Key, Value>;
    using list_type = std::list<value_type>;
    using list_iterator = typename list_type::iterator;
    using map_type = std::unordered_map<Key, list_iterator>;

    explicit LRUCache(size_t capacity) : m_capacity(capacity)
    {
        if (capacity == 0)
            throw std::invalid_argument("Capacity must be > 0");
    }

    std::optional<std::reference_wrapper<const Value>> get(const Key& key)
    {
        auto it = m_idx.find(key);
        if (it == m_idx.end()) return std::nullopt;

        m_entries.splice(m_entries.begin(), m_entries, it->second);
        return std::cref(it->second->second);
    }

    void put(const Key& key, Value value)
    {
        auto it = m_idx.find(key);
        if (it != m_idx.end())
        {
            it->second->second = std::move(value);
            m_entries.splice(m_entries.begin(), m_entries, it->second);
            return;
        }

        if (m_entries.size() == m_capacity)
        {
            const Key& evictKey = m_entries.back().first;
            m_idx.erase(evictKey);
            m_entries.pop_back();
        }

        m_entries.emplace_front(key, std::move(value));

        try
        {
            m_idx.emplace(key, m_entries.begin());
        }
        catch (...)
        {
            m_entries.pop_front();
            throw;
        }
    }

    bool contains(const Key& key) const
    {
        return m_idx.find(key) != m_idx.end();
    }

    [[nodiscard]] size_t size() const noexcept { return m_entries.size(); }
    [[nodiscard]] size_t capacity() const noexcept { return m_capacity; }

private:
    size_t m_capacity;
    list_type m_entries;
    map_type m_idx;
};
}


#ifndef SPARSEARRAY_HPP
    #define SPARSEARRAY_HPP

    #include <vector>
    #include <optional>
    #include <cstdio>
    #include <iostream>
    #include <limits>

template <typename Component>
class SparseArray {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = const value_type&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    SparseArray() = default;
    SparseArray(SparseArray const &) = default;
    SparseArray(SparseArray &&) noexcept = default;
    ~SparseArray() = default;

    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;

    iterator begin() { return data_.begin(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator cbegin() const { return data_.cbegin(); }

    iterator end() { return data_.end(); }
    const_iterator end() const { return data_.end(); }
    const_iterator cend() const { return data_.cend(); }

    size_type size() const { return data_.size(); }

    reference_type insert_at(size_type pos, const Component& value);
    reference_type insert_at(size_type pos, Component&& value);

    void erase(size_type pos);

    size_type get_index(const value_type& value) const;

private:
    container_t data_;
};

#include "./Sparse_away.cpp" // Include the source file here

#endif /* !SPARSEARRAY_HPP */
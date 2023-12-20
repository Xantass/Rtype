
#include "./SparseArray.hpp"

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, const Component& value) {
    if (pos >= data_.size()) {
        data_.resize(pos + 1);
    }
    data_[pos] = value;
    return data_[pos];
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, Component&& value) {
    if (pos >= data_.size()) {
        data_.resize(pos + 1);
    }
    data_[pos] = std::move(value);
    return data_[pos];
}

template <typename Component>
void SparseArray<Component>::erase(size_type pos) {
    if (pos < data_.size()) {
        data_[pos] = std::nullopt;
    }
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::operator[](size_t idx) {
    return data_[idx];
}

template <typename Component>
typename SparseArray<Component>::const_reference_type SparseArray<Component>::operator[](size_t idx) const {
    return data_[idx];
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::get_index(const value_type& value) const {
    auto it = std::find(data_.begin(), data_.end(), value);
    if (it != data_.end()) {
        return std::distance(data_.begin(), it);
    }
    return std::numeric_limits<size_type>::max();
}
#pragma once
#include <iostream>


template<typename Iterator>
concept BidirectionalIterator = requires(Iterator it) {
    { *it };
    { ++it };
    { it++ };
    { --it };
    { it-- };
};

template<typename Range>
concept HasBidirectionalIterator = requires(Range range) {
    { range.begin() } -> BidirectionalIterator;
    { range.end() } -> BidirectionalIterator;
};


template<typename Container>
concept HasKey = requires(Container container) {
    { container.begin()->first };
};

template<typename Container>
concept HasValue = requires(Container container) {
    { container.begin()->second };
};

//transform - изменяют значения элементов наподобие того как это делает алгоритм transform
//filter - фильтрация по определенному признаку, признак передается в качестве аргумента
//take - берет только N первых элементов
//drop - пропускаем N первых элементов
//reverse - реверсия
//keys - ключи для ассоциативных контейнеров
//values - значения для ассоциативных контейнеров

template<typename InputIterator, typename Func>
class TransformedRange {
    //transform - изменяют значения элементов наподобие того как это делает алгоритм transform
public:
    TransformedRange(InputIterator begin, InputIterator end, Func function)
            : begin_(begin)
            , end_(end)
            , function_(function)
    {}

    class Iterator {
    public:
        Iterator(InputIterator current, Func function)
                : current_(current)
                , function_(function)
        {}

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++current_;
            return tmp;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --current_;
            return tmp;
        }

        bool operator!=(const Iterator &other) const {
            return current_ != other.current_;
        }

        auto operator*() const {
            return function_(*current_);
        }

    private:
        InputIterator current_;
        Func function_;
    };

    Iterator begin() const {
        return Iterator(begin_, function_);
    }

    Iterator end() const {
        return Iterator(end_, function_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
    Func function_;
};


template<typename InputIterator, typename Predicate>
class FilteredRange {
    //filter - фильтрация по определенному признаку, признак передается в качестве аргумента
public:
    FilteredRange(InputIterator begin, InputIterator end, Predicate predicate)
            : begin_(begin)
            , end_(end)
            , predicate_(predicate)
    {}

    class Iterator {
    private:
        InputIterator current_;
        InputIterator end_;
        Predicate predicate_;

    public:
        Iterator(InputIterator current, InputIterator end, Predicate predicate)
                : current_(current)
                , end_(end)
                , predicate_(predicate) {
            next();
        }

        Iterator& operator++() {
            ++current_;
            next();
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++current_;
            next();
            return tmp;
        }

        Iterator& operator--() {
            --current_;
            prev();
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --current_;
            prev();
            return tmp;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        auto operator*() const {
            return *current_;
        }

    private:
        void next() {
            while (current_ != end_ && !predicate_(*current_)) {
                ++current_;
            }
        }

        void prev() {
            while (current_ != end_ && !predicate_(*current_)) {
                --current_;
            }
        }
    };

    Iterator begin() const {
        return Iterator(begin_, end_, predicate_);
    }

    Iterator end() const {
        return Iterator(end_, end_, predicate_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
    Predicate predicate_;
};


template<typename InputIterator>
class BasicRange {
    //take - берет только N первых элементов
    //drop - пропускаем N первых элементов
public:
    BasicRange(InputIterator begin, InputIterator end)
            : begin_(begin)
            , end_(end)
    {}

    class Iterator {
    public:
        Iterator(InputIterator current)
                : current_(current) {}

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++current_;
            return tmp;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            --current_;
            return tmp;
        }

        bool operator!=(const Iterator &other) const {
            return current_ != other.current_;
        }

        auto operator*() const {
            return *current_;
        }

    private:
        InputIterator current_;
    };

    Iterator begin() const {
        return Iterator(begin_);
    }

    Iterator end() const {
        return Iterator(end_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
};


template<typename InputIterator>
class ReverseRange {
public:
    ReverseRange(InputIterator begin, InputIterator end)
            : begin_(begin)
            , end_(end)
    {}

    class Iterator {
    public:
        Iterator(InputIterator current)
                : current_(current) {}

        Iterator& operator++() {
            --current_;
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            --current_;
            return tmp;
        }

        Iterator& operator--() {
            ++current_;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            ++current_;
            return tmp;
        }

        bool operator!=(const Iterator &other) const {
            return current_ != other.current_;
        }

        auto operator*() const {
            return *current_;
        }

    private:
        InputIterator current_;
    };

    Iterator begin() const {
        return Iterator(begin_);
    }

    Iterator end() const {
        return Iterator(end_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
};


template<typename InputIterator>
class KeysRange {
public:
    KeysRange(InputIterator begin, InputIterator end)
            : begin_(begin)
            , end_(end)
    {}

    class Iterator {
    public:
        Iterator(InputIterator iter) : current_(iter) {}

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++current_;
            return tmp;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --current_;
            return tmp;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        const auto& operator*() const {
            return current_->first;
        }

    private:
        InputIterator current_;
    };

    Iterator begin() const {
        return Iterator(begin_);
    }

    Iterator end() const {
        return Iterator(end_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
};




template<typename InputIterator>
class ValuesRange {
public:
    ValuesRange(InputIterator begin, InputIterator end)
            : begin_(begin)
            , end_(end)
    {}

    class Iterator {
    public:
        Iterator(InputIterator current) : current_(current) {}

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++current_;
            return tmp;
        }

        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --current_;
            return tmp;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        const auto& operator*() const {
            return current_->second;
        }

    private:
        InputIterator current_;
    };

    Iterator begin() const {
        return Iterator(begin_);
    }

    Iterator end() const {
        return Iterator(end_);
    }

private:
    InputIterator begin_;
    InputIterator end_;
};


template<typename Func>
struct my_transform {
    Func function;
    my_transform(Func func) : function(func) {}
};


template<typename Func>
struct my_filter {
    Func predicate;
    my_filter(Func func) : predicate(func) {}
};


struct my_take {
    size_t count;
    my_take(size_t count) : count(count) {}
};


struct my_drop {
    size_t count;
    my_drop(size_t count) : count(count) {}
};


struct my_reverse {
    my_reverse() = default;
};


struct my_values {
    my_values() = default;
};


struct my_keys {
    my_keys() = default;
};

//transform
template<typename InputRange, typename Func>
requires HasBidirectionalIterator<InputRange>
auto operator|(const InputRange& range, const my_transform<Func>& transform) {
    return TransformedRange(range.begin(), range.end(), transform.function);
}

//filter
template<typename InputRange, typename Func>
requires HasBidirectionalIterator<InputRange>
auto operator|(const InputRange& range, const my_filter<Func>& filter) {
    return FilteredRange(range.begin(), range.end(), filter.predicate);
}

//take
template<typename InputRange>
requires HasBidirectionalIterator<InputRange>
auto operator|(const InputRange& range, const my_take& take) {
    auto new_end = range.begin();
    for (size_t i = 0; i < take.count && new_end != range.end(); ++i) {
        ++new_end;
    }
    return BasicRange(range.begin(), new_end);
}

//drop
template<typename InputRange>
auto operator|(const InputRange& range, const my_drop& drop) {
    auto new_begin = range.begin();
    for (size_t i = 0; i < drop.count && new_begin != range.end(); ++i) {
        ++new_begin;
    }
    return BasicRange(new_begin, range.end());
}

//reverse
template<typename InputRange>
requires HasBidirectionalIterator<InputRange>
auto operator|(const InputRange& range, const my_reverse& reverse) {
    return ReverseRange(--range.end(), --range.begin());
}

//keys
template<typename InputRange>
requires HasBidirectionalIterator<InputRange> && HasKey<InputRange>
auto operator|(const InputRange& range, const my_keys& k) {
    return KeysRange(range.begin(), range.end());
}


//values
template<typename InputRange>
requires HasBidirectionalIterator<InputRange> && HasValue<InputRange>
auto operator|(const InputRange& range, const my_values& v) {
    return ValuesRange(range.begin(), range.end());
}
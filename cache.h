/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file cache.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-11-25 14:54:12

 * @brief 
 */
#pragma once

#include <array>
#include <cstddef>
#include <chrono>
#include <functional>
#include <utility>

namespace cache {

template <typename Tp_, std::size_t N_> class FixedQueue;
template <typename _Tp> class Item;
template <typename _Tp, std::size_t _N> class Cache {
    FixedQueue<Item<_Tp>, _N> queue_;
public:
    Cache() = default;

    void Update(_Tp&& val) {
        queue_.Enqueue(std::forward<_Tp>(val));
    }

    _Tp Peek(bool *ok) const {
        return queue_.PeekNew().Value(ok);
    }
};

template <typename _Tp> class Item {
    bool slot_;
    _Tp value_;
    std::chrono::steady_clock::time_point at_;
public:
    // using ms = std::chrono::milliseconds;
    // using sec = std::chrono::seconds;
    typedef long long ms;
    typedef long long sec;

    Item() : slot_(true), at_(std::chrono::steady_clock::now()) {}
    Item(_Tp&& val) : slot_(false), value_(std::forward<_Tp>(val)), at_(std::chrono::steady_clock::now()) {}
    Item(const Item& other) : slot_(other.slot_), value_(other.value_), at_(std::chrono::steady_clock::now()) {}
    Item(Item&& other) : slot_(other.slot_), value_(std::move(other.value_)), at_(std::chrono::steady_clock::now()) {}

    Item& operator=(const Item& other) {
        slot_ = other.slot_;
        value_ = other.value_;
        at_ = std::chrono::steady_clock::now();
        return *this;
    }

    bool Valid() const
    { return !slot_; }

    ms LifeMs() const { if (Valid()) return -1; return lifeMs(); }
    sec LifeSec() const { if (Valid()) return -1; return lifeSec(); }

    _Tp Value(bool *ok) const
    { return *ok = Valid(), value_; }

protected:
private:
    ms lifeMs() const
    { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - at_).count(); }
    sec lifeSec() const
    { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - at_).count(); }
};


template <typename Tp_, std::size_t N_> class FixedQueue {
    static_assert(N_ > 0, "FixedQueue capacity must be greater than 0");
    const Tp_ kTpNull = Tp_();

    std::size_t new_, old_, len_;
    std::array<Tp_, N_> data_;
public:

    FixedQueue() : new_(0), old_(0), len_(0) {}
    ~FixedQueue() = default;
    FixedQueue(const FixedQueue&) = delete;
    FixedQueue(FixedQueue&&) = delete;

    void Enqueue(const Tp_& item) {
        auto copy = item;
        Enqueue(std::move(copy));
    }
    void Enqueue(Tp_&& item) {
        data_[new_] = std::forward<Tp_>(item);
        new_ = Advance(new_);

        if (Full()) {
            old_ = Advance(old_);
            return;
        }

        ++len_;
    }
    void Dequeue() {
        (void) TakeDequeue();
    }
    Tp_ TakeDequeue() {
        if (Empty()) {
            return kTpNull;
        }

        --len_;
        std::size_t pos = old_;
        old_ = Advance(old_);
        return data_[pos];
    }

    std::size_t Len() const {
        return len_;
    }

    std::size_t Cap() const 
    { return N_; }

    bool Full() const
    { return len_ == N_; }

    bool Empty() const
    { return len_ == 0; }

    void Debug(std::function<void(const Tp_&)> print) const {
        std::size_t tail = old_;
        std::size_t len = len_;
        for (;len > 0; --len) {
            print(data_[tail]);
            tail = Advance(tail);
        }
    }

    Tp_ PeekNew() const {
        if (Empty()) {
            return kTpNull;
        }

        return data_[Rewind(new_)] ;
    }

    Tp_ PeekOld() const {
        if (Empty()) {
            return kTpNull;
        }

        return data_[old_];
    }

protected:
    std::size_t Advance(std::size_t pos)  const
    { return (pos + 1) % N_; }
    std::size_t Rewind(std::size_t pos) const
    { return (pos + N_ - 1) % N_; }
private:
};


} /* namespace cache */

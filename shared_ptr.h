#pragma once
#include <atomic>
#include <algorithm>
#include <cassert>

namespace mysharedsptr
{
template<typename T>
class shared_ptr
{
private:
    T* _ptr;
    std::size_t* _count;
public:
    shared_ptr(T* ptr = nullptr)
    {
        _ptr = ptr;
        if (ptr)
        {
            _count = new std::size_t(1);
        }
        else
        {
            _count = new std::size_t(0);
        }
    }

    shared_ptr(const shared_ptr& other)
    {
        _ptr = other._ptr;
        _count = other._count;
        (*_count)++;
    }

    ~shared_ptr()
    {
        if(_ptr == nullptr)
        {
            delete _count;
            return;
        }
        (*_count)--;
        if (*_count == 0)
        {
            delete _ptr;
            delete _count;
        }
    }

    // 当shared_ptr赋予一个新值或是shared_ptr被销毁，计数器递减
    shared_ptr& operator=(const shared_ptr& other)
    {
        if (this != &other)
        {
            if (_ptr)
            {
                // 旧引用计数减一
                (*_count)--;
                // 原来指向的对象已经没有引用者，则释放
                if (*_count == 0)
                {
                    delete _ptr;
                    delete _count;
                }
            }
            _ptr = other._ptr;
            _count = other._count;
            // 新引用计数加一
            (*_count)++;
        }
        return *this;
    }

    T* get() const
    {
        return _ptr;
    }

    T& operator*() const
    {
        assert(_ptr != nullptr);
        return *_ptr;
    }

    T* operator->() const
    {
        assert(_ptr != nullptr);
        return _ptr;
    }

    std::size_t use_count() const
    {
        return *_count;
    }

    void swap(shared_ptr& rhs)
    {
        std::swap(_ptr, rhs._ptr);
        std::swap(_count, rhs._count);
    }
};

template <typename T>
void swap(shared_ptr<T> &left, shared_ptr<T> &right) {
    left.swap(right);
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
}
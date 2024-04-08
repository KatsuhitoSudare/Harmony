#pragma once
#include "gc_cpp.h"
#include "gc/gc_allocator.h"
#include <algorithm> // std::copyを使用
#include <initializer_list> // 初期化リストのサポート

namespace HARMONY
{
	template<typename T>
	class HMArray
	{
    public:
        using value_type = T;
        using iterator = value_type*;
        using const_iterator = const value_type*;

        HMArray();
        HMArray(std::initializer_list<value_type> init);
        HMArray(size_t size);
        ~HMArray() = default;

        void Add(const value_type& value);
        size_t GetSize() const;
        value_type* GetData()const;
        value_type& Back()const;
        bool isEmpty()const noexcept;
        value_type& operator[](size_t size)const;
        void ReSize(size_t size);
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

    private:
        value_type* data;
        size_t capacity;
        size_t size;

        void ensureCapacity(size_t minCapacity);
	};
    
}

// デフォルトのメタ関数定義。特定の型にはマッチしない。
template<typename T>
struct is_innertype {
    
};

// HMArrayに対する特殊化。
template<typename T>
struct is_innertype<HARMONY::HMArray<T>> {
    // HMArrayから内部型Tを抜き出す。
    using type = T;
};

#include"detail/HMArray_impl.inl"
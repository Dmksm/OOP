#pragma once

#include "stdafx.h"


template <typename T>
class CMyArray
{
	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;

	public:
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_item(other.m_item)
		{
		}

		reference& operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}

		MyType operator+(difference_type offset) const
		{
			MyType self(m_item);
			return self += offset;
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}

	public:
		IteratorBase(T* item)
			: m_item(item)
		{
		}

	protected:
		T* m_item = nullptr;
	};

public:
	CMyArray& operator=(CMyArray && arr)
	{
		if (this != &arr)
		{
			DeleteItems(m_begin, m_end);
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;

			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}

		return *this;
	}

	CMyArray& operator=(const CMyArray& arr)
	{
		if (this != std::addressof(arr))
		{
			size_t newCapacity = arr.GetCapacity();

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(arr.m_begin, arr.m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		
		return *this;
	}

	T& operator[](size_t offset)
	{
		if (offset >= this->GetSize())
		{
			throw std::out_of_range("out of range with index ");
		}

		return *(this->m_begin + offset);
	}

	const T& operator[](size_t offset) const
	{
		return this[offset];
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}
	
	void Resize(size_t size, const T& value)
	{
		if (size < 0)
		{
			throw std::invalid_argument("size for resize must be positive or zero");
		}
		if (size == 0)
		{
			Clear();
			return;
		}

		size_t currSize = this->GetSize();
		if (size != currSize)
		{
			if (size < currSize)
			{
				DestroyItems(m_end - (currSize - size), m_end);
				m_end -= (currSize - size);
			}
			else
			{
				while (size > currSize)
				{
					--size;
					Append(value);
				}
			}
		}
	}

	void Resize(size_t count)
	{
		Resize(count, 0);
	}

	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		if (this != std::addressof(arr))
		{
			const auto size = arr.GetSize();
			if (size != 0)
			{
				m_begin = RawAlloc(size);
				try
				{
					CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
					m_endOfCapacity = m_end;
				}
				catch (...)
				{
					DeleteItems(m_begin, m_end);
					throw;
				}
			}
		}
	}

	CMyArray(CMyArray&& arr)
	{
		this = std::move(arr);
	}

	void Append(const T& value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	T& GetBack()
	{
		if (GetSize() == 0u)
		{
			throw std::out_of_range("Array is empty!");
		}
		return m_end[-1];
	}

	const T& GetBack() const
	{
		if (GetSize() == 0u)
		{
			throw std::out_of_range("Array is empty!");
		}
		return m_end[-1];
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator begin()
	{
		return { m_begin };
	}

	const_iterator begin() const
	{
		return { m_begin };
	}

	iterator end()
	{
		return { m_end - 1};
	}

	const_iterator end() const
	{
		return { m_end - 1};
	}

	const_iterator cbegin() const
	{
		return { m_begin };
	}

private:
	static void DeleteItems(T* begin, T* end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};
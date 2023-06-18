#pragma once
#include "stdafx.h"

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

public:
	size_t GetSize() const;
	void Append(const std::string& data);
	void Prepend(const std::string& data);

	class CBaseIterator
	{
		friend CStringList;
		CBaseIterator(Node* node);

	public:
		CBaseIterator() = default;
		void operator=(const std::string& data);
		bool operator==(const CBaseIterator& it) const;

	private:
		Node* m_node = nullptr;
	};

	class CIterator : public CBaseIterator
	{
	public:
		using CBaseIterator::operator=;
		bool operator==(const CIterator& it) const
		{
			return CBaseIterator::operator==(it);
		}
		std::string& operator*() const;
		CIterator& operator++();
		CIterator& operator--();
	};

	class CConstIterator : public CBaseIterator
	{
	public:
		using CBaseIterator::operator=;
		bool operator==(const CConstIterator& it) const
		{
			return CBaseIterator::operator==(it);
		}
		const std::string& operator*() const;
		CConstIterator& operator++();
		CConstIterator& operator--();
	};	

	class CReverseIterator : public CBaseIterator
	{
	public:
		using CBaseIterator::operator=;
		bool operator==(const CReverseIterator& it) const
		{
			return CBaseIterator::operator==(it);
		}
		std::string& operator*() const;
		CReverseIterator& operator++();
		CReverseIterator& operator--();
	};

	class CConstReverseIterator : public CBaseIterator
	{
	public:
		using CBaseIterator::operator=;
		bool operator==(const CConstReverseIterator& it) const
		{
			return CBaseIterator::operator==(it);
		}
		const std::string& operator*() const;
		CConstReverseIterator& operator++();
		CConstReverseIterator& operator--();
	};

	CIterator begin();
	CIterator end();
	CConstIterator cbegin();
	CConstIterator cend();
	CReverseIterator rbegin();
	CReverseIterator rend();
	CConstReverseIterator crbegin();
	CConstReverseIterator crend();

	CStringList() = default;

	CStringList& operator=(const CStringList& list);

	CStringList& operator=(CStringList&& list) noexcept;

	CStringList(CStringList&& list) noexcept;

	CStringList(const CStringList& list);

	CIterator Insert(CConstIterator it, const std::string& data);
	CIterator Erase(CIterator it);
	void Clear();
	bool IsEmpty() const;
	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	~CStringList();

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};
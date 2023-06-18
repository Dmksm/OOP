#include "stdafx.h"
#include "CStringList.h"

using namespace std;

CStringList& CStringList::operator=(const CStringList& list)
{
	if (this != std::addressof(list))
	{	
		auto currNode = move(list.m_firstNode.get());
		while (currNode)
		{
			Append(currNode->data);
			currNode = move(currNode->next.get());
		}
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& list) noexcept
{
	if (this != std::addressof(list))
	{
		m_size = std::move(list.m_size);
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = std::move(list.m_lastNode);

		list.m_size = 0;
		list.m_firstNode = nullptr;
		list.m_lastNode = nullptr;
	}
	return *this;
}

CStringList::CStringList(CStringList&& list) noexcept
{
	*this = std::move(list);
}

CStringList::CStringList(const CStringList& list)
{
	*this = list;
}

CStringList::~CStringList()
{
	this->Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Append(const std::string& data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::Prepend(const std::string& data)
{
	auto newNode = make_unique<Node>(data, nullptr, nullptr);
	newNode->next = move(m_firstNode);
	Node* newFirstNode = newNode.get();
	if (m_lastNode == nullptr)
	{
		m_lastNode = newFirstNode;
	}
	m_firstNode = move(newNode);
	++m_size;
}

void CStringList::Clear()
{
	auto currNode = move(m_firstNode);
	while (currNode)
	{
		currNode.get()->data.clear();
		currNode = move(currNode.get()->next);
	}
	m_lastNode = nullptr;
	m_size = 0;
}

bool CStringList::IsEmpty() const 
{
	return m_size == 0;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode->next.get());
}

CStringList::CConstIterator CStringList::cbegin()
{
	return CConstIterator(m_firstNode.get());
}

CStringList::CConstIterator CStringList::cend()
{
	return CConstIterator(m_lastNode->next.get());
}

CStringList::CReverseIterator CStringList::rbegin()
{
	return CReverseIterator(m_lastNode);
}

CStringList::CReverseIterator CStringList::rend()
{
	return CReverseIterator(m_firstNode->prev);
}

CStringList::CConstReverseIterator CStringList::crbegin()
{
	return CConstReverseIterator(m_lastNode);
}

CStringList::CConstReverseIterator CStringList::crend()
{
	return CConstReverseIterator(m_firstNode->prev);
}

std::string& CStringList::GetBackElement()
{
	if (!m_lastNode)
	{
		throw std::logic_error("last node is null!");
	}
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (!m_lastNode)
	{
		throw std::logic_error("last node is null!");
	}
	return m_lastNode->data;
}

CStringList::CIterator CStringList::Erase(CIterator it)
{
	if (m_size == 1)
	{
		Clear();
		return CIterator();
	}

	const auto result = it.m_node->next.get();
	if (it.m_node != m_lastNode)
	{
		result->prev = it.m_node->prev;
	}
	else
	{
		m_lastNode = it.m_node->prev;
	}

	it.m_node->data.clear();
	if (m_firstNode.get() == it.m_node)
	{
		m_firstNode = std::move(m_firstNode->next);
	}
	else
	{
		it.m_node->prev->next = move(it.m_node->next);
	}
	--(this->m_size);

	return CIterator(result);
}

CStringList::CIterator CStringList::Insert(CConstIterator it, const std::string& data)
{
	if (m_firstNode.get() == it.m_node)
	{
		Prepend(data);
		return begin();
	}
	if (it == cend())
	{
		Append(data);
		return CIterator(m_lastNode);
	}

	Node* prevNode = it.m_node->prev;
	auto newNode = make_unique<Node>(data, prevNode, nullptr);
	newNode->next = move(prevNode->next);
	auto resultIterator = CIterator(newNode.get());
	prevNode->next = move(newNode);

	++m_size;
	return resultIterator;
}


CStringList::CBaseIterator::CBaseIterator(Node* node)
	: m_node(node)
{
}

bool CStringList::CBaseIterator::operator==(const CBaseIterator& it) const
{
	return this->m_node == it.m_node;
}

std::string& CStringList::CIterator::operator*() const
{
	return m_node->data;
}

const std::string& CStringList::CConstIterator::operator*() const
{
	return m_node->data;
}

std::string& CStringList::CReverseIterator::operator*() const
{
	return m_node->data;
}

const std::string& CStringList::CConstReverseIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	m_node = m_node->prev;
	return *this;
}

CStringList::CConstIterator& CStringList::CConstIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

CStringList::CConstIterator& CStringList::CConstIterator::operator--()
{
	m_node = m_node->prev;
	return *this;
}

CStringList::CReverseIterator& CStringList::CReverseIterator::operator++()
{
	m_node = m_node->prev;
	return *this;
}

CStringList::CReverseIterator& CStringList::CReverseIterator::operator--()
{
	m_node = m_node->next.get();
	return *this;
}

CStringList::CConstReverseIterator& CStringList::CConstReverseIterator::operator++()
{
	m_node = m_node->prev;
	return *this;
}

CStringList::CConstReverseIterator& CStringList::CConstReverseIterator::operator--()
{
	m_node = m_node->next.get();
	return *this;
}

void CStringList::CBaseIterator::operator=(const std::string& data)
{
	this->m_node->data = data;
}
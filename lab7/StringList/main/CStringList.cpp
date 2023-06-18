#include "stdafx.h"
#include "CStringList.h"
#include <cassert>

using namespace std;

CStringList& CStringList::operator=(const CStringList& list)
{

}

CStringList& CStringList::operator=(CStringList&& list)
{
	if (this != std::addressof(list))
	{
		m_size = list.m_size;
		m_firstNode = list.m_firstNode;
		m_lastNode = list.m_lastNode;
	}
	return *this;
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
	else // empty list
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

std::string& CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

CStringList::CIterator::CIterator(Node* node)
	: m_node(node)
{
}

std::string& CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}
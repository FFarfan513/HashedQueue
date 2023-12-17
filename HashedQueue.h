#pragma once

#include <list>
#include <unordered_map>

template<typename QueuedType> class HashedQueue
{
private:
	using ListPosition = std::list<QueuedType>::iterator;

	std::unordered_map<QueuedType, ListPosition> internalMap;
	std::list<QueuedType> internalList;

public:
	inline size_t Size() { return internalList.size(); }

	void Enqueue(const QueuedType& item)
	{
		if (!Contains(item))
		{
			internalList.push_back(item);
			internalMap[item] = --internalList.end();
		}
	}

	void Emplace(const QueuedType& item)
	{
		if (!Contains(item))
		{
			internalList.emplace_back(item);
			internalMap.emplace(item, --internalList.end());
		}
	}

	QueuedType Dequeue()
	{
		QueuedType result = internalList.front();
		internalMap.erase(result);
		internalList.pop_front();
		return result;
	}

	void Erase(QueuedType item)
	{
		if (Contains(item))
		{
			ListPosition position = internalMap[item];
			internalList.erase(position);
			internalMap.erase(item);
		}
	}

	inline QueuedType Peek()
	{
		return internalList.front();
	}

	inline bool Contains(const QueuedType& item) const
	{
		return internalMap.find(item) != internalMap.end();
	}

	void Empty()
	{
		internalMap.empty();
		internalList.empty();
	}

	void Reserve(size_t capacity)
	{
		internalMap.reserve(capacity);
	}
};

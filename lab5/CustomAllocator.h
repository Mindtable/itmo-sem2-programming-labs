#pragma once

#include <iostream>
#include <windows.h>
#include <cassert>

class Block
{
public:
	void changeUsed()
	{
		assert(size % WORD_T <= 1UL);
		if (size % WORD_T)
		{
			size -= 1UL;
		}
		else
		{
			size += 1UL;
		}
	}
	bool getUsed()
	{
		return (bool) size % WORD_T;
	}
	std::size_t getSize()
	{
		return WORD_T * (size / WORD_T);
	}

	void merge(Block& b)
	{
		if (b.next != nullptr)
		{
			b.next->prev = this;
		}
		next = b.next;
		size += b.getSize() + sizeof(Block);
		//std::cout << "merge " << this << " new size " << size << std::endl;
	}

	void split(std::size_t newSize)
	{
		std::size_t sizeDiff = getSize() - newSize;
		Block* newBlock = (Block*)((char*)this + sizeof(Block) + newSize);
		newBlock->next = next;
		newBlock->prev = this;
		newBlock->size = sizeDiff - sizeof(Block);

		next = newBlock;
		size = newSize;

		std::cout << "split " << this << " new size " << newSize << std::endl;
	}

public:
	Block* prev, * next;
	std::size_t size;

	constexpr static std::size_t WORD_T = sizeof(void*);
};

template<typename T>
class CustomAllocator
{
public:
	using value_type = T;
    using pointer = T*;

	CustomAllocator()
		: m_areaSize(80 * 1024 * MIN_AREA_SIZE / 4)
		, m_chunksList(nullptr)
	{
		m_areaBegin = VirtualAlloc(NULL, m_areaSize, MEM_COMMIT, PAGE_READWRITE);
		m_curBrk = m_areaBegin;
		m_areaEnd = (char*)m_areaBegin + m_areaSize;
	};
	~CustomAllocator()
	{
		VirtualFree(m_areaBegin, 0, MEM_RELEASE);
	};

	pointer allocate(std::size_t size)
	{
		std::cout << "allocate call " << size << std::endl;
		if (size == 0)
		{
			return nullptr;
		}

		size = alignSize(size);
		auto curBlock = m_chunksList;
		if (curBlock != nullptr)
		{
			if (!curBlock->getUsed() && curBlock->getSize() >= size)
			{
				if (curBlock->getSize() - size > sizeof(Block))
				{
					curBlock->split(size);
				}
				curBlock->changeUsed();
				return (T*)((char*)curBlock + sizeof(Block));
			}

			while (curBlock->next != nullptr)
			{
				curBlock = curBlock->next;

				if (!curBlock->getUsed() && curBlock->getSize() >= size)
				{
					if (curBlock->getSize() - size > sizeof(Block))
					{
						curBlock->split(size);
					}
					curBlock->changeUsed();
					return (T*)((char*)curBlock + sizeof(Block));
				}
			}

			if (!curBlock->getUsed() && curBlock->getSize() >= size)
			{
				if (curBlock->getSize() - size > sizeof(Block))
				{
					curBlock->split(size);
				}
				curBlock->changeUsed();
				return (T*)((char*)curBlock + sizeof(Block));
			}
		}
		if ((void*)((char*)m_curBrk + sizeof(Block) + size) > m_areaEnd)
		{
			throw std::bad_alloc();
		}



		auto kek = (Block*)m_curBrk;
		*((Block*)m_curBrk) = Block();
		((Block*)m_curBrk)->prev = curBlock;
		((Block*)m_curBrk)->next = nullptr;
		((Block*)m_curBrk)->size = size;
		((Block*)m_curBrk)->changeUsed();

		if (curBlock != nullptr)
		{
			curBlock->next = (Block*)m_curBrk;
			m_curBrk = (void*)((char*)m_curBrk + sizeof(Block) + size);
			return (T*)((char*)curBlock->next + sizeof(Block));
		}
		else
		{
			m_chunksList = (Block*)m_curBrk;
			m_curBrk = (void*)((char*)m_curBrk + sizeof(Block) + size);
			return (T*)((char*)m_chunksList + sizeof(Block));
		}


	};
	void deallocate(void* ptr, std::size_t count = 0)
	{
		//std::cout << count << " deallocate call " << ptr << std::endl;
		if (ptr == nullptr ||
			ptr < (void*)((char*)m_areaBegin + sizeof(Block)) ||
			ptr > m_areaEnd) {
			std::cout << "something went wrong..." << ptr << std::endl;
			return;
		}

		auto pBlock = (Block*)((char*)ptr - sizeof(Block));
		pBlock->changeUsed();
		while (pBlock->next != nullptr && !pBlock->next->getUsed())
		{
			pBlock->merge(*(pBlock->next));
		}
		while (pBlock->prev != nullptr && !pBlock->prev->getUsed())
		{
			pBlock->prev->merge(*(pBlock));
			pBlock = pBlock->prev;
		}
	};

private:
	std::size_t calculateAreaSize(std::size_t size)
	{
		if (size % MIN_AREA_SIZE == 0)
		{
			return size;
		}
		else
		{
			return MIN_AREA_SIZE * (size / MIN_AREA_SIZE + 1);
		}
	};
	std::size_t alignSize(std::size_t size)
	{
		if (size % WORD_T == 0)
		{
			return size;
		}
		else
		{
			return WORD_T * (size / WORD_T + 1);
		}
	};

private:
	constexpr static std::size_t MIN_AREA_SIZE = 4096UL;
	constexpr static std::size_t WORD_T = sizeof(void*);

	void* m_areaBegin;
	void* m_curBrk;
	void* m_areaEnd;
	std::size_t m_areaSize;
	Block* m_chunksList;
};


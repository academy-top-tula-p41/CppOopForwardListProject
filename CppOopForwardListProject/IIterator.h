#pragma once

template <typename T>
class IIterator
{
public:
	virtual void Setup() = 0;
	virtual bool Next() = 0;
	virtual T Current() = 0;
	virtual bool IsEnd() = 0;
};




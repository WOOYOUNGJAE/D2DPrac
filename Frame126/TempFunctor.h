#pragma once

template<typename T>
void	Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void	Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

// Functor

class CDeleteObj
{
public:
	template<typename T>
	void		operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void		operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

class CTagFinder
{
public:
	CTagFinder(char* pTag)
		: m_pTag(pTag)
	{

	}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		if (!strcmp(Pair.First, m_pTag))
			return true;

		return false;
	}

private:
	char*		m_pTag;
};
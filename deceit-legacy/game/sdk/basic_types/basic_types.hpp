#pragma once

template<typename T>
class TArray
{
private:
	T* _data;
	int32_t _count;
	int32_t _max;

	friend class FString;
public:
	TArray( )
	{
		_data = nullptr;
		_count = 0;
		_max = 0;
	}

	T* Data( ) const
	{
		return _data;
	}

	int32_t Count( ) const
	{
		return _count;
	}

	int32_t Max( ) const
	{
		return _max;
	}

	bool IsValidIndex( int32_t i ) const
	{
		return i < _count;
	}

	T& operator[]( int32_t i )
	{
		return _data[i];
	}

	const T& operator[]( int32_t i ) const
	{
		return _data[i];
	}
};
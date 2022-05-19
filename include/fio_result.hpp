#pragma once
#include <fio_base.hpp>

FIO_BEGIN

class file_result
{
public:
	file_result(void* data)
		: _data(data)
	{}

	~file_result() = default;

	inline char* str() { return reinterpret_cast<char*>(_data); }
	inline const char* c_str() const { return reinterpret_cast<const char*>(_data); }

	inline short* stream_16() { return reinterpret_cast<short*>(_data); }
	inline int* stream_32() { return reinterpret_cast<int*>(_data); }
	inline float* stream_32f() { return reinterpret_cast<float*>(_data); }

	inline operator void* () const { return _data; }
	inline operator bool() const { return _data; }
private:
	void* _data;
};

const file_result file_result_null = nullptr;

FIO_END

#pragma once
#include <fio_base.hpp>
#include <fio_result.hpp>
#include <fstream>

FIO_BEGIN

DEPTHS_BEGIN

DEPTHS_END

class file_utils
{
protected:
	inline std::ios_base::openmode translate_mode(u32 flags)
	{
		while (flags) {
			if ((flags & open_mode::read) == open_mode::read) return std::ios::in;
			if ((flags & open_mode::write) == open_mode::write) return std::ios::out;
			if ((flags & open_mode::binary) == open_mode::binary) return std::ios::binary;
		}
		return std::ios::in;
	}
};

class file_base
{
public:
	inline u64 size() const { return _file_size; }
	inline bool valid() const { return _valid; }
protected:
	std::fstream _fstream = {};
	u64 _file_size = 0;
	bool _valid = false;
};

class file : public file_base, public file_utils
{
public:
	file(const string& filename);

	error_state open(const string& filename, u32 flags = file_open_flags());

	file_result read(u64 count = 0, u32 size = sizeof(char));

	error_state write(file_result data, size_t size);

	void close();
};

file::file(const string& filename)
{
	if (!filename.empty())
		open(filename);
}

inline error_state file::open(const string& filename, u32 flags /* = file_open_flags() */)
{
	_fstream.open(filename, translate_mode(flags));
	if (!_fstream.is_open())
		return error_state::file_not_found;
	_valid = true;
	_file_size = _fstream.tellg();
	_fstream.seekg(0, std::ios::end);
	_file_size = static_cast<u64>(_fstream.tellg()) - _file_size;
	_fstream.seekg(0, std::ios::beg);
	return error_state::ok;
}

inline file_result file::read(u64 count, u32 size /* = sizeof(char) */)
{
	if (count) {
		void* data = calloc(count + 1, size);
		if (data)
		{
			_fstream.read(reinterpret_cast<char*>(data), count);
			return data;
		}
	}
	else
	{
		void* data = calloc(_file_size + 1, size);
		if (data)
		{
			_fstream.read(reinterpret_cast<char*>(data), _file_size);
			return data;
		}
	}
	_valid = false;
	return file_result_null;
}

inline error_state file::write(file_result data, size_t size)
{
	if (!data) return error_state::memory_null;
	_fstream.write(data.c_str(), size);
	return error_state::ok;
}

inline void file::close()
{
	_fstream.close();
	_valid = false;
	_file_size = 0;
}

FIO_END

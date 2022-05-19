#pragma once
#include <string>
#include <vector>

#define FIO_BEGIN namespace fio {
#define FIO_END }

#define DEPTHS_BEGIN namespace depths {
#define DEPTHS_END }

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using native_module = HMODULE;
using native_instance = HINSTANCE;
using native_handle = HWND;
#else
using native_module = void*;
using native_instance = void*;
using native_handle = void*;
#endif

FIO_BEGIN

using u64 = unsigned long long;
using u32 = unsigned int;
using u16 = unsigned short;

using i32 = int;
using i16 = short;

using string = std::string;

template<class T> 
using vector = std::vector<T>;


template<u32 flag>
struct flag_bits {
	flag_bits() {}
	inline operator u32() const { return _flags; }
private:
	u32 _flags = flag;
};

enum class error_state : u32
{
	ok = 0,
	file_not_found,
	file_readonly,
	size_mismatch,
	memory_null,
};

enum open_mode : u32
{
	read = 0,
	write,
	binary = 32
};

using file_open_flags = flag_bits<open_mode::read | open_mode::binary>;

class file_base;
class file_result;
class file;

FIO_END

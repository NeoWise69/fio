#include <fio_file.hpp>

int main()
{
	fio::file f("main.cpp");
	char* ccccccccccc;
	if (f.valid())
	{
		ccccccccccc = f.read().str();
		f.write(ccccccccccc, 194);
	}
	f.close();
}

#include <iostream>
#include <memory>

void foo(std::unique_ptr<int>& i)
{
	(*i)++;
}

int main()
{
	auto i = 10;
	std::unique_ptr<int> sp;
	sp.reset(&i);
	foo(sp);
	std::cout << i << std::endl;
	std::cout << *sp << std::endl;
	system("pause");
	sp.release();
}
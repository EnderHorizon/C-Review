#include"pch.h"
#include "Expansion.h"

int main()
{
	std::vector<int> numlist;
	numlist.reserve(20);

	std::random_device randomseed;//生成随机数种子
	std::mt19937 gen(randomseed());// 梅森旋转算法, rd() 只调用一次，只为 gen 设置初始状态
	std::uniform_int_distribution<int> int_dist(0, 100);//定义范围
	for (int i = 0; i < 20; ++i)
	{
		numlist.emplace_back(int_dist(gen));
	}

	for (int& c : numlist)
	{
		std::cout << c << ",";
	}

	//lambda+thread
	std::thread thread1([&]() 
		{
		std::cout << "\nSort thread id:" << std::this_thread::get_id() << std::endl;
		sort::ShellSort(numlist);
		});
	thread1.join();

	std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
	for (int& c : numlist)
	{
		std::cout << c << ",";
	}
	std::cout << "\n\n";


	//Matrix
	std::unique_ptr<Matrix>m1 = std::make_unique<Matrix>(3, 4);
	std::unique_ptr<Matrix>m2 = std::make_unique<Matrix>(4, 5);

	std::uniform_int_distribution<int> int_dist_m(0, 10);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
			(*m2)(i, j) = int_dist_m(gen);
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
			(*m1)(i, j) = int_dist_m(gen);
	}
	m1->Print();
	m2->Print();

	std::unique_ptr<Matrix> m_result((*m1) * (*m2));
	m_result->Print();
	std::cin.get();
}
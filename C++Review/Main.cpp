#include <iostream>

#include <string>
#include<vector>
#include<array>
#include<random>
#include<thread>
#include<algorithm>
#include<memory>//smartptr
#include<chrono>

#include "Expansion.h"

/*
#ifdef DEBUG
#define LOG(x) std::cout << x << std::endl
#else 
#define 
#endif
*/

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
		sort::BubbleSort(numlist);
		});
	thread1.join();

	std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
	for (int& c : numlist)
	{
		std::cout << c << ",";
	}
	std::cin.get();
}
#pragma once
/*
Timer
sort
String
Vector
*/
#include<iostream>
#include<string>
#include<vector>
#include<chrono>

class Timer
{
private:
	std::string m_name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start; //high_resolution_clock是windows提供的最高精度时钟
	std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
public:
	Timer(const std::string& name)
		:m_name(name), m_start(std::chrono::high_resolution_clock::now()){}
	~Timer()
	{
		m_end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start);
		std::cout << m_name << duration.count() << "ns\n";
	}
};

namespace sort
{
	//用于vector
	template<typename Ty>
	void SelectSort(Ty& array)//选择排序
	{
		Timer time("SeletSort");
		int present = 1;
		int sel = 0;
		int temp = 0;
		for (; present < array.size(); ++present)
		{
			if (array[present - 1] > array[present])
			{
				temp = array[present];					//缓存
				for (; array[sel] > temp;)
				{
					array[sel + 1] = array[sel];
					if (sel > 0)						//排序区左边界
						--sel;
					else
					{
						--sel;
						break;
					}
				}
				array[sel + 1] = temp;
			}
			sel = present;
		}
	}

	template<typename Ty>
	void BubbleSort(Ty& array) //冒泡排序
	{
		Timer time("BubbleSort");
		int present = 0;
		int temp = 0;
		for (int i = 1; (present + i) < array.size(); ++i)
		{
			for (; (present + 1) < array.size(); ++present)
			{
				if (array[present] > array[present + 1])
				{
					temp = array[present];
					array[present] = array[present + 1];
					array[present + 1] = temp;
				}
			}
			present = 0;
		}
	}

	template<typename Ty>
	void ShellSort(Ty& array)
	{
		Timer time("ShellSort");
		
	}
	
};

class Log
{
//variable
public:      
	enum level : const char                  //static 使变量在所有实例中共用同一内存 enum使代码更简洁
	{
		DEBUG, INFO, WARN, ERROR, CRITICAL
	};

private:                                    //private只有friend可访问，子类也不可以；protected增加子类可访问
	short m_loglevel;

//method
public:
	explicit Log()//构造函数（constructor）默认存在    explicit拒绝隐式转换
		:m_loglevel(0)	{}
	~Log(){}


	void SetLevel(int level)   //Critical=4 Error=3 Warn=2 Info=1 Debug=0
	{
		m_loglevel = level;
	}

	void Critical(const char* contest) const
	{
		if (m_loglevel <= CRITICAL)
			std::cout << "[Critical]:" << contest << std::endl;
	}
	void Error(const char* contest) const
	{
		if(m_loglevel <= ERROR)
			std::cout << "[Error]:" << contest << std::endl;
	}
	void Warn(const char* contest) const
	{
		if(m_loglevel <= WARN)
			std::cout << "[Warn]:" << contest << std::endl;
	}
	void Info(const char* contest) const
	{
		if(m_loglevel <= INFO)
			std::cout << "[Info]:" << contest << std::endl;
	}
	void Debug(const char* contest) const
	{
		if(m_loglevel <= DEBUG)
			std::cout << "[Debug]:" << contest << std::endl;
	}
};

class string
{
private:
	char* m_buffer;
	size_t m_size;
public:
	string(const char* string)//constructor
	{
		m_size = strlen(string);
		m_buffer = new char[m_size + 1];//终止符
		memcpy(m_buffer, string, m_size);
		m_buffer[m_size] = '\0';
	}
	~string()
	{
		delete[] m_buffer;
	}

	string(const string& other) //copyconstructor
		:m_size(other.m_size)
	{
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, other.m_buffer, m_size + 1);
	}
	
	char& operator[](unsigned const int index)
	{
		return m_buffer[index];
	}
	
	friend std::ostream& operator<<(std::ostream& stream, const string& str);
};

std::ostream& operator<<(std::ostream& stream, const string& str)//<<运算符重载
{
	stream << str.m_buffer;
	return stream;
}


template<typename Type, size_t m_size>
class array
{
private:
	Type* head_ptr;
public:
	array()
	{
		head_ptr = new Type[m_size];
	}
	~array()
	{
		delete[] head_ptr;
	}

	array(const array& other) = delete;  //copyconstructor

	size_t size() const
	{
		return m_size;
	}

	Type& operator[](unsigned const int& index)
	{
		return head_ptr[index];
	}
};
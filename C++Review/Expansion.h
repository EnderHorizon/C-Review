#pragma once
#include"pch.h"

/*
Timer
sort
String
Vector
Matrix
*/

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
	void InsertSort(Ty& array)//插入排序
	{
		Timer time("InsertSort");
		int sel = 0;
		int temp = 0;
		for (int cur = 1; cur < array.size(); ++cur)
		{
			if (array[cur - 1] > array[cur])
			{
				temp = array[cur];				//缓存
				sel = cur - 1;
				while (sel > -1 && array[sel] > temp)
				{
					array[sel + 1] = array[sel];
					--sel;
				}
				array[sel + 1] = temp;
			}
		}
	}

	template<typename Ty>
	void BubbleSort(Ty& array) //冒泡排序
	{
		Timer time("BubbleSort");
		unsigned int cur = 0;
		int temp = 0;
		for (int i = 1; (cur + i) < array.size(); ++i)
		{
			for (; (cur + 1) < array.size(); ++cur)
			{
				if (array[cur] > array[cur + 1])
				{
					temp = array[cur];
					array[cur] = array[cur + 1];
					array[cur + 1] = temp;
				}
			}
			cur = 0;
		}
	}

	template<typename Ty>
	void ShellSort(Ty& array)
	{
		Timer time("ShellSort");
		unsigned int cur = 0;
		int sel = 0;
		int temp = 0;
		for(size_t gap = array.size() / 2; gap > 0; gap /= 2)
		{
			cur = 0;
			for (; (cur + gap) < array.size(); cur += gap)//插入排序
			{
				if (array[cur] > array[cur + gap])
				{
					temp = array[cur + gap];
					array[cur + gap] = array[cur];
					sel = cur - gap;
					while (sel > -1 && temp < array[sel])
					{
						array[sel + gap] = array[sel];
						sel -= gap;
					}
					array[sel + gap] = temp;
				}
			}
		}
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
	~array() {delete[] head_ptr;}

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

class vector
{

};

class Matrix
{
private:
	size_t m_row;
	size_t m_col;
	int* m_matrix;
public:
	Matrix(const size_t& row, const size_t& col)
		:m_row(row), m_col(col)
	{
		m_matrix = new int[m_row * m_col];
	}
	~Matrix() {delete[] m_matrix;}
	//重载（）运算符
	int& operator()(unsigned const int& row, unsigned const int& col) const
	{
#ifdef P_DEBUG
		if (row >= m_row || col >= m_col)
			throw std::invalid_argument("索引超出数组大小");
#endif
		return m_matrix[m_col * row + col];
	}
	//深拷贝
	Matrix(const Matrix& other) = delete;

	//矩阵加法
	Matrix* operator+(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相加");
#endif
		Matrix* m = new Matrix(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				(*m)(i, j) = (*this)(i, j) + other(i, j);
			}
		}
		return m;
	}
	//矩阵减法
	Matrix* operator-(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_row != other.m_row || m_col != other.m_col)
			throw std::invalid_argument("矩阵维度不匹配，无法相减");
#endif
		Matrix* m = new Matrix(m_row, m_col);
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				(*m)(i, j) = (*this)(i, j) - other(i, j);
			}
		}
		return m;
	}
	//矩阵乘法
	Matrix* operator*(const Matrix& other)
	{
#ifdef P_DEBUG
		if (m_col != other.m_row)
			throw std::invalid_argument("矩阵无法相乘");
#endif
		Matrix* m = new Matrix(m_row, other.m_col);
		for (int i = 0; i < m_row; ++i)//row
		{
			for (int j = 0; j < other.m_col; ++j)//col
			{
				(*m)(i, j) = 0;
				for (int x = 0; x < m_col; ++x)
				{
					(*m)(i, j) += (*this)(i, x) * other(x, j);
				}
			}
		}
		return m;
	}

	Matrix* Transform()
	{
		Matrix* m = new Matrix(m_col, m_row);
		for (int i = 0; i < m_col; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{

			}
		}
	}
	//打印矩阵
	void Print()
	{
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				std::cout << (*this)(i, j) << "  ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
};
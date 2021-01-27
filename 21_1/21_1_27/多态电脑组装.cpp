#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

//三大零件抽象类
class CPU//CPU抽象类
{
public:
	virtual void calculate() = 0;
};

class VideoCard//显卡抽象类
{
public:
	virtual void display() = 0;
};

class Memory//内存抽象类
{
public:
	virtual void storage() = 0;
};

          //Intel品牌
class IntelCPU :public CPU
{
public:
	void calculate()
	{
		cout << "IntelCPU正在工作" << endl;
	}
};
class IntelVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "IntelVideoCard正在工作" << endl;
	}
};
class IntelMemory :public Memory
{
public:
	void storage()
	{
		cout << "IntelMemory正在工作" << endl;
	}
};

          //Lenovo品牌
class LenovoCPU :public CPU
{
public:
	void calculate()
	{
		cout << "LenovoCPU正在工作" << endl;
	}
};
class LenovoVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "LenovoVideoCard正在工作" << endl;
	}
};
class LenovoMemory :public Memory
{
public:
	void storage()
	{
		cout << "LenovoMemory正在工作" << endl;
	}
};

class Computer//电脑类
{
public:
	Computer(CPU *cpu, VideoCard *videocard, Memory *memory)//电脑组装
	{
		this->m_cpu = cpu;
		cout << "我来组成CPU！！" << endl;
		this->m_videocard = videocard;
		cout << "我来组成显卡！！" << endl;
		this->m_memory = memory;
		cout << "我来组成内存！！" << endl;
		cout << "电脑组装完成！！！" << endl;
	}

	void ComputerWork()
	{
		m_cpu->calculate();
		m_videocard->display();
		m_memory->storage();
	}

	~Computer()//电脑拆解
	{
		assert(m_cpu != NULL);
		assert(m_videocard != NULL);
		assert(m_memory != NULL);
		delete m_cpu;
		m_cpu = NULL;
		cout << "CPU已销毁！！" << endl;
		delete m_videocard;
		m_videocard = NULL;
		cout << "显卡已销毁！！" << endl;
		delete m_memory;
		m_memory = NULL;
		cout << "内存已销毁！！" << endl;
		cout << "电脑已全部销毁！！" << endl;
	}
private:
	CPU *m_cpu;
	VideoCard *m_videocard;
	Memory *m_memory;
};

void Test01()
{
	Computer c1(new IntelCPU, new IntelVideoCard, new IntelMemory);//制作一个Intel电脑
	c1.ComputerWork();//电脑运行
}
int main()
{
	Test01();
	return 0;
}
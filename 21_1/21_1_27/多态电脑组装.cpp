#include<iostream>
using namespace std;
#include<string>
#include<assert.h>

//�������������
class CPU//CPU������
{
public:
	virtual void calculate() = 0;
};

class VideoCard//�Կ�������
{
public:
	virtual void display() = 0;
};

class Memory//�ڴ������
{
public:
	virtual void storage() = 0;
};

          //IntelƷ��
class IntelCPU :public CPU
{
public:
	void calculate()
	{
		cout << "IntelCPU���ڹ���" << endl;
	}
};
class IntelVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "IntelVideoCard���ڹ���" << endl;
	}
};
class IntelMemory :public Memory
{
public:
	void storage()
	{
		cout << "IntelMemory���ڹ���" << endl;
	}
};

          //LenovoƷ��
class LenovoCPU :public CPU
{
public:
	void calculate()
	{
		cout << "LenovoCPU���ڹ���" << endl;
	}
};
class LenovoVideoCard :public VideoCard
{
public:
	void display()
	{
		cout << "LenovoVideoCard���ڹ���" << endl;
	}
};
class LenovoMemory :public Memory
{
public:
	void storage()
	{
		cout << "LenovoMemory���ڹ���" << endl;
	}
};

class Computer//������
{
public:
	Computer(CPU *cpu, VideoCard *videocard, Memory *memory)//������װ
	{
		this->m_cpu = cpu;
		cout << "�������CPU����" << endl;
		this->m_videocard = videocard;
		cout << "��������Կ�����" << endl;
		this->m_memory = memory;
		cout << "��������ڴ棡��" << endl;
		cout << "������װ��ɣ�����" << endl;
	}

	void ComputerWork()
	{
		m_cpu->calculate();
		m_videocard->display();
		m_memory->storage();
	}

	~Computer()//���Բ��
	{
		assert(m_cpu != NULL);
		assert(m_videocard != NULL);
		assert(m_memory != NULL);
		delete m_cpu;
		m_cpu = NULL;
		cout << "CPU�����٣���" << endl;
		delete m_videocard;
		m_videocard = NULL;
		cout << "�Կ������٣���" << endl;
		delete m_memory;
		m_memory = NULL;
		cout << "�ڴ������٣���" << endl;
		cout << "������ȫ�����٣���" << endl;
	}
private:
	CPU *m_cpu;
	VideoCard *m_videocard;
	Memory *m_memory;
};

void Test01()
{
	Computer c1(new IntelCPU, new IntelVideoCard, new IntelMemory);//����һ��Intel����
	c1.ComputerWork();//��������
}
int main()
{
	Test01();
	return 0;
}
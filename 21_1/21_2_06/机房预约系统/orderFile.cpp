#include"orderFile.h"

//���캯��
OrderFile::OrderFile()
{
	ifstream ifs(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "order.txt�ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}

	this->m_Size = 0;

	string date;//����
	string interval;//ʱ���
	string stuId;//ѧ��ѧ��
	string stuName;//ѧ���û���
	string comId;//������
	string status;//ԤԼ״̬
	

	while (ifs >> date && ifs >> interval
		&& ifs >> stuId && ifs >> stuName
		&& ifs >> comId && ifs >> status)
	{
		string key;
		string value;
		map<string, string> m;

		//����
		int pos = date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//ʱ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//ѧ��ѧ��
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//ѧ���û���
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//������
		pos = comId.find(":");
		if (pos != -1)
		{
			key = comId.substr(0, pos);
			value = comId.substr(pos + 1, comId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		//ԤԼ״̬
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}

	//���Դ���
	//for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end();it++)
	//{
	//	cout << "key = " << it->first << " value = " << endl;
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << mit->first << " " << mit->second << " ";
	//	}
	//	cout << endl;
	//}

	ifs.close();
}

//����ԤԼ��Ϣ
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);

	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:"	   << m_orderData[i]["date"]     << " ";
		ofs << "interval:" << m_orderData[i]["interval"] << " ";
		ofs << "stuId:"    << m_orderData[i]["stuId"]    << " ";
		ofs << "stuName:"  << m_orderData[i]["stuName"]  << " ";
		ofs << "comId:"    << m_orderData[i]["comId"]    << " ";
		ofs << "status:"   << m_orderData[i]["status"]   << endl;
	}

	ofs.close();
}

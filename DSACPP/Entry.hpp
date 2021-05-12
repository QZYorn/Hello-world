#pragma once

template<typename K, typename V>
struct Entry//����
{
	//�ؼ���
	K key;
	//��ֵ
	V value;
	Entry(K k = K(), V v = V()) :key(k), value(v){}	         //Ĭ�Ϲ���
	Entry(Entry<K, V> const &e) :key(e.key), value(e.value){}//��������

	bool operator<  (Entry<K, V> const& e) { return key < e.key; }  //�Ƚ�����С��
	bool operator>  (Entry<K, V> const& e) { return key > e.key; }  //�Ƚ���������
	bool operator== (Entry<K, V> const& e) { return key == e.key; } //�е���������
	bool operator!= (Entry<K, V> const& e) { return key != e.key; } //�е�����������
};
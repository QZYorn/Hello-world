#pragma once

template<typename K, typename V>
struct Entry//词条
{
	//关键码
	K key;
	//数值
	V value;
	Entry(K k = K(), V v = V()) :key(k), value(v){}	         //默认构造
	Entry(Entry<K, V> const &e) :key(e.key), value(e.value){}//拷贝构造

	bool operator<  (Entry<K, V> const& e) { return key < e.key; }  //比较器：小于
	bool operator>  (Entry<K, V> const& e) { return key > e.key; }  //比较器：大于
	bool operator== (Entry<K, V> const& e) { return key == e.key; } //判等器：等于
	bool operator!= (Entry<K, V> const& e) { return key != e.key; } //判等器：不等于
};
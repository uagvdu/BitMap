#pragma once 
#include<iostream>
#include<vector>
using namespace std;
//哈希  -》 位图 -》布隆过滤器
//位图：类似于hash中的除留余数法，每一个数都可以经过适当运算得到对应位。
//本来由一个或多个字节表示的数，此时将有一个位来表示其 是否存在，，适合于大数据查找某个数的存在状态
class BitMap
{
public:
	BitMap(size_t range)             //由数的最大范围得到所需的最少字节+1
		:_sz(0)
	{  //移位运算符优先级很低
		_v.resize((range >> 5) + 1);  //之所以除32，本来4个字节可以表示一个数，此时4个字节可以表示32个数，数的表示扩大了32倍，那么开辟的空间就可以减少32倍
		cout << "字节数：" << _v.size() << endl;
	}

	void Set(size_t num) 
	{
		size_t index = num>>5;                     //得到该数在位图属于第几个字节
		size_t bit = num % 32; //得到该数在该字节的  第几位

		_v[index] |= (1<<bit);              //1 : 第0位   。该坐标对应num所在的字节中对应的位设置为存在；
		_sz++;
	}
	void Reset(size_t num)
	{
		size_t index = num >> 5;                      
		size_t bit = num % 32;  

		_v[index] &= ~(1<<bit);
		_sz--;
	}
	bool Test(size_t num)
	{
		size_t index = num >> 5;
		size_t bit = num % 32;
		return _v[index] & (1<<bit);
	}


protected:
	vector<size_t> _v;
	size_t _sz;
};

void BitMapTest()
{
	BitMap bm(142);
	
	for (int i = 70; i <142; i++)
	{
		bm.Set(i);
	}
	cout << bm.Test(75) << endl;
	cout << bm.Test(71) << endl;
	cout << bm.Test(5) << endl;
}
#pragma once 
#include<iostream>
#include<iostream>
#include"bitMap.h"
using namespace std;
//布隆过滤器只是位图的一个扩展。位图是一个位表示key的存在状态，而布隆过滤器是多个位表示


template<class K>
struct _func1
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<class K>
struct _func2
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<class K>
struct _func3
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<class K>
struct _func4
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<class K>
struct _func5
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _func1<string>
{
	size_t JSHash(const char *str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}

	size_t operator() (const string& str)
	{
		return JSHash(str.c_str());
	}
};

template<>
struct _func2<string>
 {

	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
 				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}

 	size_t operator() (const string& str)
	{
		return APHash(str.c_str());
	}
};

template<>
struct _func3<string>
{
	size_t RSHash(const char *str)
 	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
 
	size_t operator() (const string& str)
	{
		return RSHash(str.c_str());
	}
};

template<>
struct _func4<string>
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}

	size_t operator() (const string& str)
	{
		return SDBMHash(str.c_str());
	}
};

template<>
struct _func5<string>
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch; 
			// 也可以乘以31、131、1313、13131、131313.. 
		}
		return hash;
	}

	size_t operator() (const string& str)
	{
		return BKDRHash(str.c_str());
	}
};


template<class K = string, class func1 = _func1<K>, class func2 = _func2<K>,
class func3 = _func3<K>, class func4 = _func4<K>, class func5 = _func5<K >>
class  BloomFilter
{
public:
	BloomFilter(size_t num)//num表示数据的范围，而不是数据的个数，只要在该范围内都可以被位图或者bloom表示
		//布隆过滤器有点类似于直接定址法，只是多了函数而已，本质和直接定址法是一样的
		 :_bm(num*5)    //之所以*5，是因为布隆过滤器是多位表示一个数据的存在状态。在表示相同范围的数据，该位图比原来所需要的位数数少了五倍，所以*5，补回少的位数
	    , _range(num*5)   //布隆过滤器的范围，和上面原因一致，若我让range = num，那么代表着bloom的范围就仍然是num的大小，但是此时bloom已经是一个数据五个位的状态，比原先的少了五倍，为了保证数据的不丢失，就扩大range = num * 5
	{     
		
		//_bitmap._array.resize((size>>5)+1)
	}                    

	void Set(const K& key)  //用相同的key调用不同的函数得到不同的位，设置为1
	{
		//key % range;                     //没用到位的时候，别想位，range只是num这个关键字表示的范围   range个字节，key%range得到key所在的位置 ，此时这个位置并不是位，
		_bm.Set(func1()(key) % _range);
		_bm.Set(func2()(key) % _range);   //插入一个字符串的时候，对于不知道key大小的字符串来说，当key有可能非常大的时候，如果按照位图那样直接定址法，传参过去，难道我也开辟一个非常大的顺序表？《如果key为整型的最大值，那岂不是顺序表至少也要为8000万左右》所以此处采用除留余数法，
		_bm.Set(func3()(key) % _range); //并且顺序表永远不会越界
		_bm.Set(func4()(key) % _range);
		_bm.Set(func5()(key) % _range);



	}

	bool Test(const K& key)
	{
		return (_bm.Test(func1()(key) % _range) 
			&& _bm.Test(func2()(key) % _range)
			&& _bm.Test(func3()(key) % _range)
			&& _bm.Test(func4()(key) % _range)
			&& _bm.Test(func5()(key) % _range));

	}


protected:

	BitMap _bm;
	size_t _range;
};


void TestBloomFilter()
{
	char* url1 = "file:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD.html";

	char* url2 = "file:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AE.html";

	char* url3 = "file:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AF.html";

	char* url4 = "file:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$2/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AG.html";

	BloomFilter<> bf2(5);
	bf2.Set(url1);
	bf2.Set(url2);
	bf2.Set(url3);

	cout << "Test?" << bf2.Test(url1) << endl;
	cout << "Test?" << bf2.Test(url2) << endl;
	cout << "Test?" << bf2.Test(url3) << endl;
	cout << "Test?" << bf2.Test(url4) << endl;

	cout << "----------------- "<< endl;
	BloomFilter<int> bf(142);

	for (int i = 70; i <142; i++)
	{
		bf.Set(i);
	}
	cout << bf.Test(75) << endl;
	cout << bf.Test(71) << endl;
	cout << bf.Test(5) << endl;
	
}

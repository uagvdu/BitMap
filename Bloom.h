#pragma once 
#include<iostream>
#include<iostream>
#include"bitMap.h"
using namespace std;
//��¡������ֻ��λͼ��һ����չ��λͼ��һ��λ��ʾkey�Ĵ���״̬������¡�������Ƕ��λ��ʾ


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
		if (!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
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
			// Ҳ���Գ���31��131��1313��13131��131313.. 
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
	BloomFilter(size_t num)//num��ʾ���ݵķ�Χ�����������ݵĸ�����ֻҪ�ڸ÷�Χ�ڶ����Ա�λͼ����bloom��ʾ
		//��¡�������е�������ֱ�Ӷ�ַ����ֻ�Ƕ��˺������ѣ����ʺ�ֱ�Ӷ�ַ����һ����
		 :_bm(num*5)    //֮����*5������Ϊ��¡�������Ƕ�λ��ʾһ�����ݵĴ���״̬���ڱ�ʾ��ͬ��Χ�����ݣ���λͼ��ԭ������Ҫ��λ���������屶������*5�������ٵ�λ��
	    , _range(num*5)   //��¡�������ķ�Χ��������ԭ��һ�£�������range = num����ô������bloom�ķ�Χ����Ȼ��num�Ĵ�С�����Ǵ�ʱbloom�Ѿ���һ���������λ��״̬����ԭ�ȵ������屶��Ϊ�˱�֤���ݵĲ���ʧ��������range = num * 5
	{     
		
		//_bitmap._array.resize((size>>5)+1)
	}                    

	void Set(const K& key)  //����ͬ��key���ò�ͬ�ĺ����õ���ͬ��λ������Ϊ1
	{
		//key % range;                     //û�õ�λ��ʱ�򣬱���λ��rangeֻ��num����ؼ��ֱ�ʾ�ķ�Χ   range���ֽڣ�key%range�õ�key���ڵ�λ�� ����ʱ���λ�ò�����λ��
		_bm.Set(func1()(key) % _range);
		_bm.Set(func2()(key) % _range);   //����һ���ַ�����ʱ�򣬶��ڲ�֪��key��С���ַ�����˵����key�п��ܷǳ����ʱ���������λͼ����ֱ�Ӷ�ַ�������ι�ȥ���ѵ���Ҳ����һ���ǳ����˳��������keyΪ���͵����ֵ��������˳�������ҲҪΪ8000�����ҡ����Դ˴����ó�����������
		_bm.Set(func3()(key) % _range);
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
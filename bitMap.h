#pragma once 
#include<iostream>
#include<vector>
using namespace std;
//��ϣ  -�� λͼ -����¡������
//λͼ��������hash�еĳ�����������ÿһ���������Ծ����ʵ�����õ���Ӧλ��
//������һ�������ֽڱ�ʾ��������ʱ����һ��λ����ʾ�� �Ƿ���ڣ����ʺ��ڴ����ݲ���ĳ�����Ĵ���״̬
class BitMap
{
public:
	BitMap(size_t range)             //���������Χ�õ�����������ֽ�+1
		:_sz(0)
	{  //��λ��������ȼ��ܵ�
		_v.resize((range >> 5) + 1);  //֮���Գ�32������4���ֽڿ��Ա�ʾһ��������ʱ4���ֽڿ��Ա�ʾ32���������ı�ʾ������32������ô���ٵĿռ�Ϳ��Լ���32��
		cout << "�ֽ�����" << _v.size() << endl;
	}

	void Set(size_t num) 
	{
		size_t index = num>>5;                     //�õ�������λͼ���ڵڼ����ֽ�
		size_t bit = num % 32; //�õ������ڸ��ֽڵ�  �ڼ�λ

		_v[index] |= (1<<bit);              //1 : ��0λ   ���������Ӧnum���ڵ��ֽ��ж�Ӧ��λ����Ϊ���ڣ�
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
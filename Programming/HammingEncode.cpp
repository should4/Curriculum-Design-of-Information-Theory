#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//������Դ���� ��ȡ ����������
int calcRedundantBits(int dataBits)
{
    int r = 0;

    while (true)
    {
        // ���������� �� ��������ϵ�Ĺ�ʽ     
        // 2^r >= m + r + 1

        if (pow(2, r) >= dataBits + r + 1)
            break;

        ++r;
    }

    return r;
}

//������������λ��ռλ
void positionRedundantBits(vector<int>& dataWithParity, int r)
{
    //�ҵ� ÿ��������λ�� ������ֵ��ʼ�� Ϊ -1 ��������λ����
    for (int i = 0;i < r;++i)
    {
        dataWithParity.insert(dataWithParity.begin() + static_cast<int>(pow(2, i)) - 1,-1);
    }

}

//��������������ֵ
void calcRedundantBits(vector<int>& dataWithParity, int r)
{
    for (int i = 0;i < r;++i)
    {
        int x = static_cast<int>(pow(2, i));//�������λ��
        int count = 0;//������ֵ��ʼ��
        //������������
        //��������λ �� ���ݣ�������Hamming����λ��ֵ ���� x ���ӣ� ��ֵȫ�������� ������żУ��
        for (int j = x;j <= dataWithParity.size();j += 2 * x)
        {
            for (int k = j;k < j + x;++k)
            {
                if (k <= dataWithParity.size() && dataWithParity[k - 1] != -1)
                {
                    count ^= dataWithParity[k - 1];
                }
            }
        }
        //���� ��У��
        //cout << "here i = " << i << " count = " << count << endl;
        dataWithParity[x - 1] = count;
    }
}

//��ȡ Hamming ������
vector<int> encodeHamming(vector<int> data)
{
    vector<int> dataWithParity(data);

    //��ȡ��������
    int r = calcRedundantBits(data.size());

    cout << "redundant bits = " << r << endl;

    //������������ ������������
    positionRedundantBits(dataWithParity, r);

    //��������������ֵ
    calcRedundantBits(dataWithParity, r);

    return dataWithParity;
}

int main()
{
	vector<int> data = { 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 };//��������//0 0 0 0 1 0 1 1 0 1 1 1 1 1 0 1 0 0 0 1

    cout << "root data :";
    for (auto bit : data)
    {
        cout << bit << " ";
    }
    cout << endl;

    vector<int> encoded_data = encodeHamming(data);

    cout << "encoded_data :";
    for (auto bit : encoded_data)
    {
        cout << bit << " ";
    }
    cout << endl;

    return 0;
}


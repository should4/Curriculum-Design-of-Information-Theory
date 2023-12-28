#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//根据信源数据 获取 冗余码数量
int calcRedundantBits(int dataBits)
{
    int r = 0;

    while (true)
    {
        // 根据冗余码 和 数据量关系的公式     
        // 2^r >= m + r + 1

        if (pow(2, r) >= dataBits + r + 1)
            break;

        ++r;
    }

    return r;
}

//给冗余码所处位置占位
void positionRedundantBits(vector<int>& dataWithParity, int r)
{
    //找到 每个冗余码位置 并将其值初始化 为 -1 以于数据位区分
    for (int i = 0;i < r;++i)
    {
        dataWithParity.insert(dataWithParity.begin() + static_cast<int>(pow(2, i)) - 1,-1);
    }

}

//计算各个冗余码的值
void calcRedundantBits(vector<int>& dataWithParity, int r)
{
    for (int i = 0;i < r;++i)
    {
        int x = static_cast<int>(pow(2, i));//冗余码的位置
        int count = 0;//冗余码值初始化
        //冗余码计算规则
        //遍历数据位 将 数据（满足在Hamming表中位置值 包含 x 因子） 的值全部加起来 进行奇偶校验
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
        //进行 奇校验
        //cout << "here i = " << i << " count = " << count << endl;
        dataWithParity[x - 1] = count;
    }
}

//获取 Hamming 编码结果
vector<int> encodeHamming(vector<int> data)
{
    vector<int> dataWithParity(data);

    //获取冗余码数
    int r = calcRedundantBits(data.size());

    cout << "redundant bits = " << r << endl;

    //根据冗余码数 构建编码数组
    positionRedundantBits(dataWithParity, r);

    //计算各个冗余码的值
    calcRedundantBits(dataWithParity, r);

    return dataWithParity;
}

int main()
{
	vector<int> data = { 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 };//测试数据//0 0 0 0 1 0 1 1 0 1 1 1 1 1 0 1 0 0 0 1

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


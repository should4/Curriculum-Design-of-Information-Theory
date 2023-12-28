#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

//Huffman Tree 的节点
struct HuffmanNode
{
	char data;//字符
	unsigned int freq;//频率
	HuffmanNode* lchild,* rchild;//左右子树
};
//优先队列的比较规则 频率小的靠近队首
struct compare
{
	bool operator() (const HuffmanNode* root1, const HuffmanNode* root2)
	{
		return root1->freq > root2->freq;//小根堆
	}
};

//构建 Huffman Tree 的节点
HuffmanNode* newHuffmanNode(char data, int freq)
{
	HuffmanNode* node = new HuffmanNode;
	node->data = data;
	node->freq = freq;
	node->lchild = node->rchild = nullptr;

	return node;
}

//构建 Huffman Tree
HuffmanNode* buildHuffmanTree(char data_arr[], int freq_arr[], int size)
{
	//建立优先队列
	priority_queue<HuffmanNode*, vector<HuffmanNode* >, compare> que;

	for (int i = 0;i < size;++i)
	{
		char data = data_arr[i];
		int freq = freq_arr[i];
		que.push(newHuffmanNode(data, freq));
	}

	/*while (true)
	{
		if (que.empty())
			break;
		cout << que.top()->data << " " << que.top()->freq << endl;
		que.pop();
	}*/

	// 构建哈夫曼树
	// 步骤：
	// 从优先队列中依次取出两个节点，创建新的节点作为 两个节点的父节点 
	// 父节点的 freq_f = freq_1 + freq_2
	// 将父节点重新入队列
	// 当优先队列中只有一个节点时 结束 并将该节点作为改树的根节点返回
	HuffmanNode* root = nullptr;

	while (true)
	{
		if (que.size() <= 1)
			break;

		HuffmanNode* root1 = que.top();
		que.pop();

		HuffmanNode* root2 = que.top();
		que.pop();

		HuffmanNode* root_f = new HuffmanNode;

		root_f->lchild = root1;
		root_f->rchild = root2;
		root_f->data = '$';
		root_f->freq = root1->freq + root2->freq;

		que.push(root_f);
	}

	root = que.top();
	que.pop();

	return root;
}

//构建 Huffman 编码表
void buildHuffmanCodes(HuffmanNode* root,string str, unordered_map<char, string>& codes)
{
	//前序遍历 Huffman Tree
	//如果当前的 data 值为 '$' 则递归遍历其左右子树
	//否则 当前字符的 Huffman 编码为 str

	if (!root)
		return;

	if (root->data != '$')
	{
		char data = root->data;
		codes[data] = str;
	}

	buildHuffmanCodes(root->lchild, str + "0", codes);
	buildHuffmanCodes(root->rchild, str + "1", codes);

}

//构建 字符串 Huffman 编码结果
string buildHuffmanEncodedStr(string str, unordered_map<char, string> codes)
{
	string encoded_str = "";
	for (auto c : str)
	{
		encoded_str.append(codes[c]);
	}

	return encoded_str;
}

//构建 Huffman编码字符串 的译码结果
string buildHuffmanDecodedStr(string str, HuffmanNode* root) // 需要对应的译码表
{
	// 对 Huffman 编码后的字符串进行译码处理
	// 步骤：
	// Huffman Tree 索引指针 info																						// 建立 字符串头尾指针 head tail 与 
	// 初始化索引指针：info = root																						// 初始化头尾指针； head = tail = 1
	// info指针 如果指向的字符为 '0' 则 info = info->lchild | 如果指向的字符为 '1' 则 info = info->rchild
	// 当索引指针的数据域 不为 '$' 时	将 info->data 取出添加到译码结果字符串中
																																	//将头尾指针中间的字符串取出 该字符串即为 一个字符的
	string decoded = "";
	string::size_type index = 0;
	HuffmanNode* info = root;

	while (true)
	{
		if (index >= str.size() && info == root)
			break;

		/*cout << "#########################" << endl;
		cout << "index =  " << index << endl;
		cout << "info->freq = " << info->freq << endl;*/
		// Huffman 的编码字符 为树的叶子结点 
		// 如果 info 指针指向的节点为叶子节点 则该叶子结点的数据域 为该轮字符译码的译码结果 
		// 将 info 指针指向根节点 开始下一个字符的译码
		if (info->data != '$')
		{
			//cout << "Here" << endl;
			decoded += info->data;
			//cout << "decoded = " << decoded << endl;
			info = root;
		}
		else
		{
			if (str[index] == '0')
			{
				// cout << "L" << endl;
				info = info->lchild;
			}
			else if (str[index] == '1')
			{
				// cout << "R" << endl;
				info = info->rchild;
			}

			index++;
		}
		
	}


	return decoded;
}

int main()
{

	//测试数据1
	//string non_coded_str = "bcfcdaadeffbfcf";
	//char data_arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };						// 信源符号列表，你可以修改这个列表以适应你的需求（字符集）  
	//int freq_arr[] = { 2, 2, 3, 2, 1, 5 };


	string non_coded_str = "cbaabcabc";
	char data_arr[] = { 'a', 'b', 'c' };						// 信源符号列表，你可以修改这个列表以适应你的需求（字符集）  
	int freq_arr[] = { 3, 3, 3 };							// 对应符号的频率列表，你可以修改这个列表以适应你的需求（字符频率）  
	
	
	
	int size = sizeof(data_arr) / sizeof(data_arr[0]);

	cout << "root_data: " << non_coded_str << endl;

	//建立 Huffman Tree
	HuffmanNode* root = buildHuffmanTree(data_arr, freq_arr, size);

	//建立 Huffman 编码表 
	unordered_map<char, string> codes;


	buildHuffmanCodes(root,"", codes);

	string encoded_str = buildHuffmanEncodedStr(non_coded_str, codes);

	cout << "encoded: " << encoded_str << endl;

	string coded_str = "1100111";
	string decode_str = buildHuffmanDecodedStr(encoded_str, root);

	cout << "decoded : " << decode_str << endl;



	return 0;
}
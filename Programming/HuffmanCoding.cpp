#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

//Huffman Tree �Ľڵ�
struct HuffmanNode
{
	char data;//�ַ�
	unsigned int freq;//Ƶ��
	HuffmanNode* lchild,* rchild;//��������
};
//���ȶ��еıȽϹ��� Ƶ��С�Ŀ�������
struct compare
{
	bool operator() (const HuffmanNode* root1, const HuffmanNode* root2)
	{
		return root1->freq > root2->freq;//С����
	}
};

//���� Huffman Tree �Ľڵ�
HuffmanNode* newHuffmanNode(char data, int freq)
{
	HuffmanNode* node = new HuffmanNode;
	node->data = data;
	node->freq = freq;
	node->lchild = node->rchild = nullptr;

	return node;
}

//���� Huffman Tree
HuffmanNode* buildHuffmanTree(char data_arr[], int freq_arr[], int size)
{
	//�������ȶ���
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

	// ������������
	// ���裺
	// �����ȶ���������ȡ�������ڵ㣬�����µĽڵ���Ϊ �����ڵ�ĸ��ڵ� 
	// ���ڵ�� freq_f = freq_1 + freq_2
	// �����ڵ����������
	// �����ȶ�����ֻ��һ���ڵ�ʱ ���� �����ýڵ���Ϊ�����ĸ��ڵ㷵��
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

//���� Huffman �����
void buildHuffmanCodes(HuffmanNode* root,string str, unordered_map<char, string>& codes)
{
	//ǰ����� Huffman Tree
	//�����ǰ�� data ֵΪ '$' ��ݹ��������������
	//���� ��ǰ�ַ��� Huffman ����Ϊ str

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

//���� �ַ��� Huffman ������
string buildHuffmanEncodedStr(string str, unordered_map<char, string> codes)
{
	string encoded_str = "";
	for (auto c : str)
	{
		encoded_str.append(codes[c]);
	}

	return encoded_str;
}

//���� Huffman�����ַ��� ��������
string buildHuffmanDecodedStr(string str, HuffmanNode* root) // ��Ҫ��Ӧ�������
{
	// �� Huffman �������ַ����������봦��
	// ���裺
	// Huffman Tree ����ָ�� info																						// ���� �ַ���ͷβָ�� head tail �� 
	// ��ʼ������ָ�룺info = root																						// ��ʼ��ͷβָ�룻 head = tail = 1
	// infoָ�� ���ָ����ַ�Ϊ '0' �� info = info->lchild | ���ָ����ַ�Ϊ '1' �� info = info->rchild
	// ������ָ��������� ��Ϊ '$' ʱ	�� info->data ȡ����ӵ��������ַ�����
																																	//��ͷβָ���м���ַ���ȡ�� ���ַ�����Ϊ һ���ַ���
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
		// Huffman �ı����ַ� Ϊ����Ҷ�ӽ�� 
		// ��� info ָ��ָ��Ľڵ�ΪҶ�ӽڵ� ���Ҷ�ӽ��������� Ϊ�����ַ������������ 
		// �� info ָ��ָ����ڵ� ��ʼ��һ���ַ�������
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

	//��������1
	//string non_coded_str = "bcfcdaadeffbfcf";
	//char data_arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };						// ��Դ�����б�������޸�����б�����Ӧ��������ַ�����  
	//int freq_arr[] = { 2, 2, 3, 2, 1, 5 };


	string non_coded_str = "cbaabcabc";
	char data_arr[] = { 'a', 'b', 'c' };						// ��Դ�����б�������޸�����б�����Ӧ��������ַ�����  
	int freq_arr[] = { 3, 3, 3 };							// ��Ӧ���ŵ�Ƶ���б�������޸�����б�����Ӧ��������ַ�Ƶ�ʣ�  
	
	
	
	int size = sizeof(data_arr) / sizeof(data_arr[0]);

	cout << "root_data: " << non_coded_str << endl;

	//���� Huffman Tree
	HuffmanNode* root = buildHuffmanTree(data_arr, freq_arr, size);

	//���� Huffman ����� 
	unordered_map<char, string> codes;


	buildHuffmanCodes(root,"", codes);

	string encoded_str = buildHuffmanEncodedStr(non_coded_str, codes);

	cout << "encoded: " << encoded_str << endl;

	string coded_str = "1100111";
	string decode_str = buildHuffmanDecodedStr(encoded_str, root);

	cout << "decoded : " << decode_str << endl;



	return 0;
}
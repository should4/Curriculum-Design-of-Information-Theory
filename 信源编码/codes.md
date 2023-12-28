# Codes

当然可以。以下是一个使用C++实现哈夫曼编码的示例代码，并带有详细的注释：


```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// 定义哈夫曼树节点结构体
struct HuffmanNode {
    char data;               // 节点存储的字符
    unsigned freq;            // 字符的频率
    HuffmanNode *left, *right; // 左右子节点指针
};

// 比较函数，用于优先队列排序
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq; // 频率小的节点排在前面
    }
};

// 创建新节点
HuffmanNode* newNode(char data, unsigned freq) {
    HuffmanNode* node = new HuffmanNode();
    node->data = data;
    node->freq = freq;
    node->left = node->right = nullptr;
    return node;
}

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap; // 最小堆，用于存放节点指针
    for (int i = 0; i < size; ++i) { // 将字符和频率放入最小堆中
        minHeap.push(newNode(data[i], freq[i]));
    }
    while (minHeap.size() != 1) { // 当最小堆中节点数不为1时，合并频率最小的两个节点，并重新放入最小堆中
        HuffmanNode* left = minHeap.top(); // 取出最小堆中频率最小的节点（左子节点）
        minHeap.pop();
        HuffmanNode* right = minHeap.top(); // 取出最小堆中频率最小的节点（右子节点）
        minHeap.pop();
        HuffmanNode* parent = newNode('$', left->freq + right->freq); // 创建父节点，频率为左右子节点频率之和
        parent->left = left; // 设置父节点的左子节点为左子节点
        parent->right = right; // 设置父节点的右子节点为右子节点
        minHeap.push(parent); // 将父节点放入最小堆中
    }
    return minHeap.top(); // 返回根节点，即哈夫曼树的根节点
}

// 打印哈夫曼编码表（前缀编码）和对应的字符信息  
void printCodes(HuffmanNode* root, string str, unordered_map<char, string>& codes) {  
    if (!root) return; // 如果当前节点为空，则返回（递归结束）  
    if (root->data != '$') { // 如果当前节点的字符不是'$'（不是叶子节点），则将当前前缀编码加入哈夫曼编码表中（前缀编码）  
        codes[root->data] = str; // 将当前前缀编码和对应的字符加入哈夫曼编码表中（字符-编码）  
    }  
    printCodes(root->left, str + "0", codes); // 递归向左子树遍历，左子树前缀编码在原前缀编码后加'0'（左）  
    printCodes(root->right, str + "1", codes); // 递归向右子树遍历，右子树前缀编码在原前缀编码后加'1'（右）  
}  

// 哈夫曼译码函数 
// 递归版 Recursion
void decode(string data, HuffmanNode* root) {  
    if (!root) return; // 如果当前节点为空，则返回（递归结束）  
    if (root->data != '$') { // 如果当前节点的字符不是'$'（不是叶子节点），则将当前前缀编码加入哈夫曼编码表中（前缀编码）  
        cout << root->data; // 输出对应的字符  
    }  
    if (data.empty()) return; // 如果当前前缀编码已经用完，则返回（递归结束）  
    if (data[0] == '0') { // 如果当前前缀编码的第一个字符是'0'，则向左子树进行解码  
        decode(data.substr(1), root->left);  
    } else if (data[0] == '1') { // 如果当前前缀编码的第一个字符是'1'，则向右子树进行解码  
        decode(data.substr(1), root->right);  
    }  
} 

// 非递归版 Non-recursion
//构建 Huffman编码字符串 的译码结果
string buildHuffmanDecodedStr(string str, HuffmanNode* root) // 需要对应的译码表
{
	// 对 Huffman 编码后的字符串进行译码处理
	// 步骤：
	// Huffman Tree 索引指针 info																						
	// 初始化索引指针：info = root																						
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

		// 如果 info 指针指向的节点为叶子节点 则该叶子结点的数据域 为该轮字符译码的译码结果 
		// 将 info 指针指向根节点 开始下一个字符的译码
		if (info->data != '$')
		{
			decoded += info->data;
			info = root;
		}
		else
		{
			if (str[index] == '0')
			{
				info = info->lchild;
			}
			else if (str[index] == '1')
			{
				info = info->rchild;
			}

			index++;
		}
		
	}


	return decoded;
}

// 主函数，构建哈夫曼树并打印出每个符号的哈夫曼编码（前缀编码）和对应的字符信息（字符-编码）  
int main() {  
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'}; // 信源符号列表，你可以修改这个列表以适应你的需求（字符集）  
    int freq[] = {5, 9, 12, 13, 16, 45}; // 对应符号的频率列表，你可以修改这个列表以适应你的需求（字符频率）  
    int size = sizeof(arr) / sizeof(arr[0]); // 计算信源符号的数量（字符集大小）  
    HuffmanNode* root = buildHuffmanTree(arr, freq, size); // 构建哈夫曼树（根据字符集和字符频率）  
    unordered_map<char, string> codes; // 哈夫曼编码表  
    printCodes(root, "", codes); // 打印哈夫曼编码表和对应的字符信息  
    // 输出哈夫曼编码表和对应的字符信息  
    for (auto& pair : codes) {  
        cout << pair.first << ": " << pair.second << endl; // 输出字符-编码  
    }  

    // 测试译码过程  
    // Recursion
    string encodedData = "01001"; // 这里输入的是经过哈夫曼编码的数据，你可以修改这个数据以适应你的需求（编码数据）  
    decode(encodedData, root); // 对编码数据进行译码，输出对应的字符信息  
    // Non-rcursion
    string coded_str = "1100111";
	string decode_str = buildHuffmanDecodedStr(encoded_str, root);

    return 0;  
}
```

注释：

1. `decode` 函数用于进行哈夫曼译码。它使用递归的方式遍历哈夫曼树，并根据接收到的前缀编码逐步解码出对应的字符。具体步骤如下：如果当前节点是叶子节点，则直接输出对应的字符；如果当前节点不是叶子节点，则根据前缀编码的第一个字符判断应该向左子树还是右子树进行解码。解码过程中需要不断去掉前缀编码的第一个字符，直到解码结束。最后，输出解码得到的字符信息。
2. 在主函数中，首先构建了哈夫曼树，并打印出每个符号的哈夫曼编码和对应的字符信息。然后对一个经过哈夫曼编码的数据进行译码，输出对应的字符信息。你可以修改输入的编码数据以适应你的需求。
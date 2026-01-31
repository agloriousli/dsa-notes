#ifndef HUFFMAN_MAIN_HPP
#define HUFFMAN_MAIN_HPP

#include "huffmanalgorithm.hpp"
#include "huffmaneconding.hpp"
#include <iostream>
#include <cstring>

// 打印Huffman编码表
void printHuffTable( HuffTable* table ) {
   if (!table) {
      std::cout << "编码表为空！" << std::endl;
      return;
   }
   
   std::cout << "Huffman编码表：" << std::endl;
   std::cout << "字符\t频率\t编码" << std::endl;
   std::cout << "----------------------" << std::endl;
   
   // 注意：这里需要Hashtable的遍历功能
   // 假设Hashtable有遍历接口
   // table->traverse([](char ch, char* code) {
   //    std::cout << ch << "\t\t" << code << std::endl;
   // });
}

// 测试Huffman编码
void testHuffman() {
   std::cout << "=== Huffman编码测试 ===" << std::endl;
   
   // 测试数据：字符频率
   HuffChar chars[] = {
      HuffChar(45, 'a'),
      HuffChar(13, 'b'),
      HuffChar(12, 'c'),
      HuffChar(16, 'd'),
      HuffChar(9, 'e'),
      HuffChar(5, 'f')
   };
   int n = 6;
   
   // 构建Huffman树
   std::cout << "\n1. 构建Huffman树..." << std::endl;
   HuffTree tree = buildHuffTreeFromFreq(chars, n);
   
   // 生成编码表
   std::cout << "\n2. 生成编码表..." << std::endl;
   HuffTable* table = huffCodeTable(tree);
   
   // 打印编码表
   printHuffTable(table);
   
   // 测试编码
   std::cout << "\n3. 测试编码/解码..." << std::endl;
   const char* testText = "abacdaef";
   std::cout << "原始文本: " << testText << std::endl;
   
   char* encoded = huffEncode(testText, table);
   std::cout << "编码结果: " << encoded << std::endl;
   
   char* decoded = huffDecode(encoded, tree);
   std::cout << "解码结果: " << decoded << std::endl;
   
   // 清理内存
   delete[] encoded;
   delete[] decoded;
   delete table;
   
   std::cout << "\n测试完成！" << std::endl;
}

// 计算压缩比
double calculateCompressionRatio( const char* original, const char* encoded ) {
   if (!original || !encoded) return 0.0;
   
   double originalBits = strlen(original) * 8.0; // 假设原始是8位ASCII
   double encodedBits = strlen(encoded) * 1.0;   // 编码是0/1串
   
   return (originalBits - encodedBits) / originalBits * 100.0;
}

#endif // HUFFMAN_MAIN_HPP
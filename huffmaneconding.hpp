#ifndef HUFFMAN_ENCODING_HPP
#define HUFFMAN_ENCODING_HPP

#include "hufftree.hpp"
#include "stack.hpp"
#include "hashtable.h" //用HashTable（第09章）实现

using HuffTable = Hashtable< char, char* >; //Huffman编码表

// 递归遍历生成编码表
void huffCT( Stack<char> theseus, Hashtable<char, char*>& table, 
             BinNode<HuffChar>* v ) {
   if ( IsLeaf( v ) ) { //每遇到一个叶节点，便导出对应的编码串，并添加到编码表中
      int n = theseus.size() - 1; // 减去初始的'x'
      Stack<char> sueseht;
      
      // 复制栈内容（反转顺序）
      for ( Rank k = 0; k < n; k++ ) 
         sueseht.push( theseus.pop() );
      
      // 创建编码字符串
      char* code = new char[n + 1];
      code[n] = '\0';
      
      for ( Rank k = 0; k < n; k++ ) {
         char c = sueseht.pop();
         code[k] = c;
         theseus.push( c );
      }
      
      table.put( v->data.ch, code );
   } 
   else { //否则，继续递归地遍历
      if ( v->lc ) {
         theseus.push('0');
         huffCT( theseus, table, v->lc ); //0左
      }
      
      if ( v->rc ) {
         theseus.push('1');
         huffCT( theseus, table, v->rc ); //1右
      }
   }
   
   if (theseus.size() > 0) // 回溯时弹出当前字符
      theseus.pop();
} //huffCT

// 生成Huffman编码表
HuffTable* huffCodeTable( HuffTree& tree ) { 
   //将各字符编码，统一存入
   Hashtable<char, char*>* table = new Hashtable<char, char*>();
   Stack<char> theseus;
   theseus.push('x'); // 初始标记
   
   huffCT( theseus, *table, tree.root() );
   return table;
} //huffCodeTable

// 编码函数：使用Huffman编码表编码文本
char* huffEncode( const char* text, HuffTable* table ) {
   if (!text || !table) return nullptr;
   
   // 计算编码后字符串的总长度
   int totalLen = 0;
   for (const char* p = text; *p; p++) {
      char* code = table->get(*p);
      if (code) totalLen += strlen(code);
   }
   
   // 分配内存并编码
   char* encoded = new char[totalLen + 1];
   char* dest = encoded;
   
   for (const char* p = text; *p; p++) {
      char* code = table->get(*p);
      if (code) {
         strcpy(dest, code);
         dest += strlen(code);
      }
   }
   *dest = '\0';
   
   return encoded;
} //huffEncode

// 解码函数：使用Huffman树解码
char* huffDecode( const char* encoded, HuffTree& tree ) {
   if (!encoded) return nullptr;
   
   BinNode<HuffChar>* current = tree.root();
   int maxLen = strlen(encoded);
   char* decoded = new char[maxLen + 1]; // 最大可能长度
   int decodedIndex = 0;
   
   for (int i = 0; encoded[i]; i++) {
      if (encoded[i] == '0') {
         current = current->lc;
      } else if (encoded[i] == '1') {
         current = current->rc;
      }
      
      if (IsLeaf(current)) {
         decoded[decodedIndex++] = current->data.ch;
         current = tree.root();
      }
   }
   
   decoded[decodedIndex] = '\0';
   return decoded;
} //huffDecode

#endif // HUFFMAN_ENCODING_HPP
#ifndef HUFFMAN_ALGORITHM_HPP
#define HUFFMAN_ALGORITHM_HPP

#include "HuffTree.hpp"
#include "PriorityQueue.hpp"
#include <iostream>

// Huffman树构造算法
HuffTree huffTree( HuffForest& F ) {
   while ( 1 < F.size() ) { //每迭代一步，森林中都会减少一棵树
      // 取出权重最小的两棵树，合并成S
      HuffTree T1 = F.delMax(); // T1有最大权重（但我们的比较器是反向的）
      HuffTree T2 = F.delMax(); // T2权重不小于T1
      
      // 创建新的超字符节点
      HuffChar newChar( Weight(T2) + Weight(T1) ); //权重取作子树权重之和
      
      // 创建新的树S
      HuffTree S;
      S.insert( newChar ); // 插入根节点
      
      // 附加子树
      S.attach( T2, S.root() ); // T2作为左子树
      S.attach( S.root(), T1 ); // T1作为右子树
      
      // 再插回森林
      F.insert( S );
   }
   
   // 森林中最终唯一所剩的那棵树，即Huffman编码树
   // 且层次序列必然单调非增
   return F.delMax();
} //huffTree

// 从字符频率数组构建Huffman树
HuffTree buildHuffTreeFromFreq( HuffChar* chars, int n ) {
   HuffForest forest;
   
   // 为每个字符创建单节点树并插入森林
   for (int i = 0; i < n; i++) {
      HuffTree tree;
      tree.insert( chars[i] ); // 插入根节点
      forest.insert( tree );
   }
   
   return huffTree( forest );
}

#endif // HUFFMAN_ALGORITHM_HPP
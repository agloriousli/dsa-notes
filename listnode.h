template <typename T> using LNP = ListNode<T>*; //List Node Position

template <typename T> struct ListNode { //简洁起见，完全开放而不再严格封装
T data; LNP<T> pred, succ; //数值、前驱、后继 //Each node in the list contains a data point and pointers poitning to pred and succ
ListNode(const T& e, LNP<T> p = NULL, LNP<T> s = NULL) //List node contais
: data(e), pred(p), succ(s) {} //默认构造器（类T须已定义复制方法）
LNP<T> insertPred( const T& e ); //前插入
LNP<T> insertSucc( const T& e ); //后插入
void movePred( LNP<T> s ); //转移至s之前驱 
//Move current node to be a pred of s or succ of p
void moveSucc( LNP<T> p ); //转移至p之后继
};

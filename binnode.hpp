#define BinNodePosi(T) BinNode<T>*

template <typename T> struct BinNode {
    BinNodePosi(T) parent, lChild, rChild;
    T data;
    int height;
    int size();
    BinNodePosi(T) insertAsLC(T const &);
    BinNodePosi(T) insertAsRC(T const &);
    BinNodePosi(T) succ();
    template <typename VST> void travLevel(VST &);
    template <typename VST> void travPre(VST &);
    template <typename VST> void travIn(VST &);
    template <typename VST> void travPost(VST &);
};

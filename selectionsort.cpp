#include <bits/stdc++.h>
#include <listnode.h>

template <typename T>
//Will get the max
LNP<T> List<T>::getMax(LNP<T> h, LNP<T> t){
    for(LNP<T> x = t -> pred; x!= h; x = x-> pred)
        if(t -> data < x -> data)
            t = x;
    return t;
}

template <typename T> 
void List<T>::selectionSort(LNP<T> h, LNP<T> t){
    for(; h-> succ != t; t = t->pred){
        //Move the max to be the pred of t, then move
        getMax(h,t)->movePred(t);
    }
}



int main(){
    return 0;
}
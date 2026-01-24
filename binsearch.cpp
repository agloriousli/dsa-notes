//Version A

template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
while ( lo < hi ) { //3 Branches, left needs one comparison, right needs two comparisons
Rank mi = (lo + hi) / 2; 
if ( e < S[mi] ) hi = mi; //[lo, mi)
else if ( S[mi] < e ) lo = mi + 1; //(mi, hi)
else return mi; 
} //lo==hi
return -1; 
} 
//O（1.5logn）

//Version B
template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
while ( lo - hi > 1 ) { //2 Branches, both need one comparison
Rank mi = (lo + hi) / 2; 
(e < S[mi]) ？ hi = mi : lo = mi //[lo,mi) or [mi,hi)
} //lo + 1 == hi
(e == S[lo]) ？ return lo : return -1; //returns index or not found
}

//Version C (use this for Vector.insert(vector.search(e) + 1, e))
template <typename T> Rank binSearch( T* S, const T& e, Rank lo, Rank hi ) {
while ( hi > lo ) { //3 Branches, left needs one comparison, right needs two comparisons
Rank mi = (lo + hi) / 2; 
(e < S[mi]) ？ hi = mi : lo = mi + 1 //[lo,mi) or (mi,hi) (we legit just don't visit mi)
} //lo + 1 =hi
return lo-1; //returns index of largest num not bigger than e (infimum)
}

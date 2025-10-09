/*Try this
 * Once you have a pointer,
 *  arithmetic lets you walk memory like a grid: p + n advances by n * sizeof(*p) bytes.
 */
 //IT MAKES THE ARRAY ITERATION FASTER
 //Pointers as affine spaces—base address + scalar multiple of stride (sizeof(type))
 #include<bits/stdc++.h>
 using namespace std;
 int main()
 {
     //SEE HOW IT CAN BE USED IN LOOPS WE WILL USE WITH AN EXAMPLE OF A QUANT TRADE MODEL
     const int size=5;
     double trades[size]={100.3,455.6,899.0,555.9};
     double *start=trades;// Line 1: Pointer to first element (decay from array).
                          // How it works: Array name decays to pointer to [0]
     double *end=trades+size;// Line 2: Past-the-end—valid sentinel, no deref.
                             // How it works: +N scales by sizeof(double)=8, so +40 bytes
    double sum=0.0;
    double *current=start;
    ptrdiff_t index = 0;  // Distance tracker (signed for negative diffs).
     while(start<end)
     {
         cout<<"trade["<<index<<"]"<<*current<<endl;// Dereference: Load from address.
                 // How it works: *current = memory[current]
        sum+=*current;// Add to sum—math: partial sum S_k = Σ_{i=0}^k trades[i].
                current++;  // Line 5: Increment—advances by sizeof(double)=8 bytes.
                            // How it works: add rax, 8 (postfix ++ on pointer). Cache-friendly sequential.
        index=current-start;
        if (index >= static_cast<ptrdiff_t>(size)) break;  // Guard against overflow (rare but per C++26 safety).
     }
     cout<<"The Rolling average is"<<sum/size<<endl;
     return 0;

 }

/*Raw Pointers -
 The primal beast—unmanaged, direct memory access.
 Internals: Stores address as unsigned int (e.g., 0xdeadbeef).
 Alignment math: Must align to sizeof(T) (e.g., double* aligns to 8 bytes to avoid bus errors—violate it, and CPU faults).
 Logic: Dereference * fetches from address; & grabs address.
 Pitfalls: Ownership ambiguity leads to leaks/dangles.
 */
 #include <iostream>  // For std::cout—streams output to console (I/O abstraction).
 #include <cstdint>   // For uint64_t—fixed-width types for addresses (portable math).
 int main()
 {  // Entry point: Returns int (0 = success). Stack frame allocated here.
     int value = 42;  // Line 1: Declare local int on stack. Compiler allocates 4 bytes, stores 42 (ASCII 'B' in hex, but as int).
                      // How it works: Assembly: mov DWORD PTR [rbp-4], 42h (EBP-relative addressing).
     int* ptr = &value;  // Line 2: Declare pointer to int. &value computes address (e.g., 0x7fff5fbff8ac).
                         // How it works: ptr holds that address (8 bytes). No data copy—indirection.
                         // Pitfall: If value goes out of scope, ptr dangles—UB! THATS WHERE IT GETS LEAKS BE CAREFUL WITH THAT
     std::cout<<"Address of value: " <<reinterpret_cast<uint64_t>(ptr) << std::endl;  // Line 3: Print address as uint64_t.
                                                                                        // reinterpret_cast: Raw bit reinterpret (unsafe but needed for printing addresses).
                                                                                        // How it works: << overloads for ostream; hex output shows raw memory coord.
     std::cout<<"Value via pointer:"<<*ptr<<std::endl;  // Line 4: Dereference *ptr—loads 42 from address.
                                                              // How it works: CPU fetch from RAM: mov eax, [ptr] (load indirect).
                                                              // Tie-in: In quant, *ptr loads trade price from buffer—O(1) access.
     *ptr = 100;  // Line 5: Modify via pointer—changes value to 100.
                  // How it works: mov [ptr], 64h (store indirect). Original value now 100—pointers mutate!
                  // Creative twist: In AI, *ptr updates neural weight; in cyber, overwrites buffer for encryption.
     std::cout << "Modified value: " << value << std::endl;  // Line 6: Prints 100—proves indirection.
                                                            // How it works: Direct access to value (stack load).
     int* nullPtr = nullptr;  // Line 7: Null pointer—safe "empty" state.
                              // How it works: All bits 0 (address 0x0, invalid). From research: C++11 nullptr is type-safe (no implicit int convert).
     // if (nullPtr != nullptr) *nullPtr = 5;  // Commented: Would crash—dereference null = segfault.
                                              // How it works: CPU tries fetch from 0x0 (protected page)—OS kills process.
     return 0;  // Line 8: Exit success. Stack unwinds—value deallocated, but ptr dangles if returned (UB!).
                // How it works: Assembly: mov eax, 0; ret (pop stack, jump to caller).
 }

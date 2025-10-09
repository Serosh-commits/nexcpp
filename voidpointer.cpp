/*
 * Void pointers (void*) are type-erased arrows—point to anything, but lose type info. Cast to access.
 */
 //HERE WE WILL TRY TO MAKE A GENERIC BUFFER USED IN CYBERSYSTEMS
 #include <iostream>
 #include <cstdint>  // uintptr_t for address math.
 union ThreatData {  // Union: Overlaps memory for mixed types
     int id;         // 4 bytes.
     double score;   // 8 bytes
 };
 void parseThreat(void* buffer,size_t offset,size_t typeSize)
 {  // Generic parser.
     uintptr_t addr=reinterpret_cast<uintptr_t>(buffer)+offset;  // Line 1: Compute offset address.
                                                                     // How it works: uintptr_t as integer address (math: addr = base + offset).
                                                                     // reinterpret_cast: Bit-for-bit copy to integer.

     void* typedAddr=reinterpret_cast<void*>(addr);// Line 2: Back to void*—safe offset.
                                                    // How it works: Cast integer to pointer (implementation-defined, but standard on x86).

     if (typeSize==sizeof(int))
     {                                              // Line 3: Runtime type check—dispatch.
         int* idPtr = static_cast<int*>(typedAddr);  // Safe cast to int*.
         std::cout << "Threat ID: " << *idPtr << "\n";  // Dereference.
         // How it works: *idPtr loads 4 bytes from addr.
     }
     else if (typeSize == sizeof(double))
     {
         double* scorePtr = static_cast<double*>(typedAddr);
         std::cout << "Threat Score: " << *scorePtr << "\n";
         // How it works: FPU load (movsd xmm0, [rax]). Pitfall: Misalign = slow or crash on ARM.
     }
     else
     {
         std::cerr << "Invalid type size\n";  // Error handling.
     }
 }

 int main() {
     char rawBuffer[16] = {0};  // Raw byte buffer—simulate network packet (16 bytes).

     // Simulate writing mixed data.
     int* idLoc = reinterpret_cast<int*>(rawBuffer);  // Line 4: Cast raw to int*—write ID.
     *idLoc = 1337;  // Offset 0: ID = 1337
     double* scoreLoc = reinterpret_cast<double*>(rawBuffer + 4);  // Line 5: Offset 4 bytes for double.
     *scoreLoc = 0.95;  // Offset 4: Score = 0.95

     // Parse generically.
     parseThreat(rawBuffer, 0, sizeof(int));    // Outputs "Threat ID: 1337"
     parseThreat(rawBuffer, 4, sizeof(double)); // Outputs "Threat Score: 0.95"
     return 0;
 }

# Boolean Alegbra Symbols
(~) -> NOT, flips the bits 0 to 1 and 1 to 0
(&) -> AND,Outputs 1 only if both input bits are 1 
(|) -> OR,outputs 1 if either (or both) input bits are 1
(^) -> EXCLUSIVE-OR,Outputs 1 only if the input bits are different (one is 0, the other is 1).

# Bit vectors
Bit Vectors: The machine doesn't just process one bit at a time. It applies these operations across entire strings of bits (bit vectors) simultaneously, matching up the bits position by position

# Set Encoding 
Set Encoding: Bit vectors mechanically represent finite sets, where a 1 at a specific position means that element is present, and a 0 means it is absent Because of this, & physically performs set intersection, | performs set union, and ~ performs set complement.

# XOR 
The XOR Annihilator: XOR mathematically forms a "Boolean ring" where every element is its own additive inverse. Mechanically, this means applying XOR to a value with itself strictly cancels it out to zero ( a ˆ a =0).

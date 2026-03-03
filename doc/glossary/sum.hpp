#error This file is for documentation only - DO NOT INCLUDE
/**

@page sum Sum Types 

@section sum_construction Sum Constructions (The Logic of "OR")

Sums represent types where a choice is made between different alternatives. They are the mathematical **Dual** of 
Products Types.

@subsection sum_type Sum Type  \f$ (A + B) \f$ (The Coproduct)

An unlabeled, positional choice between types. 

An instance of a sum type represents an **Exclusive Choice**, formally it is the disjoint union of sets.

* **Exclusive Choice**: An instance of \f$ A + B \f$ contains either an A or a B, but never both simultaneously.

* **Cardinality**: The state space is the **sum** of its components: \f$ Card(A + B) = Card(A) + Card(B) \f$.

* **Algebraic Property**: It is the dual of the Product. While a Product asks you to "Take All," a Sum asks you to "Pick One."

In C++, this is most commonly represented by `std::variant`.
### Example
```cpp
std::variant<int, float> p; 
```

---

@section variant Variant Type (The Labeled Sum)

A **Variant** (commonly refered to as Tagged Union) is the labeled version of a Sum Type, serving as the dual of the 
**Record**.

While a Record has multiple labels present at once, a Variant as exactly one active label from a set of possibilities.

* **The Tag**: To ensure type safety, the implementation often uses a tag to track the currently stored type.

* **Cardinality**: The state space of a variant is the sum of the cardinalities of it's fields:
                    \f$ Card({l_1 : T_1, l_2 : T_2, ..., l_n : T_n}) = \sum_i^n Card(T_i) \f$

### Example 
```cpp
union particles {
    muons   m;  
    leptons l; 
    quarks  q;
};
```

@note As of today, kumi does not provides it's own sum types. The focus was made on product type and it's associated 
algebra.

---

[In the next page](@ref containers), we will one of the last kind of types that can be found througout kumi which are 
called container types.

**/

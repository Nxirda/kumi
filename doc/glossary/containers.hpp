#error This file is for documentation only - DO NOT INCLUDE
/**

@page containers Container Types

@section container_type Container Type (Type Constructors)
A **Container Type** is not a type itself, but a **Type Constructor**: a function that takes a type \f$ T \f$ and 
returns a new type \f$ F(T) \f$.

---

@section type_constructor The Role of F(T)

While Product and Sum types compose existing types, a Container defines a "shape" or "structure" independently of the 
data it holds.

* **Generics**: In C++, these are implemented via Templates. The template `std::vector<T>` is the constructor; 
                `std::vector<int>` is the resulting type.

* **Transformation**: Containers often allow for "Mapping" (Functors), where a function \f$ A \to B \f$ can be lifted 
                      to transform \f$ F(A) \to F(B) \f$.

@subsection container_programming Programming Languages Considerations

In the context of **Kumi**, understanding the difference between the **Container** (the wrapper) and the **Product** 
(the contents) is vital for optimization.

| Container Concept | C++ Implementation | Algebraic Intuition |
|:------------------|:-------------------|:--------------------|
| List / Sequence   | `std::vector<T>`   | Ordered collection of \f$ T \f$ |
| Set               | `std::set<T>`      | Unique collection of \f$ T \f$ |

### Example
```cpp
template<typename T>
struct Box {
    T value; // Box is the Type Constructor F
};

Box<int> instance; // F(int)

**/

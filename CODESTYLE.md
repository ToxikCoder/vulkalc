# Codestyle

If you are using JetBrains CLion make sure to apply codeStyleSettings.xml in `.idea/`

1. **Names**

Use camel case for classes, namespaces and file names. File name should be same as a class declared in this file or 
describe declared functions if there is no class inside

```cpp
namespace MyNameSpace
{
    class MyClass {}
}
```

Use lower camel case for naming methods, functions and public and protected fields
```cpp
void myFunction();

class MyClass
{
public:
    int myNumber;
protected:
    void protectedMethod();
    long protectedNumber;
}
```

Private methods should have `_` prefix, but still use lower camel case

```cpp
private:
    void _privateMethod();
```

Use capital letters and underscores to define macros

```cpp
#define MY_MACRO
```

Private fields use lower camel case too and `m_` prefix, 
pointer fields should add `p` before name, smart pointer should add pointer type before name

```cpp
class MyClass
{
private:
    int* m_pPointer;
    shared_ptr<int> m_spMyPointer // 's' for shared
    unique_ptr<int> m_upAnotherPointer // 'u' for unique
    auto_ptr<int> m_apYetAnother pointer // 'a' for auto
}
```

2. **Braces**

Every brace should be at the new line, except for lambda, empty or short function bodies, and lists initializers. Braces can be 
dropped out in if statements

```cpp
namespace MyNamespace
{
    class MyClass
    {
    public:
        void method()
        {
            ...
        }
        void emptyBody() {}
        int getMeaningOfLife() { return 42; }
    }
}

if() //same for "for", "while" e.t.c.
{
    ...
}
else if()
{
    ...
}
else
{
    ...
}

if(short)
    return 0;
else
    return 1;

MyClass obj = {1, "text"};

```

3. **Indentation**

Use tabs or spaces, but make sure you use 4 spaces for indentation and tab is equal to 4 spaces.

Access modifiers shouldn't be indented in class definition, only methods and fields.

```cpp
class MyClass
{
public:
    void m(); //indented
protected:
    void n(); //indented
private:
    int n; //indented
}
```

Class definition inside the namespace should be indented too.

```cpp
namespace MyNamespace
{
    class MyClass //indented
    {
    
    }
}
```

4. **Spaces, blank lines and line breaks**

Put a blank line after local headers - before system headers. This order is recommended: local files - 
library and framework files - system files.

```cpp
#include "Header.hpp"
#include "AnotherHeader.hpp"

#include <vulkan/vulkan.h>
#include <iostream>
#include <memory>
```

Put a blank line before every Doxygen comment

```cpp
void func();

/*!
 * Documentation here
 */
void documentedFunc(); 
```

Put a blank line between functions definitions and at the end of the file

```cpp
void func()
{
    ...
}

void anotherFunc()
{
    ...
}

```

Line can be broken inside the parameters list, initialization lists, method definition, template instantiation and 
definition parameters if the line is too long. Template class and function declaration should always be wrapped.

```cpp
void method(VeryLongClassNameThatProbablyShouldHaveBeenChangedALongTimeAgoButIAmNotSure& obj,
            AndAnotherRidiculouslyLongType& obj2, 
            YouWouldHaveThoughtThatByNowEveryoneShouldBeTiredOfWritingTheseLongTypes& obj3,
            Who::Thought::That::It::Is::Okay::For::Thing::Like::This::To::exist param4)
{
    ...
}

template<Oh::God::No::Please::Stop::It::I::Beg::You::I::Would::Give::You::Literally::Anything<Please::Have:: //this could have
Mercy<You::Son::Of::A<Grrm>>> type1, shared_ptr<vector<unique_ptr<MoreTemplates::Please<Iterator>>>> type2> //been a nice one line
templateFunction() //this is always on the new line
{
    ...
}

```

Chained method calls and operators can be wrapped too

```cpp
FunctionalObject obj;
obj.this().is().not().very().funny().i().would().prefer().you().do().not().write().like().that().but().it().is().still().up().to().you().if().you().break().the().lines() // not okay

obj.this().is().not().very().funny()
   .i().would().prefer().you().do().not().write().like().that()
   .but().it().is().still().up().to().you()
   .if().you().break().the().lines() //it's okay if you break lines like this
  
obj.this()
    .is()
    .not()
    .very()
    .funny()
    .i()
    .would()
    .prefer()
    .you()
    .do()
    .not()
    .write()
    .like()
    .that()
    .but()
    .it()
    .is()
    .still()
    .up()
    .to()
    .you()
    .if()
    .you()
    .break()
    .the()
    .lines() // don't you think that's overkill?
```

You shouldn't put spaces before parentheses

```cpp
void function(); //okay
void function (); //not okay
```

Put spaces before and after braces, around any operators except for unary operators and `*`, `&`, `->` operators.

```cpp
if() {} //okay
if(){} //not okay

int a = 1 * 2 * 3 * 4 * 5 * 6; //okay, you can break line, if it's too long
int a=1*2*3*4*5*6; //not okay
int* pa = &a; //okay
int* pa = & a; //not okay
```

There should be no spaces before `*` or `&` symbols in definitions or function parameters, but should be one space **after**.

```cpp
int* pa = &a; //okay
int * pa = &a; //not okay
int *pa = &a; //not okay

int* func(char* parameter); //okay
int * func(char *parameter); //not okay
```

5. **Other**

Const modifier

```cpp
void func(const int*); //okay
void func(int const*); //not okay
```

- You should use smart pointers wherever possible
- Check the parameters at the beginning of the function
- Specify thrown exception in signature
- Prefer short and descriptive names
- Document public classes, functions, fields

GL HF ;)

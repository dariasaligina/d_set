# d_set
*d_set* – библиотека для удобной и быстрой работы с множествами на С++.
## Установка и подключение
Для работы необходимо загрузить файлы проекта и убедиться что в свойствах стоит тип конфигурации `.lib`
Для использования библиотеки необходимо указать в дерективе `include` путь до файла `d_set.h`
``` c++
#include "D:\d_set\d_set.h"
```
## Функции
Множество `d_set` может быть использовано с любыми типами данных для которых определены знаки > и <.
### insert 
позволяет добавить элемент в множество.
```c++
int main()
{
    d_set<int> st;
    st.insert(1);   // st = {1}
    st.insert(4);   // st = {1, 4}
    st.insert(3);   // st = {1, 3, 4}
    st.insert(4);   // st = {1, 3, 4} 
}
```
### erase
позволяет удалить элемент из множества, если элемента нет ничего не делает
``` c++
int main()
{
    d_set<int> st;
    st.insert(1);   // st = {1}
    st.insert(4);   // st = {1, 4}
    st.insert(3);   // st = {1, 3, 4}

    st.erase(1);    // st = {3, 4}
    st.erase(2);    // st = {3, 4}
}
```
### to_vector
позволяет составить vector содержащий элементы множества отсортированными по возрастанию
```c++
int main()
{
    d_set<int> st;
    st.insert(1);   // st = {1}
    st.insert(4);   // st = {1, 4}
    st.insert(3);   // st = {1, 3, 4}
    
    vector<int> v = st.to_vector(); // v = {1, 3, 4}
}
```
### Операторы
Для множеств определены операторы + (объединение), & (пересечение) и – (разность)
``` c++
int main()
{
    d_set<int> st1, st2, st_sum, st_and, st_dif;
    st1.insert(1);   
    st1.insert(4);   
    st1.insert(3);   
    st1.insert(7);  // st1 = {1, 3, 4, 7}

    st2.insert(2);
    st2.insert(3);
    st2.insert(7);  // st2 = {2, 3, 7}

    st_sum = st1 + st2; // st_sum = {1, 2, 3, 4, 7}
    st_and = st1 & st2; // st_and = {3, 7}
    st_dif = st1 - st2; // st_dif = {1, 4}
}
```
### is_in
позволяет проверить наличие элемента или подмножества в множестве
``` c++
int main()
{
    d_set<int> st, st2;
    st.insert(1);   
    st.insert(4);   
    st.insert(3);   
    st.insert(7);  // st = {1, 3, 4, 7}

    st2.insert(1);
    st2.insert(3); // st2 = {1, 3}

    bool b1 = st.is_in(st2);    // true
    bool b2 = st.is_in(1);      // true
    bool b3 = st.is_in(5);      // false
}
```
### copy
копирование массива
``` c++
int main()
{
    d_set<int> st1, st2;
    st1.insert(1);   
    st1.insert(4);   
    st1.insert(3);   
    st1.insert(7);  // st1 = {1, 3, 4, 7}

    st2 = st1.copy();   // st2 = {1, 3, 4, 7}
}
```
### clear
очистка массива
``` c++
int main()
{
    d_set<int> st;
    st.insert(1);   
    st.insert(4);   
    st.insert(3);   
    st.insert(7);  // st = {1, 3, 4, 7}

    st.clear();    // st = {}
    return 0;
}
```
### size
Возвращает количество элементов массива
``` c++
int main()
{
    d_set<int> st;
    st.insert(1);   
    st.insert(4);   
    st.insert(3);   
    st.insert(7);  // st = {1, 3, 4, 7}

    int n = st.size(); // n = 4
}
```



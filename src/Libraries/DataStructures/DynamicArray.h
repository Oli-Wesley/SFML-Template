#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <iostream>
#include <stdexcept>

template<class T>
class DynamicArray
{
 public:
  DynamicArray() { reAlloc(2); };
  ~DynamicArray() { delete[] array_data; };

  // add an element at the end of the list.
  void append(const T& data)
  {
    if (array_size >= array_capacity)
    {
      reAlloc(array_capacity + array_capacity * 0.5);
    }
    array_data[array_size] = data;
    array_size++;
  };

  // Remove all elements.
  void clear()
  {
    for (int i = 0; i < array_size; i++)
    {
      array_data[i].~T();
    }
    reAlloc(2);
    array_size = 0;
  };

  // returns the number of elements with specified value.
  int count(T value)
  {
    int count = 0;

    for (int i = 0; i < array_size; i++)
    {
      if (array_data[i] == value)
        count++;
    }
    return count;
  };

  // adds the elements of any other list(of the same type) to the end of the
  // current list.
  void extend(DynamicArray<T> other_list)
  {
    for (int i = 0; i < other_list.size; i++)
    {
      append(other_list[i]);
    }
  };

  // returns index of the first element with specified Value.
  int index(T value)
  {
    int count = 0;
    for (int i = 0; i < array_size; i++)
    {
      if (array_data[i] == value)
      {
        return count;
      }
      count++;
    }
  };

  T find(T value) 
  { 
      return array_data[index(value)]; 
  }

  // Adds element into specified index.
  void insert(int index, T value)
  {
    // check if array has room, if not, grow it.
    if (array_size >= array_capacity)
    {
      reAlloc(array_capacity + array_capacity * 0.5);
    }

    T* new_array = new T[array_capacity];

    array_size++;
    index           = checkValidIndex(index);
    int current_pos = 0;

    for (int i = 0; i < array_size; i++)
    {
      if (i != index)
      {
        new_array[i] = array_data[current_pos];
        current_pos++;
      }
      else
      {
        new_array[i] = value;
      }
    }

    delete[] array_data;
    array_data = new_array;
  };

  // removes and returns element at specified Index.
  T pop(int index)
  {
    index = checkValidIndex(index);
    T data;
    int current_pos = 0;
    T* new_array    = new T[array_capacity];

    for (int i = 0; i < array_size; i++)
    {
      if (i != index)
      {
        // add to new array.
        new_array[current_pos] = array_data[i];
        current_pos++;
      }
      else
      {
        data = array_data[i];
      }
    }
    array_size--;

    delete[] array_data;
    array_data = new_array;

    // check if array needs shrinking.
    if (array_size - 1 < array_capacity - array_capacity * 0.5)
    {
      reAlloc(array_capacity - array_capacity * 0.5);
    }
    return data;
  };

  // Removes the first item with specified Value.
  bool remove(T value)
  {
    int count = 0;
    for (int i = 0; i < array_size; i++)
    {
      if (array_data[i] == value)
      {
        pop(count);
        return true;
      }
      count++;
    }
    return false;
  }

  int size() { return array_size; };

  T& operator[](int index)
  {
    index = checkValidIndex(index);

    return array_data[index];
  };
  
  T& get(int index) {
    index = checkValidIndex(index);

    return array_data[index];
  }

 private:
  int array_capacity = 2;
  int array_size     = 0;
  T* array_data      = nullptr;

  // re-allocate size of the array.
  void reAlloc(int new_capacity)
  {
    if (new_capacity >= 2)
    {
      T* new_array = new T[new_capacity];

      if (new_capacity < array_size)
      {
        array_size = new_capacity;
      }

      for (int i = 0; i < array_size; i++)
      {
        new_array[i] = array_data[i];
      }
      delete[] array_data;
      array_data     = new_array;
      array_capacity = new_capacity;
    }
  };

  int checkValidIndex(int index)
  {
    // wrap index:
    if (array_size == 0)
    {
      return 0;
    }
    if (index > array_size-1)
    {
      return index % array_size;
    }
    else if (index < 0)
    {
      return (index % array_size) + array_size;
    }
    return index;
  }
};

#endif // !DYNAMIC_ARRAY_H
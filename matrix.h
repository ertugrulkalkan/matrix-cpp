#include <iostream>

template<typename T>
class matrix
{
  private:
    size_t rowC;
    size_t colC;
    T ** buffer;

  public:
    matrix();
    matrix(size_t _rows, size_t _cols);
    matrix(matrix<T> &reading);
    virtual ~matrix();

    bool operator=(matrix<T> &in);
    matrix<T> operator+(matrix<T> &in);
    matrix<T> operator-(matrix<T> &in);
    matrix<T> operator*(matrix<T> &in);
    matrix<T> transpose();
    matrix<T> inverse();
    T det();
    
    T* operator[](size_t in)
    {
      if(in >= rowC) return NULL;
      return buffer[in];
    }

    size_t getRowC();
    size_t getColC();

    bool resize(size_t _rows, size_t cols, bool _copy = true);  
};
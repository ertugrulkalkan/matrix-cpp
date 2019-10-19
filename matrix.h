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

    matrix<T> submatrix(const matrix<T> &mx, size_t i_ignore, size_t j_ignore) const;


    bool operator==(const matrix<T> &in) const;
    bool operator=(const matrix<T> &in);
    matrix<T> operator+(const matrix<T> &in) const;
    matrix<T> operator-(const matrix<T> &in) const;
    matrix<T> operator*(const matrix<T> &in) const;
    void transpose();
    matrix<T> inverse();
    T det();
    
    T* operator[](size_t in) const
    {
      if(in >= rowC) return NULL;
      return buffer[in];
    }

    const size_t getRowC() const;
    const size_t getColC() const;

    bool resize(size_t _rows, size_t cols, bool _copy);  
};
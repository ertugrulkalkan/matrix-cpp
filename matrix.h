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
    matrix(const size_t _rows, const size_t _cols);
    matrix(const matrix<T> &reading);
    virtual ~matrix();

    /*
     * If both matrices equals, returns 'true',
     * Else returns 'false'.
     */
    bool operator==(const matrix<T> &in) const;
    /*
     * Copy 'in' matrix to '(*this)'.
     * If successful, returns 'false'.
     */
    bool operator=(const matrix<T> &in);
    /*
     * Add 'AxB' sized '(*this)' matrix by 'AxB' sized 'in' matrix.
     * If successful, returns 'AxB' sized matrix,
     * Else exits
     */
    matrix<T> operator+(const matrix<T> &in) const;
    /*
     * Subtract 'AxB' sized '(*this)' matrix by 'AxB' sized 'in' matrix.
     * If successful, returns 'AxB' sized matrix,
     * Else exits.
     */
    matrix<T> operator-(const matrix<T> &in) const;
    /*
     * Multiply 'AxB' sized '(*this)' matrix by 'BxC' sized 'in' matrix.
     * If successful, returns 'AxC' sized matrix,
     * Else exits.
     */
    matrix<T> operator*(const matrix<T> &in) const;
    /*
     * Transpose the matrix.
     * 'AxB' matrix to 'BxA'
     */
    void transpose();
    /*
     * Calculate inverse of matrix if posiable.
     * '(*this)' matrix must be a square matrix.
     * '(*this)->det()' must be a non zero value.
     */
    matrix<T> inverse();
    /*
     * Calculates determinant of matrix if posiable.
     * '(*this)' matrix must be a square matrix.
     * If successful, returns determinant value,
     * Else exits.
     */
    T det();
    
    /*
     * Index buffer.
     */
    T* operator[](size_t in) const
    {
      if(in >= rowC) return NULL;
      return buffer[in];
    }

    /*
     * Returns count of rows in matrix.
     */
    const size_t getRowC() const;
    /*
     * Returns count of columns in matrix.
     */
    const size_t getColC() const;

    /*
     * Resize the matrix.
     * _rows : New count of rows in matrix
     * _cols : New count of columns in matrix
     * _copy : Keep old data in matrix
     * If '_copy' is given 'false', new values in matrix are all will be zero.
     */
    void resize(const size_t _rows, const size_t cols, bool _copy);
    /*
     * Clear all content of class.
     * Calling this will release all memory used by this class.
     */
    void remove();
};
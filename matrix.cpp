#include "matrix.h"
#include "math.h"
#include <iostream>
using namespace std;
/***************************************************************************************************/
template <typename T> matrix<T> submatrix(const matrix<T> &in, size_t row_ignore, size_t col_ignore);
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix()
{
  this->rowC = 0;
  this->colC = 0;
  this->buffer = NULL;  
}
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix(const size_t _rows, const size_t _cols)
{
  this->rowC = 0;
  this->colC = 0;
  this->buffer = NULL;
  this->resize(_rows, _cols, false);
}
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix(const matrix<T> &reading)
{ 
  this->rowC = 0;
  this->colC = 0;
  this->buffer = NULL;
  (*this) = reading;
}
/***************************************************************************************************/
template <typename T>
matrix<T>::~matrix()
{
  this->remove();
}
/***************************************************************************************************/
template <typename T>
bool matrix<T>::operator==(const matrix<T> &in) const
{
  if((this->rowC != in.getRowC()) || (this->colC != in.getColC()))
    return false;

  for(size_t i = 0; i < this->rowC; i++)
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      if(this->buffer[i][j] != in[i][j])
        return false;
    }
  }
  return true;
}
/***************************************************************************************************/
template <typename T>
bool matrix<T>::operator=(const matrix<T> &in)
{
  this->resize(in.getRowC(), in.getColC(), false);
  for(size_t i = 0; i < this->rowC; i++)
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      buffer[i][j] = in[i][j];
    }
  }
  return false;
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &in) const
{
  matrix<T> out;
  if((this->rowC == in.getRowC()) && (this->colC == in.getColC()))
  {
    out.resize(this->rowC, this->colC, false);
    for(size_t i = 0; i < this->rowC; i++)
    {
      for(size_t j = 0; j < this->colC; j++)
      {
        out[i][j] = this->buffer[i][j] + in[i][j];
      }
    }
  }
  else
  {
    cout << "Operator is not available to add different sized matrices ! [function : matrix<T>::operator+(const matrix<T> &)]" << endl;
    cout << "EXIT_FAILURE" << endl;
    exit(EXIT_FAILURE);
  }
  return out;
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::operator+=(const matrix<T> &in)
{
  (*this) = (*this) + in;
  return;
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &in) const
{
  matrix<T> out;
  if((this->rowC == in.getRowC()) && (this->colC == in.getColC()))
  {
    out.resize(this->rowC, this->colC, false);
    for(size_t i = 0; i < this->rowC; i++)
    {
      for(size_t j = 0; j < this->colC; j++)
      {
        out[i][j] = this->buffer[i][j] - in[i][j];
      }
    }
  }
  else
  {
    cout << "Operator is not available to subtract different sized matrices ! [function : matrix<T>::operator-(const matrix<T> &)]" << endl;
    cout << "EXIT_FAILURE" << endl;
    exit(EXIT_FAILURE);
  }
  return out;
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::operator-=(const matrix<T> &in)
{
  (*this) = (*this) - in;
  return;
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &in) const
{
  matrix<T> out;
  
  if(this->colC != in.getRowC())
  {
    cout << "Operator is not available to multiply these matrices ! [function : matrix<T>::operator*(const matrix<T> &)]" << endl;
    cout << "EXIT_FAILURE" << endl;
    exit(EXIT_FAILURE);
  }

  out.resize(this->rowC, in.getColC(), false);
  for(size_t i = 0; i < out.getRowC(); i++)
    {
        for(size_t j = 0; j < out.getColC(); j++)
        {
            out[i][j] = 0;
            for(size_t k = 0; k < this->colC; k++)
            {
                out[i][j] += ((this->buffer[i][k]) * (in[k][j]));
            }
        }
    }
    return out;  
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::operator*=(const matrix<T> &in)
{
  (*this) = (*this) * in;
  return;
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::transpose()
{
  (*this) = this->getTranspose();
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::getTranspose() const
{
  matrix<T> out;

  out.resize(this->colC, this->rowC, false);
  for(size_t i = 0; i < this->rowC; i++)
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      out[j][i] = this->buffer[i][j];
    }
  }
  return out;
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::inverse()
{
  (*this) = this->getInverse();
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::getInverse() const
{
  if((this->det()) == 0)
  {
    cout << "Matrix is not invertable (det() equals zero) ! [function : matrix<T>::getInverse()]" << endl;
    cout << "EXIT_FAILURE" << endl;
    exit(EXIT_FAILURE);
  }
  matrix<T> out;
  out = this->getCofactor().getTranspose();
  out *= 1.0 / (double)this->det();
  return out;
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::cofactor()
{
  (*this) = this->getCofactor();
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::getCofactor() const
{
  matrix<T> out;
  out = (*this);
  for(size_t i = 0; i < this->rowC; i++)
  {
    for (size_t j = 0; j < this->colC; j++)
    {
      out[i][j] = submatrix((*this), i, j).det();
    }
  }

  return out;
}
/***************************************************************************************************/
template <typename T>
matrix<T> submatrix(const matrix<T> &in, size_t row_ignore, size_t col_ignore)
{
  matrix<T> submx;

  submx.resize((in.getRowC() - 1), (in.getColC() - 1), false);
  for(size_t i = 0, ii = 0; i < in.getRowC(); i++)
  {
    if(i == row_ignore)
      continue;
    for(size_t j = 0, jj = 0; j < in.getColC(); j++)
    {
      if(j == col_ignore)
      {
        continue;
      }
      else
      {
        submx[ii][jj] = in[i][j];
        jj++;
      }
    }
    ii++;
  }
  return submx;
}
/***************************************************************************************************/
template <typename T>
T matrix<T>::det() const
{
  if(!(this->isSquare()))
  {
    cout << "Not a square matrix ! [function : matrix<T>::det()]" << endl;
    cout << "EXIT_FAILURE" << endl;
    exit(EXIT_FAILURE);
  }
  T dt = (T)0;
  if((this->rowC == 2) && (this->colC == 2))
  {
    dt = (T)((this->buffer[0][0] * this->buffer[1][1]) - (this->buffer[0][1] * this->buffer[1][0]));
  }
  else
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      dt += (T)(this->buffer[0][j] * pow(-1,(0 + j)) * submatrix((*this), 0, j).det());
    }
  }
  return dt;
}
/***************************************************************************************************/
template <typename T>
const size_t matrix<T>::getRowC() const
{
  return this->rowC;
}
/***************************************************************************************************/
template <typename T>
const size_t matrix<T>::getColC() const
{
  return this->colC;
}
/***************************************************************************************************/
template <typename T>
const bool matrix<T>::isSquare() const
{
  return (this->rowC == this->colC) & (this->rowC != 0);
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::resize(const size_t _rows, const size_t _cols, bool _copy)
{
  if((_rows == 1) && (_cols == 1) || (_rows == 0) || (_cols == 0))
  {
    /* cannot resize a matrix as 1x1 */
                                /* if any of them equals zero than the total size is zero */
    this->remove();
    return;
  }
  else if(this->rowC == _rows)
  {
    /* no need to resize buffer */
    if(_cols == this->colC)
    {
      /* no need to resize buffer[i] */
      if(!(_copy))
      {
        for(size_t i = 0; i < this->rowC; i++)
        {
          for(size_t j = 0; j < this->colC; j++)
            this->buffer[i][j] = 0;
        }
      }
      return;
    } 
    else
    {
      /* need to resize buffer[i] */
      T* temp;
      for(size_t i = 0; i < this->rowC; i++)
      {
        temp = this->buffer[i];
        this->buffer[i] = new T[_cols];

        /* if copy resize, copy old content */
        for(size_t j = 0; _copy && (j < (min(_cols, this->colC))); j++)
        {
          this->buffer[i][j] = temp[j];
        }
        free(temp);        
      }
      this->colC = _cols;
      this->rowC = _rows;
      return;
    }
  }
  else
  {
    /* need to resize buffer */
    T** temp;
    temp = this->buffer;

    this->buffer = new T*[_rows];
    for(size_t i = 0; i < _rows; i++)
    {
      this->buffer[i] = new T[_cols];
    }

    /* if copy resize, copy old content */
    for(size_t i = 0; _copy  && (i < min(_rows, this->rowC)); i++)
    {
      for(size_t j = 0; j < min(_cols, this->colC); j++)
      {
        this->buffer[i][j] = temp[i][j];
      }
    }

    /* free old buffer */
    for(size_t i = 0; i < this->rowC; i++)
      free(temp[i]);
    free(temp);

    this->colC = _cols;
    this->rowC = _rows;
    return;
  }
  cout << "Couldn't resize the matrix ! [function : matrix<T>::resize(size_t _rows, size_t _cols, bool _copy)]" << endl;
  cout << "EXIT_FAILURE" << endl;
  exit(EXIT_FAILURE);
}
/***************************************************************************************************/
template <typename T>
void matrix<T>::remove()
{
  if(buffer != NULL){
    for(size_t i = 0; i < this->rowC; i++)
      if((this->buffer[i]) != NULL)
        free(this->buffer[i]);
    free(this->buffer);
    this->buffer = NULL;
  }
  this->rowC = 0;
  this->colC = 0;
}
/***************************************************************************************************/
template class matrix<double>;
template class matrix<float>;
template class matrix<int>;
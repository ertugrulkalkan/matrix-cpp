#include "matrix.h"
#include "math.h"
#include <iostream>
using namespace std;
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix()
{
  this->rowC = 0;
  this->colC = 0;
  buffer = NULL;
}
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix(size_t _rows, size_t _cols)
{
  if(_rows == 0 || _cols == 0)
    return;

  this->rowC = _rows;
  this->colC = _cols;

  buffer = new T*[this->rowC];
  for(size_t i = 0; i < this->rowC; i++)
    buffer[i] = new T[this->colC];
}
/***************************************************************************************************/
template <typename T>
matrix<T>::matrix(matrix<T> &reading)
{
  size_t _rows,_cols;

  _rows = reading.getRowC();
  _cols = reading.getColC();

  if(_rows == 0 || _cols == 0)
    return;

  this->rowC = _rows;
  this->colC = _cols;

  buffer = new T*[this->rowC];
  for(size_t i = 0; i < this->rowC; i++)
    buffer[i] = new T[this->colC];

  for(size_t i = 0; i < this->rowC; i++)
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      buffer[i][j] = reading[i][j];
    }
  }
}
/***************************************************************************************************/
template <typename T>
matrix<T>::~matrix()
{
  for(int i = 0; i < this->rowC; i++)
    free(buffer[i]);
  free(buffer);
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
      continue;
    }
  }
  return true;
}
/***************************************************************************************************/
template <typename T>
bool matrix<T>::operator=(const matrix<T> &in)
{
  if((resize(in.rowC, in.colC, false)))
  {
    for(size_t i = 0; i < this->rowC; i++)
    {
      for(size_t j = 0; j < this->colC; j++){
        buffer[i][j] = in[i][j];
      }
    }
    return false;
  }
  return true;
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
      for(size_t j = 0; j < this->colC; j++){
        out[i][j] = this->buffer[i][j] + in[i][j];
      }
    }
  }
  return out;
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
      for(size_t j = 0; j < this->colC; j++){
        out[i][j] = this->buffer[i][j] - in[i][j];
      }
    }
  }
  return out;
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &in) const
{
  matrix<T> out;
  
  if(this->colC != in.getRowC())
    return out;
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
void matrix<T>::transpose()
{
  matrix<T> out;

  if(out.resize(this->colC, this->rowC, false))
  {
    for(size_t i = 0; i < this->rowC; i++)
    {
      for(size_t j = 0; j < this->colC; j++)
      {
        out[j][i] = this->buffer[i][j];
      }
    }
  }
  *this = out;
}
/***************************************************************************************************/
template <typename T>
matrix<T> matrix<T>::inverse()
{

}
/***************************************************************************************************/
template <typename T>
matrix<T> submatrix(const matrix<T> &mx, size_t row_ignore, size_t col_ignore)
{
  size_t mx_row = mx.getRowC();
  size_t mx_col = mx.getColC();
  matrix<T> submx;

  if((row_ignore >= mx_row) || (col_ignore >= mx_col))
  {
    submx = mx;
  }
  else
  {
    submx.resize((mx_row - 1), (mx_col - 1), false);
    for(size_t i = 0, ii = 0; i < mx_row; i++)
    {
      if(i == row_ignore)
      {
        continue;
      }
      else
      {
        for(size_t j = 0, jj = 0; j < mx_col; j++)
        {
          if(j == col_ignore)
          {
            continue;
          }
          else
          {
            submx[ii][jj] = mx[i][j];
            jj++;
          }
        }
        ii++;
      }
    }
  }
  return submx;
}
/***************************************************************************************************/
template <typename T>
T matrix<T>::det()
{
  T dt = (T)0;
  if((this->rowC == 2) && (this->colC == 2))
  {
    dt = (T)((this->buffer[0][0] * this->buffer[1][1]) - (this->buffer[0][1] * this->buffer[1][0]));
  }
  else
  {
    for(size_t i = 0; i < this->rowC; i++)
    {
      for(size_t j = 0; j < this->colC; j++)
      {
        dt += (T)(this->buffer[i][j] * pow(-1,(i + j)) * submatrix((*this), i, j).det());
      }
    }
    dt /= (T)(this->rowC);
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
bool matrix<T>::resize(size_t _rows, size_t _cols, bool _copy)
{
  if(_rows == 0 || _cols == 0)
    return false;
  
  if(_rows == this->rowC)
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
      return true;
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
        
        this->colC = _cols;
        this->rowC = _rows;
        
        return true;
      }
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
      for(size_t j = 0; j < min(_cols, this->colC); j++){
        this->buffer[i][j] = temp[i][j];
      }
    }

    for(size_t i = 0; i < this->rowC; i++)
      free(temp[i]);
    free(temp);

    this->colC = _cols;
    this->rowC = _rows;

    return true;
  }
  return false;
}
/***************************************************************************************************/
template class matrix<double>;
template class matrix<float>;
template class matrix<int>;
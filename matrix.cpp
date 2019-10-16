#include "matrix.h"
#include <iostream>
using namespace std;

template <typename T>
matrix<T>::matrix()
{
  this->rowC = 0;
  this->colC = 0;
  buffer = NULL;
}

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

template <typename T>
matrix<T>::~matrix()
{
  for(int i = 0; i < this->rowC; i++)
    free(buffer[i]);
  free(buffer);
}

template <typename T>
bool matrix<T>::operator=(matrix<T> &in)
{ 
  
  /*
  for(int i = 0; i < this->rowC; i++)
    free(buffer[i]);
  free(buffer);

  size_t _rows,_cols;

  _rows = in.getRowC();
  _cols = in.getColC();

  if(_rows == 0 || _cols == 0)
    return true;

  this->rowC = _rows;
  this->colC = _cols;

  buffer = new T*[this->rowC];
  for(size_t i = 0; i < this->rowC; i++)
    buffer[i] = new T[this->colC];

  for(size_t i = 0; i < this->rowC; i++)
  {
    for(size_t j = 0; j < this->colC; j++)
    {
      buffer[i][j] = in[i][j];
    }
  }
  return true;
  */
}

template <typename T>
matrix<T> matrix<T>::operator+(matrix<T> &in)
{
  
}

template <typename T>
matrix<T> matrix<T>::operator-(matrix<T> &in)
{
  
}

template <typename T>
matrix<T> matrix<T>::operator*(matrix<T> &in)
{
  
}

template <typename T>
size_t matrix<T>::getRowC()
{
  return this->rowC;
}

template <typename T>
size_t matrix<T>::getColC()
{
  return this->colC;
}

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

template class matrix<double>;
template class matrix<float>;
template class matrix<int>;
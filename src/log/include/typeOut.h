/** @file typeOut.h
	@brief Базовый класс для разных видов вывода в лог
*/

#ifndef __TYPEOUT_H__
#define __TYPEOUT_H__

#include <string>
#include <memory>

class typeOut
{
public:
  /** @brief получаем строку для записи в лог*/
  virtual void logstr( std::string log_ ) = 0 ;
protected:
    /** @brief Мьютекс */
  std::mutex _lock;
};

#endif // __TYPEOUT_H__
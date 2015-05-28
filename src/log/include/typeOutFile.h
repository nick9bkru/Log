/** @file typeOutFile.h
	@brief Класс для вывода лога в файл
*/

#ifndef __TYPEOUTFILE_H__
#define __TYPEOUTFILE_H__

#include <fstream>
#include <mutex> 
#include "typeOut.h"

class typeOutFile: public typeOut
{
public:  
  typeOutFile( std::string file /**< Имя файла */);
  /** @brief получаем строку для записи в лог*/
  virtual void logstr( std::string log_ /**< Строка вывода в лог */) ;
private:
  /** @brief Поток */
  std::unique_ptr<std::ofstream> logStream;

};

#endif // __TYPEOUTFILE_H__
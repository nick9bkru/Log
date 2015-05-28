#include "typeOutFile.h"

typeOutFile::typeOutFile( std::string file)
{
   logStream.reset(new std::ofstream(file.c_str(), std::ios::out | std::ios::app));
};
    
void typeOutFile::logstr( std::string log_ /**< Строка вывода в лог */) 
{
  std::lock_guard<std::mutex> locker(_lock);
  if (!logStream.get() || !logStream->good())
	return;
  *logStream.get() << log_;
};
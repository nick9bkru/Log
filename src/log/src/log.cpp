#include "log.h"
#include <limits.h>

/** @brief Параметры вывода лога */
Log::outputInf Log::outInf;
/** @brief Указатель на базовый класс записи строки */
typeOut * Log::logout ;
/** @brief количество строк в файле */
unsigned long long Log::countStr;

Log::Log(const outputInf outputInf_ , typeOut * logout_)
{
  outInf =  outputInf_;
  logout = logout_;
  countStr = 0;
  if ( logout == nullptr )
  {
    outInf.stdout = true;
    outInf.fileLog = false;
  };
}

Log::Log()
{
  if ( logout == nullptr )
  {
    outInf.stdout = true;
    outInf.fileLog = false;
  };
};

Log::~Log()
{
}


void Log::message(LogLevel messageLevel, const std::string& message)
{
	static const std::string sLevels[] = { " < DEBUG > ", " < INFO >  ", " < WARING >", " < ERROR > ", " < FATAL > " };

	std::ostringstream log;
	countStr ++;
	countStr %= ULLONG_MAX;
	//std::ofstream& log = *logStream;
	if ( outInf.numLine)
	{
	  log << countStr << " ";
	};
	if ( outInf.logDate ) 
	{
	  log << getDate();
	};
	if ( outInf.logDate ) 
	{
	  log << sLevels[messageLevel] ;
	};
	log << std::setw(5) << std::setfill(' ') << getpid();
	log << ":: " <<message << std::endl;
	
	if ( outInf.stdout )
	{
	  std::cout << log.str();
	} else 
	{
	  logout->logstr(log.str());
	};
}

Log::MessageInternal::~MessageInternal() 
{
	if ( Log::shouldWrite(level) )
		log->message(level, s.str());
};

Log::Message Log::error() 
{
  return Message(new MessageInternal(this, ERROR)); 
}

Log::Message Log::warning() 
{ 
  return Message(new MessageInternal(this, WARNING)); 
}

Log::Message Log::info() 
{ 
  return Message(new MessageInternal(this, INFO)); 
}

Log::Message Log::debug() 
{ 
  return Message(new MessageInternal(this, DEBUG));
}

Log::Message Log::fatal()
{ 
  return Message(new MessageInternal(this, FATAL)); 
}

bool Log::shouldWrite(LogLevel messageLevel) 
{
  return messageLevel >=  outInf.Level ;
}

std::string Log::getDate()
{
  const time_t t_now = time(NULL);
  tm now;
  localtime_r(&t_now, &now);
  struct timeval timeofday;
  gettimeofday(&timeofday, (struct timezone *) NULL);
  std::ostringstream date_;
  date_ << (1900 + now.tm_year) << ":"<< std::setw(2) << std::setfill('0') << (1 + now.tm_mon)<< ":" << std::setw(2) << std::setfill('0') << now.tm_mday << "-";
  date_<< std::setw(2) << std::setfill('0') << now.tm_hour << ":" << std::setw(2) << std::setfill('0') << now.tm_min << ":" << std::setw(2) << std::setfill('0') <<
  now.tm_sec << "." << std::setw(3) << std::setfill('0') << (timeofday.tv_usec / 1000) << " ";
  return date_.str();
};

Log::outputInf Log::outputInf::operator =( const Log::outputInf & right)
{
  Level = right.Level;
  logDate = right.logDate;
  numLine = right.numLine;
  fileLog = right.numLine;
  stdout = right.stdout;
  return *this;
};


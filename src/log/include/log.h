/** @file log.h
	@brief Класс, осуществляющий ведение лога
*/

#ifndef __LOG_H__
#define __LOG_H__

#include <fstream>
#include <memory>
#include <sstream>
#include <string>


#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>

#include "typeOutFile.h"

/** @class Log	
	@brief Класс, осуществляющий ведение внутреннего лога сервера
*/
class Log {
public:
	/** @brief Уровень детализации лога */
	enum LogLevel { 		DEBUG, /**< Отладочный режим */
					INFO, /**< Стандартный режим */
					WARNING, /**< Отображаются только предупреждения */
					ERROR, /**< Отображаются только ошибки */
                                        FATAL /**< Отоборажаются только фатальные ошибки */
				};
				
	/** @brief Уровень детализации лога */	
	struct outputInf_s
	{
	  LogLevel Level; /**< Уровень подробности лога */
	  bool logDate;   /**< Записывать ли в лог дату в каждую строку */
	  bool numLine;   /**< считать ли строки  */
	  bool fileLog;   /**< название файла лога в каждой строке   */
	  bool stdout;    /**< выводить ли на экран   */
	  public:
	    struct outputInf_s operator =( const struct outputInf_s & right);
	};
	typedef struct outputInf_s outputInf;	
	
	Log( const outputInf outputInf_ , /**< Уровень подробности лога */
		typeOut * logout_ = nullptr /**< Класс вывода в лог */
	);
	
	Log( );
	~Log();
	
	/** @brief Сообщение лога */
	class MessageInternal {
		friend class Log;
	public:
		~MessageInternal() ;
	/** @brief Оператор вывода в поток */
		template<typename T> MessageInternal& operator<< (const T& t)
		{
		  s << t;
		  return *this;
		};
	private:
		MessageInternal(Log* _log, LogLevel _level) : log(_log), level(_level) { }
		MessageInternal(const MessageInternal&);
	/** @brief Оператор присваивания */
		MessageInternal& operator= (const MessageInternal&);

	/** @brief Поток */
		std::ostringstream s;
	/** @brief Лог */
		Log* log;
	/** @brief Уровень подробности лога */
		LogLevel level;
	};

	/** @brief Сообщение */
	typedef std::shared_ptr <MessageInternal> Message;
	
	/** 
		@brief Создать сообщение уровня подробности "ERROR"
		@brief @return Сообщение уровня "ERROR"
	*/
	Message error() ;
	/** 
		@brief Создать сообщение уровня подробности "WARNING"
		@brief @return Сообщение уровня "WARNING"
	*/
	Message warning();
	/** 
		@brief Создать сообщение уровня подробности "INFO"
		@brief @return Сообщение уровня "INFO"
	*/
	Message info();
	/** 
		@brief Создать сообщение уровня подробности "DEBUG"
		@brief @return Сообщение уровня "DEBUG"
	*/
	Message debug();
	/** 
		@brief Создать сообщение уровня подробности "DETAILED_DEBUG"
		@brief @return Сообщение уровня "DETAILED_DEBUG"
	*/
	Message fatal();
	/** 
		@brief Сделать запись в лог
	*/
	void message(LogLevel messageLevel, /**< Уровень подробности сообщения */
					const std::string& message /**< Сообщение */
					);
	/** 
		@brief Узнать, подходит ли данное сообщение под уровень подробности лога
		@brief @return Подходит ли данное сообщение под уровень подробности лога
	*/

	static bool shouldWrite(LogLevel messageLevel);
	
private:
	/** 
		@brief Получить строку даты
		@brief @return Дата
	*/
	std::string getDate();

// 	/** @brief Уровень подробности лога */
// 	static LogLevel minLevel;
	/** @brief Поток записи лога*/
//	static std::auto_ptr<std::ofstream> logStream;
	
	/** @brief Параметры вывода лога */
	static outputInf outInf;
	
	/** @brief Мьютекс */
	///*static */std::mutex _lock;
	
	/** @brief Указатель на базовый класс записи строки */
	static typeOut * logout ;
	/** @brief количество строк в файле */
	static unsigned long long countStr;
};


template<typename T>
Log::Message operator<< (Log::Message msg, const T& t) 
{
	*(msg.get()) << t;
	return msg;
}

#endif // __LOG_H__

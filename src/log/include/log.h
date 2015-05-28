/** @file log.h
	@brief �����, �������������� ������� ����
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
	@brief �����, �������������� ������� ����������� ���� �������
*/
class Log {
public:
	/** @brief ������� ����������� ���� */
	enum LogLevel { 		DEBUG, /**< ���������� ����� */
					INFO, /**< ����������� ����� */
					WARNING, /**< ������������ ������ �������������� */
					ERROR, /**< ������������ ������ ������ */
                                        FATAL /**< ������������� ������ ��������� ������ */
				};
				
	/** @brief ������� ����������� ���� */	
	struct outputInf_s
	{
	  LogLevel Level; /**< ������� ����������� ���� */
	  bool logDate;   /**< ���������� �� � ��� ���� � ������ ������ */
	  bool numLine;   /**< ������� �� ������  */
	  bool fileLog;   /**< �������� ����� ���� � ������ ������   */
	  bool stdout;    /**< �������� �� �� �����   */
	  public:
	    struct outputInf_s operator =( const struct outputInf_s & right);
	};
	typedef struct outputInf_s outputInf;	
	
	Log( const outputInf outputInf_ , /**< ������� ����������� ���� */
		typeOut * logout_ = nullptr /**< ����� ������ � ��� */
	);
	
	Log( );
	~Log();
	
	/** @brief ��������� ���� */
	class MessageInternal {
		friend class Log;
	public:
		~MessageInternal() ;
	/** @brief �������� ������ � ����� */
		template<typename T> MessageInternal& operator<< (const T& t)
		{
		  s << t;
		  return *this;
		};
	private:
		MessageInternal(Log* _log, LogLevel _level) : log(_log), level(_level) { }
		MessageInternal(const MessageInternal&);
	/** @brief �������� ������������ */
		MessageInternal& operator= (const MessageInternal&);

	/** @brief ����� */
		std::ostringstream s;
	/** @brief ��� */
		Log* log;
	/** @brief ������� ����������� ���� */
		LogLevel level;
	};

	/** @brief ��������� */
	typedef std::shared_ptr <MessageInternal> Message;
	
	/** 
		@brief ������� ��������� ������ ����������� "ERROR"
		@brief @return ��������� ������ "ERROR"
	*/
	Message error() ;
	/** 
		@brief ������� ��������� ������ ����������� "WARNING"
		@brief @return ��������� ������ "WARNING"
	*/
	Message warning();
	/** 
		@brief ������� ��������� ������ ����������� "INFO"
		@brief @return ��������� ������ "INFO"
	*/
	Message info();
	/** 
		@brief ������� ��������� ������ ����������� "DEBUG"
		@brief @return ��������� ������ "DEBUG"
	*/
	Message debug();
	/** 
		@brief ������� ��������� ������ ����������� "DETAILED_DEBUG"
		@brief @return ��������� ������ "DETAILED_DEBUG"
	*/
	Message fatal();
	/** 
		@brief ������� ������ � ���
	*/
	void message(LogLevel messageLevel, /**< ������� ����������� ��������� */
					const std::string& message /**< ��������� */
					);
	/** 
		@brief ������, �������� �� ������ ��������� ��� ������� ����������� ����
		@brief @return �������� �� ������ ��������� ��� ������� ����������� ����
	*/

	static bool shouldWrite(LogLevel messageLevel);
	
private:
	/** 
		@brief �������� ������ ����
		@brief @return ����
	*/
	std::string getDate();

// 	/** @brief ������� ����������� ���� */
// 	static LogLevel minLevel;
	/** @brief ����� ������ ����*/
//	static std::auto_ptr<std::ofstream> logStream;
	
	/** @brief ��������� ������ ���� */
	static outputInf outInf;
	
	/** @brief ������� */
	///*static */std::mutex _lock;
	
	/** @brief ��������� �� ������� ����� ������ ������ */
	static typeOut * logout ;
	/** @brief ���������� ����� � ����� */
	static unsigned long long countStr;
};


template<typename T>
Log::Message operator<< (Log::Message msg, const T& t) 
{
	*(msg.get()) << t;
	return msg;
}

#endif // __LOG_H__

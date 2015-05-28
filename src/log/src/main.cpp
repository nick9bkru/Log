#include <iostream>
#include "log.h"
#include <unistd.h> 
#include <thread>

#define PROG_NAME "LOG"
#define UNUSED(x) (void)x

using namespace std;

void start()
{
  cout << "=============================" <<endl;
  cout << "=============================" <<endl;
  cout << "|                           |" <<endl;
  cout << "|    Start "<< PROG_NAME <<" program   |" <<endl;
  cout << "|                           |" <<endl;
  cout << "=============================" <<endl;
  cout << "==========  BUILD  ==========" <<endl;
  cout << "=  " << __TIMESTAMP__ << "  =" <<endl;
  cout << "=============================" <<endl;

};

void thread_()
{
  Log log;
   while (1)
  {
    log.fatal() << "11111111111111111 == " << std::this_thread::get_id();
    log.error() << std::string("1234123 ") << "asdasd";
    log.debug() << std::string("1234123 ") << "asdasd";
   log.info() << std::string("1234123 ") << "asdasd";
   log.warning() << std::string("1234123 ") << "asdasd";
   usleep(100);
  }
  
};

int main(int argc, char **argv)
{
 UNUSED (argc); UNUSED (argv);
 start();

 Log::outputInf inf;
 inf.Level=Log::WARNING; /**< Уровень подробности лога */
 inf.logDate=1;   /**< Записывать ли в лог дату в каждую строку */
 inf.numLine=1;   /**< считать ли строки  */
 inf.fileLog=1;   /**< название файла лога в каждой строке   */
 inf.stdout=0;
 
 typeOut* OutFile = new typeOutFile ( "./1.log" );
 Log log( inf ,OutFile);
 std::thread *t[100];
 for ( int i = 0; i < 100; i++)
 {
  t[i]= new std::thread (thread_); 
 }
 t[1]->join();
 return 0;
};
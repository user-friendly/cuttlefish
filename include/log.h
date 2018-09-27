/**
 * @file
 * Log declaration file.
 */

#ifndef LOG_H
#define LOG_H

#include "std.h"

BOOST_LOG_GLOBAL_LOGGER(BLogger, boost::log::sources::logger_mt);  

namespace cuttlefish
{

  class Log
  {
  public:
    Log();

#ifdef DEBUG
    ~Log();
#endif
    
    const Log& DebugApplication(const char* fmt, ...) const;

    template<int Category, SDL_LogPriority Priority>
    inline const Log& Message(const char* fmt, ...) const
    {
      va_list args;
      va_start(args, fmt);
      SDL_LogMessageV(Category, Priority, fmt, args);
      return *this;
    };
    
    template<int Category, SDL_LogPriority Priority>
    inline const Log& MessageV(const char* fmt, va_list args) const
    {
      SDL_LogMessageV(Category, Priority, fmt, args);
      return *this;
    };
  };
  
}
#endif // LOG_H

// All units should have access to the logger.
extern const cuttlefish::Log Logger;

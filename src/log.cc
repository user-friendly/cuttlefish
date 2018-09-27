/**
 * @file
 * Log driver definition file.
 */

#include "log.h"

BOOST_LOG_GLOBAL_LOGGER_INIT(BLogger, boost::log::sources::logger_mt)
{
  boost::log::sources::logger_mt lg;
  return lg;
};

namespace cuttlefish
{
  Log::Log()
  {
    #ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    #endif
    
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Logger created");
  };
  
#ifdef DEBUG
  Log::~Log()
  {
    std::cerr << "DEBUG: Logger destroyed." << std::endl;
  };
#endif

  const Log& Log::DebugApplication(const char* fmt, ...) const
  {
    va_list args;
    va_start(args, fmt);
    MessageV<SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG>(fmt, args);
    return *this;
  };


  
}

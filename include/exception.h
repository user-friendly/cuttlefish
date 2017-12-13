/**
 * @file
 * Exception declaration file.
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "types.h"

namespace cuttlefish
{
  class Exception
  {
  public:
    Exception ();
    Exception (const char* message);
    Exception (const String& message);
    String message();
    Exception& operator<<(const char* append);
    Exception& operator<<(const String& append);
  protected:
    String msg;
  };
}

#endif
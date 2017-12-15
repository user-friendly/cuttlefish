/**
 * @file
 * Exception declaration file.
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

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

#endif // EXCEPTION_H

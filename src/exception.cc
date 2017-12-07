/**
 * @file
 * Exception definition file.
 */

#include "exception.h"

namespace cuttlefish
{
  Exception::Exception() :
    msg("Undefined error")
  {};

  Exception::Exception(const char* message) :
    msg(message)
  {};

  Exception::Exception(const String& message) :
    msg(message)
  {};

  String Exception::message()
  {
    return this->msg;
  };

  Exception& Exception::operator<<(const char* append)
  {
    this->msg += append;
    return *this;
  };
  
  Exception& Exception::operator<<(const String& append)
  {
    this->msg += append;
    return *this;
  };
}

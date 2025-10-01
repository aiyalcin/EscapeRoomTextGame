#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <iostream>

#ifdef _DEBUG
#define LOG_DEBUG   std::cout  << __FILE__<< " " << __LINE__ << " " <<  __FUNCTION__ << std::endl;
#else
#define LOG_DEBUG
#endif
#endif

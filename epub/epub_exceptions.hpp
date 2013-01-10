// =====================================================================================
// 
//       Filename:  epub_exceptions.hpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2013 09:40:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================
#pragma once
#include <exception>
namespace epub
{
class file_write_exception                :public std::exception{};
class terrible_operating_system_exception :public std::exception{};
class zip_exit_status_exception           :public std::exception{};
class path_changed_exception              :public std::exception{};
class user_wants_out_exception            :public std::exception{};
}

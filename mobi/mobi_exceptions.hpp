#pragma once
#include <exception>
namespace mobi 
{
class no_such_file_exception                :public std::exception{};
class invalid_file_exception                :public std::exception{};
class invalid_compression_type_exception    :public std::exception{};
class header_out_of_range_exception         :public std::exception{};
class unsupported_compressiontype_exception :public std::exception{};
}

#pragma once

#include<iostream>
#include<string>
#include<tuple>

#if !defined(DEBUG_COUT)
#define DEBUG_COUT 1
#endif 

#if !defined(DEBUG_FILE)
#define DEBUG_FILE 1
#endif 

inline void log(std::string s)
{
    if constexpr (DEBUG_COUT)
    {
        std::cout << s << std::endl;
    }
}

template <typename... Args>
inline void log(Args &&...args)
{
    if constexpr (DEBUG_COUT)
    {
         [&]<std::size_t... I>(std::index_sequence<I...>)
        {
            auto tuple = std::forward_as_tuple(std::forward<Args>(args)...);
            ((std::cout << std::get<I * 2>(tuple) << " : " << std::get<I * 2 + 1>(tuple) 
            << std::endl), ...);
        }(std::make_index_sequence<sizeof...(Args) / 2>{});
    }
}

inline void log_file(std::string s)
{

}

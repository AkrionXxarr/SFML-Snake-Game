#ifndef _GENERAL__INCLUDE_HPP_
#define _GENERAL__INCLUDE_HPP_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <cstdint>

#define SAFE_DELETE(p) { if (p) { delete(p); (p) = NULL; } }

#define u8max 0xFF
#define u16max 0xFFFF
#define u32max 0xFFFFFFFF

typedef std::int8_t  i8;
typedef std::int16_t i16;
typedef std::int32_t i32;

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;

#endif
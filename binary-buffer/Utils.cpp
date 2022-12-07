#include "pch.hpp"
#include "Utils.hpp"

const bool Utils::IsLittleEndian = IsLittleEndianCast();

bool Utils::IsLittleEndianCast()
{
	const uint32_t i = 1;

	return reinterpret_cast<const uint8_t*>(&i)[0] == i;
}

#include "pch.hpp"
#include "BinaryBufferReader.hpp"

BinaryBufferReader::BinaryBufferReader(const std::vector<uint8_t>& obj)
	: Buffer(std::addressof(obj))
{
}

bool BinaryBufferReader::Read(std::string& obj)
{
	uint32_t size = 0;
	if (!Read(size))
		return false;

	obj.resize(size);
	if (!Read(obj.data(), size))
		return false;

	return true;
}

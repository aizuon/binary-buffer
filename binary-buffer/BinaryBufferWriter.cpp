#include "pch.hpp"
#include "BinaryBufferWriter.hpp"

BinaryBufferWriter::BinaryBufferWriter(std::vector<uint8_t>& obj)
	: Buffer(std::addressof(obj)), Offset(static_cast<uint32_t>(obj.size()))
{
}

void BinaryBufferWriter::Write(const std::string& obj)
{
	Write(static_cast<uint32_t>(obj.size()));

	Write(obj.data(), static_cast<uint32_t>(obj.size()));
}

void BinaryBufferWriter::GrowIfNeeded(uint32_t write_length)
{
	const uint32_t final_length = Offset + write_length;
	const bool reserve_needed = Buffer->capacity() < final_length;
	const bool resize_needed = Buffer->size() < final_length;

	if (reserve_needed)
	{
		uint32_t final_capacity = static_cast<uint32_t>(static_cast<float>(final_length) * BUFFER_GROWTH_FACTOR) + 128;
		final_capacity -= final_capacity % 64;
		Buffer->reserve(final_capacity);
	}

	if (resize_needed)
		Buffer->resize(final_length);
}

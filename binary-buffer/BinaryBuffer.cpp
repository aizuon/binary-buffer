#include "pch.hpp"
#include "BinaryBuffer.hpp"

BinaryBuffer::BinaryBuffer(const std::vector<uint8_t>& obj)
	: Buffer(obj), WriteOffset(static_cast<uint32_t>(obj.size()))
{
}

BinaryBuffer::BinaryBuffer(std::vector<uint8_t>&& obj)
	: Buffer(std::move(obj)), WriteOffset(static_cast<uint32_t>(obj.size()))
{
}

BinaryBuffer::BinaryBuffer(const BinaryBuffer& obj)
	: Buffer(obj.Buffer), WriteOffset(obj.WriteOffset), ReadOffset(obj.ReadOffset)
{
}

BinaryBuffer::BinaryBuffer(BinaryBuffer&& obj) noexcept
	: Buffer(std::move(obj.Buffer)), WriteOffset(obj.WriteOffset), ReadOffset(obj.ReadOffset)
{
}

BinaryBuffer& BinaryBuffer::operator=(const BinaryBuffer& obj)
{
	Buffer = obj.Buffer;
	WriteOffset = obj.WriteOffset;
	ReadOffset = obj.ReadOffset;

	return *this;
}

BinaryBuffer& BinaryBuffer::operator=(BinaryBuffer&& obj) noexcept
{
	std::swap(Buffer, obj.Buffer);
	std::swap(WriteOffset, obj.WriteOffset);
	std::swap(ReadOffset, obj.ReadOffset);

	return *this;
}

void BinaryBuffer::Write(const std::string& obj)
{
	Write(static_cast<uint32_t>(obj.size()));

	WriteRaw(obj);
}

void BinaryBuffer::WriteRaw(const std::string& obj)
{
	Write(obj.data(), static_cast<uint32_t>(obj.size()));
}

bool BinaryBuffer::Read(std::string& obj)
{
	uint32_t size = 0;
	if (!Read(size))
		return false;

	obj.resize(size);
	if (!Read(obj.data(), size))
		return false;

	return true;
}

bool BinaryBuffer::operator==(const BinaryBuffer& obj) const
{
	if (WriteOffset != obj.WriteOffset)
		return false;

	if (ReadOffset != obj.ReadOffset)
		return false;

	return Buffer == obj.Buffer;
}

void BinaryBuffer::GrowIfNeeded(uint32_t write_length)
{
	const uint32_t final_length = WriteOffset + write_length;
	const bool reserve_needed = Buffer.capacity() < final_length;
	const bool resize_needed = Buffer.size() < final_length;

	if (reserve_needed)
	{
		uint32_t final_capacility = static_cast<uint32_t>(static_cast<float>(final_length) * BUFFER_GROW_FACTOR) + 128;
		final_capacility -= final_capacility % 64;
		Buffer.reserve(final_capacility);
	}

	if (resize_needed)
		Buffer.resize(final_length);
}

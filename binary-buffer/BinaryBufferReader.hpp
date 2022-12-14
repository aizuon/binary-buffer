#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <type_traits>

#include <boost/endian/conversion.hpp>

#include "Utils.hpp"

class BinaryBufferReader
{
public:
	BinaryBufferReader() = delete;
	BinaryBufferReader(const std::vector<uint8_t>& obj);

	BinaryBufferReader(const BinaryBufferReader& obj) = delete;
	BinaryBufferReader(BinaryBufferReader&& obj) noexcept = delete;
	BinaryBufferReader& operator=(const BinaryBufferReader& obj) = delete;
	BinaryBufferReader& operator=(BinaryBufferReader&& obj) noexcept = delete;

	template <typename T>
	bool Read(T& obj)
	{
		return Read(&obj, 1);
	}

	template <typename T>
	bool Read(std::vector<T>& obj)
	{
		uint32_t size = 0;
		if (!Read(size))
			return false;

		obj.resize(size);
		if (!Read(obj.data(), size))
			return false;

		return true;
	}

	bool Read(std::string& obj);

private:
	const std::vector<uint8_t>* Buffer;
	uint32_t Offset = 0;

	template <typename T>
	bool Read(T* obj, uint32_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		const uint32_t length = count * sizeof(T);

		const uint32_t final_offset = Offset + length;
		if (Buffer->size() < final_offset)
			return false;

		std::memcpy(obj, Buffer->data() + Offset, length);
		if (!Utils::IsLittleEndian)
		{
			for (uint32_t i = 0; i < count; i++)
			{
				boost::endian::endian_reverse_inplace(reinterpret_cast<T&>(obj[i]));
			}
		}
		Offset = final_offset;

		return true;
	}
};

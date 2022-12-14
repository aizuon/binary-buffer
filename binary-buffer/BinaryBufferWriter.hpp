#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <type_traits>

#include <boost/endian/conversion.hpp>

#include "Utils.hpp"

class BinaryBufferWriter
{
public:
	BinaryBufferWriter() = delete;
	BinaryBufferWriter(std::vector<uint8_t>& obj);

	BinaryBufferWriter(const BinaryBufferWriter& obj) = delete;
	BinaryBufferWriter(BinaryBufferWriter&& obj) noexcept = delete;
	BinaryBufferWriter& operator=(const BinaryBufferWriter& obj) = delete;
	BinaryBufferWriter& operator=(BinaryBufferWriter&& obj) noexcept = delete;

	template <typename T>
	void Write(const T& obj)
	{
		Write(&obj, 1);
	}

	template <typename T>
	void Write(const std::vector<T>& obj)
	{
		Write(static_cast<uint32_t>(obj.size()));

		Write(obj.data(), static_cast<uint32_t>(obj.size()));
	}

	void Write(const std::string& obj);

private:
	std::vector<uint8_t>* Buffer;
	uint32_t Offset = 0;

	static constexpr float BUFFER_GROWTH_FACTOR = 1.5f;

	template <typename T>
	void Write(const T* obj, uint32_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		const uint32_t length = count * sizeof(T);
		GrowIfNeeded(length);
		std::memcpy(Buffer->data() + Offset, obj, length);
		if (!Utils::IsLittleEndian)
		{
			for (uint32_t i = 0; i < count; i++)
			{
				boost::endian::endian_reverse_inplace(reinterpret_cast<T&>(Buffer[Offset + i * sizeof(T)]));
			}
		}
		Offset += length;
	}

	void GrowIfNeeded(uint32_t write_length);
};

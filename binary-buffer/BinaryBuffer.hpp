#pragma once
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>
#include <mutex>
#include <type_traits>
#include <boost/endian/conversion.hpp>

#include "Utils.hpp"

class BinaryBuffer
{
public:
	BinaryBuffer() = default;
	BinaryBuffer(const std::vector<uint8_t>& obj);
	BinaryBuffer(std::vector<uint8_t>&& obj);

	BinaryBuffer(const BinaryBuffer& obj);
	BinaryBuffer(BinaryBuffer&& obj) noexcept;
	BinaryBuffer& operator=(const BinaryBuffer& obj);
	BinaryBuffer& operator=(BinaryBuffer&& obj) noexcept;

	const std::vector<uint8_t>& GetBuffer() const
	{
		return Buffer;
	}

	std::vector<uint8_t>& GetWritableBuffer()
	{
		return Buffer;
	}

	uint32_t GetSize() const
	{
		return static_cast<uint32_t>(Buffer.size());
	}

	uint32_t GetWriteOffset() const
	{
		return WriteOffset;
	}

	uint32_t GetReadOffset() const
	{
		return ReadOffset;
	}

	void SetThreadSafety(bool val)
	{
		ThreadSafe = val;
	}

	void GrowTo(uint32_t size)
	{
		assert(size > Buffer.size());

		Buffer.resize(size);
	}

	void Reserve(uint32_t size)
	{
		Buffer.reserve(size);
	}

	template <typename T>
	void Write(const T& obj)
	{
		Write(&obj, 1);
	}

	template <typename T>
	void Write(const std::vector<T>& obj)
	{
		Write(static_cast<uint32_t>(obj.size()));

		WriteRaw(obj);
	}

	template <typename T>
	void WriteRaw(const std::vector<T>& obj)
	{
		Write(obj.data(), static_cast<uint32_t>(obj.size()));
	}

	void Write(const std::string& obj);

	void WriteRaw(const std::string& obj);

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

	bool operator==(const BinaryBuffer& obj) const;

private:
	std::vector<uint8_t> Buffer;
	uint32_t WriteOffset = 0;
	uint32_t ReadOffset = 0;

	bool ThreadSafe = false;
	std::recursive_mutex Mutex;

	static constexpr float BUFFER_GROW_FACTOR = 1.5f;

	template <typename T>
	void Write(const T* obj, uint32_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		std::unique_lock lock(Mutex, std::defer_lock);
		if (ThreadSafe)
			lock.lock();

		const uint32_t length = count * sizeof(T);
		GrowIfNeeded(length);
		std::memcpy(Buffer.data() + WriteOffset, obj, length);
		if (!Utils::IsLittleEndian)
		{
			for (uint32_t i = 0; i < count; i++)
			{
				boost::endian::endian_reverse_inplace(reinterpret_cast<T&>(Buffer[WriteOffset + i * sizeof(T)]));
			}
		}
		WriteOffset += length;
	}

	template <typename T>
	bool Read(T* obj, uint32_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		std::unique_lock lock(Mutex, std::defer_lock);
		if (ThreadSafe)
			lock.lock();

		const uint32_t length = count * sizeof(T);

		const uint32_t final_offset = ReadOffset + length;
		if (Buffer.size() < final_offset)
			return false;

		std::memcpy(obj, Buffer.data() + ReadOffset, length);
		if (!Utils::IsLittleEndian)
		{
			for (uint32_t i = 0; i < count; i++)
			{
				boost::endian::endian_reverse_inplace(reinterpret_cast<T&>(obj[i]));
			}
		}
		ReadOffset = final_offset;

		return true;
	}

	void GrowIfNeeded(uint32_t write_length);
};

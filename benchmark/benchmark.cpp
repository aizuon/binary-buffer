#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <utility>
#include <istream>
#include <boost/timer/timer.hpp>

#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
#include <bitsery/traits/vector.h>
#include <bitsery/traits/string.h>

#include "../binary-buffer/BinaryBuffer.hpp"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <sstream>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

#define SER_LOOP_COUNT 1'000'000
#define LOOP_COUNT 100

std::pair<std::vector<uint8_t>, size_t> bitsery_serialize()
{
	using OutputAdapter = bitsery::OutputBufferAdapter<std::vector<uint8_t>>;

	std::vector<uint8_t> buffer;
	bitsery::Serializer<OutputAdapter> ser(buffer);

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		ser.boolValue(true);
		ser.value1b(static_cast<int8_t>(-3));
		ser.value1b(static_cast<uint8_t>(3));
		ser.value2b(static_cast<int16_t>(-3));
		ser.value2b(static_cast<uint16_t>(3));
		ser.value4b(-3);
		ser.value4b(static_cast<uint32_t>(3));
		ser.value8b(static_cast<int64_t>(-3));
		ser.value8b(static_cast<uint64_t>(3));
		auto res = std::string("foo");
		ser.text1b(res, res.size());
		auto res2 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		ser.container1b(res2, res2.size());
	}

	return { buffer, ser.adapter().writtenBytesCount() };
}

void bitsery_deserialize(const std::vector<uint8_t>& buffer, size_t written_size)
{
	using InputAdapter = bitsery::InputBufferAdapter<std::vector<uint8_t>>;

	bitsery::Deserializer<InputAdapter> des(buffer.begin(), written_size);

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		auto res = false;
		des.boolValue(res);
		auto res2 = static_cast<int8_t>(-3);
		des.value1b(res2);
		auto res3 = static_cast<uint8_t>(3);
		des.value1b(res3);
		auto res4 = static_cast<int16_t>(-3);
		des.value2b(res4);
		auto res5 = static_cast<uint16_t>(3);
		des.value2b(res5);
		auto res6 = -3;
		des.value4b(res6);
		auto res7 = static_cast<uint32_t>(3);
		des.value4b(res7);
		auto res8 = static_cast<int64_t>(-3);
		des.value8b(res8);
		auto res9 = static_cast<uint64_t>(3);
		des.value8b(res9);
		auto res10 = std::string("foo");
		des.text1b(res10, res10.size());
		auto res11 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		des.container1b(res11, res11.size());
	}
}

std::vector<uint8_t> binary_buffer_serialize()
{
	auto ser = BinaryBuffer();

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		ser.Write(true);
		ser.Write(static_cast<int8_t>(-3));
		ser.Write(static_cast<uint8_t>(3));
		ser.Write(static_cast<int16_t>(-3));
		ser.Write(static_cast<uint16_t>(3));
		ser.Write(-3);
		ser.Write(static_cast<uint32_t>(3));
		ser.Write(static_cast<int64_t>(-3));
		ser.Write(static_cast<uint64_t>(3));
		auto res = std::string("foo");
		ser.Write(res);
		auto res2 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		ser.Write(res2);
	}

	return ser.GetBuffer();
}

void binary_buffer_deserialize(const std::vector<uint8_t>& buffer)
{
	auto des = BinaryBuffer(buffer);

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		auto res = false;
		des.Read(res);
		auto res2 = static_cast<int8_t>(-3);
		des.Read(res2);
		auto res3 = static_cast<uint8_t>(3);
		des.Read(res3);
		auto res4 = static_cast<int16_t>(-3);
		des.Read(res4);
		auto res5 = static_cast<uint16_t>(3);
		des.Read(res5);
		auto res6 = -3;
		des.Read(res6);
		auto res7 = static_cast<uint32_t>(3);
		des.Read(res7);
		auto res8 = static_cast<int64_t>(-3);
		des.Read(res8);
		auto res9 = static_cast<uint64_t>(3);
		des.Read(res9);
		auto res10 = std::string("foo");
		des.Read(res10);
		auto res11 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		des.Read(res11);
	}
}

std::string boost_serialize()
{
	std::stringstream input_stream;
	auto ser = boost::archive::binary_oarchive(input_stream, boost::archive::no_header);

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		ser << true;
		ser << static_cast<int8_t>(-3);
		ser << static_cast<uint8_t>(3);
		ser << static_cast<int16_t>(-3);
		ser << static_cast<uint16_t>(3);
		ser << -3;
		ser << static_cast<uint32_t>(3);
		ser << static_cast<int64_t>(-3);
		ser << static_cast<uint64_t>(3);
		auto res = std::string("foo");
		ser << res;
		auto res2 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		ser << res2;
	}

	return input_stream.str();
}

void boost_deserialize(const std::string& buffer)
{
	std::stringstream output_stream(buffer);
	auto des = boost::archive::binary_iarchive(output_stream, boost::archive::no_header);

	for (int i = 0; i < SER_LOOP_COUNT; i++)
	{
		auto res = false;
		des >> res;
		auto res2 = static_cast<int8_t>(-3);
		des >> res2;
		auto res3 = static_cast<uint8_t>(3);
		des >> res3;
		auto res4 = static_cast<int16_t>(-3);
		des >> res4;
		auto res5 = static_cast<uint16_t>(3);
		des >> res5;
		auto res6 = -3;
		des >> res6;
		auto res7 = static_cast<uint32_t>(3);
		des >> res7;
		auto res8 = static_cast<int64_t>(-3);
		des >> res8;
		auto res9 = static_cast<uint64_t>(3);
		des >> res9;
		auto res10 = std::string("foo");
		des >> res10;
		auto res11 = std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 };
		des >> res11;
	}
}

int main()
{
	{
		boost::timer::cpu_timer timer;
		auto [buffer, written_size] = bitsery_serialize();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			auto [buffer, written_size] = bitsery_serialize();
		}
		timer.stop();
		std::cout << "bitsery size: " << buffer.size() << std::endl;
		std::cout << "bitsery serialize: " << timer.format();
		timer = boost::timer::cpu_timer();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			bitsery_deserialize(buffer, written_size);
		}
		bitsery_deserialize(buffer, written_size);
		timer.stop();
		std::cout << "bitsery deserialize: " << timer.format();
	}

	{
		boost::timer::cpu_timer timer;
		auto buffer = binary_buffer_serialize();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			auto buffer = binary_buffer_serialize();
		}
		timer.stop();
		std::cout << "binary_buffer size: " << buffer.size() << std::endl;
		std::cout << "binary_buffer serialize: " << timer.format();
		timer = boost::timer::cpu_timer();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			binary_buffer_deserialize(buffer);
		}
		timer.stop();
		std::cout << "binary_buffer deserialize: " << timer.format();
	}

	{
		boost::timer::cpu_timer timer;
		auto buffer = boost_serialize();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			auto buffer = boost_serialize();
		}
		timer.stop();
		std::cout << "boost size: " << buffer.size() << std::endl;
		std::cout << "boost serialize: " << timer.format();
		timer = boost::timer::cpu_timer();
		for (int i = 0; i < LOOP_COUNT; i++)
		{
			boost_deserialize(buffer);
		}
		timer.stop();
		std::cout << "boost deserialize: " << timer.format();
	}

	return 0;
}

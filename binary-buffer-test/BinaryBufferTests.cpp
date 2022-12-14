#include "pch.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include "../binary-buffer/BinaryBufferWriter.hpp"
#include "../binary-buffer/BinaryBufferReader.hpp"
#include "gtest/gtest.h"

TEST(BinaryBufferTest, PrimitiveReadWrite)
{
	std::vector<uint8_t> buffer;
	BinaryBufferWriter ser(buffer);
	BinaryBufferReader des(buffer);

	bool b_real = true;
	ser.Write(b_real);
	bool b_read = false;
	ASSERT_TRUE(des.Read(b_read));
	EXPECT_EQ(b_real, b_read);

	uint8_t u8 = 3;
	ser.Write(u8);
	uint8_t u8_read = 0;
	ASSERT_TRUE(des.Read(u8_read));
	EXPECT_EQ(u8, u8_read);

	int8_t i8 = -5;
	ser.Write(i8);
	int8_t i8_read = 0;
	ASSERT_TRUE(des.Read(i8_read));
	EXPECT_EQ(i8, i8_read);

	uint16_t u16 = 10000;
	ser.Write(u16);
	uint16_t u16_read = 0;
	ASSERT_TRUE(des.Read(u16_read));
	EXPECT_EQ(u16, u16_read);

	int16_t i16 = -5000;
	ser.Write(i16);
	int16_t i16_read = 0;
	ASSERT_TRUE(des.Read(i16_read));
	EXPECT_EQ(i16, i16_read);

	uint32_t ui32 = 7000000;
	ser.Write(ui32);
	uint32_t ui32_read = 0;
	ASSERT_TRUE(des.Read(ui32_read));
	EXPECT_EQ(ui32, ui32_read);

	int32_t i32 = -3000000;
	ser.Write(i32);
	int32_t i32_read = 0;
	ASSERT_TRUE(des.Read(i32_read));
	EXPECT_EQ(i32, i32_read);

	uint64_t ui64 = 4000000000;
	ser.Write(ui64);
	uint64_t ui64_read = 0;
	ASSERT_TRUE(des.Read(ui64_read));
	EXPECT_EQ(ui64, ui64_read);

	int64_t i64 = -2000000000;
	ser.Write(i64);
	int64_t i64_read = 0;
	ASSERT_TRUE(des.Read(i64_read));
	EXPECT_EQ(i64, i64_read);
}

TEST(BinaryBufferTest, StringReadWrite)
{
	std::vector<uint8_t> buffer;
	BinaryBufferWriter ser(buffer);
	BinaryBufferReader des(buffer);

	const std::string str = "foo";
	ser.Write(str);
	std::string str_read;
	ASSERT_TRUE(des.Read(str_read));
	EXPECT_EQ(str, str_read);
}

TEST(BinaryBufferTest, VectorReadWrite)
{
	std::vector<uint8_t> buffer;
	BinaryBufferWriter ser(buffer);
	BinaryBufferReader des(buffer);

	//std::vector b = { true, false, true, false, true, false, true };
	//ser.Write(b);
	//std::vector<bool> b_read;
	//ASSERT_TRUE(des.Read(b_read));
	//EXPECT_EQ(b, b_read);

	std::vector<uint8_t> u8 = { 3, 5, 7, 9, 11, 55, 75 };
	ser.Write(u8);
	std::vector<uint8_t> u8_read;
	ASSERT_TRUE(des.Read(u8_read));
	EXPECT_EQ(u8, u8_read);

	std::vector<int8_t> i8 = { -6, -14, -32, -44, -65, -77, -99, -102 };
	ser.Write(i8);
	std::vector<int8_t> i8_read;
	ASSERT_TRUE(des.Read(i8_read));
	EXPECT_EQ(i8, i8_read);

	std::vector<uint16_t> u16 = { 10000, 20000, 30000, 40000, 50000 };
	ser.Write(u16);
	std::vector<uint16_t> u16_read;
	ASSERT_TRUE(des.Read(u16_read));
	EXPECT_EQ(u16, u16_read);

	std::vector<int16_t> i16 = { -5000, -6000, -7000, -8000, -9000, -10000 };
	ser.Write(i16);
	std::vector<int16_t> i16_read;
	ASSERT_TRUE(des.Read(i16_read));
	EXPECT_EQ(i16, i16_read);

	std::vector<uint32_t> ui32 = { 7000000, 8000000, 9000000 };
	ser.Write(ui32);
	std::vector<uint32_t> ui32_read;
	ASSERT_TRUE(des.Read(ui32_read));
	EXPECT_EQ(ui32, ui32_read);

	std::vector i32 = { -3000000, -4000000, -5000000 };
	ser.Write(i32);
	std::vector<int32_t> i32_read;
	ASSERT_TRUE(des.Read(i32_read));
	EXPECT_EQ(i32, i32_read);

	std::vector<uint64_t> ui64 = { 4000000000, 5000000000, 6000000000 };
	ser.Write(ui64);
	std::vector<uint64_t> ui64_read;
	ASSERT_TRUE(des.Read(ui64_read));
	EXPECT_EQ(ui64, ui64_read);

	std::vector<int64_t> i64 = { -2000000000, -5000000000, -8000000000 };
	ser.Write(i64);
	std::vector<int64_t> i64_read;
	ASSERT_TRUE(des.Read(i64_read));
	EXPECT_EQ(i64, i64_read);
}

# Binary Buffer

## What is it?

A quite fast and efficient binary serialization library

## Example

```cpp
std::vector<uint8_t> buffer;
auto ser = BinaryBufferWriter(buffer);
auto des = BinaryBufferWriter(buffer);

ser.Write(true);
ser.Write(static_cast<int8_t>(-3));
ser.Write(static_cast<uint8_t>(3));
ser.Write(static_cast<int16_t>(-3));
ser.Write(static_cast<uint16_t>(3));
ser.Write(-3);
ser.Write(static_cast<uint32_t>(3));
ser.Write(static_cast<int64_t>(-3));
ser.Write(static_cast<uint64_t>(3));
ser.Write(std::string("foo"));
ser.Write(std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 });

auto res = false;
des.Read(res);
auto res2 = static_cast<int8_t>(0);
des.Read(res2);
auto res3 = static_cast<uint8_t>(0);
des.Read(res3);
auto res4 = static_cast<int16_t>(0);
des.Read(res4);
auto res5 = static_cast<uint16_t>(0);
des.Read(res5);
auto res6 = 0;
des.Read(res6);
auto res7 = static_cast<uint32_t>(0);
des.Read(res7);
auto res8 = static_cast<int64_t>(0);
des.Read(res8);
auto res9 = static_cast<uint64_t>(0);
des.Read(res9);
auto res10 = std::string();
des.Read(res10);
auto res11 = std::vector<uint8_t>();
des.Read(res11);
```

## Benchmarks

TODO

## TODO

- Custom object serialization extensions
- std::vector<bool> support
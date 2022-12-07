# Binary Buffer

## What is it?

A quite fast and efficient binary serialization library

## Example

```cpp
auto buffer = BinaryBuffer();

buffer.Write(true);
buffer.Write(static_cast<int8_t>(-3));
buffer.Write(static_cast<uint8_t>(3));
buffer.Write(static_cast<int16_t>(-3));
buffer.Write(static_cast<uint16_t>(3));
buffer.Write(-3);
buffer.Write(static_cast<uint32_t>(3));
buffer.Write(static_cast<int64_t>(-3));
buffer.Write(static_cast<uint64_t>(3));
buffer.Write(std::string("foo"));
buffer.Write(std::vector<uint8_t>{ 0x00, 0x01, 0x02, 0x03, 0x04 });

auto res = false;
buffer.Read(res);
auto res2 = static_cast<int8_t>(0);
buffer.Read(res2);
auto res3 = static_cast<uint8_t>(0);
buffer.Read(res3);
auto res4 = static_cast<int16_t>(0);
buffer.Read(res4);
auto res5 = static_cast<uint16_t>(0);
buffer.Read(res5);
auto res6 = 0;
buffer.Read(res6);
auto res7 = static_cast<uint32_t>(0);
buffer.Read(res7);
auto res8 = static_cast<int64_t>(0);
buffer.Read(res8);
auto res9 = static_cast<uint64_t>(0);
buffer.Read(res9);
auto res10 = std::string();
buffer.Read(res10);
auto res11 = std::vector<uint8_t>();
buffer.Read(res11);
```

## Benchmarks

TODO

## TODO

- Custom object serialization extensions
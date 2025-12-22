#pragma once

#include "sock_addr.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <cstddef>
#include <cstdint>

namespace libsocket {

class Message {
public:
    // --- Constructors ---

    /// Creates an empty message ready for writing.
    explicit Message(const SockAddr& address);

    /// Creates a message with existing data (e.g., from a raw socket read).
    Message(const SockAddr& address, std::vector<std::byte> data);

    /// Creates a message by copying raw bytes.
    Message(const SockAddr& address, const void* data, size_t size);

    // --- Write Operations (Serialization) ---

    /// Appends a POD type (int, float, struct) to the buffer.
    template <typename T>
    void write(const T& value);

    /// Appends a raw byte array to the buffer.
    void write(const void* data, size_t size);

    /// Appends a string (prefixed with its length).
    void writeString(const std::string_view& str);

    // --- Read Operations (Deserialization) ---

    /// Reads a POD type from the current cursor position.
    template <typename T>
    T read();

    /// Reads raw bytes into a destination buffer.
    void read(void* dest, size_t size);

    /// Reads a string (reads length first, then characters).
    std::string readString();

    // --- Accessors & Utilities ---

    const SockAddr& getAddr() const;
    const std::vector<std::byte>& getData() const;
    size_t getSize() const;
    
    /// Resets the read cursor to the beginning.
    void resetReadCursor();

    /// Checks if the read cursor has reached the end of the buffer.
    bool isEndOfBuffer() const;

private:
    SockAddr m_addr;
    std::vector<std::byte> m_data;
    mutable size_t m_readCursor = 0;
};


}

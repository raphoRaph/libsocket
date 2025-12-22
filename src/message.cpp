#include "libsocket/message.h"
#include "libsocket/sock_addr.h"

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string_view>
#include <type_traits>

libsocket::Message::Message(const libsocket::SockAddr& address):
    m_addr(address) {}


libsocket::Message::Message(const libsocket::SockAddr& address, std::vector<std::byte> data):
    m_addr(address), m_data(data) {}

libsocket::Message::Message(const libsocket::SockAddr& address, const void *data, size_t size) :
    m_addr(address) {
    std::memcpy(m_data.data(), data, size);
}


template <typename T>
void libsocket::Message::write(const T& value) {
    static_assert(std::is_standard_layout<T>::value && std::is_trivial<T>::value,
                  "Only POD types can be streamed via Message::write<T>");
    const auto *ptr = reinterpret_cast<const std::byte*>(&value);
    m_data.insert(m_data.end(), ptr, ptr + sizeof(T));
}


void libsocket::Message::write(const void *data, size_t size) {
    std::memcpy(m_data.data(), data, size);
}

void libsocket::Message::writeString(const std::string_view& str) {
    std::memcpy(m_data.data(), str.data(), str.size());
}

template <typename T>
T libsocket::Message::read() {
    static_assert(std::is_standard_layout<T>::value && std::is_trivial<T>::value,
                  "Only POD types can be streamed directly via Message::read<T>");
    if (m_readCursor + sizeof(T) > m_data.size()) {
        throw new std::logic_error("Message::read<T> not enough data to read.");
    }
    T value;
    std::memcpy(&value, m_data.data() + m_readCursor, sizeof(T));
    m_readCursor += sizeof(T);
    return value;
}


void libsocket::Message::read(void *dest, size_t size) {
    std::memcpy(dest, m_data.data(), size);
}


std::string libsocket::Message::readString() {
    return std::string(reinterpret_cast<const char*>(m_data.data()), m_data.size());
}


const libsocket::SockAddr& libsocket::Message::getAddr() const {
    return m_addr;
}


const std::vector<std::byte>& libsocket::Message::getData() const {
    return m_data;
}

size_t libsocket::Message::getSize() const {
    return m_data.size();
}


void libsocket::Message::resetReadCursor() {
    m_readCursor = 0;
}

bool libsocket::Message::isEndOfBuffer() const {
    return m_readCursor >= m_data.size();
}

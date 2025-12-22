#pragma once

namespace libsocket {

/**
 * @brief Represents a socket address (IP address).
 * 
 * Currently a simple wrapper around a string representation of an address.
 */
class SockAddr {
public:
	// TODO: This might need better encapsulation or memory management
	// depending on how the pointer is used (ownership vs view).
	const char *m_addr;

	SockAddr() : m_addr(nullptr) {}
	SockAddr(const char* addr) : m_addr(addr) {}
};

}
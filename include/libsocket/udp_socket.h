#pragma once

#include <cstdint>
#include <memory>
#include <optional>

#include "message.h"
#include "sock_addr.h"

namespace libsocket {

/**
 * @brief A wrapper class for UDP sockets.
 * 
 * This class provides a high-level interface for creating, binding, sending, 
 * and receiving messages over UDP. It uses the Pimpl idiom to hide implementation details.
 */
class UDPSocket {
	class Impl;
	std::unique_ptr<Impl> m_impl;

public:
	/**
	 * @brief Default constructor.
	 * 
	 * Creates an unbound UDP socket.
	 */
	UDPSocket();

	/**
	 * @brief Constructs a UDP socket and binds it to a specific port.
	 * 
	 * @param port The local port number to bind to.
	 */
	UDPSocket(uint16_t port);

	/**
	 * @brief Constructs a UDP socket bound to a specific address and port.
	 * 
	 * @param addr The local address to bind to.
	 * @param port The local port number to bind to.
	 */
	UDPSocket(const SockAddr& addr, uint8_t port);

	/**
	 * @brief Destructor.
	 * 
	 * Cleans up the socket resources.
	 */
	~UDPSocket();

	/**
	 * @brief Binds the socket to its configured address and port.
	 * 
	 * If the socket was created with a port/address, this is called automatically? 
	 * (Implementation details would verify this, but standard socket logic implies binding).
	 */
	void bind();

	/**
	 * @brief Sends a message to a destination.
	 * 
	 * @param msg The message to send, which contains the destination address.
	 * @return true if the message was sent successfully, false otherwise.
	 */
	bool sendTo(const Message& msg);

	/**
	 * @brief Receives a message from the socket.
	 * 
	 * @param sender Output parameter that will contain the address of the sender.
	 * @return An std::optional containing the received Message if successful, or std::nullopt if no message was received (or on error).
	 */
	std::optional<Message> recvFrom(const SockAddr& sender);
};

}
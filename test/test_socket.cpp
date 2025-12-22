#include <gtest/gtest.h>

#include <libsocket/udp_socket.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

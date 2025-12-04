add_rules("mode.debug", "mode.release")
add_requires("gtest")

target("libsocket")
	set_kind("binary")
	add_files("src/*.cpp")

target("test")
	set_kind("binary")
	add_files("test/*.cpp")
	add_packages("gtest")

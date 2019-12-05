include_directories("/root/workspace/test_codes/cmake/Hello")
#link_directories("/root/workspace/test_codes/cmake/Hello")
add_library (DemoLib SHARED demo_lib.cxx)
#target_link_libraries (DemoLib Hello)

#add_executable (helloDemo demo.cxx)
#target_link_libraries (helloDemo DemoLib)

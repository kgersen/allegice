add_compile_definitions(NOMINMAX USE32bit=true)

file(GLOB AME_SRC CONFIGURE_DEPENDS
   "*.h"
   "*.cpp"
   "*.res")

add_executable(AME WIN32 ${AME_SRC})
set_property(TARGET AME PROPERTY CXX_STANDARD 14)

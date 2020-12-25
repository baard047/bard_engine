#set( SPDLOG_FMT_EXTERNAL_HO ON CACHE BOOL "Spdlog uses external header-only fmt" )
set( SPDLOG_BUILD_TESTS OFF CACHE BOOL "Do not build spdlog tests" )
set( SPDLOG_BUILD_TESTS_HO OFF CACHE BOOL "Do not build spdlog-header-only tests" )
set( SPDLOG_BUILD_BENCH OFF CACHE BOOL "Do not build spdlog benchmarks" )
set( SPDLOG_BUILD_WARNINGS OFF CACHE BOOL "Do not enable spdlog warnings" )
set( SPDLOG_INSTALL OFF CACHE BOOL "Do not install spdlog" )

add_subdirectory( spdlog )
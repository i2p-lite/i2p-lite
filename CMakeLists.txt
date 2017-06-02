cmake_minimum_required( VERSION 2.8.12 )
cmake_policy( VERSION 2.8.12)

set(EXE i2prouter)

find_package(PkgConfig)
include(FindPackageHandleStandardArgs)
include(GNUInstallDirs)

set(CMAKE_C_FLAGS "-g")

pkg_check_modules(UV libuv)
pkg_check_modules(OPENSSL openssl)

include_directories(${UV_INCLUDEDIR})
include_directories(${OPENSSL_INCLUEDIR})


set(MALLOC_LIBRARY -ljemalloc)


include_directories(include)

# ipc (standalone)
# interface defining inter process communication
file(GLOB LIBI2PIPC_SRC "src/ipc/*.c")
set(IPC_LIB i2pipc)
add_library(${IPC_LIB} ${LIBI2PIPC_SRC})
# i/o (standalone)
# interface defining async network/file io
file(GLOB LIBI2PIO_SRC "src/io/*.c")
set(IO_LIB i2pio)
add_library(${IO_LIB} ${LIBI2PIO_SRC})
# threadpool (standalone)
# interface defining thread pooling
file(GLOB LIBI2PTHREAD_SRC "src/threadpool/*.c")
set(THREAD_LIB i2pthread)
add_library(${THREAD_LIB} ${LIBI2PTHREAD_SRC})
# libuv glue layer (depends on libuv)
# threadpool, ipc and i/o implementation using libuv
file(GLOB LIBI2PUV_SRC "src/libuv/*.c")
set(UVGLUE_LIB i2puv)
add_library(${UVGLUE_LIB} ${LIBI2PUV_SRC})
# crypto (depends on threadpool and ipc)
# interface for threadpooled async i2p cryptography implementation
file(GLOB LIBI2PCRYPTO_SRC "src/crypto/*.c")
set(CRYPTO_LIB i2pcrypto)
add_library(${CRYPTO_LIB} ${LIBI2PCRYPTO_SRC})
# openssl cryptoimpl ( depends on openssl, implements crypto )
# openssl implementation of crypto
file(GLOB LIBOPENSSLCRYPTO_SRC "src/crypto/oepnssl/*.c")
set(CRYPTOIMPL_OPENSSL i2pcryptoimpl-openssl)
add_library(${CRYPTIOIMPL_OPENSSL} ${LIBOPENSSLCRYPTO_SRC})
# librel cryptoimpl ( depends on libressl, implements crypto )
# libressl implementation of crypto
file(GLOB LIBLIBRESSLCRYPTO_SRC "src/crypto/libressl/*c")
set(CRYPTOIMPL_LIBRESSL i2pcryptoimpl-libressl)
add_library(${CRYPTIOIMPL_LIBRESSL} ${LIBLIBRESSLCRYPTO_SRC})
# libnettle cryptoimpl ( depends on libnettle, implements crypto )
file(GLOB LIBNETTELECRYPTO_SRC "src/crypto/nettle/*.c")
set(CRYPTOIMPL_NETTLE i2pcryptoimpl-nettle)
add_library(${CRYPTIOIMPL_NETTLE} ${LIBNETTELECRYPTO_SRC})
# datatypes (standalone)
# i2p data structures
file(GLOB LIBI2PDATATYPES_SRC "src/datatypes/*.c")
# netdb (depends on ipc, datatypes and crypto)
# local netdb i/o
file(GLOB LIBI2PNETDB_SRC "src/netdb/*.c")
# i2np transport (depends on netdb)
# interface defining sending and receiving i2np messages
file(GLOB LIBI2NPTRANSPORT_SRC "src/transport/interface/*.c")
# ntcp transport (depends on i/o and crypto, implements i2np transport )
# ntcp i2np transport implementation
file(GLOB LIBNTCP_SRC "src/transport/ntcp/*.c")
# transport muxer (depends on ipc and i2np transport )
# ipc for transport layer
file(GLOB LIBTRANSPORTMUX_SRC "src/transport/*.c")
# i2np message router ( depends on datatypes, transport muxer and netdb )
# for routing inbound i2np messages to handlers
file(GLOB LIBI2NPROUTER_SRC "src/i2np/router/*.c")
# i2np dispatcher ( depends on transport muxer )
# interface defining outbound message dispatcher
file(GLOB LIBI2NPDISPATCHER_SRC "src/i2np/dispatcher/*.c")
# i2np handler ( depends on i2np dispatcher )
# interface defining i2np message handler
file(GLOB LIBI2NPHANDLER_SRC "src/i2np/handler/*.c")
# i2np context ( depends on ipc, i2np message router and i2np dispatcher )
# ipc for i2np layer
file(GLOB LIBI2NP_SRC "src/i2np/*.c")
# garlic handler (implements i2np handler and i2np dispatcher)
# interface defining handling of garlic messages from tunnels and dispatching garlic messages to tunnels
file(GLOB LIBI2PGARLIC_SRC "src/i2np/garlic/*.c")
# dht ( implements i2np handler and garlic handler )
# i2p dht interface
file(GLOB LIBI2PDHT_SRC "src/dht/*.c")
# floodfill dht ( depends on netdb, datatypes and crypto implements i2p dht )
# i2p dht implementation for floodfill dht
file(GLOB LIBI2PFLOODFILL_SRC "src/dht/floodfill/*.c")
# i2np tunnel handler ( implements i2np handler and i2np dispatcher )
# i2np tunnel message handler
file(GLOB LIBI2NPTUNNEL_SRC "src/i2np/tunnel/*.c")
# netdb profiler ( depends on datatypes and netdb )
# interface defining peer profiler and peer selection for tunnels
file(GLOB LIBI2PPROFOLER_SRC "src/profiler/*.c")
# native profiler ( implements netdb profiler )
# defacto netdb profiler implementation
file(GLOB LIBI2PNATIVEPROFILER_SRC "src/profiler/native/*.c")
# lua profiler ( implements netdb profiler )
# netdb profiler implementation using lua scripts
file(GLOB LIBI2PLUAPROFILER_SRC "src/profiler/lua/*.c")
# mruby profiler ( implements netdb profiler )
# netdb profiler implementation using mruby scripts
file(GLOB LIBI2PRUBYPROFILER_SRC "src/profiler/mruby/*.c")
# i2cp protocol ( implements garlic handler )
# interface defining i2cp message handling
file(GLOB LIBI2PGARLICPROTOCOL_SRC "src/protocol/*.c")
# garlic destination ( depends on netdb profiler, i2cp protocol, datatypes and crypto, implements garlic handler )
# client tunnel builder and base for i2p app tunnels
file(GLOB LIBI2PDESTINATION_SRC "src/garlic/*.c")
# streaming protocol ( depends on crypto and datatypes, implements i2cp protocol )
# tcp/i2p protocol implementation
file(GLOB LIBI2PSTREAMING_SRC "src/protocol/streaming/*.c")
# raw datagram protocol ( implements i2cp protocol )
# i2cp raw datagram implementation
file(GLOB LIBI2PRAW_SRC "src/protocol/raw/*.c")
# signed datagram protocol ( depends on crypto and datatypes, implements i2cp protocol )
# i2cp replyable datagram protocol implemenation
file(GLOB LIBI2PDATAGRAM_SRC "src/protocol/datagram/*.c")
# i2p apptunnel ( depends on garlic destination )
# garlic destination muxer for application tunnels
file(GLOB LIBI2PAPPTUNNEL_SRC "src/apptunnel/*.c")

# i2p router context ( depends on ipc, i2np transports, i2np dispatcher, i2np handler and i2p dht )
# passive i2p router implementation that sits on 1 i2p network
file(GLOB LIBI2PROUTER "src/router/*.c")
# i2p client context ( depends on ipc, i2p router context and garlic destination )
# destination and router context bridge layer
file(GLOB LIBI2PCONTEXT "src/context/*.c")

# i2p router executable (depends on libuv glue layer, crypto, i2p router context and i2p client context )
add_executable(${EXE} "src/i2prouter.c")

set(LIBS ${CORE_LIB} ${UV_LIBRARIES} ${OPENSSL_LIBRARIES} ${MALLOC_LIBRARY})
target_link_libraries(${EXE} ${LIBS})
add_executable(benchmark_crypto "test/bench_crypto.c")
target_link_libraries(benchmark_crypto ${LIBS})

add_executable(test_netdb "test/test_netdb.c")
target_link_libraries(test_netdb ${LIBS})

set(PATH_SEP "/")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__PATH_SEP__='\"${PATH_SEP}\"'")

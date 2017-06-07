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
include_directories(${OPENSSL_INCLUDEDIR})


set(MALLOC_LIBRARY -ljemalloc)


include_directories(include)

set(LIBS "")

# ipc (standalone)
# interface defining inter process communication
file(GLOB LIBI2PIPC_SRC "src/ipc/*.c")
set(IPC_LIB i2p_ipc)
add_library(${IPC_LIB} ${LIBI2PIPC_SRC})
set(LIBS "${LIBS} ${IPC_LIB}")

# i/o (standalone)
# interface defining async network/file io
file(GLOB LIBI2PIO_SRC "src/io/*.c")
set(IO_LIB i2p_io)
add_library(${IO_LIB} ${LIBI2PIO_SRC})
set(LIBS "${LIBS} ${IO_LIB}")

# threadpool (standalone)
# interface defining thread pooling
file(GLOB LIBI2PTHREAD_SRC "src/threadpool/*.c")
set(THREAD_LIB i2p_thread)
add_library(${THREAD_LIB} ${LIBI2PTHREAD_SRC})
set(LIBS "${LIBS} ${THREAD_LIB}")

# misc utilities (standalone)
file(GLOB LIBUTILS_SRC "src/util/*.c")
set(UTIL_LIB i2p_util)
add_library(${UTIL_LIB} ${LIBUTILS_SRC})
set(LIBS "${LIBS} ${UITL_LIB}")

# libuv glue layer (depends on libuv)
# threadpool, ipc and i/o implementation using libuv
file(GLOB LIBI2PUV_SRC "src/libuv/*.c")
set(UVGLUE_LIB i2p_uv)
add_library(${UVGLUE_LIB} ${LIBI2PUV_SRC})
set(LIBS "${LIBS} ${UVGLUE_LIB}")

# crypto (depends on threadpool and ipc)
# interface for threadpooled async i2p cryptography implementation
file(GLOB LIBI2PCRYPTO_SRC "src/crypto/*.c")
set(CRYPTO_LIB i2p_crypto)
add_library(${CRYPTO_LIB} ${LIBI2PCRYPTO_SRC})
set(LIBS "${LIBS} ${CRYPTO_LIB}")

# openssl cryptoimpl ( depends on openssl, implements crypto )
# openssl implementation of crypto
file(GLOB LIBOPENSSLCRYPTO_SRC "src/crypto/oepnssl/*.c")
set(CRYPTOIMPL_OPENSSL i2p_cryptoimpl_openssl)
add_library(${CRYPTOIMPL_OPENSSL} ${LIBOPENSSLCRYPTO_SRC})
set(LIBS "${LIBS} ${CRYPTIOIMPL_OPENSSL}")

# librel cryptoimpl ( depends on libressl, implements crypto )
# libressl implementation of crypto
file(GLOB LIBLIBRESSLCRYPTO_SRC "src/crypto/libressl/*c")
set(CRYPTOIMPL_LIBRESSL i2p_cryptoimpl_libressl)
add_library(${CRYPTOIMPL_LIBRESSL} ${LIBLIBRESSLCRYPTO_SRC})
set(LIBS "${LIBS} ${CRYPTOIMPL_LIBRESSL}")

# libnettle cryptoimpl ( depends on libnettle, implements crypto )
file(GLOB LIBNETTELECRYPTO_SRC "src/crypto/nettle/*.c")
set(CRYPTOIMPL_NETTLE i2p_cryptoimpl_nettle)
add_library(${CRYPTOIMPL_NETTLE} ${LIBNETTELECRYPTO_SRC})
set(LIBS "${LIBS} ${CRYPTOIMPL_NETTLE}")

# datatypes (standalone)
# i2p data structures
file(GLOB LIBI2PDATATYPES_SRC "src/datatypes/*.c")
set(DATA_LIB i2p_data)
add_library(${DATA_LIB} ${LIBI2PDATATYPES_SRC})
set(LIBS "${LIBS} ${DATA_LIB}")

# netdb (depends on ipc, datatypes and crypto)
# local netdb i/o
file(GLOB LIBI2PNETDB_SRC "src/netdb/*.c")
set(NETDB_LIB i2p_netdb)
add_library(${NETDB_LIB} ${LIBI2PNETDB_SRC})
set(LIBS "${LIBS} ${NETDB_LIB}")

# i2np transport (depends on netdb)
# interface defining sending and receiving i2np messages
file(GLOB LIBI2NPTRANSPORT_SRC "src/transport/abstract/*.c")
set(I2NPTRANSPORT_LIB i2np_transport)
add_library(${I2NPTRANSPORT_LIB} ${LIBI2NPTRANSPORT_SRC})
set(LIBS "${LIBS} ${I2NPTRANSPORT_LIB}")

# ntcp transport (depends on i/o and crypto, implements i2np transport )
# ntcp i2np transport implementation
file(GLOB LIBNTCP_SRC "src/transport/ntcp/*.c")
set(TRANSPORT_IMPL_NTCP ntcp)
add_library(${TRANSPORT_IMPL_NTCP} ${LIBNTCP_SRC})
set(LIBS "${LIBS} ${TRANSPORT_IMPL_NTCP}")

# transport muxer (depends on ipc and i2np transport )
# ipc for transport layer
file(GLOB LIBTRANSPORTMUX_SRC "src/transport/*.c")
set(TRANSPORT_LIB i2np_transport_mux)
add_library(${TRANSPORT_LIB} ${LIBTRANSPORTMUX_SRC})
set(LIBS "${LIBS} ${TRANSPORT_LIB}")

# i2np message router ( depends on datatypes, transport muxer and netdb )
# for routing inbound i2np messages to handlers
file(GLOB LIBI2NPROUTER_SRC "src/i2np/router/*.c")
set(I2NPROUTER_LIB i2np_router)
add_library(${I2NPROUTER_LIB} ${LIBI2NPROUTER_SRC})
set(LIBS "${LIBS} ${I2NPROUTER_LIB}")

# i2np dispatcher ( depends on transport muxer )
# interface defining outbound message dispatcher
file(GLOB LIBI2NPDISPATCHER_SRC "src/i2np/dispatcher/*.c")
set(I2NPDISPATCHER_LIB i2np_dispatcher)
add_library(${I2NPDISPATCHER_LIB} ${LIBI2NPDISPATCHER_SRC})
set(LIBS "${LIBS} ${I2NPDISPATCHER_LIB}")

# i2np handler ( depends on i2np dispatcher )
# interface defining i2np message handler
file(GLOB LIBI2NPHANDLER_SRC "src/i2np/handler/*.c")
set(I2NPHANDLER_LIB i2np_handler)
add_library(${I2NPHANDLER_LIB} ${LIBI2NPHANDLER_SRC})
set(LIBS "${LIBS} ${I2NPHANDLER_LIB}")

# i2np context ( depends on ipc, i2np message router and i2np dispatcher )
# ipc for i2np layer
file(GLOB LIBI2NP_SRC "src/i2np/*.c")
set(I2NP_LIB i2np)
add_library(${I2NP_LIB} ${LIBI2NP_SRC})
set(LIBS "${LIBS} ${I2NP_LIB}")

# garlic handler (implements i2np handler and i2np dispatcher)
# interface defining handling of garlic messages from tunnels and dispatching garlic messages to tunnels
file(GLOB LIBI2PGARLIC_SRC "src/i2np/garlic/*.c")
set(GARLIC_LIB i2p_garlic)
add_library(${GARLIC_LIB} ${LIBI2PGARLIC_SRC})
set(LIBS "${LIBS} ${GARLIC_LIB}")

# dht ( implements i2np handler and garlic handler )
# i2p dht interface
file(GLOB LIBI2PDHT_SRC "src/dht/*.c")
set(DHT_LIB i2p_dht)
add_library(${DHT_LIB} ${LIBI2PDHT_SRC})
set(LIBS "${LIBS} ${DHT_LIB}")

# floodfill dht ( depends on netdb, datatypes and crypto implements i2p dht )
# i2p dht implementation for floodfill dht
file(GLOB LIBI2PFLOODFILL_SRC "src/dht/floodfill/*.c")
set(DHTIMPL_FLOODFILL i2p_floodfill)
add_library(${DHTIMPL_FLOODFILL} ${LIBI2PFLOODFILL_SRC})
set(LIBS "${LIBS} ${DHTIMPL_FLOODFILL}")

# i2np tunnel handler ( implements i2np handler and i2np dispatcher )
# i2np tunnel message handler
file(GLOB LIBI2NPTUNNEL_SRC "src/i2np/tunnel/*.c")
set(I2NPTUNNEL_LIB i2np_tunnel)
add_library(${I2NPTUNNEL_LIB} ${LIBI2NPTUNNEL_SRC})
set(LIBS "${LIBS} ${I2NPTUNNEL_LIB}")

# netdb profiler ( depends on datatypes and netdb )
# interface defining peer profiler and peer selection for tunnels
file(GLOB LIBI2PPROFOLER_SRC "src/profiler/*.c")
set(PROFILER_LIB i2p_profiler)
add_library(${PROFILER_LIB} ${LIBI2PPROFOLER_SRC})
set(LIBS "${LIBS} ${PROFILER_LIB}")

# native profiler ( implements netdb profiler )
# default netdb profiler implementation
file(GLOB LIBI2PNATIVEPROFILER_SRC "src/profiler/native/*.c")
set(PROFILER_IMPL_NATIVE i2p_native_profiler)
add_library(${PROFILER_IMPL_NATIVE} ${LIBI2PNATIVEPROFILER_SRC})
set(LIBS "${LIBS} ${PROFILER_IMPL_NATIVE}")

# lua profiler ( implements netdb profiler )
# netdb profiler implementation using lua scripts
file(GLOB LIBI2PLUAPROFILER_SRC "src/profiler/lua/*.c")
set(PROFILER_IMPL_LUA i2p_lua_profiler)
add_library(${PROFILER_IMPL_LUA} ${LIBI2PLUAPROFILER_SRC})
set(LIBS "${LIBS} ${PROFILER_IMPL_LUA}")

# mruby profiler ( implements netdb profiler )
# netdb profiler implementation using mruby scripts
file(GLOB LIBI2PMRUBYPROFILER_SRC "src/profiler/mruby/*.c")
set(PROFILER_IMPL_MRUBY i2p_mruby_profiler)
add_library(${PROFILER_IMPL_MRUBY} ${LIBI2PMRUBYPROFILER_SRC})
set(LIBS "${LIBS} ${PROFILER_IMPL_MRUBY}")

# i2cp protocol ( implements garlic handler )
# interface defining i2cp message handling
file(GLOB LIBI2PGARLICPROTOCOL_SRC "src/protocol/*.c")
set(I2PGARLICPROTO_LIB i2p_garlic_proto)
add_library(${I2PGARLICPROTO_LIB} ${LIBI2PGARLICPROTOCOL_SRC})
set(LIBS "${LIBS} ${I2PGARLICPROTO_LIB}")

# garlic destination ( depends on netdb profiler, i2cp protocol, datatypes and crypto, implements garlic handler )
# client tunnel builder and base for i2p app tunnels
file(GLOB LIBI2PDESTINATION_SRC "src/garlic/*.c")
set(I2PDESTINATION_LIB i2p_garlic_destination)
add_library(${I2PDESTINATION_LIB} ${LIBI2PDESTINATION_SRC})
set(LIBS "${LIBS} ${I2PDESTINATION_LIB}")

# streaming protocol ( depends on crypto and datatypes, implements i2cp protocol )
# tcp/i2p protocol implementation
file(GLOB LIBI2PSTREAMING_SRC "src/protocol/streaming/*.c")
set(I2PSTREAMING_LIB i2p_streaming_proto)
add_library(${I2PSTREAMING_LIB} ${LIBI2PSTREAMING_SRC})
set(LIBS "${LIBS} ${I2PSTREAMING_LIB}")

# raw datagram protocol ( implements i2cp protocol )
# i2cp raw datagram implementation
file(GLOB LIBI2PRAW_SRC "src/protocol/raw/*.c")
set(I2PRAWPROTO_LIB i2p_garlic_proto_raw)
add_library(${I2PRAWPROTO_LIB} ${LIBI2PRAW_SRC})
set(LIBS "${LIBS} ${I2PRAWPROTO_LIB}")

# signed datagram protocol ( depends on crypto and datatypes, implements i2cp protocol )
# i2cp replyable datagram protocol implemenation
file(GLOB LIBI2PDATAGRAM_SRC "src/protocol/datagram/*.c")
set(I2PDATAGRAM_LIB i2p_garlic_proto_dgram)
add_library(${I2PDATAGRAM_LIB} ${LIBI2PDATAGRAM_SRC})
set(LIBS "${LIBS} ${I2PDATAGRAM_LIB}")

# i2p apptunnel ( depends on garlic destination )
# garlic destination muxer for application tunnels
file(GLOB LIBI2PAPPTUNNEL_SRC "src/apptunnel/*.c")
set(I2PAPPTUNNEL_LIB i2p_apptunnel)
add_library(${I2PAPPTUNNEL_LIB} ${LIBI2PAPPTUNNEL_SRC})
set(LIBS "${LIBS} ${I2PAPPTUNNEL_LIB}")

# i2p router context ( depends on ipc, i2np transports, i2np dispatcher, i2np handler and i2p dht )
# passive i2p router implementation that sits on 1 i2p network
file(GLOB LIBI2PROUTER_SRC "src/router/*.c")
set(I2PROUTER_LIB i2p_router)
add_library(${I2PROUTER_LIB} ${LIBI2PROUTER_SRC})
set(LIBS "${LIBS} ${I2PROUTER_LIB}")

# i2p client context ( depends on ipc, i2p router context and garlic destination )
# destination and router context bridge layer
file(GLOB LIBI2PCONTEXT "src/context/*.c")
set(I2PCONTEXT_LIB i2p_context)
add_library(${I2PCONTEXT_LIB} ${LIBI2PCONTEXT_SRC})
set(LIBS "${LIBS} ${I2PCONTEXT_LIB}")

# i2p router executable (depends on libuv glue layer, crypto, i2p router context and i2p client context )
add_executable(${EXE} "src/i2prouter.c")

set(LIBS "${LIBS} ${UV_LIBRARIES} ${OPENSSL_LIBRARIES} ${MALLOC_LIBRARY}")
target_link_libraries(${EXE} ${LIBS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

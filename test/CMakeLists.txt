set(TEST_CRYPTO "test_crypto")

add_executable(${TEST_CRYPTO} src/test_crypto.c)
target_link_libraries(${TEST_CRYPTO} ${LIBS})
add_test(${TEST_CRYPTO} ${TEST_CRYPTO})

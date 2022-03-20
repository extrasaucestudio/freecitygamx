project(freecitygame)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( freecitygame freecitygame freecitygame.cpp )
target_include_directories( freecitygame PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( freecitygame ${CMAKE_SOURCE_DIR}/../ricardian )
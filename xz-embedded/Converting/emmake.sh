em++ -DXZ_USE_CRC64 -DXZ_DEC_ANY_CHECK -c unxz.cpp
emcc -DXZ_USE_CRC64 -DXZ_DEC_ANY_CHECK -c xz_crc32.c xz_crc64.c xz_dec_lzma2.c xz_dec_stream.c
em++ -O2 unxz.o xz_crc32.o xz_crc64.o xz_dec_lzma2.o xz_dec_stream.o --bind bind.cpp -o unxz.js

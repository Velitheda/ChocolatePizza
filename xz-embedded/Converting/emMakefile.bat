em++ --bind -c bind.cpp
em++ -DXZ_USE_CRC64 -DXZ_DEC_ANY_CHECK -c unxz.cpp
emcc -DXZ_USE_CRC64 -DXZ_DEC_ANY_CHECK -c xz_crc32.c xz_crc64.c xz_dec_lzma2.c xz_dec_stream.c
em++ bind.o unxz.o xz_crc32.o xz_crc64.o xz_dec_lzma2.o xz_dec_stream.o -o unxz.js
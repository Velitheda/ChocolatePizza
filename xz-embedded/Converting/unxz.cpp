#include <string>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "xz.h"


std::string unxz(const std::string& compressed ){
	
	struct xz_buf b;
	struct xz_dec* s;
	enum xz_ret ret;	
	const char *msg;
	uint8_t out[BUFSIZ];
	std::string uncompressed;


	xz_crc32_init();
#ifdef XZ_USE_CRC64
	xz_crc64_init();
#endif

	s = xz_dec_init(XZ_DYNALLOC, 1 << 26);
	if (s == NULL) {
		msg = "Memory allocation failed";
		goto error;
	}

	b.in = (const uint8_t*) compressed.c_str();
	b.in_pos = 0;
	b.in_size = compressed.length();
	b.out = out;
	b.out_pos = 0;
	b.out_size = BUFSIZ;

	for (int i = 0; i < 16; i++) {
		printf("%02x ", b.in[i]);
	}
	printf("\n");

	while (b.in_pos != b.in_size) {

		ret = xz_dec_run(s, &b);

        printf("Output % d\n", (int) b.in_pos);
		uncompressed.append((const char*) out, b.out_pos);
		b.out_pos = 0;
	

		if (ret == XZ_OK)
			continue;


#ifdef XZ_DEC_ANY_CHECK
		if (ret == XZ_UNSUPPORTED_CHECK) {
			fputs(": ", stderr);
			fputs("Unsupported check; not verifying "
					"file integrity\n", stderr);
			continue;
		}
#endif

		switch (ret) {
		case XZ_STREAM_END:
	                return uncompressed;

		case XZ_MEM_ERROR:
			msg = "Memory allocation failed\n";
			goto error;

		case XZ_MEMLIMIT_ERROR:
			msg = "Memory usage limit reached\n";
			goto error;

		case XZ_FORMAT_ERROR:
			msg = "Not a .xz file\n";
			goto error;

		case XZ_OPTIONS_ERROR:
			msg = "Unsupported options in the .xz headers\n";
			goto error;

		case XZ_DATA_ERROR:
		case XZ_BUF_ERROR:
			msg = "File is corrupt\n";
			goto error;

		default:
			msg = "Bug!\n";
			goto error;
		}
	}

error:
	xz_dec_end(s);
	fputs(": ", stderr);
	fputs(msg, stderr);

	uncompressed.clear();
	return uncompressed;	
}




/*
int main(int argc, char* argv[]){
    static char buffer[1000000];

	FILE* f=fopen("1984.txt.xz", "rb");
	if (!f) {
		printf("Error\n");
		return 1;
	}
    size_t size=fread(buffer, 1, sizeof(buffer), f);
    printf("Read %d bytes\n", (int) size);

    std::string s;
    s.append(buffer, size);

    std::string o = unxz(s);
    printf("Length=%d\n, %s\n", (int) o.length(), o.c_str());

    return 0;
}*/
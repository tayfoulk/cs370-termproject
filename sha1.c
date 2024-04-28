#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sha1.h"

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

void sha1(const char *message, uint32_t hash[5]) {
    uint32_t h0, h1, h2, h3, h4;
    uint32_t a, b, c, d, e, f, k, temp;
    uint32_t w[80];
    size_t message_len = strlen(message);

    // Initialize hash values
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;

    // Pre-processing
    size_t new_len = ((((message_len + 8) / 64) + 1) * 64);
    uint8_t *msg = calloc(new_len + 64, 1);
    memcpy(msg, message, message_len);
    msg[message_len] = 0x80;
    uint64_t bits_len = 8 * message_len;
    memcpy(msg + new_len, &bits_len, 8);

    // Process the message in successive 512-bit chunks
    for (int i = 0; i < new_len; i += 64) {
        uint32_t *chunk = (uint32_t *)(msg + i);
        
        // Break chunk into 16 words
        for (int j = 0; j < 16; j++) {
            w[j] = chunk[j];
        }
        
        // Extend the sixteen 32-bit words into eighty 32-bit words
        for (int j = 16; j < 80; j++) {
            w[j] = LEFTROTATE((w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16]), 1);
        }

        // Initialize hash value for this chunk
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        // Main loop
        for (int j = 0; j < 80; j++) {
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            temp = LEFTROTATE(a, 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = LEFTROTATE(b, 30);
            b = a;
            a = temp;
        }

        // Add this chunk's hash to result so far
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    free(msg);

    // Produce the final hash value
    hash[0] = h0;
    hash[1] = h1;
    hash[2] = h2;
    hash[3] = h3;
    hash[4] = h4;
}

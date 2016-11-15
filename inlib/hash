// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifndef inlib_hash
#define inlib_hash

namespace inlib {

    inline unsigned int hash(const void* txt, int ntxt)
    {
        //From TString::Hash() v5-24-00b
        // Calculates hash index from any char string.
        // Based on precalculated table of 256 specially selected numbers.
        // These numbers are selected in such a way, that for string
        // length == 4 (integer number) the hash is unambigous, i.e.
        // from hash value we can recalculate input (no degeneration).
        //
        // The quality of hash method is good enough, that
        // "random" numbers made as R = Hash(1), Hash(2), ...Hash(N)
        // tested by <R>, <R*R>, <Ri*Ri+1> gives the same result
        // as for libc rand().
        //
        // For string:  i = hash(cstring,ncstring);
        // For int:     i = hash(&intword,sizeof(int));
        // For pointer: i = hash(&pointer,sizeof(void*));
        //
        //              V.Perev
        static const unsigned int utab[] = {
            0xdd367647, 0x9caf993f, 0x3f3cc5ff, 0xfde25082
            , 0x4c764b21, 0x89affca7, 0x5431965c, 0xce22eeec
            , 0xc61ab4dc, 0x59cc93bd, 0xed3107e3, 0x0b0a287a
            , 0x4712475a, 0xce4a4c71, 0x352c8403, 0x94cb3cee
            , 0xc3ac509b, 0x09f827a2, 0xce02e37e, 0x7b20bbba
            , 0x76adcedc, 0x18c52663, 0x19f74103, 0x6f30e47b
            , 0x132ea5a1, 0xfdd279e0, 0xa3d57d00, 0xcff9cb40
            , 0x9617f384, 0x6411acfa, 0xff908678, 0x5c796b2c
            , 0x4471b62d, 0xd38e3275, 0xdb57912d, 0x26bf953f
            , 0xfc41b2a5, 0xe64bcebd, 0x190b7839, 0x7e8e6a56
            , 0x9ca22311, 0xef28aa60, 0xe6b9208e, 0xd257fb65
            , 0x45781c2c, 0x9a558ac3, 0x2743e74d, 0x839417a8
            , 0x06b54d5d, 0x1a82bcb4, 0x06e97a66, 0x70abdd03
            , 0xd163f30d, 0x222ed322, 0x777bfeda, 0xab7a2e83
            , 0x8494e0cf, 0x2dca2d4f, 0x78f94278, 0x33f04a09
            , 0x402b6452, 0x0cd8b709, 0xdb72a39e, 0x170e00a2
            , 0x26354faa, 0x80e57453, 0xcfe8d4e1, 0x19e45254
            , 0x04c291c3, 0xeb503738, 0x425af3bc, 0x67836f2a
            , 0xfac22add, 0xfafc2b8c, 0x59b8c2a0, 0x03e806f9
            , 0xcb4938b9, 0xccc942af, 0xcee3ae2e, 0xfbe748fa
            , 0xb223a075, 0x85c49b5d, 0xe4576ac9, 0x0fbd46e2
            , 0xb49f9cf5, 0xf3e1e86a, 0x7d7927fb, 0x711afe12
            , 0xbf61c346, 0x157c9956, 0x86b6b046, 0x2e402146
            , 0xb2a57d8a, 0x0d064bb1, 0x30ce390c, 0x3a3e1eb1
            , 0xbe7f6f8f, 0xd8e30f87, 0x5be2813c, 0x73a3a901
            , 0xa3aaf967, 0x59ff092c, 0x1705c798, 0xf610dd66
            , 0xb17da91e, 0x8e59534e, 0x2211ea5b, 0xa804ba03
            , 0xd890efbb, 0xb8b48110, 0xff390068, 0xc8c325b4
            , 0xf7289c07, 0x787e104f, 0x3d0df3d0, 0x3526796d
            , 0x10548055, 0x1d59a42b, 0xed1cc5a3, 0xdd45372a
            , 0x31c50d57, 0x65757cb7, 0x3cfb85be, 0xa329910d
            , 0x6ad8ce39, 0xa2de44de, 0x0dd32432, 0xd4a5b617
            , 0x8f3107fc, 0x96485175, 0x7f94d4f3, 0x35097634
            , 0xdb3ca782, 0x2c0290b8, 0x2045300b, 0xe0f5d15a
            , 0x0e8cbffa, 0xaa1cc38a, 0x84008d6f, 0xe9a9e794
            , 0x5c602c25, 0xfa3658fa, 0x98d9d82b, 0x3f1497e7
            , 0x84b6f031, 0xe381eff9, 0xfc7ae252, 0xb239e05d
            , 0xe3723d1f, 0xcc3bda82, 0xe21b1ad3, 0x9104f7c8
            , 0x4bb2dfcd, 0x4d14a8bc, 0x6ba7f28c, 0x8f89886c
            , 0xad44c97e, 0xb30fd975, 0x633cdab1, 0xf6c2d514
            , 0x067a49d2, 0xdc461ad9, 0xebaf9f3f, 0x8dc6cac3
            , 0x7a060f16, 0xbab063ad, 0xf42e25e6, 0x60724ca6
            , 0xc7245c2e, 0x4e48ea3c, 0x9f89a609, 0xa1c49890
            , 0x4bb7f116, 0xd722865c, 0xa8ee3995, 0x0ee070b1
            , 0xd9bffcc2, 0xe55b64f9, 0x25507a5a, 0xc7a3e2b5
            , 0x5f395f7e, 0xe7957652, 0x7381ba6a, 0xde3d21f1
            , 0xdf1708dd, 0xad0c9d0c, 0x00cbc9e5, 0x1160e833
            , 0x6779582c, 0x29d5d393, 0x3f11d7d7, 0x826a6b9b
            , 0xe73ff12f, 0x8bad3d86, 0xee41d3e5, 0x7f0c8917
            , 0x8089ef24, 0x90c5cb28, 0x2f7f8e6b, 0x6966418a
            , 0x345453fb, 0x7a2f8a68, 0xf198593d, 0xc079a532
            , 0xc1971e81, 0x1ab74e26, 0x329ef347, 0x7423d3d0
            , 0x942c510b, 0x7f6c6382, 0x14ae6acc, 0x64b59da7
            , 0x2356fa47, 0xb6749d9c, 0x499de1bb, 0x92ffd191
            , 0xe8f2fb75, 0x848dc913, 0x3e8727d3, 0x1dcffe61
            , 0xb6e45245, 0x49055738, 0x827a6b55, 0xb4788887
            , 0x7e680125, 0xd19ce7ed, 0x6b4b8e30, 0xa8cadea2
            , 0x216035d8, 0x1c63bc3c, 0xe1299056, 0x1ad3dff4
            , 0x0aefd13c, 0x0e7b921c, 0xca0173c6, 0x9995782d
            , 0xcccfd494, 0xd4b0ac88, 0x53d552b1, 0x630dae8b
            , 0xa8332dad, 0x7139d9a2, 0x5d76f2c4, 0x7a4f8f1e
            , 0x8d1aef97, 0xd1cf285d, 0xc8239153, 0xce2608a9
            , 0x7b562475, 0xe4b4bc83, 0xf3db0c3a, 0x70a65e48
            , 0x6016b302, 0xdebd5046, 0x707e786a, 0x6f10200c
        };
        static const unsigned int msk[] = {
            0x11111111, 0x33333333, 0x77777777, 0xffffffff
        };
        const unsigned char* uc = (const unsigned char*) txt;
        unsigned int uu = 0;
        union {
            unsigned int u;
            unsigned short s[2];
        } u;
        u.u = 0;
        int i, idx;

        for (i = 0; i < ntxt; i++) {
            idx = (uc[i] ^ i) & 255;
            uu  = (uu << 1) ^ (utab[idx] & msk[i & 3]);

            if ((i & 3) == 3) u.u ^= uu;
        }

        if (i & 3) u.u ^= uu;

        u.u *= 1879048201;      // prime number
        u.s[0] += u.s[1];
        u.u *= 1979048191;      // prime number
        u.s[1] ^= u.s[0];
        u.u *= 2079048197;      // prime number
        return u.u;
    }

}

#endif

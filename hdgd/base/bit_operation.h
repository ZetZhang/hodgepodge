#ifndef __HDGD_BIT_OPERATION_H__
#define __HDGD_BIT_OPERATION_H__

// FIXME

//static const uint8_t _HDGD_U8B[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
//static const uint16_t _HDGD_U16B[] = { 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };
//static const uint32_t _HDGD_U32B[] = { 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608 };
//static const uint64_t _HDGD_U64B[] = { 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648 };

#define _HDGD_BIT(X) ( 1 << X )
//#define _HDGD_DIX(X) (  )

#define _HDGD_SETU8_LOWBYTE_T(X) ( X |= 0X0F  )
#define _HDGD_SETU16_LOWBYTE_T(X) ( X |= 0X00FF  )
#define _HDGD_SETU32_LOWBYTE_T(X) ( X |= 0X0000FFFF  )
#define _HDGD_SETU64_LOWBYTE_T(X) ( X |= 0X00000000FFFFFFFF  )

#define _HDGD_SETU8_LOWBYTE_F(X) ( X &= 0xF0  )
#define _HDGD_SETU16_LOWBYTE_F(X) ( X &= 0xFF00  )
#define _HDGD_SETU32_LOWBYTE_F(X) ( X &= 0xFFFF0000  )
#define _HDGD_SETU64_LOWBYTE_F(X) ( X &= 0xFFFFFFFF00000000  )

#define _HDGD_SETU8_HIGHBYTE_T(X) ( X |= 0xF0  )
#define _HDGD_SETU16_HIGHBYTE_T(X) ( X |= 0xFF00  )
#define _HDGD_SETU32_HIGHBYTE_T(X) ( X |= 0xFFFF0000  )
#define _HDGD_SETU64_HIGHBYTE_T(X) ( X |= 0xFFFFFFFF00000000  )

#define _HDGD_SETU8_HIGHBYTE_F(X) ( X &= 0X0F  )
#define _HDGD_SETU16_HIGHBYTE_F(X) ( X &= 0X00FF  )
#define _HDGD_SETU32_HIGHBYTE_F(X) ( X &= 0X0000FFFF  )
#define _HDGD_SETU64_HIGHBYTE_F(X) ( X &= 0X00000000FFFFFFFF  )

//#define __HDGD_U8_SET_BIT(X, BIT) ( X |= (1 << BIT) )

#define _HDGD_SET_BIT_T(X, B) ( X |= static_cast<uint8_t>(B) )
#define _HDGD_SET_BIT_F(X, B) ( X &= static_cast<uint8_t>(~B) )
#define _HDGD_GET_BIT_STAT(X, B) ( X & B )
//#define __HDGD_SET_BIT_STAT(X, BIT, Y) (X != (Y << BIT))

// 反转位
#define _HDGD_SET8_BITFLIP(X, B) ( X ^= B )
#define _HDGD_BIT16_BITFLIP(X, B) ( X ^= B )
#define _HDGD_BIT32_BITFLIP(X, B) ( X ^= B )
#define _HDGD_BIT64_BITFLIP(X, B) ( X ^= B )

// 有条件设位(要改的值，位数，条件)
#define _HDGD_U8_COND_SET_BIT(X, M, F) ( X = static_cast<uint8_t>((X & ~M) | (-F & M) ))
#define _HDGD_U16_COND_SET_BIT(X, M, F) ( X = static_cast<uint16_t>((X & ~M) | (-F & M) ))
#define _HDGD_U32_COND_SET_BIT(X, M, F) ( X = static_cast<uint32_t((X & ~M) | (-F & M) ))
#define _HDGD_U64_COND_SET_BIT(X, M, F) ( X = static_cast<uint64_t>((X & ~M) | (-F & M) ))

#define __unimplemented() do { } while (0)
#define __parameter_unused() void
#define __unused_var(x) do { if (x) {  }; } while (0)

#endif

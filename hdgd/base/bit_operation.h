#ifndef __HDGD_BIT_OPERATION_H__
#define __HDGD_BIT_OPERATION_H__

#define __HDGD_U8_SET_LOW_BYTE(X) ( X |= 0X0F )
#define __HDGD_U8_SET_HIGH_BYTE(X) ( X |= 0XF0 )
#define __HDGD_U8_SET_BIT(X, BIT) ( X |= (1 << BIT) )

#define __HDGD_U8_RESET_LOW_BYTE(X) ( X &= 0XF0 )
#define __HDGD_U8_RESET_HIGH_BYTE(X) ( X &= 0X0F )
#define __HDGD_U8_RESET_ON(X) ( X &= 0XFF )
#define __HDGD_U8_RESET_OFF(X) ( X |= 0X00 )


#define __HDGD_RESET_N_BIT(X, BIT) ( X &= ~(1 << BIT) )

#define __HDGD_SET_BIT(X, BIT, M) ( X = M & (1 << BIT) )

#define __HDGD_SET_BIT_STAT(X, BIT) ( X |= (1 << BIT) )
#define __HDGD_GET_BIT_STAT(X, BIT) ( X & (1 << BIT) )
//#define __HDGD_SET_BIT_STAT(X, BIT, Y) (X != (Y << BIT))

// 反转位
#define __HDGD_BIT_FLIP(x, BIT) ( x ^= (1 << BIT) )
// 有条件设位
#define __HDGD_U8_COND_SET(X, M, F) ( X = static_cast<uint8_t>((X & ~M) | (-F & M)) )
#define __HDGD_U16_COND_SET(X, M, F) ( X = static_cast<uint16_t>((X & ~M) | (-F & M)) )
#define __HDGD_U32_COND_SET(X, M, F) ( X = static_cast<uint32_t>((X & ~M) | (-F & M)) )
#define __HDGD_U64_COND_SET(X, M, F) ( X = static_cast<uint64_t>((X & ~M) | (-F & M)) )

#define __unimplemented() do { } while (0)
#define __parameter_unused() void

#endif

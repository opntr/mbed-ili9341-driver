#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifndef GPIO_ResetBits
#define GPIO_ResetBits(X, Y)
#endif

#ifndef GPIO_SetBits
#define GPIO_SetBits(X, Y)
#endif

EXTERN_C void delay_ms(long delay);

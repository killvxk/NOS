// Coprocessor.h - ARM architecture coprocessors.

#ifndef __ARCH_ARM_COPROCESSOR_H__
#define __ARCH_ARM_COPROCESSOR_H__

#include <cstdint>

#define READ_WRITE_REG(cp, crn, crm, op1, op2) \
	inline uint32_t Read(void) \
	{ \
		uint32_t x; \
		\
		asm volatile ("mrc " cp ", " op1 ", %0, " crn ", " crm ", " op2 : "=r"(x)); \
		return(x); \
	} \
	\
	inline void Write(uint32_t x) \
	{ \
		asm volatile ("mcr " cp ", " op1 ", %0, " crn ", " crm ", " op2 : : "r"(x)); \
	} \
	\
	inline void Set(uint32_t x) \
	{ \
		Write(Read() | x); \
	} \
	\
	inline void Unset(uint32_t x) \
	{ \
		Write(Read() & ~x); \
	}

namespace Kernel
{
	namespace Coprocessor
	{
		namespace MIDR
		{
			READ_WRITE_REG("p15", "c0", "c0", "0", "0")
		}

		namespace SCTLR
		{
			enum Flags : uint32_t
			{
				FLAG_MMU_EN     = 0x00000001,
				FLAG_ALIGN_EN   = 0x00000002,
				FLAG_CACHE_EN   = 0x00000004,
				FLAG_BARRIER_EN = 0x00000020,
				FLAG_BIG_ENDIAN = 0x00000080,
				FLAG_SWAP_EN    = 0x00000400,
				FLAG_BRANCH_EN  = 0x00000800,
				FLAG_ICACHE_EN  = 0x00001000,
				FLAG_VEC_HIGH   = 0x00002000,
				FLAG_ROBIN      = 0x00004000,
				FLAG_HWACCESS   = 0x00020000,
				FLAG_WNOEXEC    = 0x00080000,
				FLAG_UWNOEXEC   = 0x00100000,
				FLAG_FAST_IRQ   = 0x00200000,
				FLAG_UNALIGNED  = 0x00400000,
				FLAG_VECTORS_EN = 0x01000000,
				FLAG_EXC_BIG    = 0x02000000,
				FLAG_NM_FIQ     = 0x08000000,
				FLAG_TEX_REMAP  = 0x10000000,
				FLAG_ACCESS     = 0x20000000,
				FLAG_EXC_THUMB  = 0x40000000
			};

			READ_WRITE_REG("p15", "c1", "c0", "0", "0")
		}
	}
}

#undef READ_WRITE_REG

#endif
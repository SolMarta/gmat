#ifndef __GMAT_INCLUDE__
#define __GMAT_INCLUDE__

#ifdef GMAT_EXPORTS

#ifdef __cplusplus
#define GMAT_API extern "C" __declspec(dllexport)
#else
#define GMAT_API extern __declspec(dllexport)
#endif

#else

#ifdef __cplusplus
#define GMAT_API extern "C" __declspec(dllimport)
#else
#define GMAT_API extern __declspec(dllimport)
#endif

#endif

typedef enum {
	gmat_success,
	gmat_invalid_argument,
	gmat_internal_error,
	gmat_cuda_error,
} gmat_error_t;

typedef struct {
	size_t height;
	size_t width;
	int device;
} gmat_frame;

#if (defined __cplusplus) && (!(defined GMAT_EXPORTS))

class gmat;
class gmatc;

#include <complex>

struct gmatc_e {
	float real, imag;

	inline gmatc_e(float real = 0.0f, float imag = 0.0f)
		: real(real), imag(imag)
	{}

	operator std::complex<float>()
	{
		return std::complex<float>(real, imag);
	}
};

# else

typedef struct {
	float real, imag;
} gmatc_e;

typedef struct {
	float * data;
	gmat_frame frame;
} gmat;

typedef struct {
	gmatc_e * data;
	gmat_frame frame;
} gmatc;

#endif

GMAT_API	gmat_error_t gmat_create			(gmat * mat, size_t height, size_t width, int device);
GMAT_API	gmat_error_t gmat_create_identity	(gmat * mat, size_t size, int device);
GMAT_API	gmat_error_t gmat_destroy			(const gmat * mat);
GMAT_API	gmat_error_t gmat_get_size			(const gmat * mat, size_t * size);
GMAT_API	gmat_error_t gmat_copy_to			(const gmat * mat, void * dst);
GMAT_API	gmat_error_t gmat_copy_from			(gmat * mat, const void * src);
GMAT_API	gmat_error_t gmat_copy				(gmat * res, const gmat * mat);
GMAT_API	gmat_error_t gmat_add				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_add_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_sub				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_sub_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_sub_float_r		(gmat * res, const float val0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_mul				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_mul_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_div				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_div_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_div_float_r		(gmat * res, const float val0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_max				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_max_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_min				(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_min_float			(gmat * res, const gmat * mat0, const float val1);
GMAT_API	gmat_error_t gmat_product			(gmat * res, const gmat * mat0, const gmat * mat1);
GMAT_API	gmat_error_t gmat_transpose			(gmat * res, const gmat * mat);

GMAT_API	gmat_error_t gmatc_create			(gmatc * mat, size_t height, size_t width, int device);
GMAT_API	gmat_error_t gmatc_create_identity	(gmatc * mat, size_t size, int device);
GMAT_API	gmat_error_t gmatc_destroy			(const gmatc * mat);
GMAT_API	gmat_error_t gmatc_get_size			(const gmatc * mat, size_t * size);
GMAT_API	gmat_error_t gmatc_copy_to			(const gmatc * mat, void * dst);
GMAT_API	gmat_error_t gmatc_copy_from		(gmatc * mat, const void * src);
GMAT_API	gmat_error_t gmatc_copy				(gmatc * res, const gmatc * mat);
GMAT_API	gmat_error_t gmatc_add				(gmatc * res, const gmatc * mat0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_add_gmatc_e		(gmatc * res, const gmatc * mat0, const gmatc_e val1);
GMAT_API	gmat_error_t gmatc_sub				(gmatc * res, const gmatc * mat0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_sub_gmatc_e		(gmatc * res, const gmatc * mat0, const gmatc_e val1);
GMAT_API	gmat_error_t gmatc_sub_gmatc_e_r	(gmatc * res, const gmatc_e val0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_mul				(gmatc * res, const gmatc * mat0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_mul_gmatc_e		(gmatc * res, const gmatc * mat0, const gmatc_e val1);
GMAT_API	gmat_error_t gmatc_div				(gmatc * res, const gmatc * mat0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_div_gmatc_e		(gmatc * res, const gmatc * mat0, const gmatc_e val1);
GMAT_API	gmat_error_t gmatc_div_gmatc_e_r	(gmatc * res, const gmatc_e val0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_product			(gmatc * res, const gmatc * mat0, const gmatc * mat1);
GMAT_API	gmat_error_t gmatc_transpose		(gmatc * res, const gmatc * mat);
GMAT_API	gmat_error_t gmatc_conjugate		(gmatc * res, const gmatc * mat);

#if (defined __cplusplus) && (!(defined GMAT_EXPORTS))

#include <string>
#include <iostream>
#include <initializer_list>

#define GMAT_EXC(name) case name: return #name
struct gmat_exception
{
	gmat_error_t error;

	inline gmat_exception(gmat_error_t error)
		: error(error)
	{}

	inline std::string what() const noexcept
	{
		switch (error)
		{
			GMAT_EXC(gmat_success);
			GMAT_EXC(gmat_invalid_argument);
			GMAT_EXC(gmat_internal_error);
			GMAT_EXC(gmat_cuda_error);
		}
		return "";
	}
};
#undef GMAT_EXC

#define CHECK_EXC(exc) if((exc) != gmat_success) throw gmat_exception(exc);

#include "gmat.inl"
#include "gmatc.inl"

#undef CHECK_EXC

#endif

#endif
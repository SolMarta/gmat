#include "stdafx.h"
#include "gmat.h"

GMAT_API gmat_error_t gmat_create(gmat * mat, size_t height, size_t width, int device)
{
	CHECK_NULL(mat);
	CHECK_CSET(device);
	
	mat->frame.height = height;
	mat->frame.width = width;
	mat->frame.device = device;

	CHECK_CUDA(cudaMalloc(&(mat->data), sizeof(float) * height * width), gmat_destroy(mat));
	
	return gmat_success;
}

GMAT_API gmat_error_t gmat_destroy(const gmat * mat)
{
	if (mat == NULL)
		return gmat_success;
	
	if (cudaSetDevice(mat->frame.device) != cudaSuccess)
		return gmat_success;
	
	cudaFree(mat->data);
	ZeroMemory((void *)mat, sizeof(gmat));

	return gmat_success;
}

GMAT_API gmat_error_t gmat_get_size(const gmat * mat, size_t * size)
{
	CHECK_NULL(mat);
	*size = mat->frame.height * mat->frame.width * sizeof(float);

	return gmat_success;
}

GMAT_API gmat_error_t gmat_copy_to(const gmat * mat, void * dst)
{
	CHECK_NULL(mat);
	CHECK_NULL(dst);
	CHECK_CSET(mat->frame.device);

	size_t size;
	gmat_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpy(dst, mat->data, size, cudaMemcpyDeviceToHost), {});

	return gmat_success;
}

GMAT_API gmat_error_t gmat_copy_from(gmat * mat, const void * src)
{
	CHECK_NULL(mat);
	CHECK_NULL(src);
	CHECK_CSET(mat->frame.device);

	size_t size;
	gmat_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpy(mat->data, src, size, cudaMemcpyHostToDevice), {});

	return gmat_success;
}

GMAT_API gmat_error_t gmat_copy(gmat * res, const gmat * mat)
{
	CHECK_NULL(res);
	CHECK_NULL(mat);
	CHECK_CSET(res->frame.device);
	
	CHECK_SIZE(mat, res);

	size_t size;
	gmat_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpyPeer(res->data, res->frame.device, mat->data, mat->frame.device, size), {});

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_create(gmatc * mat, size_t height, size_t width, int device)
{
	CHECK_NULL(mat);
	CHECK_CSET(device);

	mat->frame.height = height;
	mat->frame.width = width;
	mat->frame.device = device;

	CHECK_CUDA(cudaMalloc(&(mat->data), sizeof(gmatc_e) * height * width), gmatc_destroy(mat));

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_destroy(const gmatc * mat)
{
	if (mat == NULL)
		return gmat_success;

	if (cudaSetDevice(mat->frame.device) != cudaSuccess)
		return gmat_success;

	cudaFree(mat->data);
	ZeroMemory((void *)mat, sizeof(gmatc));

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_get_size(const gmatc * mat, size_t * size)
{
	CHECK_NULL(mat);
	*size = mat->frame.height * mat->frame.width * sizeof(gmatc_e);

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_copy_to(const gmatc * mat, void * dst)
{
	CHECK_NULL(mat);
	CHECK_NULL(dst);
	CHECK_CSET(mat->frame.device);

	size_t size;
	gmatc_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpy(dst, mat->data, size, cudaMemcpyDeviceToHost), {});

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_copy_from(gmatc * mat, const void * src)
{
	CHECK_NULL(mat);
	CHECK_NULL(src);
	CHECK_CSET(mat->frame.device);

	size_t size;
	gmatc_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpy(mat->data, src, size, cudaMemcpyHostToDevice), {});

	return gmat_success;
}

GMAT_API gmat_error_t gmatc_copy(gmatc * res, const gmatc * mat)
{
	CHECK_NULL(res);
	CHECK_NULL(mat);
	CHECK_CSET(res->frame.device);

	CHECK_SIZE(mat, res);

	size_t size;
	gmatc_get_size(mat, &size);

	CHECK_CUDA(cudaMemcpyPeer(res->data, res->frame.device, mat->data, mat->frame.device, size), {});

	return gmat_success;
}


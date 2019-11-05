#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stack> 
#include "Cell.h"
#include <vector>
#include <cmath>    
#include <limits.h>
#include <chrono>

#ifdef __APPLE__
#include <sys/time.h>
#include <OpenCL/cl.h>
#else
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

#include <Windows.h>

/* FILETIME of Jan 1 1970 00:00:00. */
static const unsigned __int64 epoch = ((unsigned __int64)116444736000000000ULL);

int gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif

using namespace std;

//  Constants
extern const int ARRAY_SIZE;
extern int array_size;


// Helper class for timing calculations
class CTiming
{
public:
	CTiming() {}
	~CTiming() {}

	void Start() { gettimeofday(&tvBegin, NULL); }
	void End() { gettimeofday(&tvEnd, NULL); }
	bool Diff(int& seconds, int& useconds)
	{
		long int diff = (tvEnd.tv_usec + 1000000 * tvEnd.tv_sec) -
			(tvBegin.tv_usec + 1000000 * tvBegin.tv_sec);
		seconds = diff / 1000000;
		useconds = diff % 1000000;
		return (diff < 0) ? true : false;
	}

private:
	struct timeval tvBegin, tvEnd, tvDiff;

};

bool CheckOpenCLError(cl_int errNum, const char* errMsg);
cl_context CreateContext();
cl_command_queue CreateCommandQueue(cl_context context, cl_device_id* device);
cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName);
bool CreateMemObjects(cl_context context, cl_mem memObjects[3], float* a, float* b);
void Cleanup(cl_context context, cl_command_queue commandQueue, cl_program program, cl_kernel kernel, cl_mem memObjects[3]);
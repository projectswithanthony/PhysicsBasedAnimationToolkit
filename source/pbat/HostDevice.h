#ifndef PBAT_HOST_DEVICE_H
#define PBAT_HOST_DEVICE_H

#ifdef PBAT_GPU_SOURCE
    #define PBAT_HOST   __host__
    #define PBAT_DEVICE __device__
#else
    #define PBAT_HOST
    #define PBAT_DEVICE
#endif

#define PBAT_HOST_DEVICE PBAT_HOST PBAT_DEVICE

#endif // PBAT_HOST_DEVICE_H
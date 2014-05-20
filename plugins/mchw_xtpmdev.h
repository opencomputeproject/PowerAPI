#ifndef MCHW_XTPMDEV_H 
#define MCHW_XTPMDEV_H 

#include "mchw.h"

#ifdef __cplusplus
extern "C" {
#endif

int mchw_xtpmdev_open(mchw_dev_t *dev, char *initstr);
int mchw_xtpmdev_close(mchw_dev_t *dev);
int mchw_xtpmdev_read(mchw_dev_t dev, unsigned int arraysize,
	mchw_read_type_t type[], float reading[], unsigned long long *timestamp);
int mchw_xtpmdev_write(mchw_dev_t dev, unsigned int arraysize,
	mchw_write_type_t type[], float reading[], unsigned long long *timestamp);
int mchw_xtpmdev_time(mchw_dev_t dev, unsigned long long *time);

#ifdef __cplusplus
}
#endif

#endif

#ifndef LOGDEFS_H
#define LOGDEFS_H
#include <stdio.h>
#ifdef DEBUG
	#define LOGD(fmt, args...) do{printf("%s (%4d) DEBUG: ", __FILE__, __LINE__);printf(fmt, ##args);printf("\n");}while(0) 
	#define LOGI(fmt, args...) do{printf("%s (%4d) INFO: ", __FILE__, __LINE__);printf(fmt, ##args);printf("\n");}while(0) 
	#define LOGW(fmt, args...) do{printf("%s (%4d) WARN: ", __FILE__, __LINE__);printf(fmt, ##args);printf("\n");}while(0) 
	#define LOGE(fmt, args...) do{printf("%s (%4d) ERROR: ", __FILE__, __LINE__);printf(fmt, ##args);printf("\n");}while(0) 
#else
	#define LOGI(fmt, args...) 
	#define LOGD(fmt, args...) 
	#define LOGW(fmt, args...) 
	#define LOGE(fmt, args...) do{printf("%s (%4d) ERROR: ", __FILE__, __LINE__);printf(fmt, ##args);printf("\n");}while(0) 
#endif
#endif

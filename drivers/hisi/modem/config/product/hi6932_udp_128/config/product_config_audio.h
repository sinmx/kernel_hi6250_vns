/* MD5: 937875ecc89b70194494202071a00324*/
#if !defined(__PRODUCT_CONFIG_AUDIO_H__)
#define __PRODUCT_CONFIG_AUDIO_H__

#ifndef TENSILICA_BUILDS_HIFI
#define TENSILICA_BUILDS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux 
#endif 

#ifndef TENSILICA_TOOLS_HIFI
#define TENSILICA_TOOLS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RE-2014.5-linux 
#endif 

#ifndef FEATURE_HIFI
#define FEATURE_HIFI FEATURE_OFF 
#endif 

#ifndef FEATURE_HIFI_USE_ICC
#define FEATURE_HIFI_USE_ICC FEATURE_OFF 
#endif 

#ifndef FEATURE_MBB_MODULE_AUDIO
#define FEATURE_MBB_MODULE_AUDIO FEATURE_OFF 
#endif 

#ifndef FEATURE_VOICE_UP
#define FEATURE_VOICE_UP FEATURE_OFF 
#endif 

#ifndef FEATURE_DTMF
#define FEATURE_DTMF FEATURE_ON 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 

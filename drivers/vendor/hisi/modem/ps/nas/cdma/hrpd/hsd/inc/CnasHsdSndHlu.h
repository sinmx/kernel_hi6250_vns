/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndHlu.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年12月10日
  最近修改   :
  功能描述   : CnasHsdSndHlu.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HSD_SND_HLU_H__
#define __CNAS_HSD_SND_HLU_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_VOID CNAS_HSD_SndHluStartReq(VOS_VOID);
extern VOS_VOID CNAS_HSD_SndHluPowerOffReq(VOS_VOID);

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasHsdSndHlu.h */


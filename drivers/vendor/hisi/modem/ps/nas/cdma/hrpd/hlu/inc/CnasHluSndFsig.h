/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluSndFsig.h
  版 本 号   : 初稿
  作    者   : y00213
  生成日期   : 2014年12月17日
  最近修改   :
  功能描述   : CnasHluSndFsig.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月17日
    作    者   : y00213
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_HLU_FSIG_H__
#define __CNAS_HLU_FSIG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasHluCtx.h"
#include "CnasHluComm.h"
#include "CnasCcb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

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
VOS_VOID CNAS_HLU_SendLocNotification
(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo,
    VOS_BOOL                            bIsHandOff,
    CNAS_HLU_LOC_VALUE_STRU            *pstHandOffLocVal
);


VOS_VOID CNAS_HLU_SendLocComplete
(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
);

VOS_VOID CNAS_HLU_SendStrgBlobNotification
(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
);

VOS_VOID CNAS_HLU_SendStrgBlobComplete
(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
);


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

#endif /* end of CnasHluCtx.h */


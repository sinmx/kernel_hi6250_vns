/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScCtx.h
  版 本 号   : 初稿
  作    者   : w00184875
  生成日期   : 2012年04月19日
  最近修改   :
  功能描述   : ScCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SCCTX_H__
#define __SCCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ScCommCtx.h"
#include "ScComm.h"
#include "ScFactory.h"
#include "ScApSec.h"

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

/*****************************************************************************
 函 数 名  : SC_CTX_InitFacGlobalVar
 功能描述  : 初始化SC产线操作的全局变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  SC_CTX_InitFacGlobalVar( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacAuthStatus
 功能描述  : 获取SC产线鉴权状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC_AUTH_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
extern SC_AUTH_STATUS_ENUM_UINT8  SC_CTX_GetFacAuthStatus( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacAuthStatus
 功能描述  : 设置SC产线鉴权状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID  SC_CTX_SetFacAuthStatus( SC_AUTH_STATUS_ENUM_UINT8 enScAuthStatus );

/*****************************************************************************
 函 数 名  : SC_CTX_GetIdentifyStartFlg
 功能描述  : 获取发起产线鉴权流程标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
                VOS_TRUE:   已发起产线鉴权
                VOS_FALSE:  未发起产线鉴权
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  SC_CTX_GetIdentifyStartFlg( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_SetIdentifyStartFlg
 功能描述  : 设置发起产线鉴权流程标志
 输入参数  : VOS_UINT8 ucIdentifyStartFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  SC_CTX_SetIdentifyStartFlg( VOS_UINT8 ucIdentifyStartFlg );

/*****************************************************************************
 函 数 名  : SC_CTX_GetFacRandDataAddr
 功能描述  : 获取SC产线鉴权时随机数的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC产线产线鉴权时随机数的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月19日
    作    者   : w00184875
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT8*  SC_CTX_GetFacRandDataAddr( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecInitStateAddr
 功能描述  : 获取AP Security双备份文件初始化状态地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回双备份文件初始化状态地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月30日
    作    者   : h59254
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32*  SC_CTX_GetApSecInitStateAddr(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecItemBaseAddr
 功能描述  : 获取AP Security双备份文件内容在内存中的起始地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回AP Security双备份文件内容在内存中的起始地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月30日
    作    者   : h59254
    修改内容   : 新生成函数
*****************************************************************************/
extern SC_APSEC_ITEM_STRU*  SC_CTX_GetApSecItemBaseAddr(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_CTX_GetSecATkeyFlg
 功能描述  : 返回安全AT key的标志位
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
                VOS_TRUE    : 当前已经设置安全AT key
                VOS_FALSE   : 当前未设置安全AT key
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT8 SC_CTX_GetSecATkeyFlg( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_SetSecATkeyFlg
 功能描述  : 设置安全AT key的标志位
 输入参数  : VOS_UINT8 ucSecATkeyFlg   - 安全AT key的标志位
                 VOS_TRUE    : 当前已经设置安全AT key
                 VOS_FALSE   : 当前未设置安全AT key
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_VOID SC_CTX_SetSecATkeyFlg( VOS_UINT8 ucSecATkeyFlg );

/*****************************************************************************
 函 数 名  : SC_CTX_GetSecATkeyAddr
 功能描述  : 返回安全AT key的首地址
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8* -- 安全AT key的首地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
extern VOS_UINT8* SC_CTX_GetSecATkeyAddr( VOS_VOID );

/*****************************************************************************
 函 数 名  : SC_CTX_GetApSecSeqID
 功能描述  : 返回SeqID
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8  -- SeqID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 SC_CTX_GetApSecSeqID(VOS_VOID);

/*****************************************************************************
 函 数 名  : SC_CTX_SetApSecSeqID
 功能描述  : 设置SeqID
 输入参数  : VOS_UINT8 ucSeqID   - SeqID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月2日
    作    者   : 李紫剑/00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SC_CTX_SetApSecSeqID(VOS_UINT8 ucSeqID);


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

#endif

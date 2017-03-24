/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUMain.h
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
******************************************************************************/

#ifndef _NASEMMPUBUMAIN_H
#define _NASEMMPUBUMAIN_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "LmmLcsInterface.h"
#endif



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_EMM_STA_STRU        g_astEmmStaTbl[];
extern  VOS_UINT32              g_ulSizeof_g_astEmmStaTbl;
extern  LRRC_NAS_AC_CLASS_STRU   gstRrcNasAc;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
VOS_VOID    NAS_EMM_MtSetUeId(          NAS_EMM_MSG_STRU   *pMsg );
VOS_VOID    NAS_EMM_MtSetMobilInfo(     NAS_EMM_MSG_STRU   *pMsg );

extern VOS_VOID*  LRRC_LNAS_GetMmInfo( LRRC_LNAS_INFO_TYPE_ENUM_UINT32  enInfoType );

extern VOS_VOID NAS_EMM_ReadAccClassMask( VOS_VOID );
/* leixiantiao 00258641 降低圈复杂度 2014-7-30 begin */
extern VOS_UINT32 NAS_LMM_GetLteGutiInfo
(
    NAS_LMM_INFO_STRU             *pstLmmInfo,
    const NAS_LMM_UEID_STRU             *pstMmUeId
);
/* leixiantiao 00258641 降低圈复杂度 2014-7-30 end */


extern LRRC_NAS_UEID_STRU                       gstRrcNasUeId;
/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/

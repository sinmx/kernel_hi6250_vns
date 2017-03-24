#ifndef _DHCPV4S_TYPE_H_
#define _DHCPV4S_TYPE_H_


typedef struct tagDhcpsEnableSwitch
{
    ULONG ulDhcpServerSwitch;
} DHCPS_ENABLE_SWITCH_S;

typedef struct tagDhcpsIpinuseMsg
{
    MSG_HDR_S stMsgHdr;
    USHORT usMsgType;           /* 消息类型 */
    UCHAR  ucResult;          /* 查询结果*/
    UCHAR  ucScId;
    ULONG  ulIpNum;          /* IP数*/
}DHCPS_IPINUSE_MSG_S;

typedef enum tagDHCPS_MSGTYPE_E
{
    DHCPS_IPNUM_REQ,

}DHCPS_MSGTYPE_E;

/*DHCP Server租约的状态*/
typedef enum
{
    DHCPS_STATE_IDEL            = 0,        /*空闲*/
    DHCPS_STATE_REQUESTIP  = 1,       /*向USM申请IP地址*/
    DHCPS_STATE_OFFERED      = 2,       /*向对端发送了OFFER*/
    DHCPS_STATE_COMMITED   = 3,       /*租约的稳定状态*/
    /* Added start by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
    DHCPS_STATE_RELAY      = 4,       /*角色为SGW，PMIP接入的场景下，DHCP的RELAY状态*/
    /* Added end by ZhangYang  z00142225 at 2008-12-29 UGWV900R001C001 for 地址分配功能 */
    DHCPS_STATE_MAX
}DHCPS_LEASESTATE_E;

/*DHCP Server的状态机处理的消息*/
typedef enum
{
    DHCPS_MSG_RECIVE_DISCOVER             = 0,      /*收到客户端的Discover消息*/
    DHCPS_MSG_RECIVE_REQUEST               = 1,     /*收到客户端的Request消息*/
    DHCPS_MSG_RECIVE_DECLINE                = 2,     /*收到客户端的Decline消息*/
    DHCPS_MSG_RECIVE_RELEASE                = 3,     /*收到客户端的Release消息*/
    DHCPS_MSG_RECIVE_INFORM                 = 4,     /*收到客户端的InForm消息*/
    DHCPS_MSG_USM_ADDRESS_SUCCESS     = 5,    /*收到USM的地址分配成功消息*/
    DHCPS_MSG_USM_ADDRESS_FAILURE      = 6,    /*收到USM的地址分配失败消息*/
    DHCPS_MSG_USM_DEACTIVE                   = 7,   /*收到USM的用户去活消息*/
    DHCPS_MSG_TIMER                                 = 8,   /*收到定时器超时消息*/
    DHCPS_MSG_RELAY_SERVER_NAK    =9, /*relay 态收到server 返回的nak消息*/
    DHCPS_MSG_MAX
}DHCPS_LEASEMSG_E;


typedef struct tagDHCPS_PRE_RESULT_S
{
    DHCPS_ANALYZEDPACKET_S  *pstAnalyzedPacket;
    DHCPS_LEASE_S * pstLease;

    ULONG                       ulPdpIndex;
    ULONG                       ulIpAddress;
    
    UCHAR                       ucMsgType;              /*消息类型*/
    UCHAR                       ucReserved[3];         /*保留字段*/
} DHCPS_PRE_RESULT_S;

typedef struct tagDHCPS_SEND_UDP_PARA
{
    UCHAR* pucMsg;
    
    ULONG ulDestIP;   
    ULONG   ulMsgLen;

    ULONG  ulSrcIP;
    ULONG   ulPdpIndex;
    
    USHORT usDestPort;
    UCHAR  ucRev[1];
    UCHAR  ucMsgType;

} DHCPS_SEND_UDP_PARA_S;


/* Added start by ZhangYang  z00142225 at 2009-01-05 UGWV900R001C001 for 地址分配功能 */
typedef struct
{
	/*lint -e553*/
    #if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
	/*lint +e553*/



    UCHAR Recur:3;

    UCHAR CRKSs:5;

    UCHAR Ver:3;

    UCHAR Flags:5;

    USHORT usProType;

    ULONG ulKey;

    ULONG ulSeqNum;

    #else

    UCHAR CRKSs:5;

    UCHAR Recur:3;

    UCHAR Flags:5;

    UCHAR Ver:3;

    USHORT usProType;

    ULONG ulKey;

    ULONG ulSeqNum;

    #endif


}GRE_HDR_S;  /* GRE包头定义 */


typedef struct tagDHCPS_BUILD_OPTION_PARA
{
    UCHAR *pucBuf;  
    UCHAR *pucPosition;
    UCHAR *pucMsg;
    
    USHORT usFreeLen;
    USHORT usMessageType;
} DHCPS_BUILD_OPTION_PARA_S;

typedef struct tagDHCPS_STATE_RET
{
    ULONG  ulResult;
    ULONG  ulNewState;
    ULONG  ulMessageType; 
} DHCPS_STATE_RET;

/*状态机回调函数*/
typedef ULONG (*PF_DHCPS_FSM)(DHCPS_PRE_RESULT_S *,DHCPS_STATE_RET *);

/*状态机节点类型*/
typedef struct tagDHCPS_STATE_MACHINE_NODE
{
    ULONG *pFuncFail;
    ULONG *pFuncTimerOut;
    PF_DHCPS_FSM pFuncStateMachine[DHCPS_MSG_MAX];
    
    ULONG ulTimerStartCount;
    ULONG ulTimerStartFailCount;
    ULONG ulTimerOutCount;
    ULONG ulTimerStopCount;
    ULONG ulTimerStopFailCount;
    ULONG ulTimerOutLength;
    ULONG ulTimerOutCause;
    ULONG ulTimerOutMsg;    /*如果该状态超时，应该输入的处理消息，一般都是去活处理*/
    ULONG ulTimerType;       /*0指状态机定时器，1指租约定时器*/
    ULONG ulStateMsgFailCount;
    ULONG  StateChangeOKCount[DHCPS_MSG_MAX ][DHCPS_STATE_MAX ];/*正确的状态转换基于消息类型和新状态统计*/
    ULONG  MsgChangeERRCount[DHCPS_MSG_MAX ];/*错误的状态转换基于消息类型统计*/
    ULONG  MsgNOChangeCount[DHCPS_MSG_MAX ];
    ULONG  MsgSysERRCount[DHCPS_MSG_MAX ];
    ULONG  StateChangeUNKNOWCount[DHCPS_MSG_MAX ];
    ULONG  ErrMsgCount[DHCPS_MSG_MAX ];
} DHCPS_STATE_MACHINE_NODE;

/*状态机返回结果*/
 typedef enum
 {
     DHCPS_STATE_CHANGE_OK    = 0,                     /*状态迁移成功*/
     DHCPS_STATE_CHANGE_ERR  = 1,                         /*状态迁移失败*/
     DHCPS_STATE_NO_CHANGE    = 2,                           /*状态没有发生改变*/
     DHCPS_STATE_SYSTEM_ERR   = 3,                         /*系统错误的时候直接跳出状态机*/
     DHCPS_STATE_CHANGE_END,
 } DHCPS_STATE_MACHINE_RESULT_TYPE;

typedef enum
{
    DHCPS_RECEIVE_USM = 0, 
    DHCPS_RECEIVE_DPE,
    DHCPS_SEND_USM_APPLY,
    DHCPS_SEND_USM_RELEASE,
    DHCPS_SEND_MSG_OFFER,  
    DHCPS_SEND_MSG_ACK,
    DHCPS_SEND_MSG_NAK,
    DHCPS_SEND_MSG_TOTAL,
    DHCPS_SEND_MSG_SUCC,
    DHCPS_STATISC_END
} DHCPS_STATISC_E;

typedef struct tagDHCPS_STATE_MESSAGE_NODE
{
    ULONG  ulRightStateEvent;
    ULONG  ulStateChange[DHCPS_MSG_MAX];
    ULONG  StateMessageOKCount[DHCPS_MSG_MAX ];
    ULONG  StateMessageERRCount[DHCPS_MSG_MAX ];
    ULONG  StateMessageUNKNOWCount[DHCPS_MSG_MAX ];
    ULONG  StateFuncOKCount;
    ULONG  StateFuncERRCount;
} DHCPS_STATE_MESSAGE_NODE;

/*状态机一次最大的循环次数*/  
#define DHCPS_FSM_MAX_STEP      10 

/*分支统计调试信息*/
#define DHCPS_MAX_FAILURE_COUNTER         1000

#define DHCPS_InternalBranchCounter(index)              \
    {                                                                            \
        (g_aulDHCPSDbgCnt[(index)])++;                        \
    }                                                                            \

typedef enum{
    DHCPS_INTERNAL_BRANCH_000,
    DHCPS_INTERNAL_BRANCH_001,
    DHCPS_INTERNAL_BRANCH_002,
    DHCPS_INTERNAL_BRANCH_003,
    DHCPS_INTERNAL_BRANCH_004,
    DHCPS_INTERNAL_BRANCH_005,
    DHCPS_INTERNAL_BRANCH_006,
    DHCPS_INTERNAL_BRANCH_007,
    DHCPS_INTERNAL_BRANCH_008,
    DHCPS_INTERNAL_BRANCH_009,
    DHCPS_INTERNAL_BRANCH_010,
    DHCPS_INTERNAL_BRANCH_011,
    DHCPS_INTERNAL_BRANCH_012,
    DHCPS_INTERNAL_BRANCH_013,
    DHCPS_INTERNAL_BRANCH_014,
    DHCPS_INTERNAL_BRANCH_015,
    DHCPS_INTERNAL_BRANCH_016,
    DHCPS_INTERNAL_BRANCH_017,
    DHCPS_INTERNAL_BRANCH_018,
    DHCPS_INTERNAL_BRANCH_019,
    DHCPS_INTERNAL_BRANCH_020,
    DHCPS_INTERNAL_BRANCH_021,
    DHCPS_INTERNAL_BRANCH_022,
    DHCPS_INTERNAL_BRANCH_023,
    DHCPS_INTERNAL_BRANCH_024,
    DHCPS_INTERNAL_BRANCH_025,
    DHCPS_INTERNAL_BRANCH_026,
    DHCPS_INTERNAL_BRANCH_027,
    DHCPS_INTERNAL_BRANCH_028,
    DHCPS_INTERNAL_BRANCH_029,
    DHCPS_INTERNAL_BRANCH_030,
    DHCPS_INTERNAL_BRANCH_031,
    DHCPS_INTERNAL_BRANCH_032,
    DHCPS_INTERNAL_BRANCH_033,
    DHCPS_INTERNAL_BRANCH_034,
    DHCPS_INTERNAL_BRANCH_035,
    DHCPS_INTERNAL_BRANCH_036,
    DHCPS_INTERNAL_BRANCH_037,
    DHCPS_INTERNAL_BRANCH_038,
    DHCPS_INTERNAL_BRANCH_039,
    DHCPS_INTERNAL_BRANCH_040,
    DHCPS_INTERNAL_BRANCH_041,
    DHCPS_INTERNAL_BRANCH_042,
    DHCPS_INTERNAL_BRANCH_043,
    DHCPS_INTERNAL_BRANCH_044,
    DHCPS_INTERNAL_BRANCH_045,
    DHCPS_INTERNAL_BRANCH_046,
    DHCPS_INTERNAL_BRANCH_047,
    DHCPS_INTERNAL_BRANCH_048,
    DHCPS_INTERNAL_BRANCH_049,
    DHCPS_INTERNAL_BRANCH_050,
    DHCPS_INTERNAL_BRANCH_051,
    DHCPS_INTERNAL_BRANCH_052,
    DHCPS_INTERNAL_BRANCH_053,
    DHCPS_INTERNAL_BRANCH_054,
    DHCPS_INTERNAL_BRANCH_055,
    DHCPS_INTERNAL_BRANCH_056,
    DHCPS_INTERNAL_BRANCH_057,
    DHCPS_INTERNAL_BRANCH_058,
    DHCPS_INTERNAL_BRANCH_059,
    DHCPS_INTERNAL_BRANCH_060,
    DHCPS_INTERNAL_BRANCH_061,
    DHCPS_INTERNAL_BRANCH_062,
    DHCPS_INTERNAL_BRANCH_063,
    DHCPS_INTERNAL_BRANCH_064,
    DHCPS_INTERNAL_BRANCH_065,
    DHCPS_INTERNAL_BRANCH_066,
    DHCPS_INTERNAL_BRANCH_067,
    DHCPS_INTERNAL_BRANCH_068,
    DHCPS_INTERNAL_BRANCH_069,
    DHCPS_INTERNAL_BRANCH_070,
    DHCPS_INTERNAL_BRANCH_071,
    DHCPS_INTERNAL_BRANCH_072,
    DHCPS_INTERNAL_BRANCH_073,
    DHCPS_INTERNAL_BRANCH_074,
    DHCPS_INTERNAL_BRANCH_075,
    DHCPS_INTERNAL_BRANCH_076,
    DHCPS_INTERNAL_BRANCH_077,
    DHCPS_INTERNAL_BRANCH_078,
    DHCPS_INTERNAL_BRANCH_079,
    DHCPS_INTERNAL_BRANCH_080,
    DHCPS_INTERNAL_BRANCH_081,
    DHCPS_INTERNAL_BRANCH_082,
    DHCPS_INTERNAL_BRANCH_083,
    DHCPS_INTERNAL_BRANCH_084,
    DHCPS_INTERNAL_BRANCH_085,
    DHCPS_INTERNAL_BRANCH_086,
    DHCPS_INTERNAL_BRANCH_087,
    DHCPS_INTERNAL_BRANCH_088,
    DHCPS_INTERNAL_BRANCH_089,
    DHCPS_INTERNAL_BRANCH_090,
    DHCPS_INTERNAL_BRANCH_091,
    DHCPS_INTERNAL_BRANCH_092,
    DHCPS_INTERNAL_BRANCH_093,
    DHCPS_INTERNAL_BRANCH_094,
    DHCPS_INTERNAL_BRANCH_095,
    DHCPS_INTERNAL_BRANCH_096,
    DHCPS_INTERNAL_BRANCH_097,
    DHCPS_INTERNAL_BRANCH_098,
    DHCPS_INTERNAL_BRANCH_099,
    DHCPS_INTERNAL_BRANCH_100,
    DHCPS_INTERNAL_BRANCH_101,
    DHCPS_INTERNAL_BRANCH_102,
    DHCPS_INTERNAL_BRANCH_103,
    DHCPS_INTERNAL_BRANCH_104,
    DHCPS_INTERNAL_BRANCH_105,
    DHCPS_INTERNAL_BRANCH_106,
    DHCPS_INTERNAL_BRANCH_107,
    DHCPS_INTERNAL_BRANCH_108,
    DHCPS_INTERNAL_BRANCH_109,
    DHCPS_INTERNAL_BRANCH_110,
    DHCPS_INTERNAL_BRANCH_111,
    DHCPS_INTERNAL_BRANCH_112,
    DHCPS_INTERNAL_BRANCH_113,
    DHCPS_INTERNAL_BRANCH_114,
    DHCPS_INTERNAL_BRANCH_115,
    DHCPS_INTERNAL_BRANCH_116,
    DHCPS_INTERNAL_BRANCH_117,
    DHCPS_INTERNAL_BRANCH_118,
    DHCPS_INTERNAL_BRANCH_119,
    DHCPS_INTERNAL_BRANCH_120,
    DHCPS_INTERNAL_BRANCH_121,
    DHCPS_INTERNAL_BRANCH_122,
    DHCPS_INTERNAL_BRANCH_123,
    DHCPS_INTERNAL_BRANCH_124,
    DHCPS_INTERNAL_BRANCH_125,
    DHCPS_INTERNAL_BRANCH_126,
    DHCPS_INTERNAL_BRANCH_127,
    DHCPS_INTERNAL_BRANCH_128,
    DHCPS_INTERNAL_BRANCH_129,
    DHCPS_INTERNAL_BRANCH_130,
    DHCPS_INTERNAL_BRANCH_131,
    DHCPS_INTERNAL_BRANCH_132,
    DHCPS_INTERNAL_BRANCH_133,
    DHCPS_INTERNAL_BRANCH_134,
    DHCPS_INTERNAL_BRANCH_135,
    DHCPS_INTERNAL_BRANCH_136,
    DHCPS_INTERNAL_BRANCH_137,
    DHCPS_INTERNAL_BRANCH_138,
    DHCPS_INTERNAL_BRANCH_139,
    DHCPS_INTERNAL_BRANCH_140,
    DHCPS_INTERNAL_BRANCH_141,
    DHCPS_INTERNAL_BRANCH_142,
    DHCPS_INTERNAL_BRANCH_143,
    DHCPS_INTERNAL_BRANCH_144,
    DHCPS_INTERNAL_BRANCH_145,
    DHCPS_INTERNAL_BRANCH_146,
    DHCPS_INTERNAL_BRANCH_147,
    DHCPS_INTERNAL_BRANCH_148,
    DHCPS_INTERNAL_BRANCH_149,
    DHCPS_INTERNAL_BRANCH_150,
    DHCPS_INTERNAL_BRANCH_151,
    DHCPS_INTERNAL_BRANCH_152,
    DHCPS_INTERNAL_BRANCH_153,
    DHCPS_INTERNAL_BRANCH_154,
    DHCPS_INTERNAL_BRANCH_155,
    DHCPS_INTERNAL_BRANCH_156,
    DHCPS_INTERNAL_BRANCH_157,
    DHCPS_INTERNAL_BRANCH_158,
    DHCPS_INTERNAL_BRANCH_159,
    DHCPS_INTERNAL_BRANCH_160,
    DHCPS_INTERNAL_BRANCH_161,
    DHCPS_INTERNAL_BRANCH_162,
    DHCPS_INTERNAL_BRANCH_163,
    DHCPS_INTERNAL_BRANCH_164,
    DHCPS_INTERNAL_BRANCH_165,
    DHCPS_INTERNAL_BRANCH_166,
    DHCPS_INTERNAL_BRANCH_167,
    DHCPS_INTERNAL_BRANCH_168,
    DHCPS_INTERNAL_BRANCH_169,
    DHCPS_INTERNAL_BRANCH_170,
    DHCPS_INTERNAL_BRANCH_171,
    DHCPS_INTERNAL_BRANCH_172,
    DHCPS_INTERNAL_BRANCH_173,
    DHCPS_INTERNAL_BRANCH_174,
    DHCPS_INTERNAL_BRANCH_175,
    DHCPS_INTERNAL_BRANCH_176,
    DHCPS_INTERNAL_BRANCH_177,
    DHCPS_INTERNAL_BRANCH_178,
    DHCPS_INTERNAL_BRANCH_179,
    DHCPS_INTERNAL_BRANCH_180,
    DHCPS_INTERNAL_BRANCH_181,
    DHCPS_INTERNAL_BRANCH_182,
    DHCPS_INTERNAL_BRANCH_183,
    DHCPS_INTERNAL_BRANCH_184,
    DHCPS_INTERNAL_BRANCH_185,
    DHCPS_INTERNAL_BRANCH_186,
    DHCPS_INTERNAL_BRANCH_187,
    DHCPS_INTERNAL_BRANCH_188,
    DHCPS_INTERNAL_BRANCH_189,
    DHCPS_INTERNAL_BRANCH_190,
    DHCPS_INTERNAL_BRANCH_191,
    DHCPS_INTERNAL_BRANCH_192,
    DHCPS_INTERNAL_BRANCH_193,
    DHCPS_INTERNAL_BRANCH_194,
    DHCPS_INTERNAL_BRANCH_195,
    DHCPS_INTERNAL_BRANCH_196,
    DHCPS_INTERNAL_BRANCH_197,
    DHCPS_INTERNAL_BRANCH_198,
    DHCPS_INTERNAL_BRANCH_199,
    DHCPS_INTERNAL_BRANCH_200,
    DHCPS_INTERNAL_BRANCH_201,
    DHCPS_INTERNAL_BRANCH_202,
    DHCPS_INTERNAL_BRANCH_203,
    DHCPS_INTERNAL_BRANCH_204,
    DHCPS_INTERNAL_BRANCH_205,
    DHCPS_INTERNAL_BRANCH_206,
    DHCPS_INTERNAL_BRANCH_207,
    DHCPS_INTERNAL_BRANCH_208,
    DHCPS_INTERNAL_BRANCH_209,
    DHCPS_INTERNAL_BRANCH_210,
    DHCPS_INTERNAL_BRANCH_211,
    DHCPS_INTERNAL_BRANCH_212,
    DHCPS_INTERNAL_BRANCH_213,
    DHCPS_INTERNAL_BRANCH_214,
    DHCPS_INTERNAL_BRANCH_215,
    DHCPS_INTERNAL_BRANCH_216,
    DHCPS_INTERNAL_BRANCH_217,
    DHCPS_INTERNAL_BRANCH_218,
    DHCPS_INTERNAL_BRANCH_219,
    DHCPS_INTERNAL_BRANCH_220,
    DHCPS_INTERNAL_BRANCH_221,
    DHCPS_INTERNAL_BRANCH_222,
    DHCPS_INTERNAL_BRANCH_223,
    DHCPS_INTERNAL_BRANCH_224,
    DHCPS_INTERNAL_BRANCH_225,
    DHCPS_INTERNAL_BRANCH_226,
    DHCPS_INTERNAL_BRANCH_227,
    DHCPS_INTERNAL_BRANCH_228,
    DHCPS_INTERNAL_BRANCH_229,
    DHCPS_INTERNAL_BRANCH_230,
    DHCPS_INTERNAL_BRANCH_231,
    DHCPS_INTERNAL_BRANCH_232,
    DHCPS_INTERNAL_BRANCH_233,
    DHCPS_INTERNAL_BRANCH_234,
    DHCPS_INTERNAL_BRANCH_235,
    DHCPS_INTERNAL_BRANCH_236,
    DHCPS_INTERNAL_BRANCH_237,
    DHCPS_INTERNAL_BRANCH_238,
    DHCPS_INTERNAL_BRANCH_239,
    DHCPS_INTERNAL_BRANCH_240,
    DHCPS_INTERNAL_BRANCH_241,
    DHCPS_INTERNAL_BRANCH_242,
    DHCPS_INTERNAL_BRANCH_243,
    DHCPS_INTERNAL_BRANCH_244,
    DHCPS_INTERNAL_BRANCH_245,
    DHCPS_INTERNAL_BRANCH_246,
    DHCPS_INTERNAL_BRANCH_247,
    DHCPS_INTERNAL_BRANCH_248,
    DHCPS_INTERNAL_BRANCH_249,
    DHCPS_INTERNAL_BRANCH_250,
    DHCPS_INTERNAL_BRANCH_251,
    DHCPS_INTERNAL_BRANCH_252,
    DHCPS_INTERNAL_BRANCH_253,
    DHCPS_INTERNAL_BRANCH_254,
    DHCPS_INTERNAL_BRANCH_255,
    DHCPS_INTERNAL_BRANCH_256,
    DHCPS_INTERNAL_BRANCH_257,
    DHCPS_INTERNAL_BRANCH_258,
    DHCPS_INTERNAL_BRANCH_259,
    DHCPS_INTERNAL_BRANCH_260,
    DHCPS_INTERNAL_BRANCH_261,
    DHCPS_INTERNAL_BRANCH_262,
    DHCPS_INTERNAL_BRANCH_263,
    DHCPS_INTERNAL_BRANCH_264,
    DHCPS_INTERNAL_BRANCH_265,
    DHCPS_INTERNAL_BRANCH_266,
    DHCPS_INTERNAL_BRANCH_267,
    DHCPS_INTERNAL_BRANCH_268,
    DHCPS_INTERNAL_BRANCH_269,
    DHCPS_INTERNAL_BRANCH_270,
    DHCPS_INTERNAL_BRANCH_271,
    DHCPS_INTERNAL_BRANCH_272,
    DHCPS_INTERNAL_BRANCH_273,
    DHCPS_INTERNAL_BRANCH_274,
    DHCPS_INTERNAL_BRANCH_275,
    DHCPS_INTERNAL_BRANCH_276,
    DHCPS_INTERNAL_BRANCH_277,
    DHCPS_INTERNAL_BRANCH_278,
    DHCPS_INTERNAL_BRANCH_279,
    DHCPS_INTERNAL_BRANCH_280,
    DHCPS_INTERNAL_BRANCH_281,
    DHCPS_INTERNAL_BRANCH_282,
    DHCPS_INTERNAL_BRANCH_283,
    DHCPS_INTERNAL_BRANCH_284,
    DHCPS_INTERNAL_BRANCH_285,
    DHCPS_INTERNAL_BRANCH_286,
    DHCPS_INTERNAL_BRANCH_287,
    DHCPS_INTERNAL_BRANCH_288,
    DHCPS_INTERNAL_BRANCH_289,
    DHCPS_INTERNAL_BRANCH_290,
    DHCPS_INTERNAL_BRANCH_291,
    DHCPS_INTERNAL_BRANCH_292,
    DHCPS_INTERNAL_BRANCH_293,
    DHCPS_INTERNAL_BRANCH_294,
    DHCPS_INTERNAL_BRANCH_295,
    DHCPS_INTERNAL_BRANCH_296,
    DHCPS_INTERNAL_BRANCH_297,
    DHCPS_INTERNAL_BRANCH_298,
    DHCPS_INTERNAL_BRANCH_299,
    DHCPS_INTERNAL_BRANCH_300,
    DHCPS_INTERNAL_BRANCH_301,
    DHCPS_INTERNAL_BRANCH_302,
    DHCPS_INTERNAL_BRANCH_303,
    DHCPS_INTERNAL_BRANCH_304,
    DHCPS_INTERNAL_BRANCH_305,
    DHCPS_INTERNAL_BRANCH_306,
    DHCPS_INTERNAL_BRANCH_307,
    DHCPS_INTERNAL_BRANCH_308,
    DHCPS_INTERNAL_BRANCH_309,
    DHCPS_INTERNAL_BRANCH_310,
    DHCPS_INTERNAL_BRANCH_311,
    DHCPS_INTERNAL_BRANCH_312,
    DHCPS_INTERNAL_BRANCH_313,
    DHCPS_INTERNAL_BRANCH_314,
    DHCPS_INTERNAL_BRANCH_315,
    DHCPS_INTERNAL_BRANCH_316,
    DHCPS_INTERNAL_BRANCH_317,
    DHCPS_INTERNAL_BRANCH_318,/*未使用*/
    DHCPS_INTERNAL_BRANCH_319,
    DHCPS_INTERNAL_BRANCH_320,
    DHCPS_INTERNAL_BRANCH_321,/* used 2012-02-13 label */
    DHCPS_INTERNAL_BRANCH_322,/* used 2012-02-13 label */
    DHCPS_INTERNAL_BRANCH_323,
    DHCPS_INTERNAL_BRANCH_324,
    DHCPS_INTERNAL_BRANCH_325,/* used 2013-11-14 label */
    DHCPS_INTERNAL_BRANCH_326,/* used 2013-11-14 label */
    DHCPS_INTERNAL_BRANCH_327,/* used 2013-12-20 label */
    DHCPS_INTERNAL_BRANCH_328,/* used 2013-12-20 label */
    DHCPS_INTERNAL_BRANCH_329,/* used 2013-12-20 label */
    DHCPS_INTERNAL_BRANCH_330,/* used 2013-12-20 label */
    DHCPS_INTERNAL_BRANCH_331,
    DHCPS_INTERNAL_BRANCH_332,
    DHCPS_INTERNAL_BRANCH_333,
    DHCPS_INTERNAL_BRANCH_334,
    DHCPS_INTERNAL_BRANCH_335,
    DHCPS_INTERNAL_BRANCH_336,
    DHCPS_INTERNAL_BRANCH_337,
    DHCPS_INTERNAL_BRANCH_338,
    DHCPS_INTERNAL_BRANCH_339,
    DHCPS_INTERNAL_BRANCH_340,
    DHCPS_INTERNAL_BRANCH_341,
    DHCPS_INTERNAL_BRANCH_342,
    DHCPS_INTERNAL_BRANCH_343,
    DHCPS_INTERNAL_BRANCH_344,
    DHCPS_INTERNAL_BRANCH_345,
    DHCPS_INTERNAL_BRANCH_346,
    DHCPS_INTERNAL_BRANCH_347,
    DHCPS_INTERNAL_BRANCH_348,
    DHCPS_INTERNAL_BRANCH_349,
    DHCPS_INTERNAL_BRANCH_350,
    DHCPS_INTERNAL_BRANCH_351,
    DHCPS_INTERNAL_BRANCH_352,
    DHCPS_INTERNAL_BRANCH_353,
    DHCPS_INTERNAL_BRANCH_354,
    DHCPS_INTERNAL_BRANCH_355,
    DHCPS_INTERNAL_BRANCH_356,
    DHCPS_INTERNAL_BRANCH_357,
    DHCPS_INTERNAL_BRANCH_358,
    DHCPS_INTERNAL_BRANCH_359,
    DHCPS_INTERNAL_BRANCH_360,
    DHCPS_INTERNAL_BRANCH_361,
    DHCPS_INTERNAL_BRANCH_362,
    DHCPS_INTERNAL_BRANCH_363,
    DHCPS_INTERNAL_BRANCH_364,
    DHCPS_INTERNAL_BRANCH_365,
    DHCPS_INTERNAL_BRANCH_366,
    DHCPS_INTERNAL_BRANCH_367,
    DHCPS_INTERNAL_BRANCH_368,
    DHCPS_INTERNAL_BRANCH_369,
    DHCPS_INTERNAL_BRANCH_370,
    DHCPS_INTERNAL_BRANCH_371,
    DHCPS_INTERNAL_BRANCH_372,
    DHCPS_INTERNAL_BRANCH_373,
    DHCPS_INTERNAL_BRANCH_374,
    DHCPS_INTERNAL_BRANCH_375,
    DHCPS_INTERNAL_BRANCH_376,
    DHCPS_INTERNAL_BRANCH_377,
    DHCPS_INTERNAL_BRANCH_378,
    DHCPS_INTERNAL_BRANCH_379,
    DHCPS_INTERNAL_BRANCH_380,
    DHCPS_INTERNAL_BRANCH_381,
    DHCPS_INTERNAL_BRANCH_382,
    DHCPS_INTERNAL_BRANCH_383,
    DHCPS_INTERNAL_BRANCH_384,
    DHCPS_INTERNAL_BRANCH_385,
    DHCPS_INTERNAL_BRANCH_386,
    DHCPS_INTERNAL_BRANCH_387,
    DHCPS_INTERNAL_BRANCH_388,
    DHCPS_INTERNAL_BRANCH_389,
    DHCPS_INTERNAL_BRANCH_390,
    DHCPS_INTERNAL_BRANCH_391,
    DHCPS_INTERNAL_BRANCH_392,
    DHCPS_INTERNAL_BRANCH_393,
    DHCPS_INTERNAL_BRANCH_394,
    DHCPS_INTERNAL_BRANCH_395,
    DHCPS_INTERNAL_BRANCH_396,
    DHCPS_INTERNAL_BRANCH_397,
    DHCPS_INTERNAL_BRANCH_398,
    DHCPS_INTERNAL_BRANCH_399,
    DHCPS_INTERNAL_BRANCH_400,
    DHCPS_INTERNAL_BRANCH_401,
    DHCPS_INTERNAL_BRANCH_402,
    DHCPS_INTERNAL_BRANCH_403,
    DHCPS_INTERNAL_BRANCH_404,
    DHCPS_INTERNAL_BRANCH_405,
    DHCPS_INTERNAL_BRANCH_406,
    DHCPS_INTERNAL_BRANCH_407,
    DHCPS_INTERNAL_BRANCH_408,
    DHCPS_INTERNAL_BRANCH_409,
    DHCPS_INTERNAL_BRANCH_410,
    DHCPS_INTERNAL_BRANCH_411,
    DHCPS_INTERNAL_BRANCH_412,
    DHCPS_INTERNAL_BRANCH_413,
    DHCPS_INTERNAL_BRANCH_414,
    DHCPS_INTERNAL_BRANCH_415,
    DHCPS_INTERNAL_BRANCH_416,
    DHCPS_INTERNAL_BRANCH_417,
    DHCPS_INTERNAL_BRANCH_418,
    DHCPS_INTERNAL_BRANCH_419,
    DHCPS_INTERNAL_BRANCH_420,
    DHCPS_INTERNAL_BRANCH_421,
    DHCPS_INTERNAL_BRANCH_422,
    DHCPS_INTERNAL_BRANCH_423,
    DHCPS_INTERNAL_BRANCH_424,
    DHCPS_INTERNAL_BRANCH_425,
    DHCPS_INTERNAL_BRANCH_426,
    DHCPS_INTERNAL_BRANCH_427,
    DHCPS_INTERNAL_BRANCH_428,
    DHCPS_INTERNAL_BRANCH_429,
    DHCPS_INTERNAL_BRANCH_430,
    DHCPS_INTERNAL_BRANCH_431,
    DHCPS_INTERNAL_BRANCH_432,
    DHCPS_INTERNAL_BRANCH_433,
    DHCPS_INTERNAL_BRANCH_434,
    DHCPS_INTERNAL_BRANCH_435,
    DHCPS_INTERNAL_BRANCH_436,
    DHCPS_INTERNAL_BRANCH_437,
    DHCPS_INTERNAL_BRANCH_438,
    DHCPS_INTERNAL_BRANCH_439,
    DHCPS_INTERNAL_BRANCH_440,
    DHCPS_INTERNAL_BRANCH_441,
    DHCPS_INTERNAL_BRANCH_442,
    DHCPS_INTERNAL_BRANCH_443,
    DHCPS_INTERNAL_BRANCH_444,
    DHCPS_INTERNAL_BRANCH_445,
    DHCPS_INTERNAL_BRANCH_446,
    DHCPS_INTERNAL_BRANCH_447,
    DHCPS_INTERNAL_BRANCH_448,
    DHCPS_INTERNAL_BRANCH_449,
    DHCPS_INTERNAL_BRANCH_450,
    DHCPS_INTERNAL_BRANCH_451,
    DHCPS_INTERNAL_BRANCH_452,
    DHCPS_INTERNAL_BRANCH_453,
    DHCPS_INTERNAL_BRANCH_454,
    DHCPS_INTERNAL_BRANCH_455,
    DHCPS_INTERNAL_BRANCH_456,
    DHCPS_INTERNAL_BRANCH_457,
    DHCPS_INTERNAL_BRANCH_458,
    DHCPS_INTERNAL_BRANCH_459,
    DHCPS_INTERNAL_BRANCH_460,
    DHCPS_INTERNAL_BRANCH_461,
    DHCPS_INTERNAL_BRANCH_462,
    DHCPS_INTERNAL_BRANCH_463,
    DHCPS_INTERNAL_BRANCH_464,
    DHCPS_INTERNAL_BRANCH_465,
    DHCPS_INTERNAL_BRANCH_466,
    DHCPS_INTERNAL_BRANCH_467,
    DHCPS_INTERNAL_BRANCH_468,
    DHCPS_INTERNAL_BRANCH_469,
    DHCPS_INTERNAL_BRANCH_470,
    DHCPS_INTERNAL_BRANCH_471,
    DHCPS_INTERNAL_BRANCH_472,
    DHCPS_INTERNAL_BRANCH_473,
    DHCPS_INTERNAL_BRANCH_474,
    DHCPS_INTERNAL_BRANCH_475,
    DHCPS_INTERNAL_BRANCH_476,
    DHCPS_INTERNAL_BRANCH_477,
    DHCPS_INTERNAL_BRANCH_478,
    DHCPS_INTERNAL_BRANCH_479,
    DHCPS_INTERNAL_BRANCH_480,
    DHCPS_INTERNAL_BRANCH_481,
    DHCPS_INTERNAL_BRANCH_482,
    DHCPS_INTERNAL_BRANCH_483,
    DHCPS_INTERNAL_BRANCH_484,
    DHCPS_INTERNAL_BRANCH_485,
    DHCPS_INTERNAL_BRANCH_486,
    DHCPS_INTERNAL_BRANCH_487,
    DHCPS_INTERNAL_BRANCH_488,
    DHCPS_INTERNAL_BRANCH_489,
    DHCPS_INTERNAL_BRANCH_490,
    DHCPS_INTERNAL_BRANCH_491,
    DHCPS_INTERNAL_BRANCH_492,
    DHCPS_INTERNAL_BRANCH_493,
    DHCPS_INTERNAL_BRANCH_494,
    DHCPS_INTERNAL_BRANCH_495,
    DHCPS_INTERNAL_BRANCH_496,
    DHCPS_INTERNAL_BRANCH_497,
    DHCPS_INTERNAL_BRANCH_498,
    DHCPS_INTERNAL_BRANCH_499,
    DHCPS_INTERNAL_BRANCH_500,
    DHCPS_INTERNAL_BRANCH_501,
    DHCPS_INTERNAL_BRANCH_502,
    DHCPS_INTERNAL_BRANCH_503,
    DHCPS_INTERNAL_BRANCH_504,
    DHCPS_INTERNAL_BRANCH_505,
    DHCPS_INTERNAL_BRANCH_506,
    DHCPS_INTERNAL_BRANCH_507,
    DHCPS_INTERNAL_BRANCH_508,
    DHCPS_INTERNAL_BRANCH_509,
    DHCPS_INTERNAL_BRANCH_510,
    DHCPS_INTERNAL_BRANCH_511,
    DHCPS_INTERNAL_BRANCH_512,
    DHCPS_INTERNAL_BRANCH_513,
    DHCPS_INTERNAL_BRANCH_514,
    DHCPS_INTERNAL_BRANCH_515,
    DHCPS_INTERNAL_BRANCH_516,
    DHCPS_INTERNAL_BRANCH_517,
    DHCPS_INTERNAL_BRANCH_518,
    DHCPS_INTERNAL_BRANCH_519,
    DHCPS_INTERNAL_BRANCH_520,
    DHCPS_INTERNAL_BRANCH_521,
    DHCPS_INTERNAL_BRANCH_522,
    DHCPS_INTERNAL_BRANCH_523,
    DHCPS_INTERNAL_BRANCH_524,
    DHCPS_INTERNAL_BRANCH_525,
    DHCPS_INTERNAL_BRANCH_526,
    DHCPS_INTERNAL_BRANCH_527,
    DHCPS_INTERNAL_BRANCH_528,
    DHCPS_INTERNAL_BRANCH_529,
    DHCPS_INTERNAL_BRANCH_530,
    DHCPS_INTERNAL_BRANCH_531,
    DHCPS_INTERNAL_BRANCH_532,
    DHCPS_INTERNAL_BRANCH_533,
    DHCPS_INTERNAL_BRANCH_534,
    DHCPS_INTERNAL_BRANCH_535,
    DHCPS_INTERNAL_BRANCH_536,
    DHCPS_INTERNAL_BRANCH_537,
    DHCPS_INTERNAL_BRANCH_538,
    DHCPS_INTERNAL_BRANCH_539,
    DHCPS_INTERNAL_BRANCH_540,
    DHCPS_INTERNAL_BRANCH_541,
    DHCPS_INTERNAL_BRANCH_542,
    DHCPS_INTERNAL_BRANCH_543,
    DHCPS_INTERNAL_BRANCH_544,
    DHCPS_INTERNAL_BRANCH_545,
    DHCPS_INTERNAL_BRANCH_546,
    DHCPS_INTERNAL_BRANCH_547,
    DHCPS_INTERNAL_BRANCH_548,
    DHCPS_INTERNAL_BRANCH_549,
    DHCPS_INTERNAL_BRANCH_550,
    DHCPS_INTERNAL_BRANCH_551,
    DHCPS_INTERNAL_BRANCH_552,
    DHCPS_INTERNAL_BRANCH_553,
    DHCPS_INTERNAL_BRANCH_554,
    DHCPS_INTERNAL_BRANCH_555,
    DHCPS_INTERNAL_BRANCH_556,
    DHCPS_INTERNAL_BRANCH_557,
    DHCPS_INTERNAL_BRANCH_558,
    DHCPS_INTERNAL_BRANCH_559,
    DHCPS_INTERNAL_BRANCH_560,
    DHCPS_INTERNAL_BRANCH_561,
    DHCPS_INTERNAL_BRANCH_562,
    DHCPS_INTERNAL_BRANCH_563,
    DHCPS_INTERNAL_BRANCH_564,
    DHCPS_INTERNAL_BRANCH_565,
    DHCPS_INTERNAL_BRANCH_566,
    DHCPS_INTERNAL_BRANCH_567,
    DHCPS_INTERNAL_BRANCH_568,
    DHCPS_INTERNAL_BRANCH_569,
    DHCPS_INTERNAL_BRANCH_570,
    DHCPS_INTERNAL_BRANCH_571,
    DHCPS_INTERNAL_BRANCH_572,
    DHCPS_INTERNAL_BRANCH_573,
    DHCPS_INTERNAL_BRANCH_574,
    DHCPS_INTERNAL_BRANCH_575,
    DHCPS_INTERNAL_BRANCH_576,
    DHCPS_INTERNAL_BRANCH_577,
    DHCPS_INTERNAL_BRANCH_578,
    DHCPS_INTERNAL_BRANCH_579,
    DHCPS_INTERNAL_BRANCH_580,
    DHCPS_INTERNAL_BRANCH_581,
    DHCPS_INTERNAL_BRANCH_582,
    DHCPS_INTERNAL_BRANCH_583,
    DHCPS_INTERNAL_BRANCH_584,
    DHCPS_INTERNAL_BRANCH_585,
    DHCPS_INTERNAL_BRANCH_586,
    DHCPS_INTERNAL_BRANCH_587,
    DHCPS_INTERNAL_BRANCH_588,
    DHCPS_INTERNAL_BRANCH_589,
    DHCPS_INTERNAL_BRANCH_590,
    DHCPS_INTERNAL_BRANCH_591,
    DHCPS_INTERNAL_BRANCH_592,
    DHCPS_INTERNAL_BRANCH_593,
    DHCPS_INTERNAL_BRANCH_594,
    DHCPS_INTERNAL_BRANCH_595,
    DHCPS_INTERNAL_BRANCH_596,
    DHCPS_INTERNAL_BRANCH_597,
    DHCPS_INTERNAL_BRANCH_598,
    DHCPS_INTERNAL_BRANCH_599,
    DHCPS_INTERNAL_BRANCH_600,
    DHCPS_INTERNAL_BRANCH_601,
    DHCPS_INTERNAL_BRANCH_602,
    DHCPS_INTERNAL_BRANCH_603,
    DHCPS_INTERNAL_BRANCH_604,
    DHCPS_INTERNAL_BRANCH_605,
    DHCPS_INTERNAL_BRANCH_606,
    DHCPS_INTERNAL_BRANCH_607,
    DHCPS_INTERNAL_BRANCH_608,
    DHCPS_INTERNAL_BRANCH_609,
    DHCPS_INTERNAL_BRANCH_610,
    DHCPS_INTERNAL_BRANCH_611,
    DHCPS_INTERNAL_BRANCH_612,
    DHCPS_INTERNAL_BRANCH_613,
    DHCPS_INTERNAL_BRANCH_614,
    DHCPS_INTERNAL_BRANCH_615,
    DHCPS_INTERNAL_BRANCH_616,
    DHCPS_INTERNAL_BRANCH_617,
    DHCPS_INTERNAL_BRANCH_618,
    DHCPS_INTERNAL_BRANCH_619,
    DHCPS_INTERNAL_BRANCH_620,
    DHCPS_INTERNAL_BRANCH_621,
    DHCPS_INTERNAL_BRANCH_622,
    DHCPS_INTERNAL_BRANCH_623,
    DHCPS_INTERNAL_BRANCH_624,
    DHCPS_INTERNAL_BRANCH_625,
    DHCPS_INTERNAL_BRANCH_626,
    DHCPS_INTERNAL_BRANCH_627,
    DHCPS_INTERNAL_BRANCH_628,
    DHCPS_INTERNAL_BRANCH_629,
    DHCPS_INTERNAL_BRANCH_630,
    DHCPS_INTERNAL_BRANCH_631,
    DHCPS_INTERNAL_BRANCH_632,
    DHCPS_INTERNAL_BRANCH_633,
    DHCPS_INTERNAL_BRANCH_634,
    DHCPS_INTERNAL_BRANCH_635,
    DHCPS_INTERNAL_BRANCH_636,
    DHCPS_INTERNAL_BRANCH_637,
    DHCPS_INTERNAL_BRANCH_638,
    DHCPS_INTERNAL_BRANCH_639,
    DHCPS_INTERNAL_BRANCH_640,
    DHCPS_INTERNAL_BRANCH_641,
    DHCPS_INTERNAL_BRANCH_642,
    DHCPS_INTERNAL_BRANCH_643,
    DHCPS_INTERNAL_BRANCH_644,
    DHCPS_INTERNAL_BRANCH_645,
    DHCPS_INTERNAL_BRANCH_646,
    DHCPS_INTERNAL_BRANCH_647,
    DHCPS_INTERNAL_BRANCH_648,
    DHCPS_INTERNAL_BRANCH_649,
    DHCPS_INTERNAL_BRANCH_650,
    DHCPS_INTERNAL_BRANCH_651,
    DHCPS_INTERNAL_BRANCH_652,
    DHCPS_INTERNAL_BRANCH_653,
    DHCPS_INTERNAL_BRANCH_654,
    DHCPS_INTERNAL_BRANCH_655,
    DHCPS_INTERNAL_BRANCH_656,
    DHCPS_INTERNAL_BRANCH_657,
    DHCPS_INTERNAL_BRANCH_658,
    DHCPS_INTERNAL_BRANCH_659,
    DHCPS_INTERNAL_BRANCH_660,
    DHCPS_INTERNAL_BRANCH_661,
    DHCPS_INTERNAL_BRANCH_662,
    DHCPS_INTERNAL_BRANCH_663,
    DHCPS_INTERNAL_BRANCH_664,
    DHCPS_INTERNAL_BRANCH_665,
    DHCPS_INTERNAL_BRANCH_666,
    DHCPS_INTERNAL_BRANCH_667,
    DHCPS_INTERNAL_BRANCH_668,
    DHCPS_INTERNAL_BRANCH_669,
    DHCPS_INTERNAL_BRANCH_670,
    DHCPS_INTERNAL_BRANCH_671,
    DHCPS_INTERNAL_BRANCH_672,
    DHCPS_INTERNAL_BRANCH_673,
    DHCPS_INTERNAL_BRANCH_674,
    DHCPS_INTERNAL_BRANCH_675,
    DHCPS_INTERNAL_BRANCH_676,
    DHCPS_INTERNAL_BRANCH_677,
    DHCPS_INTERNAL_BRANCH_678,
    DHCPS_INTERNAL_BRANCH_679,
    DHCPS_INTERNAL_BRANCH_680,
    DHCPS_INTERNAL_BRANCH_681,
    DHCPS_INTERNAL_BRANCH_682,
    DHCPS_INTERNAL_BRANCH_683,
    DHCPS_INTERNAL_BRANCH_684,
    DHCPS_INTERNAL_BRANCH_685,
    DHCPS_INTERNAL_BRANCH_686,
    DHCPS_INTERNAL_BRANCH_687,
    DHCPS_INTERNAL_BRANCH_688,
    DHCPS_INTERNAL_BRANCH_689,
    DHCPS_INTERNAL_BRANCH_690,
    DHCPS_INTERNAL_BRANCH_691,
    DHCPS_INTERNAL_BRANCH_692,
    DHCPS_INTERNAL_BRANCH_693,
    DHCPS_INTERNAL_BRANCH_694,
    DHCPS_INTERNAL_BRANCH_695,
    DHCPS_INTERNAL_BRANCH_696,
    DHCPS_INTERNAL_BRANCH_697,
    DHCPS_INTERNAL_BRANCH_698,
    DHCPS_INTERNAL_BRANCH_699,
    DHCPS_INTERNAL_BRANCH_700,
    DHCPS_INTERNAL_BRANCH_701,
    DHCPS_INTERNAL_BRANCH_702,
    DHCPS_INTERNAL_BRANCH_703,
    DHCPS_INTERNAL_BRANCH_704,
    DHCPS_INTERNAL_BRANCH_705,
    DHCPS_INTERNAL_BRANCH_706,
    DHCPS_INTERNAL_BRANCH_707,
    DHCPS_INTERNAL_BRANCH_708,
    DHCPS_INTERNAL_BRANCH_709,
    DHCPS_INTERNAL_BRANCH_710,
    DHCPS_INTERNAL_BRANCH_711,
    DHCPS_INTERNAL_BRANCH_712,
    DHCPS_INTERNAL_BRANCH_713,
    DHCPS_INTERNAL_BRANCH_714,
    DHCPS_INTERNAL_BRANCH_715,
    DHCPS_INTERNAL_BRANCH_716,
    DHCPS_INTERNAL_BRANCH_717,
    DHCPS_INTERNAL_BRANCH_718,
    DHCPS_INTERNAL_BRANCH_719,
    DHCPS_INTERNAL_BRANCH_720,
    DHCPS_INTERNAL_BRANCH_721,
    DHCPS_INTERNAL_BRANCH_722,
    DHCPS_INTERNAL_BRANCH_723,
    DHCPS_INTERNAL_BRANCH_724,
    DHCPS_INTERNAL_BRANCH_725,
    DHCPS_INTERNAL_BRANCH_726,
    DHCPS_INTERNAL_BRANCH_727,
    DHCPS_INTERNAL_BRANCH_728,
    DHCPS_INTERNAL_BRANCH_729,
    DHCPS_INTERNAL_BRANCH_730,
    DHCPS_INTERNAL_BRANCH_731,
    DHCPS_INTERNAL_BRANCH_732,
    DHCPS_INTERNAL_BRANCH_733,
    DHCPS_INTERNAL_BRANCH_734,
    DHCPS_INTERNAL_BRANCH_735,
    DHCPS_INTERNAL_BRANCH_736,
    DHCPS_INTERNAL_BRANCH_737,
    DHCPS_INTERNAL_BRANCH_738,
    DHCPS_INTERNAL_BRANCH_739,
    DHCPS_INTERNAL_BRANCH_740,
    DHCPS_INTERNAL_BRANCH_741,
    DHCPS_INTERNAL_BRANCH_742,
    DHCPS_INTERNAL_BRANCH_743,
    DHCPS_INTERNAL_BRANCH_744,
    DHCPS_INTERNAL_BRANCH_745,
    DHCPS_INTERNAL_BRANCH_746,
    DHCPS_INTERNAL_BRANCH_747,
    DHCPS_INTERNAL_BRANCH_748,
    DHCPS_INTERNAL_BRANCH_749,
    DHCPS_INTERNAL_BRANCH_750,
    DHCPS_INTERNAL_BRANCH_751,
    DHCPS_INTERNAL_BRANCH_752,
    DHCPS_INTERNAL_BRANCH_753,
    DHCPS_INTERNAL_BRANCH_754,
    DHCPS_INTERNAL_BRANCH_755,
    DHCPS_INTERNAL_BRANCH_756,
    DHCPS_INTERNAL_BRANCH_757,
    DHCPS_INTERNAL_BRANCH_758,
    DHCPS_INTERNAL_BRANCH_759,
    DHCPS_INTERNAL_BRANCH_760,
    DHCPS_INTERNAL_BRANCH_761,
    DHCPS_INTERNAL_BRANCH_762,
    DHCPS_INTERNAL_BRANCH_763,
    DHCPS_INTERNAL_BRANCH_764,
    DHCPS_INTERNAL_BRANCH_765,
    DHCPS_INTERNAL_BRANCH_766,
    DHCPS_INTERNAL_BRANCH_767,
    DHCPS_INTERNAL_BRANCH_768,
    DHCPS_INTERNAL_BRANCH_769,
    DHCPS_INTERNAL_BRANCH_770,
    DHCPS_INTERNAL_BRANCH_771,
    DHCPS_INTERNAL_BRANCH_772,
    DHCPS_INTERNAL_BRANCH_773,
    DHCPS_INTERNAL_BRANCH_774,
    DHCPS_INTERNAL_BRANCH_775,
    DHCPS_INTERNAL_BRANCH_776,
    DHCPS_INTERNAL_BRANCH_777,
    DHCPS_INTERNAL_BRANCH_778,
    DHCPS_INTERNAL_BRANCH_779,
    DHCPS_INTERNAL_BRANCH_780,
    DHCPS_INTERNAL_BRANCH_781,
    DHCPS_INTERNAL_BRANCH_782,
    DHCPS_INTERNAL_BRANCH_783,
    DHCPS_INTERNAL_BRANCH_784,
    DHCPS_INTERNAL_BRANCH_785,
    DHCPS_INTERNAL_BRANCH_786,
    DHCPS_INTERNAL_BRANCH_787,
    DHCPS_INTERNAL_BRANCH_788,
    DHCPS_INTERNAL_BRANCH_789,
    DHCPS_INTERNAL_BRANCH_790,
    DHCPS_INTERNAL_BRANCH_791,
    DHCPS_INTERNAL_BRANCH_792,
    DHCPS_INTERNAL_BRANCH_793,
    DHCPS_INTERNAL_BRANCH_794,
    DHCPS_INTERNAL_BRANCH_795,
    DHCPS_INTERNAL_BRANCH_796,
    DHCPS_INTERNAL_BRANCH_797,
    DHCPS_INTERNAL_BRANCH_798,
    DHCPS_INTERNAL_BRANCH_799,
    DHCPS_INTERNAL_BRANCH_800,/*used*/
    DHCPS_INTERNAL_BRANCH_801,/*used*/
    DHCPS_INTERNAL_BRANCH_802,/*used*/
    DHCPS_INTERNAL_BRANCH_803,/*used*/
    DHCPS_INTERNAL_BRANCH_804,/*used*/
    DHCPS_INTERNAL_BRANCH_805,/*used*/
    DHCPS_INTERNAL_BRANCH_806,/*used*/
    DHCPS_INTERNAL_BRANCH_807,/*used*/
    DHCPS_INTERNAL_BRANCH_808,/*used*/
    DHCPS_INTERNAL_BRANCH_809,/*used*/
    DHCPS_INTERNAL_BRANCH_810,/*used*/
    DHCPS_INTERNAL_BRANCH_811,/*used*/
    DHCPS_INTERNAL_BRANCH_812,/*used*/
    DHCPS_INTERNAL_BRANCH_813,/*used*/
    DHCPS_INTERNAL_BRANCH_814,/*used*/
    DHCPS_INTERNAL_BRANCH_815,/*used*/
    DHCPS_INTERNAL_BRANCH_816,/*used*/
    DHCPS_INTERNAL_BRANCH_817,/*used*/
    DHCPS_INTERNAL_BRANCH_818,/*used*/
    DHCPS_INTERNAL_BRANCH_819,/*used*/
    DHCPS_INTERNAL_BRANCH_820,/*used*/
    DHCPS_INTERNAL_BRANCH_821,/*used*/
    DHCPS_INTERNAL_BRANCH_822,/*used*/
    DHCPS_INTERNAL_BRANCH_823,/*used*/
    DHCPS_INTERNAL_BRANCH_824,/*used*/
    DHCPS_INTERNAL_BRANCH_825,/*used*/
    DHCPS_INTERNAL_BRANCH_826,/*used*/
    DHCPS_INTERNAL_BRANCH_827,/*used*/
    DHCPS_INTERNAL_BRANCH_828,/*used*/
    DHCPS_INTERNAL_BRANCH_829,/*used*/
    DHCPS_INTERNAL_BRANCH_830,/*used*/
    DHCPS_INTERNAL_BRANCH_831,/*used*/
    DHCPS_INTERNAL_BRANCH_832,/*used*/
    DHCPS_INTERNAL_BRANCH_833,/*used*/
    DHCPS_INTERNAL_BRANCH_834,/*used*/
    DHCPS_INTERNAL_BRANCH_835,/*used*/
    DHCPS_INTERNAL_BRANCH_836,/*used*/
    DHCPS_INTERNAL_BRANCH_837,/*used*/
    DHCPS_INTERNAL_BRANCH_838,/*used*/
    DHCPS_INTERNAL_BRANCH_839,/*used*/
    DHCPS_INTERNAL_BRANCH_840,/*used*/
    DHCPS_INTERNAL_BRANCH_841,/*used*/
    DHCPS_INTERNAL_BRANCH_842,/*used*/
    DHCPS_INTERNAL_BRANCH_843,/*used 备板释放用户 */
    DHCPS_INTERNAL_BRANCH_844,/*used 备板丢弃消息 */
    DHCPS_INTERNAL_BRANCH_845,
    DHCPS_INTERNAL_BRANCH_846,
    DHCPS_INTERNAL_BRANCH_847,
    DHCPS_INTERNAL_BRANCH_848,
    DHCPS_INTERNAL_BRANCH_849,
    DHCPS_INTERNAL_BRANCH_850,
    DHCPS_INTERNAL_BRANCH_851,
    DHCPS_INTERNAL_BRANCH_852,
    DHCPS_INTERNAL_BRANCH_853,
    DHCPS_INTERNAL_BRANCH_854,
    DHCPS_INTERNAL_BRANCH_855,
    DHCPS_INTERNAL_BRANCH_856,
    DHCPS_INTERNAL_BRANCH_857,
    DHCPS_INTERNAL_BRANCH_858,
    DHCPS_INTERNAL_BRANCH_859,
    DHCPS_INTERNAL_BRANCH_860,
    DHCPS_INTERNAL_BRANCH_861,
    DHCPS_INTERNAL_BRANCH_862,
    DHCPS_INTERNAL_BRANCH_863,
    DHCPS_INTERNAL_BRANCH_864,
    DHCPS_INTERNAL_BRANCH_865,
    DHCPS_INTERNAL_BRANCH_866,
    DHCPS_INTERNAL_BRANCH_867,
    DHCPS_INTERNAL_BRANCH_868,
    DHCPS_INTERNAL_BRANCH_869,
    DHCPS_INTERNAL_BRANCH_870,
    DHCPS_INTERNAL_BRANCH_871,
    DHCPS_INTERNAL_BRANCH_872,
    DHCPS_INTERNAL_BRANCH_873,
    DHCPS_INTERNAL_BRANCH_874,
    DHCPS_INTERNAL_BRANCH_875,
    DHCPS_INTERNAL_BRANCH_876,
    DHCPS_INTERNAL_BRANCH_877,
    DHCPS_INTERNAL_BRANCH_878,
    DHCPS_INTERNAL_BRANCH_879,
    DHCPS_INTERNAL_BRANCH_880,
    DHCPS_INTERNAL_BRANCH_881,
    DHCPS_INTERNAL_BRANCH_882,
    DHCPS_INTERNAL_BRANCH_883,
    DHCPS_INTERNAL_BRANCH_884,
    DHCPS_INTERNAL_BRANCH_885,
    DHCPS_INTERNAL_BRANCH_886,
    DHCPS_INTERNAL_BRANCH_887,
    DHCPS_INTERNAL_BRANCH_888,
    DHCPS_INTERNAL_BRANCH_889,
    DHCPS_INTERNAL_BRANCH_890,
    DHCPS_INTERNAL_BRANCH_891,
    DHCPS_INTERNAL_BRANCH_892,
    DHCPS_INTERNAL_BRANCH_893,
    DHCPS_INTERNAL_BRANCH_894,
    DHCPS_INTERNAL_BRANCH_895,
    DHCPS_INTERNAL_BRANCH_896,
    DHCPS_INTERNAL_BRANCH_897,
    DHCPS_INTERNAL_BRANCH_898,
    DHCPS_INTERNAL_BRANCH_899,
    DHCPS_INTERNAL_BRANCH_900,
    DHCPS_INTERNAL_BRANCH_901,
    DHCPS_INTERNAL_BRANCH_902,
    DHCPS_INTERNAL_BRANCH_903,
    DHCPS_INTERNAL_BRANCH_904,
    /*now it is 1000. 如果超过1000需要重新评估*/
    DHCPS_INTERNAL_BRANCH_BUTT=DHCPS_MAX_FAILURE_COUNTER
}enumDHCPSStandardCounterIndex;

/* 错误消息码 */
enum DHCPS_ERR_CODE
{
    DHCPS_ALLOC_MEMORY_ERR = 20,
    DHCPS_SYS_ERR,
    DHCPS_IPC_SEND_ERR,
    DHCPS_IPC_RCVMSG_ERR,
    DHCPS_RPC_SEND_ERR,    
    DHCPS_RPC_RCVMSG_ERR,
    DHCPS_PARAMETER_ERR,
    DHCPS_DOMAIN_INDEX_ERR,
    DHCPS_POOL_INDEX_ERR,
    DHCPS_NO_POOL_NODE,
    
    DHCPS_GET_POOL_OPNODE_ERR, /* 30 */
    DHCPS_GET_SECTION_OPNODE_ERR,
    DHCPS_GET_SUBSECTION_OPNODE_ERR,
    DHCPS_GET_IPADDR_ERR,
    DHCPS_IPCONFLIC_ERR,
    DHCPS_IP_INVALID,
    DHCPS_REQMSG_IPTYPE_ERR,
    DHCPS_REQMSG_POOL_ERR,
    DHCPS_REQMSG_DOMAIN_ERR,
    DHCPS_REQMSG_POOL_LOCK,

    DHCPS_DEL_ROUTE_ERR,    /*40*/
    DHCPS_ADD_ROUTE_ERR,
    DHCPS_REMOTE_IPRELEASE_ERR,
    DHCPS_LIST_ERR,
    DHCPS_NO_FREE_IP_ERR,
    DHCPS_CHKMSG_AGENTIP_ERR,
    DHCPS_IP_RELEASE_ERR,
    DHCPS_DHCP_RELEASE_AGENTIP,
    DHCPS_DHCP_POOL_NOTMATCH,
    DHCPS_ADDTO_WAITLIST,

    DHCPS_RCV_SCREQ_MSGLEN_ERR, /* 50 */
    DHCPS_RCV_SCREL_MSGLEN_ERR,
    DHCPS_RCV_DHCPCHK_MSGLEN_ERR,
    DHCPS_CDB_OPERATION_ERR,
    DHCPS_NULL_POINTER,
    DHCPS_AGENT_NOT_IN_POOL,
    DHCPS_POOL_TYPE_ERR,
    DHCPS_DHCP_ADDR_CONFLICT_ERR,
    DHCPS_SECTION_NUM_ERR,
    DHCPS_IP_RELEASE_LOCATE_FAILED,
    DHCPS_MCWriteQue_ERR,
    DHCPS_MCReadQue_ERR,
    DHCPS_MCEventWrite,
    DHCPS_POOL_NAME_LENGTH_ERR,
    DHCPS_POOL_RECORD_NOT_EXIST,
    DHCPS_GET_POOL_RECORD_FAILED,
    DHCPS_USED_LIST_SUBSECTION_NULL,
    DHCPS_BIT_SET_ALREADY,
    DHCPS_BIT_CLEAN_ALREADY,
    DHCPS_ERR_BUTT = 0xFFFFFFFF
};

/*dhcp数据包中选项数据结构DHCP_POOL_OPTION_S */
typedef  struct tagDHCPS_CFG_OPTION
{
    UCHAR ucUsed;
    UCHAR ucFlag;                       /*标志这个option格式类型,ascii或ip或hex*/
    UCHAR ucLen;                        /*option的长度*/
    UCHAR ucRev;
    CHAR pcData[DHCPS_OPTIONDATA_LEN];     /*option的内容*/
}DHCPS_CFG_OPTION_S;


typedef struct tagDHCPS_CDB_RECORD
{
    UCHAR  ucCode;
    UCHAR  ucType;
    UCHAR  ucLen;
    UCHAR  ucRev;
    UCHAR  aucData[64] ;
}DHCPS_CDB_RECORD_S;


/*dhcp网络包物理结构DHCP_PACKET_S*/
typedef struct tagDhcpsPacketHead
{
    UCHAR  ucOp;                /* Message opcode/type */
    UCHAR  ucHtype;             /* Hardware addr type (see net/if_types.h) */
    UCHAR  ucHlen;              /* Hardware addr length */
    UCHAR  ucHops;              /* Number of relay agent hops from client */
    ULONG ulXid;                /* Transaction ID */
    USHORT usSecs;              /* Seconds since clien t started looking */
    USHORT usFlags;             /* Flag bits */
    ULONG ulCiaddr;             /* Client IP address (if already in use) */
    ULONG ulYiaddr;             /* Client IP address */
    ULONG ulSiaddr;             /* IP address of next server to talk to */
    ULONG ulGiaddr;             /* DHCP relay agent IP address */
    UCHAR pucChaddr [DHCPS_CHADDR_LEN];               /* Client hardware address */
    CHAR pcSname [DHCPS_SNAME_LEN];      /* Server name */
    CHAR pcFile [DHCPS_FILE_LEN];        /* Boot filename */
}DHCPS_PACKET_HEAD_S;

/* 实际上，DHCP_HEAD_LEN 就是 sizeof(DHCP_PACKET_HEAD_S)*/

typedef struct tagDhcpsPacket
{
    DHCPS_PACKET_HEAD_S * pstHead;
    UCHAR *pucOptions;
}DHCPS_PACKET_S;

typedef struct
{
    ULONG ulDNSIP[2];
    ULONG ulTeid;
    ULONG ulPeerDataAddr;                 /* 对端数据地址(协) */
    ULONG ulLocDataAddr;                  /* 本端数据地址 */
    USHORT usSeqNo;
    USHORT usApnIndex;
    UCHAR ucDeliveryOrder;
    UCHAR uRev[3];

}STUB_SDB_CONTEXT_S;

/* 定时器类型*/
typedef enum
{
    E_DHCPS_INVALID_TIMER = 0,

    E_DHCPS_FSM_TIMER = 1,
    
    E_DHCPS_LEASE_TIMER = 2,

    E_DHCPS_TIMER_BUTT
    
}DHCPS_TIMER_TYPE_E;   /* 定时器类型 */


typedef struct DHCPS_TIMER_LINKLIST_S
{
    struct DHCPS_TIMER_LINKLIST_S* prev;      /* previous node */
    struct DHCPS_TIMER_LINKLIST_S* next;      /* next node */
    ULONG ulPdpIndex;                      /* R-P context index */
    ULONG ulNodeTimerCount;               /* timer count：在g_pstTimer数组中的下标值，据此可以找到链表的头指针*/
    DHCPS_TIMER_TYPE_E enTimerType;   /* timer type */
    UCHAR ucState;         /* Linklist Node State: 0: NULL, 1: used */
    UCHAR ucResv[3];
}DHCPS_TIMER_LINKLIST_S;           /* 定时链表结构定义 */

typedef struct DHCPS_MSG_BUFFLIST_NODES
{
    struct DHCPS_MSG_BUFFLIST_NODES *pPre;
    struct DHCPS_MSG_BUFFLIST_NODES *pNext;
    UCHAR *pucMsgData;
    ULONG ulPdnIndex;
    ULONG ulMsgLen;
}DHCPS_MSG_BUFFLIST_NODE;

typedef struct 
{
    DHCPS_MSG_BUFFLIST_NODE stFistNode;
    DHCPS_MSG_BUFFLIST_NODE stEndNode;
    ULONG ulNodeNum;
}DHCPS_MSG_BUFFLIST_HEAD;

#endif /* #ifndef _DHCP_CDB_H_ */ 

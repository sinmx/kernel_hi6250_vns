# MD5: 285b253341f5a49d301403b03761c1c8
set(CFG_XTENSA_CORE				 v7r22_bbe16) 

set(CFG_XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux/$(CFG_XTENSA_CORE)/config) 

set(CFG_TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux) 

set(CFG_TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux) 

set(CFG_TENSILICA_BUILDS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux) 

set(CFG_TENSILICA_TOOLS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux) 

set(LPHY_LD_MAP_PUB_PATH modem/phy/lt/Tensilica_LSP/BBE16_V722_LSP/pub_lsp) 

set(LPHY_LD_MAP_LTE_PATH modem/phy/lt/Tensilica_LSP/BBE16_V722_LSP/lte_lsp) 

set(LPHY_LD_MAP_TDS_PATH modem/phy/lt/Tensilica_LSP/BBE16_V722_LSP/tds_lsp) 

set(LPHY_LD_SDR_LIB_FILE BBE16_V722_O2) 

set(LPHY_XTENSA_RULES cc_tensilica5.0.5_rules.mk) 

set(CFG_LPHY_PUB_DTCM_BASE	 0x72740000) 

set(CFG_LPHY_PUB_ITCM_BASE	 0x72840000) 

set(CFG_LPHY_PRV_DTCM_BASE	 0x72798000) 

set(CFG_LPHY_PRV_ITCM_BASE	 0x72898000) 

set(CFG_LPHY_PUB_DTCM_SIZE		 0x58000) 

set(CFG_LPHY_PUB_ITCM_SIZE		 0x58000) 

set(CFG_LPHY_PRV_DTCM_SIZE		 0x58000) 

set(CFG_LPHY_PRV_ITCM_SIZE		 0x58000) 

set(CFG_LPHY_LTE_DTCM_SIZE		 0x58000) 

set(CFG_LPHY_LTE_ITCM_SIZE		 0x58000) 

set(CFG_LPHY_TDS_DTCM_SIZE		 0x30000) 

set(CFG_LPHY_TDS_ITCM_SIZE		 0x38000) 

set(CFG_LPHY_TOTAL_IMG_SIZE ((LPHY_PUB_DTCM_SIZE)+(LPHY_PUB_ITCM_SIZE)+(LPHY_LTE_DTCM_SIZE)*2+(LPHY_LTE_ITCM_SIZE)*2+(LPHY_TDS_DTCM_SIZE)+(LPHY_TDS_ITCM_SIZE))) 

set(CFG_TL_PHY_ASIC_V722        	 YES) 

set(CFG_LPHY_SFT NO) 

set(CFG_TL_PHY_BBE16_CACHE NO) 

set(CFG_TL_PHY_HI6932         	 YES) 

set(CFG_TL_PHY_FEATURE_LTE_LCS  	 YES) 

set(CFG_FEATURE_TAS FEATURE_OFF) 

set(CFG_FEATURE_DSDS FEATURE_OFF) 

set(CFG_FEATURE_TLPHY_SINGLE_XO		 YES) 

set(CFG_FEATURE_LPHY_RFIC_HI6362 FEATURE_ON) 

set(CFG_FEATURE_TLPHY_LOWER_SAR FEATURE_ON) 

set(CFG_FEATURE_LTE_4RX FEATURE_OFF) 


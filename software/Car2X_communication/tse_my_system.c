#ifdef ALT_INICHE
    #include "ipport.h"
#endif

#include "system.h"
#include "altera_avalon_tse.h"
#include "altera_avalon_tse_system_info.h"

//alt_tse_system_info tse_mac_device[MAXNETS] = {
//		TSE_SYSTEM_EXT_MEM_NO_SHARED_FIFO(TSE_MAC, 0, SGDMA_TX, SGDMA_RX, TSE_PHY_AUTO_ADDRESS, 0, DESCRIPTOR_MEMORY)
//
//};
alt_tse_system_info tse_mac_device[MAXNETS] = {
	TSE_SYSTEM_EXT_MEM_NO_SHARED_FIFO(ETHERNET_SUBSYSTEM_TSE_MAC, 0, ETHERNET_SUBSYSTEM_SGDMA_TX, ETHERNET_SUBSYSTEM_SGDMA_RX, TSE_PHY_AUTO_ADDRESS, &marvell_cfg_rgmii, ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY)
};

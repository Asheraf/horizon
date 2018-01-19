//
// Created by SagunKho on 16/01/2018.
//

#ifndef HORIZON_CHARPACKETS_H
#define HORIZON_CHARPACKETS_H

enum char_client_packets
{
	/**
	 * Receivable Packets
	 */
	CH_ENTER              =  0x65,
	CH_SELECT_CHAR        =  0x66,
	CH_MAKE_CHAR          =  0x67,
	CH_DELETE_CHAR        =  0x68,
	/**
	 * Sendable Packets
	 */
	HC_ACCEPT_ENTER       =  0x6b,
	HC_REFUSE_ENTER       =  0x6c,
	HC_ACCEPT_MAKECHAR    =  0x6d,
	HC_REFUSE_MAKECHAR    =  0x6e,
	HC_ACCEPT_DELETECHAR  =  0x6f,
	HC_REFUSE_DELETECHAR  =  0x70,
	HC_NOTIFY_ZONESVR     =  0x71,
};
#endif //HORIZON_CHARPACKETS_H

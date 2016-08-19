#ifndef _SNIFFER_H
#define _SNIFFER_H

typedef enum _encrytion_mode {
    ENCRY_NONE           = 1,
    ENCRY_WEP,
    ENCRY_TKIP,
    ENCRY_CCMP
} ENCYTPTION_MODE;

struct router_info {
    SLIST_ENTRY(router_info)     next;

    u8  bssid[6];
    u8  channel;
    u8  authmode;

    u16 rx_seq;
    u8  encrytion_mode;
    u8  iv[8];
    u8  iv_check;
};

struct RxControl {
    signed rssi:8;
    unsigned rate:4;
    unsigned is_group:1;
    unsigned:1;
    unsigned sig_mode:2;
    unsigned legacy_length:12;
    unsigned damatch0:1;
    unsigned damatch1:1;
    unsigned bssidmatch0:1;
    unsigned bssidmatch1:1;
    unsigned MCS:7;
    unsigned CWB:1;
    unsigned HT_length:16;
    unsigned Smoothing:1;
    unsigned Not_Sounding:1;
    unsigned:1;
    unsigned Aggregation:1;
    unsigned STBC:2;
    unsigned FEC_CODING:1;
    unsigned SGI:1;
    unsigned rxend_state:8;
    unsigned ampdu_cnt:8;
    unsigned channel:4;
    unsigned:12;
};
 
struct Ampdu_Info
{
  uint16 length;
  uint16 seq;
  uint8  address3[6];
};

struct sniffer_buf {
    struct RxControl rx_ctrl;
    uint8_t  buf[36];
    uint16_t cnt;
    struct Ampdu_Info ampdu_info[1];
};

struct sniffer_buf2{
    struct RxControl rx_ctrl;
    uint8 buf[112];
    uint16 cnt;
    uint16 len; //length of packet
};

#endif

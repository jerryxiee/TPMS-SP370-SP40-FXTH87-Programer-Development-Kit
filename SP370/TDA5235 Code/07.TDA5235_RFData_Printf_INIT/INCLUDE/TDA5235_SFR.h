/* SFR register addresses */
#ifndef SFRDEFINES_H
#define SFRDEFINES_H

#define SFR_A_MID0	0x000
#define SFR_A_MID1	0x001
#define SFR_A_MID2	0x002
#define SFR_A_MID3	0x003
#define SFR_A_MID4	0x004
#define SFR_A_MID5	0x005
#define SFR_A_MID6	0x006
#define SFR_A_MID7	0x007
#define SFR_A_MID8	0x008
#define SFR_A_MID9	0x009
#define SFR_A_MID10	0x00A
#define SFR_A_MID11	0x00B
#define SFR_A_MID12	0x00C
#define SFR_A_MID13	0x00D
#define SFR_A_MID14	0x00E
#define SFR_A_MID15	0x00F
#define SFR_A_MID16	0x010
#define SFR_A_MID17	0x011
#define SFR_A_MID18	0x012
#define SFR_A_MID19	0x013
#define SFR_A_MIDC0	0x014
#define SFR_A_MIDC1	0x015
#define SFR_A_IF1	0x016
#define SFR_A_WUC	0x017
#define SFR_A_WUPAT0	0x018
#define SFR_A_WUPAT1	0x019
#define SFR_A_WUBCNT	0x01A
#define SFR_A_WURSSITH1	0x01B
#define SFR_A_WURSSIBL1	0x01C
#define SFR_A_WURSSIBH1	0x01D
#define SFR_A_SIGDETSAT	0x024
#define SFR_A_WULOT	0x025
#define SFR_A_SYSRCTO	0x026
#define SFR_A_TOTIM_SYNC	0x027
#define SFR_A_TOTIM_TSI	0x028
#define SFR_A_TOTIM_EOM	0x029
#define SFR_A_AFCLIMIT	0x02A
#define SFR_A_AFCAGCD	0x02B
#define SFR_A_AFCSFCFG	0x02C
#define SFR_A_AFCK1CFG0	0x02D
#define SFR_A_AFCK1CFG1	0x02E
#define SFR_A_AFCK2CFG0	0x02F
#define SFR_A_AFCK2CFG1	0x030
#define SFR_A_PMFUDSF	0x031
#define SFR_A_AGCSFCFG	0x032
#define SFR_A_AGCCFG0	0x033
#define SFR_A_AGCCFG1	0x034
#define SFR_A_AGCTHR	0x035
#define SFR_A_DIGRXC	0x036
#define SFR_A_PKBITPOS	0x037
#define SFR_A_ISUPFCSEL	0x038
#define SFR_A_PDECF	0x039
#define SFR_A_PDECSCFSK	0x03A
#define SFR_A_PDECSCASK	0x03B
#define SFR_A_MFC	0x03C
#define SFR_A_SRC	0x03D
#define SFR_A_EXTSLC	0x03E
#define SFR_A_SIGDET0	0x03F
#define SFR_A_SIGDET1	0x040
#define SFR_A_SIGDETLO	0x041
#define SFR_A_SIGDETSEL	0x042
#define SFR_A_SIGDETCFG	0x043
#define SFR_A_NDTHRES	0x044
#define SFR_A_NDCONFIG	0x045
#define SFR_A_CDRP	0x046
#define SFR_A_CDRI	0x047
#define SFR_A_CDRRI	0x048
#define SFR_A_CDRTOLC	0x049
#define SFR_A_CDRTOLB	0x04A
#define SFR_A_TVWIN	0x04B
#define SFR_A_SLCCFG	0x04C
#define SFR_A_TSIMODE	0x04D
#define SFR_A_TSILENA	0x04E
#define SFR_A_TSILENB	0x04F
#define SFR_A_TSIGAP	0x050
#define SFR_A_TSIPTA0	0x051
#define SFR_A_TSIPTA1	0x052
#define SFR_A_TSIPTB0	0x053
#define SFR_A_TSIPTB1	0x054
#define SFR_A_EOMC	0x055
#define SFR_A_EOMDLEN	0x056
#define SFR_A_EOMDLENP	0x057
#define SFR_A_CHCFG	0x058
#define SFR_A_PLLINTC1	0x059
#define SFR_A_PLLFRAC0C1	0x05A
#define SFR_A_PLLFRAC1C1	0x05B
#define SFR_A_PLLFRAC2C1	0x05C
#define SFR_SFRPAGE	0x080
#define SFR_PPCFG0	0x081
#define SFR_PPCFG1	0x082
#define SFR_PPCFG2	0x083
#define SFR_RXRUNCFG0	0x084
#define SFR_RXRUNCFG1	0x085
#define SFR_CLKOUT0	0x086
#define SFR_CLKOUT1	0x087
#define SFR_CLKOUT2	0x088
#define SFR_RFC	0x089
#define SFR_BPFCALCFG0	0x08A
#define SFR_XTALCAL0	0x08C
#define SFR_XTALCAL1	0x08D
#define SFR_RSSIMONC	0x08E
#define SFR_ADCINSEL	0x08F
#define SFR_RSSIOFFS	0x090
#define SFR_RSSISLOPE	0x091
#define SFR_CDRDRTHRP	0x092
#define SFR_CDRDRTHRN	0x093
#define SFR_IM0	0x094
#define SFR_SPMAP	0x096
#define SFR_SPMIP	0x097
#define SFR_SPMC	0x098
#define SFR_SPMRT	0x099
#define SFR_SPMOFFT0	0x09A
#define SFR_SPMOFFT1	0x09B
#define SFR_SPMONTA0	0x09C
#define SFR_SPMONTA1	0x09D
#define SFR_SPMONTB0	0x09E
#define SFR_SPMONTB1	0x09F
#define SFR_EXTPCMD	0x0A4
#define SFR_CMC1	0x0A5
#define SFR_B_MID0	0x100
#define SFR_B_MID1	0x101
#define SFR_B_MID2	0x102
#define SFR_B_MID3	0x103
#define SFR_B_MID4	0x104
#define SFR_B_MID5	0x105
#define SFR_B_MID6	0x106
#define SFR_B_MID7	0x107
#define SFR_B_MID8	0x108
#define SFR_B_MID9	0x109
#define SFR_B_MID10	0x10A
#define SFR_B_MID11	0x10B
#define SFR_B_MID12	0x10C
#define SFR_B_MID13	0x10D
#define SFR_B_MID14	0x10E
#define SFR_B_MID15	0x10F
#define SFR_B_MID16	0x110
#define SFR_B_MID17	0x111
#define SFR_B_MID18	0x112
#define SFR_B_MID19	0x113
#define SFR_B_MIDC0	0x114
#define SFR_B_MIDC1	0x115
#define SFR_B_IF1	0x116
#define SFR_B_WUC	0x117
#define SFR_B_WUPAT0	0x118
#define SFR_B_WUPAT1	0x119
#define SFR_B_WUBCNT	0x11A
#define SFR_B_WURSSITH1	0x11B
#define SFR_B_WURSSIBL1	0x11C
#define SFR_B_WURSSIBH1	0x11D
#define SFR_B_SIGDETSAT	0x124
#define SFR_B_WULOT	0x125
#define SFR_B_SYSRCTO	0x126
#define SFR_B_TOTIM_SYNC	0x127
#define SFR_B_TOTIM_TSI	0x128
#define SFR_B_TOTIM_EOM	0x129
#define SFR_B_AFCLIMIT	0x12A
#define SFR_B_AFCAGCD	0x12B
#define SFR_B_AFCSFCFG	0x12C
#define SFR_B_AFCK1CFG0	0x12D
#define SFR_B_AFCK1CFG1	0x12E
#define SFR_B_AFCK2CFG0	0x12F
#define SFR_B_AFCK2CFG1	0x130
#define SFR_B_PMFUDSF	0x131
#define SFR_B_AGCSFCFG	0x132
#define SFR_B_AGCCFG0	0x133
#define SFR_B_AGCCFG1	0x134
#define SFR_B_AGCTHR	0x135
#define SFR_B_DIGRXC	0x136
#define SFR_B_PKBITPOS	0x137
#define SFR_B_ISUPFCSEL	0x138
#define SFR_B_PDECF	0x139
#define SFR_B_PDECSCFSK	0x13A
#define SFR_B_PDECSCASK	0x13B
#define SFR_B_MFC	0x13C
#define SFR_B_SRC	0x13D
#define SFR_B_EXTSLC	0x13E
#define SFR_B_SIGDET0	0x13F
#define SFR_B_SIGDET1	0x140
#define SFR_B_SIGDETLO	0x141
#define SFR_B_SIGDETSEL	0x142
#define SFR_B_SIGDETCFG	0x143
#define SFR_B_NDTHRES	0x144
#define SFR_B_NDCONFIG	0x145
#define SFR_B_CDRP	0x146
#define SFR_B_CDRI	0x147
#define SFR_B_CDRRI	0x148
#define SFR_B_CDRTOLC	0x149
#define SFR_B_CDRTOLB	0x14A
#define SFR_B_TVWIN	0x14B
#define SFR_B_SLCCFG	0x14C
#define SFR_B_TSIMODE	0x14D
#define SFR_B_TSILENA	0x14E
#define SFR_B_TSILENB	0x14F
#define SFR_B_TSIGAP	0x150
#define SFR_B_TSIPTA0	0x151
#define SFR_B_TSIPTA1	0x152
#define SFR_B_TSIPTB0	0x153
#define SFR_B_TSIPTB1	0x154
#define SFR_B_EOMC	0x155
#define SFR_B_EOMDLEN	0x156
#define SFR_B_EOMDLENP	0x157
#define SFR_B_CHCFG	0x158
#define SFR_B_PLLINTC1	0x159
#define SFR_B_PLLFRAC0C1	0x15A
#define SFR_B_PLLFRAC1C1	0x15B
#define SFR_B_PLLFRAC2C1	0x15C
#define SFR_CMC0	0x0A6

//���ӼĴ�����ַ
#define SFR_SN0				0xB6
#define SFR_SN1				0xB7
#define SFR_SN2				0xB8
#define SFR_SN3				0xB9


#define SFR_IS0				0xA8
#define SFR_PLDLEN			0xAD
#define RFPLLACC			0xAA

#endif

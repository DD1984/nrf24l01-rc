;
; D52 configuration file for hkr3000.bin
; Generated by D52 V3.4.1 on 2014/11/16 14:20
;
c 0000-087f	; Code space

b 0880-0887	    ; bit masks

c 0888-08cc	; Code space
b 08cd-08d8	; 8-bit data
a 08d9-08e6	; pointers
b 08e7-08ee	; 8-bit data
c 08ef-0b40	; Code space

b 0b41-0b93	; ram init data
l 0b41 ram_initialization_data


c 0b94-124b


; *********************************************************
; *********************************************************
; *********************************************************

;f 88 TCON
k 88 TCON_it0
k 89 TCON_ie0
k 8a TCON_it1
k 8b TCON_ie1
k 8c TCON_tr0
k 8d TCON_tf0
k 8e TCON_tr1
k 8f TCON_tf1

f 93 P0DIR
f 94 P1DIR

f 98 S0CON
k 98 S0CON_ri0
k 99 S0CON_ti0
k 9a S0CON_rb80
k 9b S0CON_tb80
k 9c S0CON_ren0
k 9d S0CON_sm20
k 9e S0CON_sm0
k 9f S0CON_sm1

f 99 S0BUF
f 9e P0CON
f 9f P1CON

f a1 PWMDC0
f a2 PWMDC1
f a3 CLKCTRL
f a4 PWRDWN
f a5 WUCON
f a7 MEMCON

f a8 IEN0
k a8 IEN0_ifp
k a9 IEN0_tf0
k aa IEN0_pwrfail
k ab IEN0_tf1
k ac IEN0_serial
k ad IEN0_tf2
k ae IEN0_6
k af IEN0_all

f a9 IP0
f aa S0RELL
f ab RTC2CPT01
f ac RTC2CPT10
f ad CLKLFCTRL
f ae OPMCON
f af WDSW

f b1 RSTREAS
f b2 PWMCON
f b3 RTC2CON
f b4 RTC2CMP0
f b5 RTC2CMP1
f b6 RTC2CPT00

f b8 IEN1
k b8 IEN1_rfready
k b9 IEN1_rfirq
k ba IEN1_spi_iic
k bb IEN1_wakeup
k bc IEN1_misc
k bd IEN1_tick
k be IEN1_6
k bf IEN1_exf2

f b9 IP1
f ba S0RELH
f bc SPISCON0
f be SPISSTAT
f bf SPISDAT

f c0 IRCON
k c0 IRCON_rfready
k c1 IRCON_rfiry
k c2 IRCON_spi_iic
k c3 IRCON_wakeup
k c4 IRCON_misc
k c5 IRCON_tick
k c6 IRCON_tf2
k c7 IRCON_exf2

f c1 CCEN
f c2 CCL1
f c3 CCH1
f c4 CCL2
f c5 CCH2
f c6 CCL3
f c7 CCH3

;f c8 T2CON
k c8 T2CON_t2i0
k c9 T2CON_t2i1
k ca T2CON_t2cm
k cb T2CON_t2r0
k cc T2CON_t2r1
k cd T2CON_i2fr
k ce T2CON_i3fr
k cf T2CON_t2ps

f c9 MPAGE
f ca CRCL
f cb CRCH
    f ce WUOPC1
f cf WUOPC0

;f d0 PSW
k d1 PSW_f1

f d1 ADCCON3
f d2 ADCCON2
f d3 ADCCON1
f d4 ADCDATH
f d5 ADCDATL
f d6 RNGCTL
f d7 RNGDAT

f d8 SERCON
k df SERCON_bd

f d9 W2SADR
f da W2DAT
f db COMPCON
f dd CCPDATIA
f de CCPDATIB
f df CCPDATO

f e1 W2CON1
f e2 W2CON0
f e4 SPIRCON0
f e5 SPIRCON1
f e6 SPIRSTAT
f e7 SPIRDAT

f e8 RFCON
k e8 RFCON_rfce
k e9 RFCON_rfcsn
k ea RFCON_rfcken

f e9 MD0
f ea MD1
f eb MD2
f ec MD3
f ed MD4
f ee MD5
f ef ARCON

f f8 FSR
k f8 FSR_0
k f9 FSR_1
k fa FSR_rdismb
k fb FSR_infen
k fc FSR_rdyn
k fd FSR_wen
k fe FSR_stp
k ff FSR_endebug

f f9 FPCR
f fa FCR
f fc SPIMCON0
f fd SPIMCON1
f fe SPIMSTAT
f ff SPIMDAT

; *********************************************************
; *********************************************************
; *********************************************************

k 92 LED_GREEN      ; p1.2
k 93 LED_RED        ; p1.3
k 86 BIND_BUTTON    ; p0.6

k 85 PORT_CH1       ; p0.5
k 87 PORT_CH2       ; p0.7
k 90 PORT_CH3       ; p1.0
k 91 PORT_CH4       ; p1.1

k 84 SCL            ; p0.4
k 83 SDA            ; p0.3


;=========================================================

r 0b rf_status
r 0d rf_detected
r 0c got_rf_payload
r 0e save_r7
r 0f save_r5

r 10 count_l
r 11 count_h

r 14 adr_0
r 15 adr_1
r 16 adr_2
r 17 adr_3
r 18 adr_4

r 1b pipe_no

r 1c adr_flag
r 1d adr_h
r 1e adr_l

r 24 rf_int_fired
r 25 div_16ms
r 2b factory
r 2c div_4ms
r 2d rf_data_avail

r 19 bind_state
r 1a bind_timeout
r 12 bind_blink_h
r 13 bind_blink_l

;=========================================================
;=========================================================
;=========================================================


! 000e OBSERVE_TX ?!
! 001e FIFO_STATUS
! 0024 Masks out TX_FULL and TX_EMPTY

l 002e i2c_eeprom_read_one_byte


l 004e init
# 004e ***************************************************************************
# 004e Initialization
# 004e ***************************************************************************

! 00c3 Enable the receiver


! 00d6 Enable Timer0 and Timer2 interrupts

l 00ee main
# 00ee ***************************************************************************
# 00ee MAIN LOOP
# 00ee ***************************************************************************

! 00df Bind switch checked at reset
! 00e9 Set channel 70 in factory mode?

l 0112 not_factory
l 0124 no_bind_button
l 012f read_fifo_loop

l 0143 payload_read
! 014c Enable Timer 1 interrupt (servo pulses)
l 014f no_rf_data_pending

l 0155 rcv_state_0
l 016f rcv_state_1
l 0191 rcv_state_2
l 01b1 rcv_state_end

# 0173 Start hopping
# 0194 Receiver locked

! 0181 T2 clock = f/12, Reload Mode 0
! 019f T2 clock = f/12, Reload Mode 0

# 01c2 More than 16 hops done: resync on first hop frequency

l 01d5 stick_data_handler
# 01d5 ***************************************************************************
# 01d5 This code below sets the servo pulse durations 0x55
# 01d5
# 01d5 It copies 8 bytes starting at payload to CH1..CH4,
# 01d5 swapping high/low byte along the way.
# 01d5 Note that CH4H is always 55 because it is a marker for stick data
# 01d5
# 01d5 Maybe the fs was added to the 4-channel version, limiting
# 01d5 the number of channels?
# 01d5 ***************************************************************************


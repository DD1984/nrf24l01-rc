;
; D52 configuration file for hk310.hex
; Generated by D52 V3.4.1 on 2014/11/13 17:38
;
c 0000-004d	; Code space

c 004e-043c	; Code space

c 043d-053e

c 053f-094c	; Code space

c 094d-09de
! 094d 094d-09de UNUSED CODE

c 09df-0a1d	; Code space

b 0a1e-0a25 ; bit masks
! 0a25 bit masks

c 0a26-0a6a	; Code space

c 0a6b-0aa3
! 0a6b 0a6b-0aa3 UNUSED CODE

c 0aa4-0aae	; Code space

c 0aaf-0ab3
! 0aaf 0aaf-0ab3 UNUSED CODE

c 0ab4-0cbb	; Code space

c 0cbc-0d0b
! 0cbc 0cbc-0d0b UNUSED CODE

b 0d0c-0d55 ; ram_initialization_data



c 0d56-0d98	; Code space

c 0d99-0ddb
! 0d99 0d99-0ddb UNUSED CODE

c 0ddc-0ecd	; Code space

c 0ece-0ef7

c 0ef8-0efe	; Code space

c 0eff-0f01	; 8-bit data

c 0f02-0f3b	; Code space

c 0f3c-0fa0

c 0fa1-0ffb	; Code space

c 0ffc-0ffe

c 0fff-1027	; Code space

c 1028-10c8

c 10c9-10ee	; Code space

c 10ef-1111

c 1112-11ac	; Code space
c 11ad-11c6
c 11c7-1221	; Code space
c 1222
c 1223-124c	; Code space

c 124d-127e

c 127f-1291	; Code space

c 1292-12f7

c 12f8-1310	; Code space

c 1311-1312
c 1313-131c	; Code space

c 131d-1334

c 1335-1340	; Code space

c 1341-1353

c 1354-1363	; Code space

c 1364-136e

c 136f-13a3	; Code space

c 13a4-13f3 ; 8-bit data
! 13a4 13a4-13f3 UNUSED CODE

c 13f4-1411	; Code space

c 1412-1413	; 8-bit data
c 1414-141f	; Code space
c 1420-1423	; 8-bit data
c 1424-1426	; Code space
c 1427-1439	; 8-bit data
c 143a-143f	; Code space
c 1440-1445	; 8-bit data
c 1446-1448	; Code space

i 1449-3ffe	; ignore data

; ******************************************************
; ******************************************************
; ******************************************************


! 0000 Vector: Reset
! 0003 Vector: Interrupt from pin GP INT0, GP INT1 or GP INT2
! 000b Vector: Timer 0 overflow
! 0013 Vector: Power Failure
! 001b Vector: Timer 1 overflow
! 0023 Vector: Serial channel
! 002b Vector: Timer 2 overflow or External reload
! 0043 Vector: RF SPI ready
! 004b Vector: RF Interrupt
;l 0053 Vector: SPI, I2C

; ******************************************************
; ******************************************************
; ******************************************************


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

f d8 ADCON
k df ADCON_bd

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


; ******************************************************
; ******************************************************
; ******************************************************


k 90 PORT_SCL       ; p1.0
k 92 PORT_SDA       ; p1.2
k 94 PORT_TX_OFF    ; p1.4

; ******************************************************
; ******************************************************
; ******************************************************

r 1b model_count
r 1c count
r 1f save_r2
r 1e save_r3_r7



; ******************************************************
; ******************************************************
; ******************************************************


; x X0041 10 bytes of data sent over-the-air! BUT: other areas sent too!




; ******************************************************
; ******************************************************
; ******************************************************





l 000e rf_setup_address_width
# 000e ************************************************************************
! 001e SETUP_AW

l 004e init
# 004e ************************************************************************
# 004e Init
# 004e ************************************************************************

! 6c Wait for the XTAL oscillator
l 00ae main
# 00ae ***************************************************************************
# 00ae MAIN LOOP
# 00ae ***************************************************************************

l 00b5 servo_data_received
# 00b5 ***************************************************************************
l 00c0 copy_from_uart_buffer
# 00c0 ***************************************************************************
l 00f2 process_stick_data
# 00f2 ***************************************************************************
! 00f2 seems to do packing of data

l 0228 check_if_failsafe_data
# 0228 ***************************************************************************

l 0287 stick_data_processed
# 0287 ***************************************************************************

l 028a check_model_cmd_received
# 028a ***************************************************************************
l 0291 process_new_model
# 0291 ***************************************************************************
! 0294 payload+1: contains the model number!

l 02a0 change_model
# 02a0 ***************************************************************************

l 02bf init_eeprom_bind_data
# 02bf ***************************************************************************

l 0349 format_eeprom
# 0349 ***************************************************************************

l 043d rf_interrupt_handler
# 043d ************************************************************************
# 043d RF Interrupt Handler
# 043d ************************************************************************

! 0462 Flush if MAX_RT
! 046c Process TX_DS
! 047a X0013 is more than 2
! 04a0 X0013 is 2
! 04ef X0013 is 3

! 04af Channel 51h has a special meaning: used for Binding with fixed address 12:23:23:45:78

l 053f timer0_handler
# 053f ************************************************************************
# 053f Timer0 Interrupt Handler
# 053f ************************************************************************

l 062e xxxxxxxxxxxxxxxx

l 070f uart_handler
# 070f ************************************************************************
# 070f UART Interrupt Handler
# 070f ************************************************************************
l 0722 uart_receive
! 072d Wait for first byte, which is FF
; s X0091 Receive_state
r 05e f_model_no
; s X0094 model_no_data
r 05f f_servo_data
; s X009a is servo_data
; s X0002.. is copied servo data in mainloop

; UART buf is copied from 009a.. to 0002.. if flag 5fh is set

l 0808 get_indirect_dptr_plus_r1_r2
# 0808 ***************************************************************************
# 0808 get_indirect_dptr_plus_r1_r2
# 0808 r3: flag; 0 = return @dptr+r1, 1 = return @dptr+r2:r1
# 0808 ***************************************************************************

l 0835 set_indirect_r1_r2
# 0835 ***************************************************************************
# 0835 set_indirect_r1_r2
# 0835 r3: flag; 0 = store at @r1, 1 = store at @r2:r1
# 0835 ***************************************************************************


l 0847 mul_16
# 0847 ***************************************************************************
! 0847 used in servo data packing?!

l 0859 div_16
# 0859 ***************************************************************************


l 09df reset_ram
# 09df ************************************************************************
# 09df Reset
# 09df ************************************************************************

l 0bac read_current_model_bind_data_from_eeprom
# 0bac ************************************************************************

l 0d0c ram_initialization_data
# 0d0c ************************************************************************
l 09eb init_ljmp

! 0d0f X0012 = #0
! 0d13 X0001 = #0
! 0d17 X003f = #0
! 0d1b X0013 = #0
! 0d22 22h = #12h, 23h = #23h, 24h = #23h, 25h =#45H, 26h = #78h  SPECIAL ADDRESS sent on ch51h for binding!
! 0d2a X004b = #55h, X004c..4f = #0
! 0d2d 2ah = #0
! 0d30 29h = #0
! 0d34 X00a8 = #0
! 0d38 X0093 = #0
! 0d3c X0092 = #0
! 0d40 X0091 = #0
! 0d43 5fh = #0
! 0d46 5eh = #0
! 0d51 X00a0..A8 = #0f82f (4 times 1.5ms) BUT: is overwritten in init!
! 0d54 63h = #0
! 0d55 end marker


l 0add rf_modify_config_bit
# 0add ***************************************************************************
# 0add rf_modify_config_bit
# 0add
# 0add r7: bit number in the CONFIG reg.  r5: new bit value
# 0add ***************************************************************************

l 09e2 clear_ram

l 0e95 init_serial
# 0e95 ***************************************************************************

! 0e97 enable reception
! 0e99 8-bit UART
! 0ebb r7 = 4: 9600 Baud
! 0eb5 r7 = 6: 38400 Baud
! 0ec1 r7 = 5: 19200 Baud
! 0eaf r7 = 7: 57600 Baud?

l 0ece rf_get_no_bytes_in_data_pipe
# 0ece ***************************************************************************

l 0ddc init_rf
# 0ddc ***************************************************************************

l 0e58  rf_set_data_rate
# 0e58 ***************************************************************************

l 0f05 spi_write_stream
# 0f05 ***************************************************************************

l 11f5 init_gpio
# 11f5 ***************************************************************************

l 08ae ic2_write_address
# 08ae ***************************************************************************
l 1238 i2c_read_byte_from_device
# 1238 ***************************************************************************
l 0fcf i2c_start
# 0fcf ***************************************************************************
l 08b6 i2c_write_byte
# 08b6 ***************************************************************************
l 0b48 i2c_read_byte
# 0b48 ***************************************************************************
l 1135 i2c_stop
# 1135 ***************************************************************************
l 0c6a i2c_has_write_finished
# 0c6a ***************************************************************************
l 120c i2c_write_byte_to_device
# 120c ***************************************************************************

l 0fa1 make_hop_data
# 0fa1 ***************************************************************************

l 10c9 make_bind_data
# 10c9 ***************************************************************************

l 1155 rf_set_power
# 1155 ***************************************************************************

l 1174 write_byte_to_eeprom
# 1174 ***************************************************************************
# 1174 In: r6:r7 address   r5: data
# 1174 ***************************************************************************

l 139a rf_get_number_of_address_bytes
! 139a SETUP_AW
# 139a ***************************************************************************
# 139a Out: R7: Number of address bytes
# 139a ***************************************************************************



l 1193 read_byte_from_eeprom
# 1193 ***************************************************************************
# 1193 In: r6:r7 address to read from
# 1193 ***************************************************************************

l 11c7 spi_write_register
# 11c7 ***************************************************************************
# 11c7 In: R7: register number, R5: value
# 11c7 ***************************************************************************

l 124d spi_set_rf_channel
# 124d ***************************************************************************
# 124d In: R7: channel number
# 124d ***************************************************************************


l 12f8 spi_read_register
# 12f8 ***************************************************************************
# 12f8 In: A: register    Out: R7: read value
# 12f8 ***************************************************************************

l 12a2 read_lf_clock_phase
# 12a2 ***************************************************************************
l 12b2 is_lf_clock_ready
# 12b2 ***************************************************************************
l 12c2 set_started_oscillators
# 12c2 ***************************************************************************
l 1292 set_keep_osc_in_retention_mode
# 1292 ***************************************************************************
l 1341 set_system_clock_frequency
# 1341 ***************************************************************************
l 134d set_lf_clock_frequency
# 134d ***************************************************************************


l 1359 get_osc_status
# 1359 ************************************************************************
# 1359 Returns 2 if the XTAL OSC is ready, otherwise 1 if running from the RC OSC
# 1359 ************************************************************************

l 1335 read_current_model_no_from_eeprom
# 1335 ************************************************************************
l 1390 init_timer0
# 1359 ************************************************************************

l 0d56 rf_set_crc
# 0d56 ***************************************************************************
# 0d56 In: R7: Number of bytes of CRC to use, 0 to turn it off
# 0d56 ***************************************************************************

l 1305 rf_get_and_clear_interrupts
# 1305 ***************************************************************************
l 12d1 rf_get_lost_packet_count
# 12d1 ***************************************************************************
l 0c10 rf_enable_data_pipes
# 0c10 ***************************************************************************
l 0e1b rf_get_or_set_address
# 0e1b ***************************************************************************
l 1112 rf_set_power_up
# 1112 ***************************************************************************
l 1311 rf_is_rx_fifo_full
# 1311 ***************************************************************************
l 131d rf_is_tx_fifo_full
# 131d ***************************************************************************
l 1329 rf_enable_dynamic_payload
# 1329 ***************************************************************************
l 1364 rf_is_tx_fifo_empty
# 1364 ***************************************************************************
l 13a4 rf_is_rx_fifo_empty
# 13a4 ***************************************************************************
l 13ae rf_get_rx_fifo_status
# 13ae ***************************************************************************
l 12de rf_get_tx_fifo_status
# 12de ***************************************************************************
l 13b8 rf_get_retransmit_count
# 13b8 ***************************************************************************
l 13c2 rf_get_power_detected
# 13c2 ***************************************************************************
l 13cc rf_write_ack_payload
# 13cc ***************************************************************************
l 13e0 rf_reuse_tx_payload
# 13e0 ***************************************************************************
l 13ea rf_flush_rx
# 13ea ***************************************************************************
l 13f4 rf_flush_tx
# 13f4 ***************************************************************************
l 142e rf_get_observe_tx
# 142e ***************************************************************************
l 1434 rf_get_fifo_status
# 1434 ***************************************************************************
l 143a rf_get_rx_payload_width
# 143a ***************************************************************************
l 13fe rf_get_status
# 13fe ***************************************************************************
l 13d6 rf_get_data_pipe_ready
# 13d6 ***************************************************************************


l 137a rng_power_on_off
# 137a ***************************************************************************
l 1385 rng_bias_corrector_on_off
# 1385 ***************************************************************************
l 1282 rng_is_result_ready
# 1282 ***************************************************************************
l 1446 rng_get_random_byte
# 1446 ***************************************************************************

l 1408 spi_write
# 1408 ***************************************************************************
l 140a _spi_write_loop
# 140a ***************************************************************************

l 1419 rf_write_tx_payload
# 1419 ***************************************************************************
! 141b W_TX_PAYLOAD

; x X00a8 contains current active model no stored in eeprom (value from address 0)
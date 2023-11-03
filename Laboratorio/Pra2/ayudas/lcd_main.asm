;*******************************************************************
;* This stationery serves as the framework for a user application. *
;* For a more comprehensive program that demonstrates the more     *
;* advanced functionality of this processor, please see the        *
;* demonstration applications, located in the examples             *
;* subdirectory of the "Freescale CodeWarrior for HC08" program    *
;* directory.                                                      *
;*******************************************************************

; Include derivative-specific definitions
            INCLUDE 'derivative.inc'
            
;
;
            XDEF _Startup
            ABSENTRY _Startup
            
; *****		CONSTANTS		*****
us_delay	EQU	2000	;delay 2 ms approx. It is valid for all 
				;commands

; ***********************************************

		ORG    Z_RAMStart
		
;**********		VARIABLES		**********
;LCD
RS_E:			DS.B   1	; RS and E LCD
KEY_decimal:	DS.B   1	; Final value to be printed
; ****************************************

;
; Section to define variables out cero page
;
		ORG    RAMStart

; Section program code 
		ORG   ROMStart
 _Startup:
 		; ********** CONFIGURATIONS WATCHDOG AND STACK **********
		; Power off WatchDOG
		LDA   #$20
		STA   SOPT1
		; Set the SP to the last RAM position
		LDHX #RAMEnd+1
		TXS 				
		
		;****************************************************
		;*****		CLEAR VARIABLES AND REGISTERS		*****
			;**************************************************** 
		CLRA						
		CLRX						
		CLRH
		
		CLR KEY_decimal		;Write in the DDRAM
		CLR	RS_E			;LCD VARIABLE
		
		;*****		INITIALIZING OUTPUT PORTS		*****
		;*****		LCD PORT		*****
		MOV #$00,PTBD		; Ports LCD D7,...,D0  ; 
		MOV #$FF, PTBDD		; Set the port like output
		
		MOV #$00,PTAD		;000000-RS-E,
						;lcd control lines. 
						;
		MOV #$FF, PTADD		; Set the port like output
		
		;*****			Set LCD to initial state				*****
		JSR LCD_inicio
		;****************************************************			
		
; Program body
main:
	; Write all the program logic here
	MOV #$1,KEY_decimal		;1
	JSR conversion_ASCII

	MOV #$3,KEY_decimal		;3
	JSR conversion_ASCII

	MOV #$5,KEY_decimal		;5
	JSR conversion_ASCII

	MOV #$7,KEY_decimal		;7
	JSR conversion_ASCII

	MOV #$9,KEY_decimal		;9
	JSR conversion_ASCII
	
	MOV #$F8,KEY_decimal	;(
	JSR conversion_ASCII
	
	MOV #$F9,KEY_decimal	;)
	JSR conversion_ASCII
	
	MOV #$FA,KEY_decimal	;*
	JSR conversion_ASCII
	
	MOV #$FB,KEY_decimal	;+
	JSR conversion_ASCII
	
	MOV #$FD,KEY_decimal	;-
	JSR conversion_ASCII
	
	MOV #$FF,KEY_decimal	;/
	JSR conversion_ASCII
	
	MOV #$0D,KEY_decimal	;=
	JSR conversion_ASCII	
			
Final:	BRA Final ; End of program body

;*****		SUBRUTINES OR FUNCTIONS		*****

 ;void Delay_LCD( us) {
Delay_LCD:
		PSHH ;guarda H into stack
		PSHX   	   
		LDHX  #us_delay;
_delay: 	AIX   #-1;h:x - 1    // 2
			CPHX  #0;     // 3
			BNE   _delay;
			PULX   
			PULH   
			RTS    

;***************		SUBRUTINE LCD INITIALIZATION		***************
LCD_inicio:
	JSR Delay_LCD
	MOV #$01,PTBD	; Clear LCD screen
	BSR habilitar	
	
	MOV #$38,PTBD	; 8 bits input LCD and two lines
	BSR habilitar	
	
	MOV #$0E,PTBD	; Turn on display and cursor
	BSR habilitar	
	
	MOV #$06,PTBD	; Mode increment direction
	BSR habilitar	
	
	MOV #$02,RS_E	; Enable Write
	RTS
	
conversion_ASCII:
		PSHX		
		PSHH		 
		PSHA		
		;**********************************
		LDA KEY_decimal
		ADD #$30
		STA PTBD	
		BSR habilitar
		;**********************************
		PULA		
		PULH		
		PULX				
		RTS
	
	;***************		ENABLE THE INSTRUCTIONS IN THE LCD			***************
habilitar:
		INC RS_E
		MOV RS_E,PTAD	;pone un 1 en salida
		BSR Delay_LCD  ;retardo		
		DEC RS_E
		MOV RS_E,PTAD  ;pone un cero en salida
		BSR Delay_LCD
		RTS
		
		;***************		CONVERSION TO ASCII			***************

     

;*                 Interrupt Vectors                          *
;**************************************************************

            ORG	$FFFE		
			DC.W  _Startup			; Reset

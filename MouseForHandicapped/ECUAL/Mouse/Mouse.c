/*
 * Mouse.c
 *
 *  Author: Mahmoud Ayoub
 */ 

#include "Mouse.h"
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM const char usbHidReportDescriptor[52] = { /* USB report descriptor, size must match usbconfig.h */
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x02,                    // USAGE (Mouse)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x09, 0x01,                    //   USAGE (Pointer)
	0xA1, 0x00,                    //   COLLECTION (Physical)
	0x05, 0x09,                    //     USAGE_PAGE (Button)
	0x19, 0x01,                    //     USAGE_MINIMUM
	0x29, 0x03,                    //     USAGE_MAXIMUM
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x95, 0x03,                    //     REPORT_COUNT (3)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x75, 0x05,                    //     REPORT_SIZE (5)
	0x81, 0x03,                    //     INPUT (Const,Var,Abs)
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (X)
	0x09, 0x31,                    //     USAGE (Y)
	0x09, 0x38,                    //     USAGE (Wheel)
	0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
	0x25, 0x7F,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x03,                    //     REPORT_COUNT (3)
	0x81, 0x06,                    //     INPUT (Data,Var,Rel)
	0xC0,                          //   END_COLLECTION
	0xC0,                          // END COLLECTION
};

static report_t reportBuffer;
static int      sinus = 7 << 6, cosinus = 0;
static unsigned char    idleRate;   /* repeat rate for keyboards, never used for mice */

static void advanceCircleByFixedAngle(void)
{
	char    d;

	#define DIVIDE_BY_64(val)  (val + (val > 0 ? 32 : -32)) >> 6    /* rounding divide */
	reportBuffer.dx = d = DIVIDE_BY_64(cosinus);
	sinus += d;
	reportBuffer.dy = d = DIVIDE_BY_64(sinus);
	cosinus -= d;
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;

    /* The following requests are never used. But since they are required by
     * the specification, we implement them in this example.
     */
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        DBG1(0x50, &rq->bRequest, 1);   /* debug output: print our request */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (void *)&reportBuffer;
            return sizeof(reportBuffer);
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

void Mouse_init (void) {
	unsigned char i = 0 ; 
	 wdt_enable(WDTO_1S);
    /* If you don't use the watchdog, replace the call above with a wdt_disable().
     * On newer devices, the status of the watchdog (on/off, period) is PRESERVED
     * OVER RESET!
     */
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    odDebugInit();
    DBG1(0x00, 0, 0);       /* debug output: main starts */
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
	
	 i = 0;
	 while(--i){             /* fake USB disconnect for > 250 ms */
	   wdt_reset();
	   _delay_ms(1);
	  }
	 usbDeviceConnect();
	 sei();
	 DBG1(0x01, 0, 0);       /* debug output: main loop starts */
	
	 
}
void Mouse_MoveLeft(void) {
	reportBuffer.dx = -1 ;
}
void Mouse_MoveRight(void) {
	reportBuffer.dx = 1 ; 
}
void Mouse_MoveUp(void) {
	reportBuffer.dy = -1 ; 
}
void Mouse_MoveDown(void) {
	reportBuffer.dy = 1 ;
}
void Mouse_RightClick(void) {
	reportBuffer.buttonMask = 1 ; 
}
void Mouse_LeftClick(void) {
	reportBuffer.buttonMask = 2 ;
}
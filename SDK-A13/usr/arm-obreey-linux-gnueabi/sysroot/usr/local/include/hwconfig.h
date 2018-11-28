/*
 * hwconfig.h
 *
 *  Created on: Jan 17, 2017
 *      Author: a.bilinets@gmail.com
 */

#ifndef SRC_HWCONFIG_H_
#define SRC_HWCONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <linux/input.h>

#define HWCONFIG_PATH "/etc/hwconfig"
#ifdef EMULATOR
#undef HWCONFIG_PATH
#define HWCONFIG_PATH "./system/config/hwconfig"
#endif

typedef enum {
	PLATFORM_WRONG = 0,
	PLATFORM_MX6SL = 5,
	PLATFORM_A13 = 14,
	PLATFORM_B288 = 16,
} platform_id_t;

typedef enum {
	DEVICE_WRONG = 0,
	DEVICE_631 = 5,
	DEVICE_641 = 17,
	DEVICE_627 = 18,
	DEVICE_614 = 19,
	DEVICE_615 = 20,
	DEVICE_740 = 21,
	DEVICE_616 = 22,
	DEVICE_632 = 23,
	DEVICE_626 = 24,
} device_id_t;

// ================ display and epd controller ==============

typedef enum {
	DISPLAY_6INCH = 0,
	DISPLAY_5INCH,
	DISPLAY_8INCH,
	DISPLAY_9INCH,
	DISPLAY_6INCH_758, // display 1024x758 6" HD
	DISPLAY_8TRITON, // display 1800x800 8"
	DISPLAY_8INCH_1200, // display 1600x1200 8"
	DISPLAY_4INCH_480_800 = 8, // display 480x800 4.3"
	DISPLAY_6INCH_1072_1448, // display 1448x1072 6"
	DISPLAY_7INCH_1872_1404, // display 1404x1872 7"
} display_id_t;

typedef enum {
	EPDC_NONE = 0,
	EPDC_IMX = 3,
	EPDC_ALLWINNER_A13 = 5,
	EPDC_ALLWINNER_B288 = 6,
} epdc_id_t;

#define UPDATE_MODE_PARTIAL   0x0
#define UPDATE_MODE_FULL      0x1
#define UPDATE_MODE_PARTIALHQ 0x2
#define UPDATE_MODE_FULLHQ    0x3

//======= input devices ============

typedef enum {
  KEYBOARD_NTX600 = 0,
  KEYBOARD_POCKET360 = 1,
  KEYBOARD_COOKIE = 2,
  KEYBOARD_DIGITEKA = 3,
  KEYBOARD_EP1234 = 4,
  KEYBOARD_EP7 = 5,
  KEYBOARD_POCKET650 = 6,
  KEYBOARD_POCKET840 = 7,
  KEYBOARD_POCKET630 = 8,
  KEYBOARD_POCKET420 = 9,
  KEYBOARD_POCKET620 = 10,
  KEYBOARD_POCKET641 = 11, //like 626, but without standart power button. Power button is KEY_MENU
  KEYBOARD_POCKET627 = 12,
  KEYBOARD_POCKET611 = 14,
  KEYBOARD_POCKET613 = 15,
  KEYBOARD_POCKET515 = 16,
  KEYBOARD_POCKET624 = 17,
  KEYBOARD_POCKET631 = 18,
  KEYBOARD_POCKET740 = 19,
  KEYBOARD_POCKET616 = 20,
  KEYBOARD_POCKET632 = 21,
} keyboard_id_t;

typedef enum {
	TOUCHPANEL_NONE = 0,
	TOUCHPANEL_IR_zFORCE = 4, //631
	TOUCHPANEL_ELAN_eKTF2227 = 8, //626, 641
	TOUCHPANEL_ELAN_eKTF2232 = 16, //627
	TOUCHPANEL_TT21XXX= 17, //632
	TOUCHPANEL_FT5X = 18, //626 CY8CTMA30
	TOUCHPANEL_CYTTSP4 = 19, //626 CY8CTMA4

} touchpanel_id_t;

typedef enum {
	SLIDER_NONE = 0,
} slider_id_t;

typedef enum {
	GYROSCOPE_NONE = 0,
	GYROSCOPE_HWEVT = 10, //SC7A20 (740 dev)
} gyroscop_id_t;

// ============== peripherals ===================

typedef enum audio_e {
	AUDIO_NONE = 0,
	AUDIO_OSS,

	/*
	 * Static hardware alsa configuration (without virtual audio card).
	 */
	AUDIO_ALSA = 4,

	/*
	 * Dynamic audio configuration, used for devices with hardware and BT(a2dp) audio output.
	 * With snd-aloop driver as virtual sound card.
	 */
	AUDIO_ALOOP,
} audio_id_t;

typedef enum {
	USB_NONE = 0,
	USB_INTERNAL = 3 //using testscript
} usb_id_t;

typedef enum {
	FRONTLIGHT_NONE = 0,
	FRONTLIGHT_PWM,
	FRONTLIGHT_DUAL, //hwlib double channel with software ramp up/down brightness value
	FRONTLIGHT_SINGLE, //hwlib single channel with software ramp up/down brightness value
	FRONTLIGHT_DUAL_HW_DIMMING, //hwlib double channel with HW ramp up/down brightness value
	FRONTLIGHT_SINGLE_HW_DIMMING //hwlib single channel with HW ramp up/down brightness value
} frontlight_id_t;

typedef enum {
	LIGHTSENSOR_NONE = 0,
} lightsensor_id_t;

// =============== communications =============

typedef enum {
	BLUETOOTH_NONE = 0,
	BLUETOOTH_RTL8761 = 6,
} bluetooth_id_t;

typedef enum {
	WIFI_NONE = 0,
	WIFI_RTL8188EU = 8,
	WIFI_RTL8189FS = 11,
	WIFI_XRADIO = 12, //internal b288 wifi driver
} wifi_id_t;

typedef enum {
	GSM_NONE = 0,
} gsm_id_t;

//========================

bool init_hwconfig(void);

device_id_t device_ID(void); //index
platform_id_t device_platform(void);
unsigned int device_number(void);

display_id_t device_display(void);
unsigned int device_display_height(void);
unsigned int device_display_width(void);
unsigned int device_display_scanline(void); //deprecated...not configured
unsigned int device_display_dpi(void);
uint8_t device_display_position(void);

typedef struct {
	int version;
	int type;
	int depth;
	int fd;
	uint8_t *framebuffer;
	int width;
	int height;
	int scanline;
	int orientation;
	uint32_t memsize;
	void (*rotate)(int value);
	int  (*update)(int x, int y, int w, int h, int wf, int mode);
	int  (*busy)(void);
    void (*sync)(void);
    void (*lock)(void);
    void (*unlock)(void);
} epdc_instance_t;

epdc_id_t device_epdc(void);
epdc_instance_t *device_epdc_init(void);

keyboard_id_t device_keyboard(void);
touchpanel_id_t device_touchpanel(void);
bool device_has_touchpanel(void);

typedef enum {
	HWKEY_BACK =       0x00000001,
	HWKEY_DELETE =     0x00000002,
	HWKEY_LEFT =       0x00000004,
	HWKEY_MENU =       0x00000008,
	HWKEY_MUSIC =      0x00000010,
	HWKEY_OK =         0x00000020,
	HWKEY_RIGHT =      0x00000040,
	HWKEY_PLUS =       0x00000080,
	HWKEY_MINUS =      0x00000100,
	HWKEY_DOWN =       0x00000200,
	HWKEY_UP =         0x00000400,
	HWKEY_PREV =       0x00000800,
	HWKEY_NEXT =       0x00001000,
	HWKEY_NEXT2 =      0x00002000,
	HWKEY_POWER =      0x00004000,
	HWKEY_PREV2 =      0x00008000,
	HWKEY_HOME =       0x00010000,
	HWKEY_PLUS2 =      0x00080000,
	HWKEY_MINUS2 =     0x00100000,
	HWKEY_ZOOMIN =     0x00200000,
	HWKEY_ZOOMOUT =    0x00400000,
	HWKEY_COVEROPEN =  0x01000000,
	HWKEY_COVERCLOSE = 0x02000000,
} hwkey_t;

int device_input_init(void);
int device_input_read(struct input_event *ev, int maxcount, int timeout_ms);
int device_keyboard_translate(struct input_event *ev, unsigned long *keymask);
unsigned long device_keyboard_buttons(void);
unsigned long device_keyboard_state(void);
const int *device_touchpanel_getmatrix(void);

slider_id_t device_slider(void);
bool device_has_slider(void);

gyroscop_id_t device_gyroscope(void);
bool device_has_gyroscope(void);

audio_id_t device_audio(void);
bool device_has_audio(void);

bool device_has_extcard(void);

usb_id_t device_usb(void);
bool device_has_usb(void);
bool device_has_usbhost(void);

frontlight_id_t device_frontlight(void);
bool device_has_frontlight(void);

#define HWLIB_FRONTLIGHT_CHANNEL_MAX 3
#define INKVIEW_FL_BRIGHTNESS_MAX 100
#define INKVIEW_FL_COLOR_MAX 100

typedef struct frontlight_ctrl_s {
	const int vesion;

	//set brightness in range from 0 to (*get_max_brightness)(void); put @value to -1 for turn off
	int (*set_brightness)(int value);
	int (*get_brightness)(void);

	//returns max brightness value
	int (*get_max_brightness)(void);

	//set color in range from 0 to (*get_max_brightness)(void)
	int (*set_color)(int value);
	int (*get_color)(void);
	int (*get_max_color)(void);

	//internal data
	void *data;

} frontlight_ctrl;

frontlight_ctrl *device_frontlight_init(void);

lightsensor_id_t device_lightsensor(void);
bool device_has_lightsensor(void);

bluetooth_id_t device_bluetooth(void);
bool device_has_bluetooth(void);

wifi_id_t device_wifi(void);
bool device_has_wifi(void);

gsm_id_t device_gsm(void);
bool device_has_gsm(void);

bool device_suspend(bool deep);
bool device_set_wakealarm(int seconds);

typedef struct {

		/*
		 * Led on\off switch path
		 */
		const char *switch_path;

		/*
		 * Trigger node path. Used for turn off power led when battery is charged.
		 * If it is not filled, then trigger will not be used
		 */
		const char *trigger_path;

		/*
		 * Name of charging trigger. It is used to turn off led when charging done (battery full)
		 */
		const char *charging_trigger;

} power_led_cfg_t; //device power led configuration

//get power led configuration
const power_led_cfg_t *device_power_led_cfg(void);

#endif /* SRC_HWCONFIG_H_ */

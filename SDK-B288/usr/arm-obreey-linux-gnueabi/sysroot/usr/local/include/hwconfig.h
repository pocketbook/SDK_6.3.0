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
	DEVICE_840,
	DEVICE_840_2,
	DEVICE_740_2,
	DEVICE_1040,
	DEVICE_606 = 29,
	DEVICE_633,
	DEVICE_628,
	DEVICE_741,
	DEVICE_617,
	DEVICE_970,
	DEVICE_700,
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
	DISPLAY_10INCH_1872_1404, //display 1404x1872 10.3"
	DISPLAY_9INCH_1200_825, //display 1200x825 9.7"
	DISPLAY_7INCH_1264_1680
} display_id_t;

typedef enum {
	EPDC_NONE = 0,
	EPDC_IMX = 3,
	EPDC_ALLWINNER_A13 = 5,
	EPDC_ALLWINNER_B288 = 6,
} epdc_id_t;

typedef enum {
	COLORMASK_NONE = 0,
	COLORMASK_CFA = 1,
	COLORMASK_CFA2 = 2,
} colormask_t;

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
  KEYBOARD_POCKET1040 = 22, //like 632, but without standart power button. Power button is KEY_MENU
  KEYBOARD_POCKET970,
  KEYBOARD_POCKET617,
  KEYBOARD_POCKET700
} keyboard_id_t;

typedef enum {
	TOUCHPANEL_NONE = 0,
	TOUCHPANEL_IR_zFORCE = 4, //631
	TOUCHPANEL_ELAN_eKTF2227 = 8, //626, 641
	TOUCHPANEL_FT5X_840 = 9, //840_1
	TOUCHPANEL_ELAN_eKTF2232 = 16, //627 ETKF2232ALW with GoldLeap lamination
	TOUCHPANEL_TT21XXX = 17, //632
	TOUCHPANEL_FT5X = 18, //626 CY8CTMA30
	TOUCHPANEL_CYTTSP4 = 19, //626 CY8CTMA4
	TOUCHPANEL_TMA448 = 20, //1040
	TOUCHPANEL_TT41701 = 21, //740; 740-2; TT41701 TrueTouch
	TOUCHPANEL_ELAN_eKTF2232ALW, //ETKF2232ALW 627 updated tp with Yitoa lamination
	TOUCHPANEL_FT6336U,
	TOUCHPANEL_FT5726, //970
	TOUCHPANEL_FT5426, //632
	TOUCHPANEL_eKTH3908F,
	TOUCHPANEL_FT5436 //700
} touchpanel_id_t;

typedef enum {
	SLIDER_NONE = 0,
	SLIDER_HWEVT,
} slider_id_t;

typedef enum {
	GYROSCOPE_NONE = 0,
	GYROSCOPE_HWEVT = 10, //SC7A20 (740 dev)
} gyroscop_id_t;

// ============== peripherals ===================

// ===== audio ====
typedef enum audio_e {
	AUDIO_NONE = 0,
	AUDIO_OSS,

	/*
	 * Static hardware alsa configuration (without virtual audio card).
	 * Without hp detection or hp disconnect event only.
	 * Audio have to start playing without hp detection.
	 */
	AUDIO_ALSA_NO_HP_DETECTION = 3,

	/*
	 * Static hardware alsa configuration (without virtual audio card).
	 */
	AUDIO_ALSA = 4,

	/*
	 * Dynamic audio configuration, used for devices with hardware and BT(a2dp) audio output.
	 * With snd-aloop driver as virtual sound card.
	 */
	AUDIO_ALOOP,

	/*
	 * Same as before, but also has built-in speaker
	 */
	AUDIO_ALOOP_WITH_SPEAKER
} audio_id_t;

audio_id_t device_audio(void);
bool device_has_audio(void);

/*
 * Detection of attach/detach HP. It is used periodical polling of status file.
 */
typedef struct hp_detect_cfg_s {
	/*
	 * path to file node which contains hp status
	 */
	const char *path;
	/*
	 * if status which is read from @path equals @attach_phrase system assumes than hp is connected
	 */
	const char *attach_phrase;
	/*
	 * invert hp status
	 */
	bool inverted;
} hp_detect_cfg_t;
const hp_detect_cfg_t *device_hp_detect_cfg(void);

// ===== usb ====
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
colormask_t  device_display_colormask(void);
unsigned int device_display_height(void);
unsigned int device_display_width(void);
unsigned int device_display_scanline(void); //deprecated...not configured
unsigned int device_display_dpi(void);
uint8_t device_display_position(void);

typedef enum {
	WAVEFORM_INIT  = 0,
	WAVEFORM_DU    = 1,
	WAVEFORM_GC16  = 2,
	WAVEFORM_GC4   = 3,
	WAVEFORM_A2    = 4,
	WAVEFORM_GL16  = 5,
	WAVEFORM_A2IN  = 6,
	WAVEFORM_A2OUT = 7,
	WAVEFORM_DU4   = 8,
} waveform_type_t;

typedef enum {
       CONVERT_SATURATE = (1 << 0), // saturate colors for CFA conversion
       CONVERT_DITHER   = (1 << 8), // apply ordered dithering for CFA conversion
       CONVERT_PURE     = (1 << 9), // convert to pure colors for DU/A2 update
} conv_flags_t;

typedef struct {
	int width;
	int height;
	int scanline;
	int depth;
	int orientation;
	void *data;
} epdc_img_t;

typedef struct {
	int version;
	int type;
	int alignment;
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
	void (*getwftimes)(uint16_t result[16]);
	void (*sync)(void);
	void (*lock)(void);
	void (*unlock)(void);
	void (*copy)(epdc_img_t *img, int x, int y, int w, int h);
	void (*convert)(epdc_img_t *src, int srcx, int srcy, int w, int h, epdc_img_t *dest, int dstx, int dsty, uint32_t flags);
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
	HWKEY_RESERVED1 =  0x00020000,
	HWKEY_RESERVED2 =  0x00040000,
	HWKEY_RESERVED3 =  0x00080000,
	HWKEY_RESERVED4 =  0x00100000,
	HWKEY_ZOOMIN =     0x00200000,
	HWKEY_ZOOMOUT =    0x00400000,
	HWKEY_POWEROFF =   0x00800000, //reserved by power off function
	HWKEY_COVEROPEN =  0x01000000,
	HWKEY_COVERCLOSE = 0x02000000,
} hwkey_t;

//input_dev_e describes input device. It is located in mode field of hwevent.
enum input_dev_e {
	DEV_UNKNOWN = 0,
	TP_CAPACITIVE,
	TP_DIGITIZER, //INDUCTIVE
	MAX_INPUT_TOUCH_DEV,

	INPUT_DEV_KEYBOARD_HW,
	INPUT_DEV_KEYBOARD_BT,
	INPUT_DEV_KEYBOARD_USB,
};

int device_input_init(void);
int device_input_read(struct input_event *ie, enum input_dev_e *devtype, int maxcount, int timeout_ms);
int device_keyboard_translate(struct input_event *ev, unsigned long *keymask);
unsigned long device_keyboard_buttons(void);
unsigned long device_keyboard_state(void);
const int *device_touchpanel_getmatrix(void);
/*
 * add linux event interface device to handle by monitor
 */
int add_input_device(const char *devpath, enum input_dev_e devtype);
/*
 * remove linux event interface device from monitor handler list
 */
int remove_input_device(const char *devpath);

slider_id_t device_slider(void);
bool device_has_slider(void);

typedef struct slider_cfg_s {
	int resolution; //max axis value
	bool reverse_axis;
	bool relative; //absolute or relative type
} slider_cfg_t;

const slider_cfg_t *device_slider_cfg(void);

gyroscop_id_t device_gyroscope(void);
uint8_t device_gyroscope_placement(void);
bool device_has_gyroscope(void);

bool device_has_extcard(void);

usb_id_t device_usb(void);
bool device_has_usb(void);
bool device_has_usbhost(void);

frontlight_id_t device_frontlight(void);
bool device_has_frontlight(void);

const char *device_model(void);
const char *device_serial_number(void);

void device_init_led(bool cfg_led_state);
void device_set_led(int value);
int device_get_led(void);

int device_battery_percent(void);
bool device_is_powered(void);

bool device_set_bootcramfs_flag(bool flag);
void device_reboot(void);
void device_poweroff(void);

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

//utility
bool device_write_file(const char *name, const char *buf, int size);
bool device_write_file_int(const char *name, int v);
int device_read_bin_file(const char *name, char *buf, int size);
bool device_read_file(const char *name, char *buf, int size);
int device_read_file_int(const char *name, int deflt);

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

struct storage_device {
	const char *path;  // e.g. "/dev/mmcblk0"
	const char *type;  // e.g. "MMC"
	const char *bus;   // e.g. "HS200"
	uint64_t size;     // total size in bytes, filled by hwlib
	int wearout;       // 0 - unknown, (1..100) - wearout level (more is worse) 
};

struct storage_partition {
	const char *path;  // device, partition, or filename
	uint64_t offset;   // offset (in bytes) from device start, usually 0 for file or partition
	uint64_t size;     // size (in bytes), filled by hwlib when initialized to 0
};

typedef struct {

	struct storage_device internal;
	struct storage_device external;
	struct storage_device usb;

	struct {
		struct storage_partition uboot;
		struct storage_partition uboot_backup;
		struct storage_partition logo;
		struct storage_partition logo_backup;
		struct storage_partition kernel;
		struct storage_partition root;
		struct storage_partition cramfs;
		struct storage_partition ebrmain;
		struct storage_partition secure;
		struct storage_partition user;
	} partition;

} storage_cfg_t;

storage_cfg_t *device_storage_cfg(void);

#endif /* SRC_HWCONFIG_H_ */


// project-specific definitions

// Selecting the LoRaWAN Version
//#define LMIC_LORAWAN_SPEC_VERSION   LMIC_LORAWAN_SPEC_VERSION_1_0_2
//#define LMIC_LORAWAN_SPEC_VERSION    LMIC_LORAWAN_SPEC_VERSION_1_0_3 //default

// Selecting the LoRaWAN Region Configuration
//#define CFG_eu868 1
#define CFG_us915 1
//#define CFG_au915 1
//#define CFG_as923 1
// #define LMIC_COUNTRY_CODE LMIC_COUNTRY_CODE_JP	/* for as923-JP */
//#define CFG_kr920 1
//#define CFG_in866 1

//If the library is configured for US915 operation, we make the following changes :
//Add the APIs LMIC_enableChannel(), LMIC_enableSubBand(), LMIC_disableSubBand(), and LMIC_selectSubBand().
//Add the constants MAX_XCHANNELS.
//Add a number of additional DR_... symbols.

// Selecting the target radio transceiver
#define CFG_sx1276_radio 1

// Controlling use of interrupts
//#define LMIC_USE_INTERRUPTS
//Configures the library to use interrupts for detecting events from the transceiver.
//If left undefined, the library will poll for events from the transceiver.

// Disabling PING
//#define DISABLE_PING
//If defined, removes all code needed for Class B downlink during ping slots(PING).
//Removes the APIs LMIC_setPingable() and LMIC_stopPingable().Class A devices don't
//support PING, so defining DISABLE_PING is often a good idea.
//By default, PING support is included in the library.

// Disabling Beacons
//#define DISABLE_BEACONS
//If defined, removes all code needed for handling beacons.
//Removes the APIs LMIC_enableTracking() and LMIC_disableTracking().

// Enabling Network Time Support
//#define LMIC_ENABLE_DeviceTimeReq number /* boolean: 0 or non-zero */
//Disable or enable support for device network - time requests(LoRaWAN MAC request 0x0D).
//If zero, support is disabled.If non - zero, support is enabled.


// Rarely changed variables

//Changing debug output
//#define LMIC_PRINTF_TO SerialLikeObject

//Getting debug from the RF library
//#define LMIC_DEBUG_LEVEL number /* 0, 1, or 2 */

//Selecting the AES library
//#define USE_ORIGINAL_AES
//#define USE_IDEETRON_AES

//Defining the OS Tick Frequency
//#define US_PER_OSTICK_EXPONENT number

//Setting the SPI-bus frequency
//#define LMIC_SPI_FREQ floatNumber

//Changing handling of runtime assertion failures
//#define LMIC_FAILURE_TO PrintLikeObject
//#define DISABLE_LMIC_FAILURE_TO

//Disabling JOIN
//#define DISABLE_JOIN
//If defined, removes code needed for OTAA activation. Removes the APIs LMIC_startJoining() and LMIC_tryRejoin().

//Disabling Class A MAC commands
//DISABLE_MCMD_DutyCycleReq, DISABLE_MCMD_RXParamSetupReq,
//DISABLE_MCMD_RXTimingSetupReq, DISABLE_MCMD_NewChannelReq, and 
//DISABLE_MCMD_DlChannelReq respectively disable code for various Class A MAC commands.

//Disabling Class B MAC commands
//DISABLE_MCMD_PingSlotChannelReq disables the PING_SET MAC commands.It's implied by DISABLE_PING.
//ENABLE_MCMD_BeaconTimingAns enables the next - beacon start command.It's disabled by default, 
//and overridden (if enabled) by DISABLE_BEACON. (This command is deprecated.)

//Disabling user events
//Code to handle registered callbacks for transmit, receive, and 
//events can be suppressed by setting LMIC_ENABLE_user_events to zero.

//Disabling external reference to onEvent()
//onEvent() may be defined for some other purpose. The LMIC has no way of knowing that this 
//is not the LMIC's onEvent, so it will call the function, and this may cause problems.
//All reference to onEvent() can be suppressed by setting LMIC_ENABLE_onEvent to 0.

//Enabling long messages
//LMIC_ENABLE_long_messages is still supported for compatibility. Setting 
//LMIC_ENABLE_long_messages to 0 is equivalent to setting LMIC_MAX_FRAME_LENGTH to 64.

//Enabling LMIC event logging calls
//Logging is enabled by setting LMIC_ENABLE_event_logging to 1. The default is not to log.

//Special purpose
//#define DISABLE_INVERT_IQ_ON_RX disables the inverted Q-I polarity on RX. Use of this variable is deprecated.

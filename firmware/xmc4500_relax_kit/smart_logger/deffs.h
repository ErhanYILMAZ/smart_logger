/**
* @file deffs.h
*
*  @date 28.2.19
*  @author Erhan YILMAZ
*  @brief definitions and variables file for the application.
*/


#ifndef DEFFS_H_
#define DEFFS_H_

// definitions
#define LED1 P1_1		///< LED1 on XMC4500 relax kit connected to the Port 1.1.
#define LED2 P1_0		///< LED2 on XMC4500 relax kit connected to the Port 1.0.
#define BUTTON1 P1_14	///< Button 1 on XMC4500 relax kit connected to the Port 1.14.
#define BUTTON2 P1_15	///< Button 2 on XMC4500 relax kit connected to the Port 1.15.
#define SAMPLING_PERIOD	1
#define CELL_VOLTAGES_SAMPLING_PERIOD	10
#define CAN_TIMEOUT	5
#define CELL_VOLTAGES_FLOW_COUNT 8
#define CELL_VOLTAGES_DATA_FLOW_COUNT 4
#define CELL_COUNTS 93
#define SET_TIME_MENU_ITEMS_COUNT	8	///< Timer set menu items count


uint8_t dataUpdated = 0;
uint8_t cellVoltagesUpdated=0;
unsigned long int sampleCounter=0;
void UpdateLCD(void);

FATFS FatFs;		///< FatFs work area needed for each volume.
FIL Fil;			///< File object needed for each open file.
XMC_RTC_TIME_t current_time;
XMC_RTC_TIME_t set_time;
uint8_t setTimeOnProcces=0;	///< Process indicator variable for the time set state machine.
uint8_t setTimeMenu = 0;	///< Menu variable for time set
uint8_t button2Pressed=0;

enum timeSetStates {
	SET_TIME_IDLE = 0,	///< Idle state.
	SET_TIME_INIT,	///< Init state.
	YEAR,		///< Year set state.
	MONTH,		///< Month set state.
	DAY,		///< Day set state.
	HOUR,		///< Hour set state.
	MINUTE,		///< Minute set state.
	SET_OK		///< Time set ok state
};
//uint8_t timeSetState= SET_TIME_IDLE;		///< State holder variable for the time set state machine.

enum enumStates{
					IDLE=0,		///< Idle state.
					GET_VELOCITY,	///< Get Smart velocity value.
					GET_BATT_AMP,		///< Get battery current.
					GET_BATT_VOLTAGE,	///< Get battery main voltage.
					GET_MODULE_TEMPS,	///< Get battery module temperatures.
					GET_CELL_VOLTAGES	///< Get battery cell voltages.
				  };
uint8_t state = IDLE;	///< State holder variable for the main state machine.

enum enumBattVoltStates{
					BATT_VOLT_IDLE = 0,			///< Batt voltage idle state.
					BATT_VOLT_REQ_RESPONSE,		///< Batt voltage request response state.
					BATT_VOLT_FLOW_RESPONSE		///< Batt voltage flow control response state.
				  };
uint8_t stateBattVolt = BATT_VOLT_IDLE;	///< State holder variable for battery voltage state machine.

enum enumModuleTempsStates{
					MODULE_TEMPS_IDLE = 0,			///< Module temperatures idle state.
					MODULE_TEMPS_REQ_RESPONSE,		///< Module temperatures request response state.
					MODULE_TEMPS_FLOW_RESPONSE		///< Module temperatures flow control response state.
				  };
uint8_t stateModuleTemps = MODULE_TEMPS_IDLE;	///< State holder variable for module temperatures state machine.

enum enumCellVoltagesStates{
					CELL_VOLTAGES_IDLE = 0,			///< Cell voltages idle state.
					CELL_VOLTAGES_REQ_RESPONSE,		///< Cell voltages request response state.
					CELL_VOLTAGES_FLOW_CONTROL,		///< Cell voltages flow control response state.
					CELL_VOLTAGES_LAST_FLOW_PACKAGE ///< Cell voltages last flow package state
				  };
uint8_t stateCellVoltages = CELL_VOLTAGES_IDLE;	///< State holder variable for module temperatures state machine.
uint8_t cellVoltagesFlowCounter = 0;

uint8_t onProcess = 0;	///< Process indicator variable for the main state machine.
uint8_t samplingTimer=0;
uint8_t canTimeoutTimerEnable=0;
uint8_t canTimeoutCounter=0;
/// Flow control package.
uint8_t flowControl[8] = {0x30, 0x08, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff};
/// Battery amp request package.
uint8_t reqBattAmp[8] = {0x03, 0x22, 0x02, 0x03, 0xff, 0xff, 0xff, 0xff};
/// Battery voltage request package.
uint8_t reqBattVolt[8] = {0x03, 0x22, 0x02, 0x04, 0xff, 0xff, 0xff, 0xff};
/// Module temperatures request package.
uint8_t reqModuleTemps[8] = {0x03, 0x22, 0x02, 0x02, 0xff, 0xff, 0xff, 0xff};
/// Battery cell voltages request package.
uint8_t reqCellVoltages[8] = {0x03, 0x22, 0x02, 0x08, 0xff, 0xff, 0xff, 0xff};



typedef struct
{
	uint16_t velocitiy;
	float battAmp;
	float battVolt;
	float battPower;
	float battEnergy;
	float bms;
	uint8_t tempRawBytes[18];
	float temps[9];
	union {
	   uint8_t 	cellVotlagesBytes[CELL_VOLTAGES_DATA_FLOW_COUNT*56+4];	///< Byte array for cell voltages to read easily from can frames.
	   uint16_t cellVoltages[CELL_VOLTAGES_DATA_FLOW_COUNT*28+2];	///< Word array for cell voltages to represent in milliVolts.
	};
} smartData_t;
smartData_t smartdata;
#endif /* DEFFS_H_ */

#pragma once

#include <string>
#include <vector>
#include <wbemidl.h>
#include <wtypes.h>



#define BYTE BYTE

namespace AlienFan_SDK {

	struct ALIENFAN_SEN_INFO {
		union {
			struct {
				BYTE index;
				BYTE type;
			};
			WORD sid; // LOBYTE - index, HIBYTE - type: 0 = ESIF, 1 = AWCC, 2 - Disk, 3 - AMD, 4 = OHM
		};
		std::std::string name;
		BSTR instance; // for ESIF/OHM/SSD sensors
		BSTR valueName;
	};

	struct ALIENFAN_FAN_INFO {
		BYTE id, type;
	};

	union ALIENFAN_INTERFACE {
		struct {
			BYTE sub,
			     arg1,
			     arg2,
			     reserved;
		};
		DWORD args;
	};

	class Control {
	private:
		BYTE sysType;
		void EnumSensors(IWbemServices* srv, const wchar_t* sname, BYTE type);
	public:
		VARIANT m_instancePath{};
		IWbemServices* m_WbemServices = NULL, * m_OHMService = NULL, * m_DiskService = NULL;
		IWbemClassObject* m_InParamaters = NULL;
		bool isAlienware = false,
			isSupported = false,
			isTcc = false,
			isXMP = false,
			isGmode = false;
		BYTE maxTCC, maxOffset;
		DWORD systemID;
		Control();
		~Control();

		// Probe hardware, sensors, fans, power modes and fill structures.
		// Result: true - compatible hardware found, false - not found.
		bool Probe(bool diskSensors);

		// Get RPM for the fan index fanID at fans[]
		// Result: fan RPM
		int GetFanRPM(int fanID);

		// Get Max. RPM for fan index fanID
		int GetMaxRPM(int fanID);

		// Get fan RPMs as a percent of RPM
		// Result: percent of the fan speed
		int GetFanPercent(int fanID);

		// Get boost value for the fan index fanID at fans[].
		// Result: Error or raw value if forced, otherwise cooked by boost.
		int GetFanBoost(int fanID);

		// Set boost value for the fan index fanID at fans[].
		// Result: value or error
		int SetFanBoost(int fanID, BYTE value);

		// Get temperature value for the sensor index TanID at sensors[]
		// Result: temperature value or error
		int GetTempValue(int TempID);

		// Unlock manual fan operations. The same as SetPower(0)
		// Result: raw value set or error
		int Unlock();

		// Set system power profile to defined power code (NOT level)
		// Result: raw value set or error
		int SetPower(BYTE level);

		// Get current system power value.
		// Result: power value (raw true) or index in powers[] (raw false) or error
		int GetPower(bool raw = false);

		// Set system GPU limit level (0 - no limit, 3 - min. limit)
		// Result: success or error
		//int SetGPU(int power);

		// Toggle G-mode on some systems
		int SetGMode(bool state);

		// Check G-mode state
		int GetGMode();

		// Get current TCC value
		int GetTCC();

		// Set TCC value, if possible
		int SetTCC(BYTE tccValue);

		// Get current XMP profile
		int GetXMP();

		// Set current XMP profile
		int SetXMP(BYTE memXMP);

		// Call custom Alienware method trough WMI
		int CallWMIMethod(BYTE com, BYTE arg1 = 0, BYTE arg2 = 0);

		// Arrays of sensors, fans, max. boosts and power values detected at Probe()
		std::vector<ALIENFAN_SEN_INFO> sensors;
		std::vector<ALIENFAN_FAN_INFO> fans;
		std::vector<BYTE> powers;

		IWbemClassObject* m_AWCCGetObj = NULL;
	};

	//class Lights {
	//private:
	//	const BSTR colorList[2]{
	//		//(BSTR)L"SetLEDColor",			// 0x04
	//		(BSTR)L"Set24BitsLEDColor",		// 0x12
	//		(BSTR)L"LEDBrightness"			// 0x03
	//	};

	//	IWbemClassObject* m_InParamaters = NULL;
	//	IWbemServices* m_WbemServices = NULL;
	//	VARIANT m_instancePath;
	//	int CallWMIMethod(BYTE com, BYTE* arg1);
	//public:
	//	bool isActivated = false;

	//	Lights(Control *ac);

	//	// Set lights brightness, 0..F
	//	bool SetBrightness(BYTE brightness);

	//	// Set color of lights mask defined by id to RGB
	//	bool SetColor(BYTE mask, BYTE r, BYTE g, BYTE b, bool save = false);

	//};

}

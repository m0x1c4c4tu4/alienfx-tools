#pragma once

#include <std::map>
#include "alienfan-sdk.h"



//DWORD WINAPI DPTFInit(LPVOID lparam);

struct fan_point {
	BYTE temp, boost;
};

struct sen_block {
	bool active = true;
	std::std::vector<fan_point> points;
};

struct fan_profile {
	union {
		struct {
			BYTE powerStage;
			BYTE powerStageDC;
			WORD gmodeStage;
		};
		DWORD powerSet = 0;
	};
	std::map<BYTE,std::map<WORD, sen_block>> fanControls;
	// OC block
	union {
		struct {
			BYTE currentTCC;
			BYTE memoryXMP;
		};
		DWORD ocSettings = 100;
	};
};

struct fan_overboost {
	BYTE maxBoost;
	USHORT maxRPM;
};

class ConfigFan {
private:
	HKEY keyMain, keySensors, keyPowers;
	void GetReg(const char *name, DWORD *value, DWORD defValue = 0);
	void SetReg(const char *text, DWORD value);
public:
	BYTE lastSelectedFan = 0;
	WORD lastSelectedSensor;
	DWORD startWithWindows;
	DWORD startMinimized;
	DWORD updateCheck;
	DWORD awcc_disable;
	DWORD keyShortcuts;
	DWORD keepSystem;
	//DWORD needDPTF;
	DWORD pollingRate;
	DWORD ocEnable;
	DWORD diskSensors;
	DWORD numlockActive;
	bool acPower = true;

	fan_profile prof;
	fan_profile* lastProf = &prof;

	std::map<BYTE, fan_overboost> boosts;
	std::map<BYTE, std::std::string> powers;
	std::map<WORD, std::std::string> sensors;

	void* niData = NULL;

	ConfigFan();
	~ConfigFan();

	void AddSensorCurve(fan_profile* prof, BYTE fid, WORD sid, BYTE* data, DWORD lend);
	void SaveSensorBlocks(HKEY key, std::std::string pname, fan_profile* data);
	std::std::string* GetPowerName(int index);
	std::std::string GetSensorName(AlienFan_SDK::ALIENFAN_SEN_INFO* acpi);
	void UpdateBoost(BYTE fanID, BYTE boost, WORD rpm);
	int GetFanScale(BYTE fanID);
	void Load();
	void Save();
};


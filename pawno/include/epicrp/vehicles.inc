main()
{
    print("\n----------------------------------");
	print(" Vehicles.inc has been included");
	print("----------------------------------\n");

#if    defined    main_vehicles
    main_vehicles();
#endif
    return 1;
}

#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_vehicles
#if    defined    main_vehicles
main_vehicles();
#endif

//------------------------------------

public OnGameModeInit()
{
    ManualVehicleEngineAndLights();
    EnableStuntBonusForAll(0);
#if    defined    OnGameModeInit_vehicles
    OnGameModeInit_vehicles();
#endif
	return 1;
}

#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_vehicles
#if    defined    OnGameModeInit_vehicles
forward OnGameModeInit_vehicles();
#endif

//------------------------------------

public OnVehicleMod(playerid, vehicleid, componentid)
{
    RemoveVehicleComponent(vehicleid,componentid);
#if    defined    OnVehicleMod_vehicles
    OnVehicleMod_vehicles(playerid, vehicleid, componentid);
#endif
	return 1;
}

#if    defined    _ALS_OnVehicleMod
    #undef    OnVehicleMod
#else
    #define    _ALS_OnVehicleMod
#endif
#define    OnVehicleMod    OnVehicleMod_vehicles
#if    defined    OnVehicleMod_vehicles
forward OnVehicleMod_vehicles(playerid, vehicleid, componentid);
#endif

//------------------------------------

public OnPlayerUpdate(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
	{
	    new Float:vhealth;
	    GetVehicleHealth(GetPlayerVehicleID(playerid), vhealth);
	    if(vhealth < 650)
		{
		    new engine, lights, alarm, doors, bonnet, boot, objective;
	    	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	    	SetVehicleParamsEx(GetPlayerVehicleID(playerid), false, lights, alarm, doors, bonnet, boot, objective);
		}
	}
#if    defined    OnPlayerUpdate_vehicles
    OnPlayerUpdate_vehicles(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    OnPlayerUpdate_vehicles
#if    defined    OnPlayerUpdate_vehicles
forward OnPlayerUpdate_vehicles(playerid);
#endif

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

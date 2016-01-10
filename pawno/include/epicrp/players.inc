main()
{
    print("\n----------------------------------");
	print(" Players.inc has been included");
	print("----------------------------------\n");

#if    defined    main_players
    main_players();
#endif
    return 1;
}

#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_players
#if    defined    main_players
main_players();
#endif

//------------------------------------

public OnPlayerConnect(playerid)
{
	printf("Player has been conecter");
#if    defined    OnPlayerConnect_players
    OnPlayerConnect_players(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerConnect
    #undef    OnPlayerConnect
#else
    #define    _ALS_OnPlayerConnect
#endif
#define    OnPlayerConnect    OnPlayerConnect_players
#if    defined    OnPlayerConnect_players
forward OnPlayerConnect_players(playerid);
#endif

//------------------------------------

public OnGameModeInit()
{
    AddPlayerClass( 0, -1976.0231,137.8876,27.6875, 0.0, 0, 0, 0, 0, 0, 0);
	SetNameTagDrawDistance(5);
	LimitGlobalChatRadius(20);
	ShowPlayerMarkers(0);
#if    defined    OnGameModeInit_players
    OnGameModeInit_players();
#endif
	return 1;
}

#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_players
#if    defined    OnGameModeInit_players
forward OnGameModeInit_players();
#endif

//------------------------------------

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
#if    defined    OnPlayerRequestClass_players
    OnPlayerRequestClass_players(playerid, classid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerRequestClass
    #undef    OnPlayerRequestClass
#else
    #define    _ALS_OnPlayerRequestClass
#endif
#define    OnPlayerRequestClass    OnPlayerRequestClass_players
#if    defined    OnPlayerRequestClass_players
forward OnPlayerRequestClass_players(playerid, classid);
#endif

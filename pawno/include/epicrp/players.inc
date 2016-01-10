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
	printf("Player has been conected");
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

public OnPlayerDisconnect(playerid, reason)
{
	printf("Player has been disconnected");
#if    defined    OnPlayerDisconnect_players
    OnPlayerDisconnect_players(playerid, reason);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerDisconnect
    #undef    OnPlayerDisconnect
#else
    #define    _ALS_OnPlayerDisconnect
#endif
#define    OnPlayerDisconnect    OnPlayerDisconnect_players
#if    defined    OnPlayerDisconnect_players
forward OnPlayerDisconnect_players(playerid, reason);
#endif

//------------------------------------

public OnGameModeInit()
{
    PlayersPayDay();
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

//------------------------------------
new PlayersPayDayTimer;

forward PlayersPayDay();

public PlayersPayDay()
{
    foreach(Player, i)
	{
	    PlayerPlaySound(i, S_MISSIONCOMPLETE, 0.0, 0.0, 10.0);
	}
	new hour,minute,second;
	gettime(hour,minute,second);
	SetWorldTime(hour);
	SetWeather(random(5));

	KillTimer(PlayersPayDayTimer);
	PlayersPayDayTimer = SetTimer("payDay", 3600000-minute*59*1000, 1);
	printf("PayDay через: ", 3600000-minute*60*1000);
	return 1;
}
//------------------------------------
stock SendClientMessageEx(playerid, color, text[])
{
	if(strlen(text) > 128)
	{
		new text2[128];
		strmid(text2,text,65,strlen(text),strlen(text));
		strdel(text, 65, strlen(text));
		format(text, 128,"%s ...", text);
		format(text2, 128, "... %s", text2);
	    SendClientMessage(playerid, color, text);
   	    SendClientMessage(playerid, color, text2);
	}
	else
	{
	    SendClientMessage(playerid, color, text);
	}
	return 1;
}

#define SendClientMessage SendClientMessageEx

//------------------------------------

stock ProxDetectorNew(playerid,Float:Radi=10.0,color,text[])
{
    new Float:pos[3];
    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
    foreach(Player, i)
    {
    	if(IsPlayerInRangeOfPoint(i,Radi,pos[0],pos[1],pos[2]))
     	{
			if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid) && GetPlayerInterior(playerid) == GetPlayerInterior(i)) SendClientMessageEx(i,color,text);
		}
    }
}

//------------------------------------

public OnPlayerText(playerid, text[])
{
	{
	new text_players[256];
	new name_players[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name_players, sizeof(name_players));
	format(text_players, sizeof(text_players), "%s: %s", name_players, text);
	ProxDetectorNew(playerid,20.0, COLOR_WHITE, text_players);
	}
#if    defined    OnPlayerText_players
    OnPlayerText_players(playerid, text);
#endif
	return 0;
}

#if    defined    _ALS_OnPlayerText
    #undef    OnPlayerText
#else
    #define    _ALS_OnPlayerText
#endif
#define    OnPlayerText    OnPlayerText_players
#if    defined    OnPlayerText_players
forward OnPlayerText_players(playerid, text[]);
#endif

// Нажми ctrl+h и замени все "props" на название инклюда
// Название должно быть уникальным
//Коммит через андроид

#define MAX_PROPS		   100

#define PLAYER_PROP_TYPE    0
#define GROUP_PROP_TYPE     1
#define STATE_PROP_TYPE     2

enum enum_props
{
	props_ID,
	Float: props_x,
	Float: props_y,
	Float: props_z,
	props_vw,
	props_int,
	props_interiorid,
	props_ownerid,
	props_ownertype,
	props_startprice,
	props_price
};

new PropsInfo[MAX_PROPS][enum_props];

main()
{
    print("\n----------------------------------");
	print(" Props.inc has been included");
	print("----------------------------------\n");

#if    defined    main_props
    main_props();
#endif
    return 1;
}
#if    defined    _ALS_main
    #undef    main
#else
    #define    _ALS_main
#endif
#define    main    main_props
#if    defined    main_props
main_props();
#endif


public OnGameModeInit()
{
    format(strSQLQuery, sizeof(strSQLQuery), "SELECT * FROM `props` LIMIT %d", MAX_PROPS);
	mysql_query(MySQL, strSQLQuery);
	for(new i = 0; i < cache_num_rows(); i++)
	{
	    PropsInfo[i][props_ID] = cache_get_field_content_int(i, "id", MySQL);
	    PropsInfo[i][props_x] = cache_get_field_content_float(i, "x", MySQL);
	    PropsInfo[i][props_y] = cache_get_field_content_float(i, "y", MySQL);
	    PropsInfo[i][props_z] = cache_get_field_content_float(i, "z", MySQL);
	    PropsInfo[i][props_vw] = cache_get_field_content_int(i, "vw", MySQL);
	    PropsInfo[i][props_int] = cache_get_field_content_int(i, "int", MySQL);
	    PropsInfo[i][props_interiorid] = cache_get_field_content_int(i, "interiorid", MySQL);
	    PropsInfo[i][props_ownerid] = cache_get_field_content_int(i, "ownerid", MySQL);
	    PropsInfo[i][props_ownertype] = cache_get_field_content_int(i, "ownertype", MySQL); // 0 - игрок, 1 - группа, 2 - государственное епт
	    PropsInfo[i][props_startprice] = cache_get_field_content_int(i, "startprice", MySQL);
	    PropsInfo[i][props_price] = cache_get_field_content_int(i, "price", MySQL);
	    
		switch(PropsInfo[i][props_ownertype])
		{
		    case PLAYER_PROP_TYPE:
		    {
		    
		    }
		    case GROUP_PROP_TYPE:
		    {
		    
		    }
		    case STATE_PROP_TYPE:
		    {
		    
		    }
		}
	}
#if    defined    OnGameModeInit_props
    OnGameModeInit();
#endif
	return 1;
}
#if    defined    _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    OnGameModeInit_props
#if    defined    OnGameModeInit_props
forward OnGameModeInit_props();
#endif

public OnGameModeExit()
{

#if    defined    OnGameModeExit_props
    OnGameModeExit();
#endif
	return 1;
}
#if    defined    _ALS_OnGameModeExit
    #undef    OnGameModeExit
#else
    #define    _ALS_OnGameModeExit
#endif
#define    OnGameModeExit    OnGameModeExit_props
#if    defined    OnGameModeExit_props
forward OnGameModeExit_props();
#endif

public OnPlayerConnect(playerid)
{

#if    defined    OnPlayerConnect_props
    OnPlayerConnect_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerConnect
    #undef    OnPlayerConnect
#else
    #define    _ALS_OnPlayerConnect
#endif
#define    OnPlayerConnect    OnPlayerConnect_props
#if    defined    OnPlayerConnect_props
forward OnPlayerConnect_props(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{

#if    defined    OnPlayerDisconnect_props
    OnPlayerDisconnect_props(playerid, reason);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerDisconnect
    #undef    OnPlayerDisconnect
#else
    #define    _ALS_OnPlayerDisconnect
#endif
#define    OnPlayerDisconnect    OnPlayerDisconnect_props
#if    defined    OnPlayerDisconnect_props
forward OnPlayerDisconnect_props(playerid, reason);
#endif

public OnPlayerSpawn(playerid)
{

#if    defined    OnPlayerSpawn_props
    OnPlayerSpawn_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerSpawn
    #undef    OnPlayerSpawn
#else
    #define    _ALS_OnPlayerSpawn
#endif
#define    OnPlayerSpawn    OnPlayerSpawn_props
#if    defined    OnPlayerSpawn_props
forward OnPlayerSpawn_props(playerid);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{

#if    defined    OnPlayerDeath_props
    OnPlayerDeath_props(playerid, killerid, reason);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerDeath
    #undef    OnPlayerDeath
#else
    #define    _ALS_OnPlayerDeath
#endif
#define    OnPlayerDeath    OnPlayerDeath_props
#if    defined    OnPlayerDeath_props
forward OnPlayerDeath_props(playerid, killerid, reason);
#endif



public OnPlayerCommandText(playerid, cmdtext[])
{
    if (strcmp("/mycommand", cmdtext, true, 10) == 0)
	{
		// Do something here
		return 1;
	}
#if    defined    OnPlayerCommandText_props
    OnPlayerCommandText_props(playerid, cmdtext);
#endif
	return 0;
}
#if    defined    _ALS_OnPlayerCommandText
    #undef    OnPlayerCommandText
#else
    #define    _ALS_OnPlayerCommandText
#endif
#define    OnPlayerCommandText    OnPlayerCommandText_props
#if    defined    OnPlayerCommandText_props
forward OnPlayerCommandText_props(playerid, cmdtext[]);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{

#if    defined    OnPlayerStateChange_props
    OnPlayerStateChange_props(playerid, newstate, oldstate);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerStateChange
    #undef    OnPlayerStateChange
#else
    #define    _ALS_OnPlayerStateChange
#endif
#define    OnPlayerStateChange    OnPlayerStateChange_props
#if    defined    OnPlayerStateChange_props
forward OnPlayerStateChange_props(playerid, newstate, oldstate);
#endif

public OnPlayerEnterCheckpoint(playerid)
{

#if    defined    OnPlayerEnterCheckpoint_props
    OnPlayerEnterCheckpoint_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerEnterCheckpoint
    #undef    OnPlayerEnterCheckpoint
#else
    #define    _ALS_OnPlayerEnterCheckpoint
#endif
#define    OnPlayerEnterCheckpoint    OnPlayerEnterCheckpoint_props
#if    defined    OnPlayerEnterCheckpoint_props
forward OnPlayerEnterCheckpoint_props(playerid);
#endif

public OnPlayerLeaveCheckpoint(playerid)
{

#if    defined    OnPlayerLeaveCheckpoint_props
    OnPlayerLeaveCheckpoint_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerLeaveCheckpoint
    #undef    OnPlayerLeaveCheckpoint
#else
    #define    _ALS_OnPlayerLeaveCheckpoint
#endif
#define    OnPlayerLeaveCheckpoint    OnPlayerLeaveCheckpoint_props
#if    defined    OnPlayerLeaveCheckpoint_props
forward OnPlayerLeaveCheckpoint_props(playerid);
#endif

public OnRconCommand(cmd[])
{

#if    defined    OnRconCommand_props
    OnRconCommand_props(cmd);
#endif
	return 1;
}
#if    defined    _ALS_OnRconCommand
    #undef    OnRconCommand
#else
    #define    _ALS_OnRconCommand
#endif
#define    OnRconCommand    OnRconCommand_props
#if    defined    OnRconCommand_props
forward OnRconCommand_props(cmd[]);
#endif

public OnObjectMoved(objectid)
{

#if    defined    OnObjectMoved_props
    OnObjectMoved_props(objectid);
#endif
	return 1;
}
#if    defined    _ALS_OnObjectMoved
    #undef    OnObjectMoved
#else
    #define    _ALS_OnObjectMoved
#endif
#define    OnObjectMoved    OnObjectMoved_props
#if    defined    OnObjectMoved_props
forward OnObjectMoved_props(objectid);
#endif

public OnPlayerObjectMoved(playerid, objectid)
{

#if    defined    OnPlayerObjectMoved_props
    OnPlayerObjectMoved_props(playerid, objectid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerObjectMoved
    #undef    OnPlayerObjectMoved
#else
    #define    _ALS_OnPlayerObjectMoved
#endif
#define    OnPlayerObjectMoved    OnPlayerObjectMoved_props
#if    defined    OnPlayerObjectMoved_props
forward OnPlayerObjectMoved_props(playerid, objectid);
#endif

public OnPlayerPickUpPickup(playerid, pickupid)
{

#if    defined    OnPlayerPickUpPickup_props
    OnPlayerPickUpPickup_props(playerid, pickupid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerPickUpPickup
    #undef    OnPlayerPickUpPickup
#else
    #define    _ALS_OnPlayerPickUpPickup
#endif
#define    OnPlayerPickUpPickup    OnPlayerPickUpPickup_props
#if    defined    OnPlayerPickUpPickup_props
forward OnPlayerPickUpPickup_props(playerid, pickupid);
#endif

public OnPlayerSelectedMenuRow(playerid, row)
{

#if    defined    OnPlayerSelectedMenuRow_props
    OnPlayerSelectedMenuRow_props(playerid, row);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerSelectedMenuRow
    #undef    OnPlayerSelectedMenuRow
#else
    #define    _ALS_OnPlayerSelectedMenuRow
#endif
#define    OnPlayerSelectedMenuRow    OnPlayerSelectedMenuRow_props
#if    defined    OnPlayerSelectedMenuRow_props
forward OnPlayerSelectedMenuRow_props(playerid, row);
#endif

public OnPlayerExitedMenu(playerid)
{

#if    defined    OnPlayerExitedMenu_props
    OnPlayerExitedMenu_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerExitedMenu
    #undef    OnPlayerExitedMenu
#else
    #define    _ALS_OnPlayerExitedMenu
#endif
#define    OnPlayerExitedMenu    OnPlayerExitedMenu_props
#if    defined    OnPlayerExitedMenu_props
forward OnPlayerExitedMenu_props(playerid);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{

#if    defined    OnPlayerInteriorChange_props
    OnPlayerInteriorChange_props(playerid, newinteriorid, oldinteriorid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerInteriorChange
    #undef    OnPlayerInteriorChange
#else
    #define    _ALS_OnPlayerInteriorChange
#endif
#define    OnPlayerInteriorChange    OnPlayerInteriorChange_props
#if    defined    OnPlayerInteriorChange_props
forward OnPlayerInteriorChange_props(playerid, newinteriorid, oldinteriorid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{

#if    defined    OnPlayerKeyStateChange_props
    OnPlayerKeyStateChange_props(playerid, newkeys, oldkeys);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerKeyStateChange
    #undef    OnPlayerKeyStateChange
#else
    #define    _ALS_OnPlayerKeyStateChange
#endif
#define    OnPlayerKeyStateChange    OnPlayerKeyStateChange_props
#if    defined    OnPlayerKeyStateChange_props
forward OnPlayerKeyStateChange_props(playerid, newkeys, oldkeys);
#endif

public OnPlayerUpdate(playerid)
{

#if    defined    OnPlayerUpdate_props
    OnPlayerUpdate_props(playerid);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    OnPlayerUpdate_props
#if    defined    OnPlayerUpdate_props
forward OnPlayerUpdate_props(playerid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{

#if    defined    OnDialogResponse_props
    OnDialogResponse_props(playerid, dialogid, response, listitem, inputtext);
#endif
	return 1;
}
#if    defined    _ALS_OnDialogResponse
    #undef    OnDialogResponse
#else
    #define    _ALS_OnDialogResponse
#endif
#define    OnDialogResponse    OnDialogResponse_props
#if    defined    OnDialogResponse_props
forward OnDialogResponse_props(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{

#if    defined    OnPlayerClickPlayer_props
    OnPlayerClickPlayer_props(playerid, clickedplayerid, source);
#endif
	return 1;
}
#if    defined    _ALS_OnPlayerClickPlayer
    #undef    OnPlayerClickPlayer
#else
    #define    _ALS_OnPlayerClickPlayer
#endif
#define    OnPlayerClickPlayer    OnPlayerClickPlayer_props
#if    defined    OnPlayerClickPlayer_props
forward OnPlayerClickPlayer_props(playerid, clickedplayerid, source);
#endif

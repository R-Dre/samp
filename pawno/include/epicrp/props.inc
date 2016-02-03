// Нажми ctrl+h и замени все "props" на название инклюда
// Название должно быть уникальным
//Коммит через андроид

#define MAX_PROPS		   8

#define PLAYER_PROP_TYPE    0
#define GROUP_PROP_TYPE     1
#define STATE_PROP_TYPE     2

enum Prop
{
	prop_ID,
	Float: prop_x,
	Float: prop_y,
	Float: prop_z,
	prop_interiorid,
	prop_vw,
	prop_interior,
	prop_ownerid,
	prop_ownertype,
	prop_startprice,
	prop_price,
	prop_mapicon
};

new Props[MAX_PROPS][Prop];

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
    MySQL = mysql_connect(SQL_HOST, SQL_USER,SQL_DB, SQL_PASS);
	mysql_query(MySQL, "SELECT * FROM `props`");
	for(new i = 0; i < cache_num_rows(); i++)
	{
	    Props[i][prop_ID] = cache_get_field_content_int(i, "id", MySQL);
	    Props[i][prop_x] = cache_get_field_content_float(i, "x", MySQL);
	    Props[i][prop_y] = cache_get_field_content_float(i, "y", MySQL);
	    Props[i][prop_z] = cache_get_field_content_float(i, "z", MySQL);
	    Props[i][prop_interiorid] = cache_get_field_content_int(i, "interiorid", MySQL);
	    Props[i][prop_vw] = cache_get_field_content_int(i, "vw", MySQL);
	    Props[i][prop_interior] = cache_get_field_content_int(i, "interior", MySQL);
	    Props[i][prop_ownerid] = cache_get_field_content_int(i, "ownerid", MySQL);
	    Props[i][prop_ownertype] = cache_get_field_content_int(i, "ownertype", MySQL); // 0 - игрок, 1 - группа, 2 - государственное епт
	    Props[i][prop_startprice] = cache_get_field_content_int(i, "startprice", MySQL);
	    Props[i][prop_price] = cache_get_field_content_int(i, "price", MySQL);
	    
	    
	    switch(Props[i][prop_ownertype])
	    {
	        case PLAYER_PROP_TYPE:
	        {
	            Props[i][prop_mapicon] = CreateDynamicMapIcon(Props[i][prop_x], Props[i][prop_y], Props[i][prop_z], 27, 0, Props[i][prop_vw], Props[i][prop_interior], -1, 250.0);
	        }
	        case GROUP_PROP_TYPE:
	        {
	            Props[i][prop_mapicon] = CreateDynamicMapIcon(Props[i][prop_x], Props[i][prop_y], Props[i][prop_z], 27, 0, Props[i][prop_vw], Props[i][prop_interior], -1, 250.0);
	        }
	        case STATE_PROP_TYPE:
	        {
	            Props[i][prop_mapicon] = CreateDynamicMapIcon(Props[i][prop_x], Props[i][prop_y], Props[i][prop_z], 27, 0, Props[i][prop_vw], Props[i][prop_interior], -1, 250.0);
	        }
		}
	}
#if    defined    OnGameModeInit_props
    OnGameModeInit_props();
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

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    print("Presskey");
    if(newkeys==KEY_WALK)
	{
		for(new i = 0; i < MAX_PROPS; i++)
		{
			if(PlayerToPoint(2.0,playerid,Props[i][prop_x],Props[i][prop_y],Props[i][prop_z]) && (GetPlayerVirtualWorld(playerid) == Props[i][prop_vw]) && (GetPlayerInterior(playerid) == Props[i][prop_interior]))
			{
				SetPlayerPos(playerid, Interiors[Props[i][prop_interiorid]][interior_x], Interiors[Props[i][prop_interiorid]][interior_y], Interiors[Props[i][prop_interiorid]][interior_z]);
				SetPlayerVirtualWorld(playerid, i);
				SetPlayerInterior(playerid, Interiors[Props[i][prop_interiorid]][interior_interior]);
			}
			else
			    continue;
		}
		for(new i = 0; i < MAX_INTERIORS; i++)
		{
			if(PlayerToPoint(2.0, playerid, Interiors[i][interior_x], Interiors[i][interior_y], Interiors[i][interior_z]))
			{
				new vw = GetPlayerVirtualWorld(playerid);
				SetPlayerPos(playerid, Props[vw][prop_x], Props[vw][prop_y], Props[vw][prop_z]);
				SetPlayerVirtualWorld(playerid, Props[vw][prop_vw]);
				SetPlayerInterior(playerid, Props[vw][prop_interior]);
			}
			else
			    continue;
		}
	}
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

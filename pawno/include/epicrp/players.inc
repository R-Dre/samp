#define IsValidRpName(%1) \
regex_match(%1, "([A-Z]{1,1})[a-z]{2,9}+_([A-Z]{1,1})[a-z]{2,9}")
#define IsValidEmail(%1) \
	regex_match(%1, "[a-zA-Z0-9_\\.]+@([a-zA-Z0-9\\-]+\\.)+[a-zA-Z]{2,4}")

#define Kick(%0) \
	SetPVarInt(%0, "forkick", 1)

//------------------------------------

enum fInfo
{
	fName[32],
	fType,// 1 - int, 2 - float, 3 - string
	fStringLen
}

new FieldInfo[2][fInfo] = 
{
	{"name", 3, 24},
	{"lvl", 1, 0}
};


#define MAX_PERMISSIONS 27
enum perInfo
{
	perName[60],
	perDesc[128]
};

new permissionInfo[MAX_PERMISSIONS][perInfo] =
{
	{"Управлять разрешениями", "/setperm"},
	{"Удалять аккаунты", "Недоступно"},//1
	{"Изменять аккаунты", "Недоступно"},
	{"Блокировать аккаунты", "/ban"},
	{"Блокировать чат", "/mute"},
	{"Выкидывать с сервера", "/kick"},//5
	{"Выдавать предупреждения", "/warn"},
	{"Удалять персонажей", "Недоступно"},
	{"Изменять персонажей", "Недоступно"},
	{"Управлять инвентарем", "Недоступно"},
	{"Удалять фракции", "/delfaction"},//10
	{"Создавать фракции", "/createfaction"},
	{"Изменять фракции", "/setfactionname"},
	{"Управлять фракциями", "/setleader"},
	{"Удалять недвижимость", "/delhouse"},
	{"Создавать недвижимость", "/createhouse"},//15
	{"Изменять недвижимость", "/hname, /hdesc"},
	{"Управлять недвижимостью", "/lock"},
	{"Удалять транспорт", "Недоступно"},
	{"Создавать транспорт", "Недоступно"},
	{"Изменять транспорт", "Недоступно"},//20
	{"Управлять транспортом", "Недоступно"},
	{"Разблокировать аккаунты", "/unban"},
	{"Выдавать временный скин", "/setskin"},
	{"Телепортироваться к игрокам", "/teleport"},
	{"Просматривать интерьеры", "/showint"},//25
	{"Перезапускать сервер", "/restart"}
};
//------------------------------------
main()
{
    print("\n----------------------------------");
	print(" Players.inc has been included");
	PlayersPayDay();
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
	{
	    
	    new temp[MAX_PLAYER_NAME];
	    GetPlayerName(playerid, temp, MAX_PLAYER_NAME);
	    SetPVarString(playerid, "name", temp);
		if(IsValidRpName(temp))
		{
			format(strSQLQuery, sizeof(strSQLQuery), "SELECT * FROM `players` WHERE `name` = '%s'", temp);
			mysql_query(MySQL, strSQLQuery);
		    if(cache_num_rows() != 0)
			{
			    format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Добро пожаловать на сервер\nИгровой аккаунт с этим имененем зарегистрирован\n\nИмя: {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"}\nВведите пароль:", temp);
			    Dialog_Show(playerid, Log, DIALOG_STYLE_PASSWORD, "{"#COLOR_DIALOG_HEAD"}Авторизация: Введите пароль", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
			}
			else
			{
			    format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Добро пожаловать на сервер\nЧтобы начать игру вам необходимо зарегистрироваться\n\nПридумайте пароль для вашего аккаунта\nОн необходим для авторизации при каждом заходе в игру");
			    format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s\n\n\t{"#COLOR_NOTE"}Примечания:\n\t- пароль может состоять из цифр, латинских и кириллических букв, знаков подчёркивания\n\t- пароль чувствителен к регистру\n\t- пароль должен содержать от 8 до 30 символов", strTextPlayerDialog);
			    Dialog_Show(playerid, RegPassEnter, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Ввод пароля", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
			}
		}
		else
		{
			SendClientMessageEx(playerid, CLR_ERROR,"«x»: {"#cOLOR_WHITE"}Логин должен иметь формат Имя_Фамилия");
			Kick(playerid);
		}
		
	}
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

forward LoadFromPlayerTableInToPVar(playerid);
public LoadFromPlayerTableInToPVar(playerid)
{
	new field_name[32], dest[128], Float: floatdata, integerdata;
	for(new i = 0; i < cache_get_field_count();i++)
	{
		cache_get_field_name(i, field_name);
		cache_get_field_content(0, field_name, dest);
		
		if(!sscanf(dest,"i", integerdata))
		{
		    format(strIOText, sizeof(strIOText), "%s is integer and = %i", dest, integerdata);
			print(strIOText);
			SetPVarInt(playerid, field_name, integerdata);
		}
		else if(!sscanf(dest,"f", floatdata))
		{
		    format(strIOText, sizeof(strIOText), "%s is float and = %f", dest, floatdata);
			print(strIOText);
			SetPVarFloat(playerid, field_name, floatdata);
		}
		
		else if(!sscanf(dest,"s[128]", dest))
		{
			format(strIOText, sizeof(strIOText), "%s is string", dest);
			print(strIOText);
			SetPVarString(playerid, field_name, dest);
		}
	}
	return 1;
}

forward LoadFromPVarInToPlayerTable(playerid);
public LoadFromPVarInToPlayerTable(playerid)
{
	new field_name[32], temp[128];

	format(strSQLQuery, sizeof(strSQLQuery), "UPDATE `players` SET");

	for(new i = 0; i < GetPVarsUpperIndex(playerid) + 1;i++)
	{
		GetPVarNameAtIndex(playerid, i, field_name, sizeof(field_name));

		switch(GetPVarType(playerid, field_name))
    	{
	        case PLAYER_VARTYPE_NONE:
	        {
	            continue;
	        }
	        case PLAYER_VARTYPE_INT:
	        {
	        	format(strSQLQuery, sizeof(strSQLQuery),"%s `%s` = '%i'",strSQLQuery, field_name, GetPVarInt(playerid, field_name));
	        }
	        case PLAYER_VARTYPE_FLOAT:
	        {
	            format(strSQLQuery, sizeof(strSQLQuery),"%s `%s` = '%f'",strSQLQuery, field_name, GetPVarFloat(playerid, field_name));
	        }
	        case PLAYER_VARTYPE_STRING:
	        {
	            GetPVarString(playerid, field_name, temp, sizeof(temp));
	 			format(strSQLQuery, sizeof(strSQLQuery),"%s `%s` = '%s'",strSQLQuery, field_name, temp);
	        }
    	}

    	if(i < GetPVarsUpperIndex(playerid) - 1)
    	{
    		format(strSQLQuery, sizeof(strSQLQuery),"%s,",strSQLQuery);
    	}
	}

	format(strSQLQuery, sizeof(strSQLQuery),"%s WHERE `id` = '%i'",strSQLQuery, GetPVarInt(playerid, "id"));
	print(strSQLQuery);
	mysql_query(MySQL, strSQLQuery);
	return 1;
}

stock RegisterPlayer(playerid)
{
	new name[MAX_PLAYER_NAME], email[64], pass[33];
	GetPVarString(playerid, "name", name, sizeof(name));
	GetPVarString(playerid, "email", email, sizeof(email));
	GetPVarString(playerid, "pass", pass, sizeof(pass));
	format(strSQLQuery, sizeof(strSQLQuery), "INSERT INTO `players` (`name`, `pass`, `email`, `sex`) VALUES ('%s', '%s', '%s', '%i')", name, pass, email, GetPVarInt(playerid, "sex"));
    mysql_query(MySQL, strSQLQuery);
    SetPVarInt(playerid, "id", GetPlayerIDByName(name));
    
    SendClientMessageEx(playerid, CLR_NOTE,"«i»: {"#cOLOR_WHITE"}Вы успешно прошли регистрацию.{"#COLOR_SUCCESS"} Поздравляем!");
	return 1;
}

stock GetPlayerIDByName(name[])
{
	format(strSQLQuery, sizeof(strSQLQuery), "SELECT `id` FROM `players` WHERE `name` = '%s'", name);
	mysql_query(MySQL, strSQLQuery);
	return cache_get_field_content_int(0, "id", MySQL);
}

//------------------------------------

CMD:mainmenu(playerid,params[])
{
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "1. Статистика\n2. Доступные права\n3. Игровая справка\n4. Обратная связь\n5. Магазин [Баланс: %iруб.]", GetPVarInt(playerid, "donate"));
    Dialog_Show(playerid, mainmenu,DIALOG_STYLE_LIST,"{"#COLOR_DIALOG_HEAD"}Меню игрока",strTextPlayerDialog,"Выбор","Закрыть");
	return 1;
}

ALTX:mainmenu("/mm", "/mn");

Dialog:mainmenu(playerid, response, listitem, inputtext[])
{
    if (response)
    {
		switch(listitem)
		{
		    case 0:
		    {
		        ShowPlayerStats(playerid, playerid);
		    }
		    case 1:
		    {

		    }
		    case 2:
		    {

		    }
		    case 3:
		    {

		    }
		    case 4:
		    {
                ShowDonateMenu(playerid);
		    }
		}
    }
    else
    {

    }
    return 1;
}

//------------------------------------

stock ShowDonateMenu(playerid)
{
    format(strHeaderPlayerDialog, sizeof(strHeaderPlayerDialog), "{"#COLOR_DIALOG_HEAD"}Магазин [Баланс: %iруб.]", GetPVarInt(playerid, "donate"));
    Dialog_Show(playerid, donate,DIALOG_STYLE_LIST, strHeaderPlayerDialog,"1. Купить игровую валюту\n2. Купить игровые права\n3. Пополнить счёт\n4. Рефералы","Выбор","Закрыть");
	return 1;
}

Dialog:donate(playerid, response, listitem, inputtext[])
{
    if (response)
    {
		switch(listitem)
		{
		    case 0:
		    {
		        
		    }
		    case 1:
		    {
                ShowPermissionsShop(playerid);
		    }
		    case 2:
		    {

		    }
		    case 3:
		    {

		    }
		    case 4:
		    {
                ShowDonateMenu(playerid);
		    }
		}
    }
    else
    {

    }
    return 1;
}

stock ShowPermissionsShop(playerid)
{
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "");
	for(new i=0;i<sizeof(permissionInfo);i++)
	{
	    format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s%i. %s\n",strTextPlayerDialog, i+1, permissionInfo[i][perName]);
	}
	Dialog_Show(playerid, donate,DIALOG_STYLE_LIST, "{"#COLOR_DIALOG_HEAD"}Покупка игровых прав",strTextPlayerDialog,"Купить","Закрыть");
	return 1;
}

//------------------------------------

CMD:stats(playerid,params[])
{
	new showid;
    if(sscanf(params,"i",showid))
    {
  		ShowPlayerStats(playerid, playerid);
	}
	else
	{
	    ShowPlayerStats(playerid, showid);
	}
	return 1;
}

stock ShowPlayerStats(playerid, showid)
{
	if(GetPVarInt(playerid, "logged") != 1) return SendClientMessageEx(playerid,CLR_ERROR,"Ошибка: {"#COLOR_ERROR"}Этот игрок не авторизован");
	new temp[128];
	GetPVarString(showid,"name",temp, sizeof(temp));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"{"#COLOR_DIALOG_BODY"}Имя: \t\t\t\t\t{"#COLOR_NOTE"}%s\n", temp);
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Уровень: \t\t\t\t{"#COLOR_NOTE"}%i\n", strTextPlayerDialog, GetPVarInt(showid,"lvl"));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Очки опыта: \t\t\t\t{"#COLOR_NOTE"}%i из %i\n", strTextPlayerDialog, GetPVarInt(showid,"exp"), GetPVarInt(showid,"lvl") * 8);
    format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Пол: \t\t\t\t\t{"#COLOR_NOTE"}%s\n", strTextPlayerDialog, GetPVarInt(showid,"sex") == 0 ? ("Мужской") : ("Женский"));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Регистрационный номер: \t\t{"#COLOR_NOTE"}%d\n", strTextPlayerDialog, GetPVarInt(showid,"id"));
	GetPVarString(showid,"email",temp, sizeof(temp));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Почта: \t\t\t\t\t{"#COLOR_NOTE"}%s\n", strTextPlayerDialog, temp);
	
	new Float: x, Float: y, Float: z;
	GetPlayerPos(showid, x, y, z);
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s\n{"#COLOR_DIALOG_BODY"}Текущее местоположение: \t\t{"#COLOR_NOTE"}%s, %s\n", strTextPlayerDialog, Zones[GetZone(x, y, z)][zone_name], Cities[GetZone(x, y, z)][zone_name]);
	
	
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s\n{"#COLOR_DIALOG_BODY"}Блокировок аккаунта: \t\t{"#COLOR_NOTE"}%i\n", strTextPlayerDialog, GetPVarInt(showid,"bans"));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Блокировок чата: \t\t\t{"#COLOR_NOTE"}%i\n", strTextPlayerDialog, GetPVarInt(showid,"mutes"));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Предупреждений: \t\t\t{"#COLOR_NOTE"}%i\n", strTextPlayerDialog, GetPVarInt(showid,"warns"));
	format(strTextPlayerDialog, sizeof(strTextPlayerDialog),"%s{"#COLOR_DIALOG_BODY"}Киков: \t\t\t\t{"#COLOR_NOTE"}%i\n", strTextPlayerDialog, GetPVarInt(showid,"kicks"));
 	Dialog_Show(playerid, MsgBox,DIALOG_STYLE_MSGBOX,"{"#COLOR_DIALOG_HEAD"}Статистика игрока",strTextPlayerDialog,"Закрыть","");
	return 1;
}

//------------------------------------

Dialog:Log(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        new temp[MAX_PLAYER_NAME];
        GetPVarString(playerid, "name", temp, MAX_PLAYER_NAME);
        if(!isnull(inputtext))
        {
			format(strSQLQuery, sizeof(strSQLQuery), "SELECT * FROM `players` WHERE `name` = '%s' AND `pass` = '%s'", temp, MD5_Hash(inputtext));
			mysql_query(MySQL, strSQLQuery);
            if(cache_num_rows() != 0)
            {
                mysql_function_query(MySQL, strSQLQuery, true, "LoadFromPlayerTableInToPVar","i", playerid);
                
                PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
                SetPVarInt(playerid, "logged", 1);
                SpawnPlayer(playerid);
                DeletePVar(playerid, "wrong_entering");
            }
            else
            {
                if(GetPVarInt(playerid, "wrong_entering") != 3)
                {
                    SetPVarInt(playerid, "wrong_entering", GetPVarInt(playerid, "wrong_entering") + 1);
	                PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
	                format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Добро пожаловать на сервер\nИгровой аккаунт с этим имененем зарегистрирован\n\nИмя: {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"}\nВведите пароль:", temp);
			    	Dialog_Show(playerid, Log, DIALOG_STYLE_PASSWORD, "{"#COLOR_DIALOG_HEAD"}Авторизация: Введите пароль {"#COLOR_ERROR"}[Пароль неверный!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
				}
				else
				{
				    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
				    Kick(playerid);
				}
			}

        }
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Добро пожаловать на сервер\nИгровой аккаунт с этим имененем зарегистрирован\n\nИмя: {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"}\nВведите пароль:", temp);
			Dialog_Show(playerid, Log, DIALOG_STYLE_PASSWORD, "{"#COLOR_DIALOG_HEAD"}Авторизация: Введите пароль {"#COLOR_ERROR"}[Поле ввода пустое!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
		}

    }
    else
    {
    
    }
    return 1;
}

Dialog:RegPassEnter(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if(!isnull(inputtext))
        {
            SetPVarString(playerid, "pass", MD5_Hash(inputtext));
            PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
            format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Введите адрес Вашей электронной почты\nВ дальнейшем он может понадобиться для восстановление доступа к игровому аккаунту, в случае взлома или если Вы забудите пароль\n\n");
    		format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}На введенный адрес будет выслан код, который необходим для подтверждения\nЭто может занять от 1 до 5 минут", strTextPlayerDialog);
    		format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s\n\n\t{"#COLOR_NOTE"}Примечание:\n\t- не используйте сервисы временных почтовых адресов\n\t- в случае потери доступа к почтовому адресу, игровой аккаунт будет удалён", strTextPlayerDialog);
		    Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Ввод EMail", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");

		}
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Добро пожаловать на сервер\nЧтобы начать игру вам необходимо зарегистрироваться\n\nПридумайте пароль для вашего аккаунта\nОн необходим для авторизации при каждом заходе в игру");
    		format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s\n\n\t{"#COLOR_NOTE"}Примечания:\n\t- пароль может состоять из цифр, латинских и кириллических букв, знаков подчёркивания\n\t- пароль чувствителен к регистру\n\t- пароль должен содержать от 8 до 30 символов", strTextPlayerDialog);
		    Dialog_Show(playerid, RegPassEnter, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Ввод пароля {"#COLOR_ERROR"}[Поле ввода пустое!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
		}
	}
	else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegEMailEnter(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if(!isnull(inputtext))
        {
	        if(IsValidEmail(inputtext))
	        {
	            SetPVarString(playerid, "email", inputtext);
                PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
				format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}На почтовый адрес {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"} был отправлен код\n", inputtext);
				format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}Сверните игру с помощью комбинации {"#COLOR_NOTE"}(alt+tab){"#COLOR_DIALOG_BODY"}, скопируйте и вставьте его в это окно\n", strTextPlayerDialog);
	   			Dialog_Show(playerid, RegEMailVerification, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Подтверждение EMail", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
	   			
				SetPVarInt(playerid, "email_confirm_code", 1000 + random(899));
				new theme[256], subject[256];
				format(subject, sizeof(subject), "Подтверждение регистрации");
				format(theme, sizeof(theme),"Скопируйте код подтверждение и вставьте в диалоговое окно в игре <br>Код: <b>%i</b>", GetPVarInt(playerid, "email_confirm_code"));
				SendMail( inputtext, "noreply@epic-rp.su", "Epic Interactive", subject, theme );
				DeletePVar(playerid, "wrong_entering");
			}
	        else
	        {
				if(GetPVarInt(playerid, "wrong_entering") != 3)
				{
				    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
                    format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Введите адрес Вашей электронной почты\nВ дальнейшем он может понадобиться для восстановление доступа к игровому аккаунту, в случае взлома или если Вы забудите пароль\n\n");
    				format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}На введенный адрес будет выслан код, который необходим для подтверждения\nЭто может занять от 1 до 5 минут", strTextPlayerDialog);
    				format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s\n\n\t{"#COLOR_NOTE"}Примечание:\n\t- не используйте сервисы временных почтовых адресов\n\t- в случае потери доступа к почтовому адресу, игровой аккаунт будет удалён", strTextPlayerDialog);
	   			 	Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Ввод EMail   {"#COLOR_ERROR"}[Невалидный EMail!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
					SetPVarInt(playerid, "wrong_entering", GetPVarInt(playerid, "wrong_entering") + 1);
				}
				else
				{
				    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
				    Kick(playerid);
				}
			}
        }
        else
        {
            PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}Введите адрес Вашей электронной почты\nВ дальнейшем он может понадобиться для восстановление доступа к игровому аккаунту, в случае взлома или если Вы забудите пароль\n\n");
			format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}На введенный адрес будет выслан код, который необходим для подтверждения\nЭто может занять от 1 до 5 минут", strTextPlayerDialog);
    		format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s\n\n\t{"#COLOR_NOTE"}Примечание:\n\t- не используйте сервисы временных почтовых адресов\n\t- в случае потери доступа к почтовому адресу, игровой аккаунт будет удалён", strTextPlayerDialog);
	   		Dialog_Show(playerid, RegEMailEnter, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Ввод EMail   {"#COLOR_ERROR"}[Поле ввода пустое!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
		}
    }
    else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegEMailVerification(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        new temp[64];
        GetPVarString(playerid, "email", temp, 64);
		if(!isnull(inputtext))
  		{
  		    if(strval(inputtext) == GetPVarInt(playerid, "email_confirm_code"))
  		    {
				PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
		    	Dialog_Show(playerid, RegSexSelect, DIALOG_STYLE_MSGBOX, "{"#COLOR_DIALOG_HEAD"}Регистрация: Выбор пола персонажа", "{"#COLOR_DIALOG_BODY"}Выберите пол вашего персонажа\n\n\t{"#COLOR_NOTE"}Примечание:\n\t- в дальнейшем его можно будет сменить в Меню игрока»Дополнительно (/mm)", "{"#COLOR_SUCCESS"}Мужской", "{"#COLOR_ERROR"}Женский");
                DeletePVar(playerid, "wrong_entering");
                DeletePVar(playerid, "email_confirm_code");
			}
			else
			{
			    if(GetPVarInt(playerid, "wrong_entering") != 3)
			    {
			    	PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
			    	format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}На почтовый адрес {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"} был отправлен код\n", temp);
					format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}Сверните игру с помощью комбинации {"#COLOR_NOTE"}(alt+tab){"#COLOR_DIALOG_BODY"}, скопируйте и вставьте его в это окно\n", strTextPlayerDialog);
	   				Dialog_Show(playerid, RegEMailVerification, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Подтверждение EMail {"#COLOR_ERROR"}[Код неверный!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
	   				SetPVarInt(playerid, "wrong_entering", GetPVarInt(playerid, "wrong_entering") + 1);
				}
				else
				{
				    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        			Kick(playerid);
				}
			}
		}
		else
  		{
		    PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
            format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "{"#COLOR_DIALOG_BODY"}На почтовый адрес {"#COLOR_NOTE"}%s{"#COLOR_DIALOG_BODY"} был отправлен код\n", temp);
			format(strTextPlayerDialog, sizeof(strTextPlayerDialog), "%s{"#COLOR_DIALOG_BODY"}Сверните игру с помощью комбинации {"#COLOR_NOTE"}(alt+tab){"#COLOR_DIALOG_BODY"}, скопируйте и вставьте его в это окно\n", strTextPlayerDialog);
	   		Dialog_Show(playerid, RegEMailVerification, DIALOG_STYLE_INPUT, "{"#COLOR_DIALOG_HEAD"}Регистрация: Подтверждение EMail {"#COLOR_ERROR"}[Поле ввода пустое!]", strTextPlayerDialog, "{"#COLOR_SUCCESS"}Ввод", "{"#COLOR_ERROR"}Выход");
		}
    }
    else
    {
        PlayerPlaySound(playerid, S_DENY, 0.0, 0.0, 10.0);
        Kick(playerid);
    }
    return 1;
}

Dialog:RegSexSelect(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        SetPVarInt(playerid, "sex", 0);
    }
    else
    {
        SetPVarInt(playerid, "sex", 1);
    }
    RegisterPlayer(playerid);
    LoadFromPlayerTableInToPVar(playerid);
    PlayerPlaySound(playerid, S_ACCEPT, 0.0, 0.0, 10.0);
    SetPVarInt(playerid, "logged", 1);
    SpawnPlayer(playerid);
    return 1;
}

//------------------------------------

public OnPlayerSpawn(playerid)
{
#if    defined    OnPlayerSpawn_players
    OnPlayerSpawn_players(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerSpawn
    #undef    OnPlayerSpawn
#else
    #define    _ALS_OnPlayerSpawn
#endif
#define    OnPlayerSpawn    OnPlayerSpawn_players
#if    defined    OnPlayerSpawn_players
forward OnPlayerSpawn_players(playerid);
#endif

//------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	if(GetPVarInt(playerid, "logged") == 1)
	{
	    DeletePVar(playerid, "logged");
	    LoadFromPVarInToPlayerTable(playerid);
	}
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

public OnPlayerUpdate(playerid)
{
	if(GetPVarInt(playerid, "forkick") == 1)
	    {
	    	Kick(playerid);
	    }
	if(GetPVarInt(playerid, "logged") == 1)
	{

	}
#if    defined    OnPlayerUpdate_players
    OnPlayerUpdate_players(playerid);
#endif
	return 1;
}

#if    defined    _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    OnPlayerUpdate_players
#if    defined    OnPlayerUpdate_players
forward OnPlayerUpdate_players(playerid);
#endif

//------------------------------------

public OnGameModeInit()
{
    
    AddPlayerClass( 0, 1734.7269,-1950.1315,14.1172, 0.0, 0, 0, 0, 0, 0, 0);
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
	    SetPVarInt(i,"exp", GetPVarInt(i,"exp") + 1);
	    if(GetPVarInt(i,"exp") > GetPVarInt(i,"lvl") * 4)
	    {
	        SetPVarInt(i,"exp", 0);
	        SetPVarInt(i,"lvl", GetPVarInt(i,"lvl") + 1);
	        SendClientMessageEx(i, CLR_NOTE,"«i»: {"#cOLOR_WHITE"}Вы достигли следующего уровня.{"#COLOR_SUCCES"} Поздравляем!");
	        SetPlayerScore(i, GetPVarInt(i,"lvl"));
	    }
	}
	new hour,minute,second;
	gettime(hour,minute,second);
	SetWorldTime(hour);
	SetWeather(random(5));

	KillTimer(PlayersPayDayTimer);
	PlayersPayDayTimer = SetTimer("payDay", 3600000-minute*60*1000, 1);
	format(strIOText, sizeof(strIOText), " PayDay всего лишь через: %i минут", (3600000-minute*60*1000)/(60*1000));
	printf(strIOText);
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

#if    defined    OnPlayerstrIOText
    OnPlayerstrIOText(playerid, text);
#endif
	return 0;
}

#if    defined    _ALS_OnPlayerText
    #undef    OnPlayerText
#else
    #define    _ALS_OnPlayerText
#endif
#define    OnPlayerText    OnPlayerstrIOText
#if    defined    OnPlayerstrIOText
forward OnPlayerstrIOText(playerid, text[]);
#endif


//------------------------------------

forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) &&
		((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

//------------------------------------

CMD:cc(playerid)
{
    for(new i=0; i<20; i++) SendClientMessageEx(playerid,COLOR_WHITE," ");
    return 1;
}

|----------------------------------------------------------------------------|
| Wizard Functions
|----------------------------------------------------------------------------|
SUB check_Harvest
	/if (${autoHarvest} && ${Defined[harvestSpells2D]}) {
    |only harvest if im not in ooc regen
    /if (${Me.CombatState.Equal[COMBAT]}) {
      /declare s int local
      /for s 1 to ${harvestSpells2D.Size[1]}
        /call check_Ready "harvestSpells2D" ${s}
        /if (${c_Ready} && ${harvestSpells2D[${s},${iIfs}]}) {
          /if (${check_Mana["harvestSpells2D",${s}]}) {
            /call e3_Cast ${Me.ID} "harvestSpells2D" ${s}
          }
        }
      /if (!${ActionTaken}) /next s
    }
	}
/RETURN

#event AE_WARD "<#1#> Ward#*#"
SUB event_AE_WARD(line, ChatSender, eventParams)
/if (${Me.Class.ShortName.Equal[WIZ]}) {
   /if (!${checkEventArgs[${ChatSender},${line},UZ,""]}) /return
   /if (${Me.AltAbilityReady[307]}) {
      /docommand ${ChatToggle} Casting Ward of Destruction
      /casting "Ward of Destruction" -maxtries|4
   }
   |/if (!${Me.AltAbilityReady[307]}) {
   |   /docommand ${ChatToggle} Ward of Destruction not available
   |}
}
/RETURN
|----------------------------------------------------------------------------|
Sub WIZ_Setup
/if (${Debug}) /echo |- WIZ_Setup ==>
	/call iniToVarV "${Character_Ini},Wizard,Evac Spell" Evac_Spell string outer
	/call iniToVarV "${Character_Ini},Wizard,Auto-Harvest (On/Off)" autoHarvest bool outer
	/call IniToArrayV "${Character_Ini},Wizard,Harvest#" harvestSpells
  /if (${Defined[harvestSpells]}) /call BuildSpellArray "harvestSpells"	"harvestSpells2D"

/if (${Debug}) /echo <== WIZ_Setup -|
/return
|----------------------------------------------------------------------------|
SUB WIZ_MacroSettings
/if (${Debug}) /echo |- WIZ_MacroSettings ==>
	/call WriteToIni "${advSettings_Ini},WIZ Functions,WIZ Function#1" "check_Burns" 1
	/call WriteToIni "${advSettings_Ini},WIZ Functions,WIZ Function#2" "check_Buffs" 1
	/call WriteToIni "${advSettings_Ini},WIZ Functions,WIZ Function#3" "check_AE" 1
	/call WriteToIni "${advSettings_Ini},WIZ Functions,WIZ Function#4" "check_Nukes" 1
	/call WriteToIni "${advSettings_Ini},WIZ Functions,WIZ Function#5" "check_Harvest" 1
/if (${Debug}) /echo <== WIZ_MacroSettings -|
/RETURN
|----------------------------------------------------------------------------|
SUB WIZ_CharacterSettings
/if (${Debug}) /echo |- WIZ_CharacterSettings ==>
	/call WriteToIni "${Character_Ini},Wizard,Evac Spell"
	/call WriteToIni "${Character_Ini},Wizard,Auto-Harvest (On/Off)" Off
	/call WriteToIni "${Character_Ini},Wizard,Harvest"
/if (${Debug}) /echo <== WIZ_CharacterSettings -|
/RETURN
|----------------------------------------------------------------------------|
Sub WIZ_Aliases
/return
|----------------------------------------------------------------------------|
Sub WIZ_Background_Events
   /doevents AE_WARD
	/if (${Me.Pet.ID} && ${Me.Pet.Race.Name.NotEqual[Gnomework]} && ${MacroQuest.Server.Equal[PEQTGC]}) /pet get lost
/return

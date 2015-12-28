use uo;
use os;

Include "include/client";

function IsCraftSkill( skill )
   var craft_skill_cfg := ReadConfigFile("CraftSkills");
   craft_skill_cfg := craft_skill_cfg["SkillList"];
   var craft_skill_list;
   if( TypeOf(skill) == TypeOf("") )
      craft_skill_list := GetConfigInt(craft_skill_cfg,"SkillID");
   elseif( TypeOf(skill) == TypeOf(0) )
      craft_skill_list := GetConfigStringArray(craft_skill_cfg,"AttributeID");
   endif

   if( skill in craft_skill_list )
      return 1;
   endif
   return 0;
endfunction

function IsCrafterz(who)
   var craft_skill_cfg := ReadConfigFile("CraftSkills");
   craft_skill_cfg := craft_skill_cfg["SkillList"];
   var crafter := GetConfigInt(craft_skill_cfg,"AttributeID");
   var num_skills;
   foreach craft_skill in craft_skill_list
      if( GetEffectiveSkill(who,craft_skill) > 12900 ) // 129 * 100
         num_skills := num_skills + 1;
      endif
   endforeach
   if( num_skills >= 3 )
      return 1;
   endif
   return 0;
endfunction

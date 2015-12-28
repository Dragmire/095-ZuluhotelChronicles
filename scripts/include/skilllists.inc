function getskilllist(me)
  var mytemplate := GetObjProperty(me, "MerchantType");
  case(mytemplate)
    "Healer":           return { "spiritspeaking", "healing", "anatomy", "camping", "fishing", "forensic evaluation" };
    "stable":           return { "animal lore", "animal taming", "veterinary" };
    "ShipWright":       return { "wrestling", "tactics" };
    "fisherman":        return { "fishing", "fencing" };
    "innkeeper":        return { "fencing", "tactics" };
    "farmer":           return { "swordsmanship", "animal lore", "herding", "veterinary" };
    "Weaponsmith":      return { "swordsmanship", "arms lore", "blacksmithy", "mining", "parrying", "tactics" };
    "Armorer":          return { "mace fighting", "arms lore", "blacksmithy", "mining", "parrying", "tactics" };
    "barkeep":          return { "mace fighting", "tactics" };
    "barmaid":          return { "fencing", "tactics" };
    "baker":            return { "wrestling", "cooking" };
    "tinker":           return { "fencing", "alchemy", "lockpicking", "tinkering" };
    "bard":             return { "fencing", "enticement", "musicianship", "provocation", "peacemaking" };
    "butcher":          return { "mace fighting", "cooking", "taste identification" };
    "cobbler":          return { "swordsmanship", "tailoring" };
    "jeweler":          return { "fencing", "item identification" };
    "Mage":             return { "magic resistance", "inscription", "magery", "meditation", "wrestling" };
    "Alchemist":        return { "magic resistance", "taste identification", "alchemy", "wrestling" };
    "Herbalist":        return { "magic resistance", "alchemy", "cooking", "taste identification", "wrestling" };
    "Tailor":           return { "tailoring", "fencing" };
    "Weaver":           return { "tailoring", "fencing" };
    "Leatherworker":    return { "parrying", "mace fighting" };
    "Provisioner":      return { "tactics", "parrying", "fencing" };
    "Carpenter":        return { "carpentry", "lumberjacking", "swordsmanship" };
    "Bowyer":           return { "archery", "bowcraft", "fencing" };
    "Architect":        return { "magic resistance", "wrestling" };
    "Scribe":           return { "magic resistance", "evaluating intelligence", "wrestling" };
    "Mapmaker":         return { "cartography", "wrestling" };
    "Vetrinarian":      return { "animal lore", "wrestling", "veterinary" };
    "TownGuard":        return { "anatomy", "tactics", "swordsmanship", "detect hidden", "arms lore" };
    "Thief":            return { "snooping", "stealing", "remove trap", "stealth", "fencing", "poisoning", "lockpicking", "hiding" };
    "Beggar":           return { "begging", "wrestling", "cooking", "fishing" };
    "Fighter1":         return { "anatomy", "tactics", "swordsmanship", "arms lore" };
    "Fighter2":         return { "anatomy", "tactics", "swordsmanship", "arms lore" };
    "Fighter3":         return { "anatomy", "tactics", "swordsmanship", "arms lore" };
    "Fighter4":         return { "anatomy", "tactics", "swordsmanship", "arms lore" };
    "Paladin":          return { "anatomy", "tactics", "swordsmanship", "detect hidden", "arms lore" };
    "Artist":
  endcase
endfunction

function FindSkillId(name)
  case(name)
    "alchemy":                  return  0;
    "anatomy":                  return  1;
    "animal lore":              return  2;
    "item identification":      return  3;
    "arms lore":                return  4;
    "parrying":                 return  5;
    "begging":                  return  6;
    "blacksmithy":              return  7;
    "bowcraft":                 return  8;
    "peacemaking":              return  9;
    "camping":                  return 10;
    "carpentry":                return 11;
    "cartography":              return 12;
    "cooking":                  return 13;
    "detect hidden":            return 14;
    "enticement":               return 15;
    "evaluating intelligence":  return 16;
    "healing":                  return 17;
    "fishing":                  return 18;
    "forensic evaluation":      return 19;
    "herding":                  return 20;
    "hiding":                   return 21;
    "provocation":              return 22;
    "inscription":              return 23;
    "lockpicking":              return 24;
    "magery":                   return 25;
    "magic resistance":         return 26;
    "tactics":                  return 27;
    "snooping":                 return 28;
    "musicianship":             return 29;
    "poisoning":                return 30;
    "archery":                  return 31;
    "spiritspeaking":           return 32;
    "stealing":                 return 33;
    "tailoring":                return 34;
    "animal taming":            return 35;
    "taste identification":     return 36;
    "tinkering":                return 37;
    "tracking":                 return 38;
    "veterinary":               return 39;
    "swordsmanship":            return 40;
    "mace fighting":            return 41;
    "fencing":                  return 42;
    "wrestling":                return 43;
    "lumberjacking":            return 44;
    "mining":                   return 45;
    "meditation":               return 46;
    "stealth":                  return 47;
    "remove trap":              return 48;
  endcase
endfunction
 
using System.Text.Json.Serialization;

namespace AAImport
{
    public class AA_Ability
    {
        public uint id { get; set; } = 0;
        public string name { get; set; } = "";
        [JsonIgnore]
        public int category { get; set; } = -1; // we don't use this in titanium
        public int classes { get; set; } = 65535;
        public int races { get; set; } = 0xFFFF;
        [JsonIgnore]
        public int drakkin_heritage { get; set; } = 127; // we don't use this in titanium
        public int deities { get; set; } = 0x1FFFF;
        [JsonIgnore]
        public int status { get; set; } = 0; // not used anywhere
        public int type { get; set; } = 1;
        [JsonIgnore]
        public int charges { get; set; } = 0; // we don't use this in titanium
        public byte grant_only { get; set; } = 0;
        [JsonIgnore]
        public int first_rank_id { get; set; } = -1;
        public byte enabled { get; set; } = 1;
        public byte reset_on_death { get; set; } = 0;
        [JsonIgnore]
        public byte auto_grant_enabled { get; set; } = 1; // we don't use this in titanium

        public List<AA_Ranks> Ranks { get; set; } = new List<AA_Ranks>();
    }
}

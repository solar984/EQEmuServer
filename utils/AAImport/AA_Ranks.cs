using System.Text.Json.Serialization;

namespace AAImport
{
    public class AA_Ranks
    {
        public uint id { get; set; }
        public int upper_hotkey_sid { get; set; } = -1;
        public int lower_hotkey_sid { get; set; } = -1;
        public int title_sid { get; set; } = 0;
        public int desc_sid { get; set; } = 0;
        public int cost { get; set; }
        public int level_req { get; set; }
        public int spell { get; set; } = -1;
        public int spell_type { get; set; } = 0;
        public int recast_time { get; set; } = 0;
        public int expansion { get; set; }
        [JsonIgnore]
        public int prev_id { get; set; } = -1;
        [JsonIgnore]
        public int next_id { get; set; } = -1;

        public List<AA_Rank_Effects> Effects { get; set; } = new List<AA_Rank_Effects>();
        public List<AA_Rank_Prereqs> Prereqs { get; set; } = new List<AA_Rank_Prereqs>();
    }
}

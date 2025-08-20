using System.Text.Json.Serialization;

namespace AAImport
{
    public class AA_Rank_Prereqs
    {
        [JsonIgnore]
        public uint rank_id { get; set; }
        public int aa_id { get; set; }
        public int points { get; set; }
    }
}

using System.Text.Json.Serialization;

namespace AAImport
{
    public class AA_Rank_Effects
    {
        [JsonIgnore]
        public uint rank_id { get; set; }
        public uint slot { get; set; }
        public int effect_id { get; set; }
        public int base1 { get; set; }
        public int base2 { get; set; }
    }
}

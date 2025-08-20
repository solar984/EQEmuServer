using MySql.Data.MySqlClient;

namespace AAImport
{
    public class DatabaseData
    {
        public List<AA_Ability> AA_Abilities { get; set; } = new();
        public List<AA_Ranks> AA_Ranks { get; set; } = new();
        public List<AA_Rank_Effects> AA_Rank_Effects { get; set; } = new();
        public List<AA_Rank_Prereqs> AA_Rank_Prereqs { get; set; } = new();

        public void Organize()
        {
            var data = this;
            foreach (var rank in data.AA_Ranks)
            {
                rank.Effects.AddRange(data.AA_Rank_Effects.FindAll(r => r.rank_id == rank.id));
                rank.Prereqs.AddRange(data.AA_Rank_Prereqs.FindAll(p => p.rank_id == rank.id));
            }
            foreach (var ability in data.AA_Abilities)
            {
                var rank = GetRank(ability.first_rank_id);
                while (rank != null)
                {
                    ability.Ranks.Add(rank);
                    rank = GetRank(rank.next_id);
                }
            }
        }

        AA_Ranks? GetRank(int id)
        {
            return AA_Ranks.Find(a => a.id == id);
        }

        public static async Task<List<T>> QueryAsync<T>(MySqlConnection conn, string query)
        {
            var cmd = new MySqlCommand(query, conn);
            var reader = await cmd.ExecuteReaderAsync();
            var list = new List<T>();
            var props = typeof(T).GetProperties();

            while (await reader.ReadAsync())
            {
                var item = Activator.CreateInstance<T>();
                foreach (var prop in props)
                {
                    if (prop.PropertyType.Name.Contains("List")) continue;
                    var val = reader[prop.Name];
                    if (val != DBNull.Value)
                        prop.SetValue(item, Convert.ChangeType(val, prop.PropertyType));
                }
                list.Add(item);
            }
            await reader.CloseAsync();
            return list;
        }

        public static async Task InsertAsync<T>(MySqlConnection conn, List<T> items, string query)
        {
            foreach (var item in items)
            {
                var cmd = new MySqlCommand(query, conn);
                foreach (var prop in typeof(T).GetProperties())
                {
                    if (prop.PropertyType.Name.Contains("List")) continue;
                    cmd.Parameters.AddWithValue("@" + prop.Name, prop.GetValue(item));
                }
                await cmd.ExecuteNonQueryAsync();
            }
        }

        public static async Task TruncateTables(MySqlConnection conn)
        {
            var tables = new[] { "aa_rank_prereqs", "aa_rank_effects", "aa_ranks", "aa_ability" };
            foreach (var table in tables)
            {
                var cmd = new MySqlCommand($"TRUNCATE TABLE {table};", conn);
                await cmd.ExecuteNonQueryAsync();
            }
        }

        public static async Task Insert_AA_Ability(MySqlConnection conn, List<AA_Ability> aa)
        {
            await InsertAsync(conn, aa, @"
        INSERT INTO aa_ability 
        (id, name, category, classes, races, drakkin_heritage, deities, status, type, charges, grant_only, first_rank_id, enabled, reset_on_death, auto_grant_enabled) 
        VALUES (@id, @name, @category, @classes, @races, @drakkin_heritage, @deities, @status, @type, @charges, @grant_only, @first_rank_id, @enabled, @reset_on_death, @auto_grant_enabled)");
        }

        public static async Task Insert_AA_Ranks(MySqlConnection conn, List<AA_Ranks> aa)
        {
            await InsertAsync(conn, aa, @"
        INSERT INTO aa_ranks 
        (id, upper_hotkey_sid, lower_hotkey_sid, title_sid, desc_sid, cost, level_req, spell, spell_type, recast_time, expansion, prev_id, next_id) 
        VALUES (@id, @upper_hotkey_sid, @lower_hotkey_sid, @title_sid, @desc_sid, @cost, @level_req, @spell, @spell_type, @recast_time, @expansion, @prev_id, @next_id)");
        }

        public static async Task Insert_AA_Rank_Effects(MySqlConnection conn, List<AA_Rank_Effects> aa)
        {
            await InsertAsync(conn, aa, @"
        INSERT INTO aa_rank_effects 
        (rank_id, slot, effect_id, base1, base2) 
        VALUES (@rank_id, @slot, @effect_id, @base1, @base2)");
        }

        public static async Task Insert_AA_Rank_Prereqs(MySqlConnection conn, List<AA_Rank_Prereqs> aa)
        {
            await InsertAsync(conn, aa, @"
        INSERT INTO aa_rank_prereqs 
        (rank_id, aa_id, points) 
        VALUES (@rank_id, @aa_id, @points)");
        }
    }
}

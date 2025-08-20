using MySql.Data.MySqlClient;
using System.Text;
using System.Text.Json;

/*
 * 
 * Warning: running this program will overwrite the contents of the following tables: "aa_rank_prereqs", "aa_rank_effects", "aa_ranks", "aa_ability"
 * 
 * AA ablities are defined in titanium-abilities.json
 * Set the ConnectionString and run the program to replace the data in the database with data from the json file.
 * You can also export the database to an importable json file, see ExportToJson below.
 * 
 */

namespace AAImport
{
    class Program
    {
        const string ConnectionString = "server=127.0.0.1;uid=eqemu;pwd=eqemu;database=peq;";

        static async Task Main()
        {
            //await ExportToJson("data-export.json");
            await ImportFromJson("titanium-abilities.json");
        }

        static async Task ImportFromJson(string JsonFilePath)
        {
            var json = await File.ReadAllTextAsync(JsonFilePath, Encoding.UTF8);
            var abilties = JsonSerializer.Deserialize<List<AA_Ability>>(json) ?? new List<AA_Ability>();

            var ranks = new List<AA_Ranks>();
            var effects = new List<AA_Rank_Effects>();
            var prereqs = new List<AA_Rank_Prereqs>();

            foreach (var ability in abilties)
            {
                AA_Ranks? prevRank = null;
                foreach (var rank in ability.Ranks)
                {
                    // The AA id in the first rank is the main base ability id and the string database title and description generally use the same ID so it can be defaulted.
                    if (rank.title_sid == 0) rank.title_sid = (int)rank.id;
                    if (rank.desc_sid == 0) rank.desc_sid = (int)rank.id;
                    rank.next_id = -1;

                    if (prevRank == null)
                    {
                        ability.id = rank.id;
                        ability.first_rank_id = (int)rank.id;
                        rank.prev_id = -1;
                    }
                    else
                    {
                        rank.prev_id = (int)prevRank.id;
                        prevRank.next_id = (int)rank.id;
                    }

                    foreach (var effect in rank.Effects)
                    {
                        effect.rank_id = rank.id;
                        effects.Add(effect);
                    }

                    foreach (var prereq in rank.Prereqs)
                    {
                        prereq.rank_id = rank.id;
                        prereqs.Add(prereq);
                    }

                    ranks.Add(rank);
                    prevRank = rank;
                }
            }

            abilties = abilties.OrderBy(o => o.id).ToList();
            ranks = ranks.OrderBy(o => o.id).ToList();
            effects = effects.OrderBy(o => o.rank_id).ThenBy(o => o.slot).ToList();
            prereqs = prereqs.OrderBy(o => o.rank_id).ToList();

            using var conn = new MySqlConnection(ConnectionString);
            Console.WriteLine("Connecting to database.");
            await conn.OpenAsync();
            Console.WriteLine("Truncating tables.");
            await DatabaseData.TruncateTables(conn);
            Console.WriteLine("Inserting {0} aa_ability records.", abilties.Count());
            await DatabaseData.Insert_AA_Ability(conn, abilties);
            Console.WriteLine("Inserting {0} aa_ranks records.", ranks.Count());
            await DatabaseData.Insert_AA_Ranks(conn, ranks);
            Console.WriteLine("Inserting {0} aa_rank_effects records.", effects.Count());
            await DatabaseData.Insert_AA_Rank_Effects(conn, effects);
            Console.WriteLine("Inserting {0} aa_rank_prereqs records.", prereqs.Count());
            await DatabaseData.Insert_AA_Rank_Prereqs(conn, prereqs);

            Console.WriteLine("Import complete.");
        }

        static async Task ExportToJson(string JsonFilePath)
        {
            using var conn = new MySqlConnection(ConnectionString);
            await conn.OpenAsync();

            var data = new DatabaseData();

            data.AA_Abilities = await DatabaseData.QueryAsync<AA_Ability>(conn, "SELECT * FROM aa_ability");
            data.AA_Ranks = await DatabaseData.QueryAsync<AA_Ranks>(conn, "SELECT * FROM aa_ranks");
            data.AA_Rank_Effects = await DatabaseData.QueryAsync<AA_Rank_Effects>(conn, "SELECT * FROM aa_rank_effects");
            data.AA_Rank_Prereqs = await DatabaseData.QueryAsync<AA_Rank_Prereqs>(conn, "SELECT * FROM aa_rank_prereqs");
            data.Organize();

            var json = JsonSerializer.Serialize(data.AA_Abilities, new JsonSerializerOptions { WriteIndented = true, TypeInfoResolver = new CustomValueOmissionResolver() });
            Console.WriteLine(json);
            await File.WriteAllTextAsync(JsonFilePath, json, Encoding.UTF8);
            Console.WriteLine("Export complete.");
        }
    }
}

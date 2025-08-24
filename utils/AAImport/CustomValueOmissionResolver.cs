using System.Text.Json;
using System.Text.Json.Serialization.Metadata;

namespace AAImport
{
    public class CustomValueOmissionResolver : IJsonTypeInfoResolver
    {
        private readonly DefaultJsonTypeInfoResolver _defaultResolver = new();

        public JsonTypeInfo? GetTypeInfo(Type type, JsonSerializerOptions options)
        {
            JsonTypeInfo? typeInfo = _defaultResolver.GetTypeInfo(type, options);
            int exampleAAId = 10000;
            if (typeInfo == null)
                return null;

            // this omits some properties with default values when generating the json export
            typeInfo.Properties.ToList().ForEach(propertyInfo =>
            {
                if (type.Name == "AA_Ability")
                {
                    if (propertyInfo.Name == "id")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((uint)value) != 0 && ((uint)value) != ((AA_Ability)instance).Ranks[0].id);
                        };
                    }
                    if (propertyInfo.Name == "deities")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((int)value) != 0x1FFFF);
                        };
                    }
                    if (propertyInfo.Name == "classes")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((int)value) != 0xFFFF);
                        };
                    }
                    if (propertyInfo.Name == "races")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((int)value) != 0xFFFF);
                        };
                    }
                    if (propertyInfo.Name == "grant_only")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((byte)value) != 0);
                        };
                    }
                    if (propertyInfo.Name == "enabled")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((byte)value) != 1);
                        };
                    }
                    if (propertyInfo.Name == "reset_on_death")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ability)instance).id == exampleAAId || (value != null && ((byte)value) != 0);
                        };
                    }
                }

                if (type.Name == "AA_Ranks")
                {
                    if (propertyInfo.Name == "upper_hotkey_sid")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != -1);
                        };
                    }
                    if (propertyInfo.Name == "lower_hotkey_sid")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != -1);
                        };
                    }
                    if (propertyInfo.Name == "title_sid")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != ((AA_Ranks)instance).ability!.Ranks[0].id);
                        };
                    }
                    if (propertyInfo.Name == "desc_sid")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != ((AA_Ranks)instance).ability!.Ranks[0].id);
                        };
                    }
                    if (propertyInfo.Name == "spell")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != -1);
                        };
                    }
                    if (propertyInfo.Name == "spell_type")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != 0);
                        };
                    }
                    if (propertyInfo.Name == "recast_time")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((int)value) != 0);
                        };
                    }
                    if (propertyInfo.Name == "Effects")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((List<AA_Rank_Effects>)value).Count > 0);
                        };
                    }
                    if (propertyInfo.Name == "Prereqs")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Ranks)instance).id == exampleAAId || (value != null && ((List<AA_Rank_Prereqs>)value).Count > 0);
                        };
                    }
                }
                if (type.Name == "AA_Rank_Effects")
                {
                    if (propertyInfo.Name == "slot") // rely on the ordering in the json to number effect slots
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Rank_Effects)instance).rank_id == exampleAAId;
                        };
                    }
                    if (propertyInfo.Name == "base1")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Rank_Effects)instance).rank_id == exampleAAId || (value != null && ((int)value) != 0);
                        };
                    }
                    if (propertyInfo.Name == "base2")
                    {
                        propertyInfo.ShouldSerialize = (instance, value) =>
                        {
                            return ((AA_Rank_Effects)instance).rank_id == exampleAAId || (value != null && ((int)value) != 0);
                        };
                    }
                }
            });

            return typeInfo;
        }
    }
}

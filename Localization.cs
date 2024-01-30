using Amazon.Runtime.Internal.Transform;

namespace ZieOnsServer
{
    public static class Localization
    {
        private static Dictionary<string, string> English = new Dictionary<string, string>()
        {
            { "home", "Home" },
            { "back", "Go back" },
            { "create", "Create" },
            { "manage", "Manage" },
            { "posters.create", "Create new poster" },
            { "posters.name", "Poster name" },
            { "posters.image", "Poster image" },
            { "posters.delete", "Delete poster" },
            { "posters.none", "No posters found." },
            { "switch_lang", "Switch language" },
            { "snapshots", "Snapshot" }
        };
        private static Dictionary<string, string> Dutch = new Dictionary<string, string>()
        {
            { "home", "Startpagina" },
            { "back", "Ga terug" },
            { "create", "Maak aan" },
            { "manage", "Beheer" },
            { "posters.create", "Maak nieuwe poster" },
            { "posters.name", "Poster naam" },
            { "posters.image", "Poster afbeelding" },
            { "posters.delete", "Verwijder poster" },
            { "posters.none", "Geen posters gevonden." },
            { "switch_lang", "Verander taal" },
            { "snapshots", "Snapshot" }
        };

        public static string GetText(HttpContext context, string key)
        {
            switch (context.Session.GetString("lang"))
            {
                case "en":
                    return English[key];
                case "nl":
                    return Dutch[key];
                default:
                    return Dutch[key];
            }
        }
    }
}

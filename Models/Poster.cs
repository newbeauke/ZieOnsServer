using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace ZieOnsServer.Models
{
    public class Poster
    {
        [BsonId]
        public string Id { get; set; }
        public string Name { get; set; }
        public string Image { get; set; }
        public List<string> Snapshots { get; set; } = new List<string>();

        public Poster(string name, string image)
        {
            Id = Guid.NewGuid().ToString();
            Name = name;
            Image = image;
        }
    }
}

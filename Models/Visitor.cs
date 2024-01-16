using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace ZieOnsServer.Models
{
    public class Visitor
    {
        [BsonId]
        public string Id { get; set; }

        public Visitor()
        {
            Id = Guid.NewGuid().ToString();
        }
    }
}

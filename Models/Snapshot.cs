using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace ZieOnsServer.Models
{
    public class Snapshot
    {
        [BsonId]
        public string Id { get; set; }
        public DateTime DateTime { get; set; }
        public byte[] Image { get; set; }
        public List<string> Visitors { get; set; }

        public Snapshot(byte[] image, List<string> visitors)
        {
            Id = Guid.NewGuid().ToString();
            DateTime = DateTime.Now;
            Image = image;
            Visitors = visitors;
        }
    }
}

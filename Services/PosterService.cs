using ZieOnsServer.Models;
using MongoDB.Driver;

namespace ZieOnsServer.Services
{
    public static class PosterService
    {
        private static IMongoCollection<Poster> posters;

        static PosterService()
        {
            var client = new MongoClient("mongodb://127.0.0.1:27017/?directConnection=true&serverSelectionTimeoutMS=2000&appName=mongosh+1.10.6");
            var db = client.GetDatabase("ZieOns");
            posters = db.GetCollection<Poster>("Posters");
        }

        public async static Task<List<Poster>> GetAsync()
        {
            return await (await posters.FindAsync(u => true)).ToListAsync();
        }

        public async static Task<Poster> GetAsync(string id)
        {
            return await (await posters.FindAsync(u => u.Id == id)).FirstOrDefaultAsync();
        }

        public async static Task CreateAsync(Poster poster)
        {
            await posters.InsertOneAsync(poster);
        }

        public async static Task UpdateAsync(string id, Poster poster)
        {
            await posters.ReplaceOneAsync(u => u.Id == id, poster);
        }

        public async static Task DeleteAsync(string id)
        {
            await posters.DeleteOneAsync(u => u.Id == id);
        }
    }
}
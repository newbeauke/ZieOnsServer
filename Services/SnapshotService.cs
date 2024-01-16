using ZieOnsServer.Models;
using MongoDB.Driver;

namespace ZieOnsServer.Services
{
    public static class SnapshotService
    {
        private static IMongoCollection<Snapshot> snapshots;

        static SnapshotService()
        {
            var client = new MongoClient("mongodb://127.0.0.1:27017/?directConnection=true&serverSelectionTimeoutMS=2000&appName=mongosh+1.10.6");
            var db = client.GetDatabase("ZieOns");
            snapshots = db.GetCollection<Snapshot>("Snapshots");
        }

        public async static Task<List<Snapshot>> GetAsync()
        {
            return await (await snapshots.FindAsync(u => true)).ToListAsync();
        }

        public async static Task<Snapshot> GetAsync(string id)
        {
            return await (await snapshots.FindAsync(u => u.Id == id)).FirstOrDefaultAsync();
        }

        public async static Task CreateAsync(Snapshot snapshot)
        {
            await snapshots.InsertOneAsync(snapshot);
        }

        public async static Task UpdateAsync(string id, Snapshot snapshot)
        {
            await snapshots.ReplaceOneAsync(u => u.Id == id, snapshot);
        }

        public async static Task DeleteAsync(string id)
        {
            await snapshots.DeleteOneAsync(u => u.Id == id);
        }
    }
}
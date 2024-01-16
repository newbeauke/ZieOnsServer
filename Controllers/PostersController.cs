using Microsoft.AspNetCore.Mvc;
using ZieOnsServer.Models;
using ZieOnsServer.Services;

namespace ZieOnsServer.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostersController : ControllerBase
    {
        #region Front end

        [HttpPost]
        public async Task<ActionResult> Create(string name)
        {
            Poster poster = new Poster(name, new byte[0]);
            await PosterService.CreateAsync(poster);
            return Ok(poster.Id);
        }

        [HttpGet]
        public async Task<ActionResult> GetAll()
        {
            List<Poster> posters = await PosterService.GetAsync();
            return Ok(posters);
        }

        [HttpGet]
        public async Task<ActionResult> Get(string id)
        {
            Poster poster = await PosterService.GetAsync(id);
            if (poster == null)
            {
                return NotFound("Poster not found");
            }
            return Ok(poster);
        }
        #endregion

        #region IoT

        [HttpPost]
        public async Task<ActionResult> Snap(string id, byte[] image)
        {
            Poster poster = await PosterService.GetAsync(id);
            if (poster == null)
            {
                return NotFound("Poster not found");
            }

            // Run facial recognition
            List<Visitor> visitors = new List<Visitor>();

            Snapshot snapshot = new Snapshot(image, visitors.Select(v => v.Id).ToList());
            await SnapshotService.CreateAsync(snapshot);
            poster.Snapshots.Add(snapshot.Id);
            await PosterService.UpdateAsync(poster.Id, poster);
            return Ok();
        }

        #endregion
    }
}

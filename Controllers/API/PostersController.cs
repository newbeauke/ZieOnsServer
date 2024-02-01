using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ZieOnsServer.Models;
using ZieOnsServer.Services;

namespace ZieOnsServer.Controllers.API
{
    [ApiController]
    [Route("api/[controller]")]
    public class PostersController : ControllerBase
    {
        [HttpGet("GetAll")]
        public async Task<ActionResult> GetAll()
        {
            List<Poster> posters = await PosterService.GetAsync();
            return Ok(posters);
        }

        [HttpGet("GetAllNested")]
        public async Task<ActionResult> GetAllNested()
        {
            List<object> postersResults = new List<object>();
            foreach (Poster poster in await PosterService.GetAsync())
            {
                List<object> snapshotsResults = new List<object>();
                foreach (Snapshot snapshot in (await SnapshotService.GetAsync()).Where(s => poster.Snapshots.Contains(s.Id)))
                {
                    snapshotsResults.Add(new { id = snapshot.Id, dateTime = snapshot.DateTime, image = snapshot.Image });
                }
                postersResults.Add(new { id = poster.Id, name = poster.Name, image = poster.Image, snapshots = snapshotsResults });
            }
            return Ok(postersResults);
        }

        [HttpGet("Get")]
        public async Task<ActionResult> Get(string id)
        {
            Poster poster = await PosterService.GetAsync(id);
            if (poster == null)
            {
                return NotFound("Poster not found");
            }
            return Ok(poster);
        }

        [HttpPost("Snap")]
        public async Task<ActionResult> Snap()
        {
            string id = Request.Form["id"];
            string image = Request.Form["image"];

            Poster poster = await PosterService.GetAsync(id);
            if (poster == null)
            {
                if (int.TryParse(id, out int index))
                {
                    poster = (await PosterService.GetAsync())[index];
                    if (poster == null)
                    {
                        return NotFound("Poster not found");
                    }
                }
                else
                {
                    return NotFound("Poster not found");
                }
            }

            // Fix plusjes
            image = image.Replace(' ', '+');

            // Run facial recognition
            List<Visitor> visitors = new List<Visitor>();

            Snapshot snapshot = new Snapshot(image, visitors.Select(v => v.Id).ToList());
            await SnapshotService.CreateAsync(snapshot);
            poster.Snapshots.Add(snapshot.Id);
            await PosterService.UpdateAsync(poster.Id, poster);
            return Ok();
        }
    }
}

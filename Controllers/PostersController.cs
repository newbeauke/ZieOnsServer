using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using ZieOnsServer.Models;
using ZieOnsServer.Services;

namespace ZieOnsServer.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class PostersController : ControllerBase
    {
        [HttpGet("Test")]
        public ActionResult Test()
        {
            return Ok("Hello back to you!");
        }

        #region Front end

        [HttpPost("Create")]
        public async Task<ActionResult> Create()
        {
            string name = Request.Form["name"];
            Poster poster = new Poster(name, new byte[0]);
            await PosterService.CreateAsync(poster);
            return Ok(poster.Id);
        }

        [HttpGet("GetAll")]
        public async Task<ActionResult> GetAll()
        {
            List<Poster> posters = await PosterService.GetAsync();
            return Ok(posters);
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
        #endregion

        #region IoT

        [HttpPost("Snap")]
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

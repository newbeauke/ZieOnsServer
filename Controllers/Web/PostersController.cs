using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Dynamic;
using System.IO;
using ZieOnsServer.Models;
using ZieOnsServer.Services;

namespace ZieOnsServer.Controllers.Web
{
    public class PostersController : Controller
    {
        public async Task<ActionResult> Index()
        {
            dynamic model = new ExpandoObject();
            model.Context = HttpContext;
            model.Posters = await PosterService.GetAsync();

            return View(model);
        }

        public ActionResult Create()
        {
            dynamic model = new ExpandoObject();
            model.Context = HttpContext;

            return View(model);
        }

        public async Task<ActionResult> Create_Button(string name, IFormFile image)
        {
            if (image == null || image.Length == 0)
            {
                return RedirectToAction("Create");
            }
            using (MemoryStream stream = new MemoryStream())
            {
                await image.CopyToAsync(stream);
                byte[] imageData = stream.ToArray();
                Poster poster = new Poster(name, Convert.ToBase64String(imageData));
                await PosterService.CreateAsync(poster);
            }
            return RedirectToAction("Index");
        }

        public async Task<ActionResult> Delete_Button(string id)
        {
            await PosterService.DeleteAsync(id);
            return RedirectToAction("Index");
        }
    }
}

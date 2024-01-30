using Microsoft.AspNetCore.Mvc;
using System.Dynamic;

namespace ZieOnsServer.Controllers.Web
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            dynamic model = new ExpandoObject();
            model.Context = HttpContext;

            return View(model);
        }

        public ActionResult SwitchLang_Button()
        {
            if (HttpContext.Session.GetString("lang") == "en")
            {
                HttpContext.Session.SetString("lang", "nl");
            }
            else
            {
                HttpContext.Session.SetString("lang", "en");
            }
            return RedirectToAction("Index");
        }
    }
}
